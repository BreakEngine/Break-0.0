#ifndef LIBRARY_BUILD
#include "AudioTest.h"
#include <ContentLoader.h>
#include "IKeyboard.h"

using namespace Break;
using namespace Break::Graphics;
using namespace Break::Infrastructure;
using namespace Break::GXWrapper;
using namespace Break::Audio;

AudioTest::AudioTest()
{
	display = IDisplayPtr(new IDisplay(640,480,"audio test"));
	forest = nullptr;
	dum = nullptr;
	tunes = nullptr;
	scratch = nullptr;
}

AudioTest::~AudioTest()
{
	forest = nullptr;
	dum = nullptr;
	tunes = nullptr;
	scratch = nullptr;
}

void AudioTest::init()
{
	Application::init();
}

void AudioTest::setupScene()
{
	Application::setupScene();
}

void AudioTest::loadResources()
{
	forest = Assets::ContentLoader::load<Music>("res\\audio\\Forest.mp3");
	tunes = Assets::ContentLoader::load<Music>("res\\audio\\Chiptunes.mp3");
	forest->play();
	//tunes->play();
	dum = Assets::ContentLoader::load<SoundEffect>("res\\audio\\high.wav");
	scratch = Assets::ContentLoader::load<SoundEffect>("res\\audio\\scratch.wav");
	scratch->play(true);
	dum->play();
	Application::loadResources();
}

void AudioTest::cleanUp()
{
	Application::cleanUp();
}

void AudioTest::input()
{
	if(IKeyboard::getKey(IKeyboard::Esc) == IKeyboard::KeyState::State_Down)
	{
		shutdown();
	}
	if(IKeyboard::getKey(IKeyboard::Z) == IKeyboard::State_Down)
	{
		dum->play();
	}
	if(IKeyboard::getKey(IKeyboard::X) == IKeyboard::State_Down)
	{
		scratch->play();
	}
	if(IKeyboard::getKey(IKeyboard::Space) == IKeyboard::KeyState::State_Down)
	{
		if(forest->getStatus() == Sound::PLAYING)
			forest->pause();
		else if(forest->getStatus() == Sound::PAUSED)
			forest->play();
	}
	Application::input();
}

void AudioTest::update(Break::Infrastructure::TimeStep time)
{
	Application::update(time);
}

void AudioTest::render()
{
	Application::render();
}

#endif