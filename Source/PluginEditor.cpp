/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "CustomSlider.h"


//==============================================================================
StatikDistortionAudioProcessorEditor::StatikDistortionAudioProcessorEditor (StatikDistortionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{

    juce::LookAndFeel::setDefaultLookAndFeel(&myCustomLNF);
    Distortion();
    Compression();
    setSize (600, 400);
}
StatikDistortionAudioProcessorEditor::~StatikDistortionAudioProcessorEditor()
{
}
//==============================================================================


void StatikDistortionAudioProcessorEditor::Distortion() {
    addAndMakeVisible(driveKnob);
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.attachToComponent(&driveKnob, false);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Drive", driveKnob);


    addAndMakeVisible(rangeKnob);
    rangeLabel.setText ("Range", juce::dontSendNotification);
    rangeLabel.attachToComponent(&rangeKnob, false);
    rangeLabel.setJustificationType(juce::Justification::centred);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Distortion", rangeKnob);

    addAndMakeVisible(blendKnob);
    blendLabel.setText ("Mix", juce::dontSendNotification);
    blendLabel.attachToComponent(&blendKnob, false);
    blendLabel.setJustificationType(juce::Justification::centred);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Mix", blendKnob);
}

void StatikDistortionAudioProcessorEditor::Compression() {

    addAndMakeVisible(thresholdKnob);
    thresholdKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
    thresholdLabel.setText("Threshold", juce::dontSendNotification);
    thresholdLabel.attachToComponent(&thresholdKnob, false);
    thresholdLabel.setJustificationType(juce::Justification::centred);
    thresholdAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Threshold", thresholdKnob);
    thresholdKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, thresholdKnob.getTextBoxHeight());

    addAndMakeVisible(limitAttackKnob);
    limitAttackKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
    limitAttackLabel.setText("Attack", juce::dontSendNotification);
    limitAttackLabel.attachToComponent(&limitAttackKnob, false);
    limitAttackLabel.setJustificationType(juce::Justification::centred);
    limitAttackAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Attack", limitAttackKnob);
    limitAttackKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, limitAttackKnob.getTextBoxHeight());


    addAndMakeVisible(limitReleaseKnob);
    limitReleaseKnob.setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::white);
    limitReleaseLabel.setText("Release", juce::dontSendNotification);
    limitReleaseLabel.attachToComponent(&limitReleaseKnob, false);
    limitReleaseLabel.setJustificationType(juce::Justification::centred);
    limitReleaseAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Release", limitReleaseKnob);
    limitReleaseKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, limitReleaseKnob.getTextBoxHeight());
}

void StatikDistortionAudioProcessorEditor::paint (juce::Graphics& g) {
    
    juce::Image background = juce::ImageCache::getFromMemory (BinaryData::StatikDistortionImage_jpg, BinaryData::StatikDistortionImage_jpgSize);
    
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::fillDestination);

}

void StatikDistortionAudioProcessorEditor::resized()
{

    driveKnob.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 4) - (100 / 2 ), 100, 100);
    rangeKnob.setBounds(((getWidth() / 5) * 2.5) - (100 / 2), (getHeight() / 4) - (100 / 2 ), 100, 100);
    blendKnob.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 4)- (100 / 2), 100, 100);
    thresholdKnob.setBounds(((getWidth() / 5) * 1) - (100 / 2), (getHeight() / 2), 100, 100);
    limitAttackKnob.setBounds(((getWidth() / 5) * 2.5) - (100 / 2), (getHeight() / 2), 100, 100);
    limitReleaseKnob.setBounds(((getWidth() / 5) * 4) - (100 / 2), (getHeight() / 2), 100, 100);

}


