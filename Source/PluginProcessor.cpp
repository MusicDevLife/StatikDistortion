/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
StatikDistortionAudioProcessor::StatikDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

StatikDistortionAudioProcessor::~StatikDistortionAudioProcessor()
{
}

//==============================================================================
const juce::String StatikDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StatikDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StatikDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool StatikDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double StatikDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StatikDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StatikDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StatikDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String StatikDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void StatikDistortionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void StatikDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
//        for (int channel = 0; channel < getTotalNumOutputChannels(); channel++) {
//            allBuffers.add(CircularBuffer(10, 1));
//        }
//        gain = 1.0f;
//        peak = 0.0f;
}

void StatikDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StatikDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StatikDistortionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    float drive = *apvts.getRawParameterValue("Drive");
    float range = *apvts.getRawParameterValue("Distortion");
    float blend = *apvts.getRawParameterValue("Mix");
    float volume = *apvts.getRawParameterValue("Volume");
 
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; i++) {
            buffer.clear (i, 0, buffer.getNumSamples());
    }
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        for (int sample = 0; sample < buffer.getNumSamples(); sample++) {

            float cleanSignal = *channelData;

            *channelData *= drive * range;

            *channelData = (((((2 / juce::float_Pi) * atan(*channelData) * blend) + (cleanSignal * (1.f - blend))) / 2.f) * volume);

            channelData++;
        }
    }
}

//==============================================================================
bool StatikDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* StatikDistortionAudioProcessor::createEditor()
{
    return new StatikDistortionAudioProcessorEditor (*this);
}

//==============================================================================
void StatikDistortionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    auto state = apvts.copyState();
            std::unique_ptr<juce::XmlElement> xml (state.createXml());
            copyXmlToBinary (*xml, destData);
}

void StatikDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
 
        if (xmlState.get() != nullptr)
            if (xmlState->hasTagName (apvts.state.getType()))
                apvts.replaceState (juce::ValueTree::fromXml (*xmlState));
}

ChainSettings getChainSettings (juce::AudioProcessorValueTreeState& apvts) {

    ChainSettings settings;
    settings.Drive = apvts.getRawParameterValue("Drive")->load();
    settings.Distortion = apvts.getRawParameterValue("Distortion")->load();
    settings.Mix = apvts.getRawParameterValue("Mix")->load();
    settings.Volume = apvts.getRawParameterValue("Volume")->load();

    return settings;
}


juce::AudioProcessorValueTreeState::ParameterLayout StatikDistortionAudioProcessor::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>("Drive", "Drive", juce::NormalisableRange<float>(0.00f, 1.0f, 0.01f),0.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>("Distortion", "Distortion", juce::NormalisableRange<float>(0.00f, 25.f, 0.01f), 0.0f));
    
    parameters.add(std::make_unique<juce::AudioParameterFloat>("Mix", "Mix", juce::NormalisableRange<float>(0.00f, 100.0f, 1.0), 0.0f));

    parameters.add(std::make_unique<juce::AudioParameterFloat>("Volume", "Volume", juce::NormalisableRange<float>(-5.0f, 5.0f, 0.01f), 0.0f));
    
    return parameters;

}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StatikDistortionAudioProcessor();
}
