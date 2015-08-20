#pragma once
#include "Sound.h"
#include <SDL_mixer.h>

namespace Break
{
	namespace Audio
	{
		/**
		 * \brief reperesents a raw sound class
		 * \author Mohammed Shaalan
		 */
		class SoundEffect:public Sound
		{
		public:
			///changes the volume of the current playing music
			void setVolume(int val) override{
				m_volume =val;
				Mix_VolumeChunk(m_data,m_volume);
			}

			/**
			 * \brief plays a sound object in case of paused or stopped
			 * \param repeat if true will repreat infinitly (OPTIONAL default is false)
			 * \author Mohammed Shaalan
			 */
			void play(bool repeat=false) override{
				if(m_status == STOPPED || m_status == PLAYING)
				{
					if(repeat)
						Mix_PlayChannel(-1,m_data,-1);
					else
						Mix_PlayChannel(-1,m_data,0);
					m_status = PLAYING;
				}else if(m_status == PAUSED)
				{
					Mix_ResumeMusic();
					m_status = PLAYING;
				}
			}

			///pauses this sound
			void pause() override{
				if(m_status == PLAYING)
				{
					Mix_PauseMusic();
					m_status = PAUSED;
				}
			}

			///stops this sound
			void stop() override{
				if(m_status != STOPPED){
					Mix_HaltMusic();
					m_status = STOPPED;
				}
			}

		protected:
			///sound data
			Mix_Chunk* m_data;

		public:
			SoundEffect(Mix_Chunk* data):m_data(data)
			{
				m_status = STOPPED;
			}

			virtual ~SoundEffect(){
				if(m_data)
					Mix_FreeChunk(m_data);
			}
		};

		typedef std::shared_ptr<SoundEffect> SoundEffectPtr;
	}
}