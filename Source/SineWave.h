#pragma once

#include <juce_audio_basics/juce_audio_basics.h>
#include <numbers>

class SineWave
{
public:
  void prepare (const double sampleRate, const int numChannels);
  void process (juce::AudioBuffer<float>& buffer);
  [[nodiscard]] float getAmplitude() { return smoothedAmp_.getCurrentValue(); }
  [[nodiscard]] float getFrequency() { return smoothedFreq_.getCurrentValue(); }
  void setAmplitude(const float amplitude) { smoothedAmp_.setTargetValue(amplitude); }
  void setFrequency(const float frequency) { smoothedFreq_.setTargetValue(frequency); }
  void setPower(const bool powerOn) {smoothedPower_.setTargetValue(powerOn ? 1.0f : 0.0f); }

private:
  std::vector<float> phases_;
  float sampleRate_ = 0.0f;
  static constexpr float doublePi = 2.0f * std::numbers::pi_v<float>;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Multiplicative> smoothedFreq_;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothedAmp_;
  juce::SmoothedValue<float, juce::ValueSmoothingTypes::Linear> smoothedPower_;
};