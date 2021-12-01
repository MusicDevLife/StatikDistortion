/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomSlider.h"

//==============================================================================
/**
*/
class StatikDistortionAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    StatikDistortionAudioProcessorEditor (StatikDistortionAudioProcessor&);
    ~StatikDistortionAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void Distortion();
    void Compression();

private:
    
    CustomLNF myCustomLNF;

    CustomDial driveKnob;
    CustomDial rangeKnob;
    CustomDial blendKnob;
    CustomDial thresholdKnob;
    CustomDial limitAttackKnob;
    CustomDial limitReleaseKnob;

    juce::Label driveLabel;
    juce::Label rangeLabel;
    juce::Label blendLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> rangeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> blendAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> thresholdAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> limitAttackAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> limitReleaseAttachment;
    
  
    juce::Label thresholdLabel;
    juce::Label limitAttackLabel;
    juce::Label limitReleaseLabel;
    
    StatikDistortionAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatikDistortionAudioProcessorEditor)
};
