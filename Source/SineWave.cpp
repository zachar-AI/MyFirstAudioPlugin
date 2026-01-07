#include "SineWave.h"
#include <cmath>

void SineWave::prepare(const double sampleRate, const int numChannels)
{
  sampleRate_ = static_cast<float>(sampleRate);
  timeIncrement_ = 1.0f / sampleRate_;
  currentTime_.resize(static_cast<size_t>(numChannels), 0.0f);
  smoothedFreq_.reset(sampleRate_, 1.0f);
  smoothedFreq_.setCurrentAndTargetValue(getFrequency());
}

void SineWave::process(juce::AudioBuffer<float> &buffer) {
  if (currentTime_.size() != static_cast<size_t>(buffer.getNumChannels()))
    return;

  for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
  {
    auto *output = buffer.getWritePointer(channel);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
      float frequency = smoothedFreq_.getNextValue();
      output[sample] = amplitude_ * std::sinf(doublePi * frequency * currentTime_[static_cast<size_t>(channel)]);
      currentTime_[static_cast<size_t>(channel)] += timeIncrement_;
    }
  }
}