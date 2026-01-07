#include "Square.h"
#include "juce_graphics/juce_graphics.h"

void Square::paint (juce::Graphics& g)
{
  g.fillAll (juce::Colours::orange);

  g.setColour (juce::Colours::white);
  g.setFont (15.0f);
  g.drawFittedText ("I have successfully aquired a box", getLocalBounds(), juce::Justification::centred, 1);
}

void Square::resized()
{

}