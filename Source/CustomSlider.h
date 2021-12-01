/*
  ==============================================================================

    CustomSlider.h
    Created: 20 Nov 2021 6:15:25pm
    Author:  Josh's Macbook Air

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CustomLNF : public juce::LookAndFeel_V4
{
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle, juce::Slider &);

};

class CustomDial : public juce::Slider
{
public:
    CustomDial()
    {
        
        auto rotaryParam = getRotaryParameters();
        rotaryParam.startAngleRadians = juce::MathConstants<float>::pi * 1.5f;
        rotaryParam.endAngleRadians =juce::MathConstants<float>::pi * 3.0f;
        setRotaryParameters(rotaryParam);
        
        setSliderStyle(juce::Slider::SliderStyle::Rotary);
        setRange(0.0f, 100.0f);
        setValue(25.0f);
        setTextBoxStyle(juce::Slider::NoTextBox, true, 100, 25);
        
        setColour(juce::Slider::ColourIds::rotarySliderFillColourId, juce::Colours::whitesmoke);
        setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::white);
    }
    
    
    
};
