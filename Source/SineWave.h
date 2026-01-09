#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <numbers>

class SineWave
{
public:
  void prepare (const double sampleRate, const int numChannels);
  void process (juce::AudioBuffer<float>& buffer);
  [[nodiscard]] float getAmplitude() { return smoothedAmp_.getNextValue(); }
  [[nodiscard]] float getFrequency() { return smoothedFreq_.getNextValue(); }
  void setAmplitude(const float amplitude) { smoothedAmp_.setTargetValue(amplitude); }
  void setFrequency(const float frequency) { smoothedFreq_.setTargetValue(frequency); }

private:
  std::vector<float> phases_;
  float sampleRate_ = 0.0f;
  static constexpr float doublePi = 2.0f * std::numbers::pi_v<float>;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq_;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothedAmp_;
};