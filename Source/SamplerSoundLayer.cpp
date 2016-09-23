/*
  ==============================================================================

    SamplerSoundLayer.cpp
    Created: 24 Aug 2016 11:07:16pm
    Author:  sda1_k1404

  ==============================================================================
*/

#include "SamplerSoundLayer.h"


SamplerSoundLayer::SamplerSoundLayer ( const String &soundName,
                            AudioFormatReader &source,
                            const BigInteger &notes,
                            const int midiNoteForNormalPitch,
                            Range<float> velocityRange,
                            const double attackTimeSecs,
                            const double releaseTimeSecs,
                            const double maxSampleLengthSeconds )
    :   SamplerSound(
            soundName,
            source,
            notes,
            midiNoteForNormalPitch,
            attackTimeSecs,
            releaseTimeSecs,
            maxSampleLengthSeconds
        ),
        velocity( velocityRange )
{
}

SamplerSoundLayer::~SamplerSoundLayer()
{
}

bool SamplerSoundLayer::appliesTo( int midiNoteNumber, float velocity )
{
    bool appliesToMidiNote = appliesToNote( midiNoteNumber );
    bool isInVelocityRange = this->velocity.contains( velocity );

    return appliesToMidiNote && isInVelocityRange;
}
