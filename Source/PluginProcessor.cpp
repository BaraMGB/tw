/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TrommelwerkAudioProcessor::TrommelwerkAudioProcessor() :
	startTime (Time::getMillisecondCounterHiRes() * 0.001)
{
	// The base class constructor will already add a main stereo output bus
	// If you want to add your own main channel then simply call clear the
	// output buses (busArrangement.outputBuses.clear()) and then add your own

	// Add additional output buses but disable these by default
	log = Logger::getCurrentLogger();
	for (int busNr = 1; busNr < maxMidiChannel; ++busNr)
		busArrangement.outputBuses.add (AudioProcessorBus (String ("Output #") += String (busNr + 1), AudioChannelSet::disabled()));

	// initialize other stuff (not related to buses)
	m_clickedSampleButton.clear( true );
	formatManager.registerBasicFormats();

	for (int midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
	{
		synth.add (new Sampler());


		for (int i = 0; i < maxNumberOfVoices; ++i)
		{
            synth[midiChannel]->setNoteStealingEnabled( false );
			synth[midiChannel]->addVoice (new SamplerVoice());
			synth[midiChannel]->clearSounds();
		}
	}
}

TrommelwerkAudioProcessor::~TrommelwerkAudioProcessor()
{
}

//==============================================================================
const String TrommelwerkAudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool TrommelwerkAudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool TrommelwerkAudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

double TrommelwerkAudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int TrommelwerkAudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
	// so this should be at least 1, even if you're not really implementing programs.
}

int TrommelwerkAudioProcessor::getCurrentProgram()
{
	return 0;
}

void TrommelwerkAudioProcessor::setCurrentProgram (int index)
{
}

const String TrommelwerkAudioProcessor::getProgramName (int index)
{
	return String();
}

void TrommelwerkAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void TrommelwerkAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	ignoreUnused (samplesPerBlock);

	for (int midiChannel = 0; midiChannel < maxMidiChannel; ++midiChannel)
		synth[midiChannel]->setCurrentPlaybackSampleRate (sampleRate);
}

void TrommelwerkAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}





bool TrommelwerkAudioProcessor::setPreferredBusArrangement (bool isInputBus, int busIndex, const AudioChannelSet& preferred)
{
	// Reject any bus arrangements that are not compatible with your plugin

	const int numChannels = preferred.size();
	const bool isMainBus = (busIndex == 0);
	// do not allow disabling the main output bus
	if (isMainBus && preferred.isDisabled()) return false;
	// only support mono or stereo (or disabling) buses
	if (numChannels > 2) return false;
	// pass the call on to the base class
	return AudioProcessor::setPreferredBusArrangement (isInputBus, busIndex, preferred);
}




void TrommelwerkAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiBuffer)
{
	if( !m_clickedSampleButton.isEmpty() )
	{
		for( int i = 0; i < m_clickedSampleButton.size(); i++)
		{
			if( m_clickedSampleButton.operator[](i)->getSampleFile().exists() )
			{
				MidiMessage message = MidiMessage::noteOn ( 1, m_clickedSampleButton.operator[](i)->getNoteNumber() , (uint8) 126 );
				message.setTimeStamp (Time::getMillisecondCounterHiRes() * 0.001 - startTime);
				midiBuffer.addEvent( message, midiBuffer.getLastEventTime() + 1 );

			}
		}
		m_clickedSampleButton.clear( false );
	}


	for (int busNr = 0; busNr < maxMidiChannel; ++busNr)
	{
		MidiBuffer midiChannelBuffer = filterMidiMessagesForChannel (midiBuffer, busNr + 1);
		AudioSampleBuffer audioBusBuffer = busArrangement.getBusBuffer (buffer, false, busNr);

		if (! busArrangement.outputBuses.getReference (busNr).channels.isDisabled())
			synth [busNr]->renderNextBlock (audioBusBuffer, midiChannelBuffer, 0, audioBusBuffer.getNumSamples());
	}
}

//==============================================================================
bool TrommelwerkAudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* TrommelwerkAudioProcessor::createEditor()
{
	return new TrommelwerkAudioProcessorEditor (*this);
}

//==============================================================================
void TrommelwerkAudioProcessor::getStateInformation (MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.
}

void TrommelwerkAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.
}



MidiBuffer TrommelwerkAudioProcessor::filterMidiMessagesForChannel (const MidiBuffer& input, int channel)
{
	MidiMessage msg;
	int samplePosition;
	MidiBuffer output;

	for (MidiBuffer::Iterator it (input); it.getNextEvent (msg, samplePosition);)
		if (msg.getChannel() == channel) output.addEvent (msg, samplePosition);

	return output;
}




void TrommelwerkAudioProcessor::setFile( File s)
{
	sampleFile = s;
}



void TrommelwerkAudioProcessor::testFunction()
{

}




void TrommelwerkAudioProcessor::loadNewSample ( File f, SampleButton * b)
{
	if( f.exists() )
	{
		ScopedPointer<AudioFormatReader> formatReader (formatManager.createReaderFor (f));

		BigInteger midiNotes;
		midiNotes.setRange (0, 126, false);
		midiNotes.setBit( b->getNoteNumber() );
		if( formatReader != nullptr )
		{
            Range<float> velocity = Range<float>( 0.0, 1.0 );
			SynthesiserSound::Ptr newSound = new SamplerSoundLayer ("Voice", *formatReader, midiNotes, 0x40, velocity, 0.0, 0.0, 10.0);

			sound = newSound;

			for (int channel = 0; channel < maxMidiChannel; ++channel)
            {
                //synth[channel]->removeSound( 0 );
				synth[channel]->addSound (sound);
				log->writeToLog( "Sound zugewiesen");
				log->writeToLog( String( synth[channel]->getNumSounds() ) );
            }
		}
	}
}




void TrommelwerkAudioProcessor::addClickedButton( SampleButton *sampleButton )
{
	m_clickedSampleButton.add( sampleButton );
}




//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new TrommelwerkAudioProcessor();
}
