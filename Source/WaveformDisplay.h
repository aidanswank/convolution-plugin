/*
  ==============================================================================

    WaveformDisplay.h
    Created: 26 Apr 2022 7:55:00pm
    Author:  aidan

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class WaveformDisplay    : public juce::Component,
public juce::ChangeListener
{
public:
    WaveformDisplay( juce::AudioFormatManager &     formatManagerToUse,
                    juce::AudioThumbnailCache &     cacheToUse );
    ~WaveformDisplay();

    void paint (juce::Graphics&) override;
    void resized() override;

    void changeListenerCallback (juce::ChangeBroadcaster *source) override;

    void loadURL(juce::URL audioURL);

    /** set the relative position of the playhead*/
    void setPositionRelative(double pos);

private:
    juce::AudioThumbnail audioThumb;
    bool fileLoaded;
    double position;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WaveformDisplay)
};
