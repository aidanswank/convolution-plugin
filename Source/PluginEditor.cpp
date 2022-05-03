/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ConvolveAudioProcessorEditor::ConvolveAudioProcessorEditor (ConvolveAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 400);
    
    setResizable (true, true);

    formatManager.registerBasicFormats();
    addAndMakeVisible(waveformDisplay);
    
    addAndMakeVisible(drywetSlider);
    addAndMakeVisible(drywetLabel);
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(gainLabel);

//    drywetLabel.setText("dry/wet", juce::dontSendNotification);
//    drywetLabel.attachToComponent(&drywetSlider, true);
//    gainLabel.setText("gain", juce::dontSendNotification);
//    gainLabel.attachToComponent(&gainSlider, true);

    
    drywetSlider.addListener(this);
    drywetSlider.setRange(0, 1.0);
    
    gainSlider.addListener(this);
    gainSlider.setRange(0, 2.0);
    gainSlider.setValue(1.0);
    
    rowH = getHeight()/8;
//    resized();
//    std::cout << rowH << std::endl;
        
    addAndMakeVisible(thisWebBrowserComponent);
    thisWebBrowserComponent->goToURL("https://aidanswank.github.io/convolution-animation/");
    thisWebBrowserComponent->setVisible(false);
    toggleBrowser=false;

    addKeyListener(this); // for keypress
    
}

ConvolveAudioProcessorEditor::~ConvolveAudioProcessorEditor()
{
}

//==============================================================================
void ConvolveAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::topLeft, 1);

}

void ConvolveAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    rowH=getHeight()/8;
    waveformDisplay.setBounds(0, 0, getWidth(), rowH*4);
    drywetSlider.setBounds(0, rowH*4, getWidth(), rowH);
//    drywetLabel.setBounds(0, rowH*4, getWidth(),rowH);
    gainSlider.setBounds(0, rowH*5, getWidth(), rowH);
//    gainLabel.setBounds(0, rowH*5, getWidth(),rowH);
}

bool ConvolveAudioProcessorEditor::isInterestedInFileDrag (const juce::StringArray &files)
{
  std::cout << "isInterestedInFileDrag" << std::endl;
  return true;
}

void ConvolveAudioProcessorEditor::filesDropped (const juce::StringArray &files, int x, int y)
{
  if (files.size() == 1)
  {
//      std::cout << files[0].toStdString() << std::endl;
      waveformDisplay.loadURL(juce::URL{juce::File{files[0]}});
//      p.convolution
      audioProcessor.convolution.loadImpulseResponse(juce::File{files[0]}, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0, juce::dsp::Convolution::Normalise::yes);
  }
}

void ConvolveAudioProcessorEditor::sliderValueChanged (juce::Slider *slider)
{
    std::cout << "value " << slider->getValue() << std::endl;
    if(slider==&gainSlider)
    {
        audioProcessor.gainValue = slider->getValue();
    }
    if(slider==&drywetSlider)
    {
        audioProcessor.drywetValue = slider->getValue();
    }
}

bool ConvolveAudioProcessorEditor::keyPressed(const juce::KeyPress &k, Component *c)
{
    std::cout << "key pressed " << &k << std::endl;
    toggleBrowser=!(toggleBrowser);
    std::cout << toggleBrowser << std::endl;
    
    thisWebBrowserComponent->setVisible(toggleBrowser);
    thisWebBrowserComponent->setBounds(getLocalBounds());

    return false;
}

