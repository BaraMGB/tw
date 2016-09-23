/*
  ==============================================================================

    Sampler.cpp
    Created: 24 Aug 2016 11:06:34pm
    Author:  sda1_k1404

  ==============================================================================
*/

#include "Sampler.h"

#include "SamplerSoundLayer.h"

void Sampler::noteOn (const int midiChannel,
                          const int midiNoteNumber,
                          const float velocity)
{
    const ScopedLock sl (lock);

    for (int i = sounds.size(); --i >= 0;)
    {
        SynthesiserSound* const soundSource = sounds.getUnchecked(i);
        SamplerSoundLayer* const sound = static_cast<SamplerSoundLayer* const>( soundSource );

        if ( sound->appliesTo ( midiNoteNumber, velocity ) && sound->appliesToChannel ( midiChannel ) )
        {
            // If hitting a note that's still ringing, stop it first (it could be
            // still playing because of the sustain or sostenuto pedal).
            for ( int j = voices.size(); --j >= 0; )
            {
                SynthesiserVoice* const voice = voices.getUnchecked( j );
                if ( voice->getCurrentlyPlayingNote() == midiNoteNumber && voice->isPlayingChannel ( midiChannel ) )
                {
                    stopVoice ( voice, 1.0f, true );
                }
            }
            startVoice ( findFreeVoice ( sound, midiChannel, midiNoteNumber, isNoteStealingEnabled() ),
                        sound, midiChannel, midiNoteNumber, velocity );
        }
    }
}
