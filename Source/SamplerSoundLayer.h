/*
  ==============================================================================

    SamplerSoundLayer.h
    Created: 24 Aug 2016 11:07:16pm
    Author:  sda1_k1404

  ==============================================================================
*/

#ifndef SAMPLERSOUNDLAYER_H_INCLUDED
#define SAMPLERSOUNDLAYER_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class SamplerSoundLayer : public SamplerSound
{
public:
    SamplerSoundLayer (
        const String &name,
        AudioFormatReader &source,
        const BigInteger &midiNotes,
        int midiNoteForNormalPitch,
        Range<float> velocityRange,
        double attackTimeSecs,
        double releaseTimeSecs,
        double maxSampleLengthSeconds
    );
    ~SamplerSoundLayer();
    bool appliesTo( int midiNoteNumber, float velocity );
private:
    Range<float> velocity;
};




#endif  // SAMPLERSOUNDLAYER_H_INCLUDED
