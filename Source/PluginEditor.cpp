#include "PluginProcessor.h"
#include "juce_core/juce_core.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "BinaryData.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
    , freqSliderAttachment(processorRef.getState(), "freqHz", frequencySlider)
    , playButtonAttachment(processorRef.getState(), "play", playButton)
    , ampSliderAttachment(processorRef.getState(), "amp", amplitudeSlider)
{
    juce::ignoreUnused (processorRef);

    // Load bkg img from binary data
    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::theremin_jpg, BinaryData::theremin_jpgSize);

    // freq slider setup
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 100, 50);
    frequencySlider.setTextValueSuffix(" Hz");
    frequencySlider.textFromValueFunction = [] (double value)
    {
        return juce::String(static_cast<int>(std::round(value)));
    };
    frequencySlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    frequencySlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    frequencySlider.setColour(juce::Slider::thumbColourId, juce::Colours::navajowhite);
    addAndMakeVisible(frequencySlider);
    
    // set up freq label
    // frequencyLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::wheat);
    frequencyLabel.setJustificationType(juce::Justification::centred);    
    addAndMakeVisible(frequencyLabel);
    
    // amp slider setup
    amplitudeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    amplitudeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 100, 50);
    amplitudeSlider.setColour(juce::Slider::textBoxBackgroundColourId, juce::Colours::transparentBlack);
    amplitudeSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    amplitudeSlider.setColour(juce::Slider::thumbColourId, juce::Colours::navajowhite);
    addAndMakeVisible(amplitudeSlider);

    // play Button Setup
    playButton.setButtonText("On");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification); 
    playButton.setClickingTogglesState(true);

    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::navajowhite);
    playButton.setColour(juce::TextButton::textColourOnId, juce::Colours::black);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::maroon);

    playButton.onClick = [this]()
    {
        // change state of the button when it is clicked
        const bool isPlaying = playButton.getToggleState();
        playButton.setButtonText(isPlaying ? "On": "Off");
    };
    addAndMakeVisible(playButton);



    frequencySlider.updateText();
    setSize (710, 947);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    if (backgroundImage.isValid())
    {
        g.drawImage(backgroundImage, getLocalBounds().toFloat(), juce::RectanglePlacement::stretchToFit);
    }
    else
    {
        g.fillAll (juce::Colours::black);
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // square.setBounds(50, 250, 300, 100);
    // frequencyLabel.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 120, 100, 20);
    frequencySlider.setBounds(getWidth() / 2 - 125, getHeight() / 2 - 100, 250, 100);
    amplitudeSlider.setBounds(getWidth() / 2 - 250, getHeight() / 2 - 150, 100, 200);
    playButton.setBounds(getWidth() / 2 - 50, getHeight() / 2 + 280, 100, 30);
}
