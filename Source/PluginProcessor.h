/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#ifndef PLUGINPROCESSOR_H_INCLUDED
#define PLUGINPROCESSOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleButton.h"
#include "Sampler.h"
#include "SamplerSoundLayer.h"


//==============================================================================
/**
*/
class TrommelwerkAudioProcessor  : public AudioProcessor
{
public:
	enum
	{
		maxMidiChannel = 16,
		maxNumberOfVoices = 5
	};
    //==============================================================================
    TrommelwerkAudioProcessor();
    ~TrommelwerkAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool setPreferredBusArrangement (bool isInputBus, int busIndex, const AudioChannelSet& preferred) override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
	void addClickedButton( SampleButton *sampleButton );
	void setFile( File s);
	void loadNewSample ( File f, SampleButton * b);
	void testFunction();


private:

	double startTime;
	static MidiBuffer filterMidiMessagesForChannel (const MidiBuffer& input, int channel);
	AudioFormatManager formatManager;
	OwnedArray<Sampler> synth;
	OwnedArray<SampleButton> m_clickedSampleButton;
	SynthesiserSound::Ptr sound;
	File sampleFile;
	Logger * log;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrommelwerkAudioProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
