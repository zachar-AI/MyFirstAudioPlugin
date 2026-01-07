#pragma once

#include <juce_audio_basics/juce_audio_basics.h>

class SineWave
{
public:
  void prepare (const double sampleRate, const int numChannels);
  void process (juce::AudioBuffer<float>& buffer);
  [[nodiscard]] float getAmplitude() const {return amplitude_;}
  [[nodiscard]] float getFrequency() const {return frequency_;}
  void setAmplitude(const float amplitude) {amplitude_ = amplitude;}
  void setFrequency(const float frequency) {frequency_ = frequency;}

private:
  float amplitude_ = 0.5f;
  float frequency_ = 50.0f;
  float sampleRate_ = 0.0f;
  float timeIncrement_ = 0.0f;
  std::vector<float> currentTime_;
};