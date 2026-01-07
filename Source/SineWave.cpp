#include "SineWave.h"
#include <cmath>

void SineWave::prepare (double sampleRate, int numChannels)
{
  sampleRate_ = static_cast<float>(sampleRate);
  timeIncrement_ = 1.0f / sampleRate_;
  currentTime_.resize(numChannels, 0.0f);
}

void SineWave::process (juce::AudioBuffer<float>& buffer)
{
  if (currentTime_.size() != buffer.getNumChannels())
    return;

  for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
  {
    auto* output = buffer.getWritePointer(channel);

    for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
    {
      output[sample] = amplitude_ * std::sinf(juce::MathConstants<float>::twoPi * frequency_ * currentTime_[channel]);
      currentTime_[channel] += timeIncrement_;
    }
  }
}