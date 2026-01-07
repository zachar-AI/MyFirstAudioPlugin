#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <numbers>

class SineWave
{
public:
  void prepare (const double sampleRate, const int numChannels);
  void process (juce::AudioBuffer<float>& buffer);
  [[nodiscard]] float getAmplitude() const { return amplitude_; }
  [[nodiscard]] float getFrequency() { return smoothedFreq_.getNextValue(); }
  void setAmplitude(const float amplitude) { amplitude_ = amplitude; }
  void setFrequency(const float frequency) { smoothedFreq_.setTargetValue(frequency); }

private:
  std::vector<float> currentTime_;
  float amplitude_ = 0.5f;
  float sampleRate_ = 0.0f;
  float timeIncrement_ = 0.0f;
  static constexpr float doublePi = 2.0f * std::numbers::pi_v<float>;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq_;
};