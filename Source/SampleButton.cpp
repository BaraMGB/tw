/*
  ==============================================================================

    SampleButton.cpp
    Created: 18 Aug 2016 1:53:59pm
    Author:  sda1_k1404

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleButton.h"

//==============================================================================
SampleButton::SampleButton( int noteNumber)
        : m_defaultWidth ( 40 ),
          m_defaultHeight ( 40 ),
          m_noteNumber( noteNumber )
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SampleButton::~SampleButton()
{
}

void SampleButton::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll (Colours::white);   // clear the background

    g.setColour (Colours::grey);
    g.drawRect ( getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (Colours::lightblue);
    g.setFont (14.0f);
    g.drawText (MidiMessage::getMidiNoteName( m_noteNumber, true, true, 3 ), getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}



int SampleButton::getDefaultWidth()
{
    return m_defaultWidth;
}




int SampleButton::getDefaultHeight()
{
    return m_defaultHeight;
}


void SampleButton::loadFile()
{
    FileChooser chooser ("Select a Wave file to play...", File::nonexistent, "*.wav");
    if (chooser.browseForFileToOpen())
    {
        File file (chooser.getResult());
        setSampleFile( file );
    }
}



void SampleButton::setSampleFile( File file )
{
    m_sampleFile = file;
}




File SampleButton::getSampleFile()
{
    return m_sampleFile;
}




int SampleButton::getNoteNumber()
{
    return m_noteNumber;
}




void SampleButton::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
