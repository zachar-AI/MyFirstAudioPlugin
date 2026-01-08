#include "PluginProcessor.h"
#include "juce_events/juce_events.h"
#include "juce_graphics/juce_graphics.h"
#include "juce_gui_basics/juce_gui_basics.h"
#include "public.sdk/source/vst/moduleinfo/jsoncxx.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , processorRef (p)
    , freqSliderAttachment(processorRef.getState(), "freqHz", frequencySlider)
    , playButtonAttachment(processorRef.getState(), "play", playButton)
    , ampSliderAttachment(processorRef.getState(), "vol", amplitudeSlider)
{
    juce::ignoreUnused (processorRef);


    // freq slider setup
    frequencySlider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    frequencySlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    // frequencySlider.setRange(0.0f, 1.0f, 0.01f);
    addAndMakeVisible(frequencySlider);
    
    // set up freq label
    // frequencyLabel.setColour(juce::Label::ColourIds::outlineColourId, juce::Colours::wheat);
    frequencyLabel.setJustificationType(juce::Justification::centred);    
    addAndMakeVisible(frequencyLabel);

    // amp slider setup
    amplitudeSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    amplitudeSlider.setTextBoxStyle(juce::Slider::TextBoxAbove, true, 100, 50);
    addAndMakeVisible(amplitudeSlider);

    // play Button Setup
    playButton.setButtonText("Play");
    playButton.setToggleState(true, juce::NotificationType::dontSendNotification); 
    playButton.setClickingTogglesState(true);

    playButton.setColour(juce::TextButton::ColourIds::buttonOnColourId, juce::Colours::forestgreen);
    playButton.setColour(juce::TextButton::ColourIds::buttonColourId, juce::Colours::rebeccapurple);

    playButton.onClick = [this]()
    {
        // change state of the button when it is clicked
        const bool isPlaying = playButton.getToggleState();
        playButton.setButtonText(isPlaying ? "Playing": "Bypassed");
    };
    addAndMakeVisible(playButton);



    setSize (1000, 600);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::black);

    // g.setColour (juce::Colours::red);
    // g.setFont (30.0f);
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // square.setBounds(50, 250, 300, 100);
    // frequencyLabel.setBounds (getWidth() / 2 - 50, getHeight() / 2 - 120, 100, 20);
    frequencySlider.setBounds(600, 300, 100, 100);
    playButton.setBounds(450, 450, 100, 30);
    amplitudeSlider.setBounds(450, 200, 100, 200);
}
