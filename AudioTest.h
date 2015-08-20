#ifndef LIBRARY_BUILD
#pragma once
#include <Application.h>
#include <Music.h>
#include <SoundEffect.h>
class AudioTest:public Break::Infrastructure::Application
{
public:
	Break::Audio::MusicPtr forest,tunes;
	Break::Audio::SoundEffectPtr dum,scratch;
	AudioTest();
	~AudioTest() override;
	void init() override;
	void setupScene() override;
	void loadResources() override;
	void cleanUp() override;
	void input() override;
	void update(Break::Infrastructure::TimeStep time) override;
	void render() override;
};
#endif