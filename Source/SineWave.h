#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SineWave
{
public:
  void prepare (double sampleRate, int numChannels);
  void process (juce::AudioBuffer<float>& buffer);

private:
  float amplitude_ = 0.5f;
  float frequency_ = 50.0f;
  float sampleRate_ = 0.0f;
  float timeIncrement_ = 0.0f;
  std::vector<float> currentTime_;
};