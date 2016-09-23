/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SampleButton.h"


//==============================================================================
/**
*/
class TrommelwerkAudioProcessorEditor  : public AudioProcessorEditor,
	public Button::Listener

	{
public:
	TrommelwerkAudioProcessorEditor (TrommelwerkAudioProcessor&);
	~TrommelwerkAudioProcessorEditor();

	//==============================================================================
	void paint (Graphics&) override;
	void resized() override;

private:
	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	TrommelwerkAudioProcessor& processor;
	OwnedArray<SampleButton> m_sampleButtonList;
	Logger * log;
	void buttonClicked( Button * button ) override;
	void mouseDown( const MouseEvent & event );

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TrommelwerkAudioProcessorEditor)
	};


#endif  // PLUGINEDITOR_H_INCLUDED
