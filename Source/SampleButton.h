/*
  ==============================================================================

    SampleButton.h
    Created: 18 Aug 2016 1:53:59pm
    Author:  sda1_k1404

  ==============================================================================
*/

#ifndef SAMPLEBUTTON_H_INCLUDED
#define SAMPLEBUTTON_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SampleButton    : public TextButton
{
public:
    SampleButton( int noteNumber );
    ~SampleButton();

    void paint (Graphics&) override;
    void resized() override;
    int getDefaultWidth();
    int getDefaultHeight();
    void loadFile();
    void setSampleFile( File file );
    File getSampleFile();
    int getNoteNumber();

private:
    int m_defaultWidth;
    int m_defaultHeight;
    int m_noteNumber;
    File m_sampleFile;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleButton)
};


#endif  // SAMPLEBUTTON_H_INCLUDED
