#include "SineWave.h"
#include <cmath>

void SineWave::prepare(const double sampleRate, const int numChannels)
{
  sampleRate_ = static_cast<float>(sampleRate);
  phases_.resize(static_cast<size_t>(numChannels), 0.0f);
  smoothedFreq_.reset(sampleRate_, 0.05f);
  smoothedFreq_.setCurrentAndTargetValue(getFrequency());
  smoothedAmp_.reset(sampleRate_, 0.05f);
  smoothedAmp_.setCurrentAndTargetValue(getAmplitude());
}

void SineWave::process(juce::AudioBuffer<float> &buffer) {
  if (phases_.size() != static_cast<size_t>(buffer.getNumChannels()))
    return;

  for (size_t channel = 0; channel < static_cast<size_t>(buffer.getNumChannels()); ++channel)
  {
    auto *output = buffer.getWritePointer(static_cast<int>(channel));

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
      float frequency = smoothedFreq_.getNextValue();
      float amplitude = smoothedAmp_.getNextValue();
      const float phaseInc = doublePi * frequency / sampleRate_;

      output[sample] = amplitude * std::sinf(phases_[channel]);
      phases_[channel] += phaseInc;

      if (phases_[channel] >= doublePi)
        phases_[channel] -= doublePi;
    }
  }
}