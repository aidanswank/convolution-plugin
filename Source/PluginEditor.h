/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "WaveformDisplay.h"

//==============================================================================
/**
*/
class ConvolveAudioProcessorEditor  : public juce::AudioProcessorEditor,
public juce::FileDragAndDropTarget,
public juce::Slider::Listener,
public juce::KeyListener
{
public:
    ConvolveAudioProcessorEditor (ConvolveAudioProcessor&);
    ~ConvolveAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    bool isInterestedInFileDrag (const juce::StringArray &files) override;
    void filesDropped (const juce::StringArray &files, int x, int y) override;
    bool keyPressed(const juce::KeyPress &k, Component *c) override;
    void sliderValueChanged (juce::Slider *slider) override;
    
    bool toggleBrowser;
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
//    WaveformDisplay waveformDisplay;

    ConvolveAudioProcessor& audioProcessor;
    
    juce::AudioFormatManager formatManager;
    juce::AudioThumbnailCache thumbCache{100};
    
    WaveformDisplay waveformDisplay{formatManager, thumbCache};
    
    float rowH;
    juce::Slider drywetSlider;
    juce::Label drywetLabel;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    
    juce::ScopedPointer<juce::WebBrowserComponent> thisWebBrowserComponent = new juce::WebBrowserComponent(false);
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConvolveAudioProcessorEditor)
};
