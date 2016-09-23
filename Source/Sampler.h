/*
  ==============================================================================

    Sampler.h
    Created: 24 Aug 2016 11:06:34pm
    Author:  sda1_k1404

  ==============================================================================
*/

#ifndef SAMPLER_H_INCLUDED
#define SAMPLER_H_INCLUDED


#include "../JuceLibraryCode/JuceHeader.h"

class Sampler : public Synthesiser
{
public:
    void noteOn(
        const int midiChannel,
        const int midiNoteNumber,
        const float velocity
    ) override;
};

#endif  // SAMPLER_H_INCLUDED
