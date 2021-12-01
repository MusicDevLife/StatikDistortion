/*
  ==============================================================================

    CircularBuffer.h
    Created: 21 Nov 2021 8:55:50am
    Author:  Josh's Macbook Air

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class CircularBuffer {
public:
    CircularBuffer();
    CircularBuffer(int bufferSize, int delayLength);
    float getData();
    void setData(float data);
    void nextSample();
    
private:
    juce::AudioSampleBuffer buffer;
    int writeIndex;
    int readIndex;
    int delayLength;
};
