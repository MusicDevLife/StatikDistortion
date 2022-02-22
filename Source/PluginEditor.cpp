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
    setSize (600, 400);
    
}
StatikDistortionAudioProcessorEditor::~StatikDistortionAudioProcessorEditor()
{
}
//==============================================================================


void StatikDistortionAudioProcessorEditor::Distortion() {
    addAndMakeVisible(driveKnob);
    driveKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, driveKnob.getTextBoxHeight());
//    driveKnob.setSkewFactorFromMidPoint (0.50f);
    driveLabel.setText ("Drive", juce::dontSendNotification);
    driveLabel.setJustificationType(juce::Justification::centred);
    driveLabel.attachToComponent(&driveKnob, false);
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Drive", driveKnob);


    addAndMakeVisible(rangeKnob);
    rangeKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, rangeKnob.getTextBoxHeight());
    rangeLabel.setText ("Range", juce::dontSendNotification);
    rangeLabel.attachToComponent(&rangeKnob, false);
    rangeLabel.setJustificationType(juce::Justification::centred);
    rangeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Distortion", rangeKnob);

    addAndMakeVisible(blendKnob);
    blendKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, blendKnob.getTextBoxHeight());
    blendLabel.setText ("Mix", juce::dontSendNotification);
    blendLabel.attachToComponent(&blendKnob, false);
    blendLabel.setJustificationType(juce::Justification::centred);
    blendAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Mix", blendKnob);
    
    addAndMakeVisible(volumeKnob);
    volumeKnob.setTextBoxStyle (juce::Slider::TextBoxBelow, false, 100, volumeKnob.getTextBoxHeight());
    volumeLabel.setText ("Volume", juce::dontSendNotification);
    volumeLabel.attachToComponent(&volumeKnob, false);
    volumeLabel.setJustificationType(juce::Justification::centred);
    volumeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Volume", volumeKnob);
}

void StatikDistortionAudioProcessorEditor::paint (juce::Graphics& g) {

    juce::Image background = juce::ImageCache::getFromMemory (BinaryData::StatikDistortionImage_jpg, BinaryData::StatikDistortionImage_jpgSize);
  
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::fillDestination);

    }

void StatikDistortionAudioProcessorEditor::resized()
{

    driveKnob.setBounds(((getWidth() / 5) * 2.5) - (100 / 4), (getHeight() / 4) - (100 / 2 ), 100, 100);
    volumeKnob.setBounds(((getWidth() / 5) * 2.5) - (100 / 4), (getHeight() / 2), 100, 100);
    rangeKnob.setBounds(((getWidth() / 5) * 3.75) - (100 / 4), (getHeight() / 4) - (100 / 2 ), 100, 100);
    blendKnob.setBounds(((getWidth() / 5) * 3.75) - (100 / 4), (getHeight() / 2), 100, 100);

}


