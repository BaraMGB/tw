#include "PluginProcessor.h"
#include "PluginEditor.h"

const int NumberOfButtons = 16;

TrommelwerkAudioProcessorEditor::TrommelwerkAudioProcessorEditor (TrommelwerkAudioProcessor& p)
	: AudioProcessorEditor (&p), processor (p)

{
	log = Logger::getCurrentLogger();
	for( int i = 0; i < NumberOfButtons; ++i )
	{
		SampleButton * button = new SampleButton( 60 + i );
		button->addMouseListener( this, true );
		m_sampleButtonList.add( button );
		addAndMakeVisible( button );
	}
	setSize (400, 300);
}




TrommelwerkAudioProcessorEditor::~TrommelwerkAudioProcessorEditor()
{
}




void TrommelwerkAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll (Colours::white);

	g.setColour (Colours::black);
	g.setFont (15.0f);
}




void TrommelwerkAudioProcessorEditor::resized()
{
    int i = 0;
	for( int colum = 0; colum < 4; ++colum )
	{
		for( int row = 0; row < 4 ; ++row )
		{
			int width = m_sampleButtonList[i]->getDefaultWidth();
			int height = m_sampleButtonList[i]->getDefaultHeight();
			m_sampleButtonList[i]->setBounds( 60 * row, 60 * colum , width, height );
		    i++;
		}
	}
}




void TrommelwerkAudioProcessorEditor::buttonClicked( Button * b )
{
}




void TrommelwerkAudioProcessorEditor::mouseDown( const MouseEvent & event)
{
	for( int i = 0; i < m_sampleButtonList.size(); ++i )
	{
		if( event.eventComponent == m_sampleButtonList[i] )
		{
			if( event.mods == ModifierKeys::leftButtonModifier )
			{
				processor.addClickedButton( m_sampleButtonList[i] );
			}
			if( event.mods == ModifierKeys::rightButtonModifier )
			{
				m_sampleButtonList[i]->loadFile();
				processor.loadNewSample( m_sampleButtonList[i]->getSampleFile() , m_sampleButtonList[i] );

			}
		}
	}
}
