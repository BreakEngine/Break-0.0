#pragma once
#include "Sound.h"
#include <SDL_mixer.h>

namespace Break
{
	namespace Audio
	{
		/**
		 * \brief reperesents a music class, you can only play one music object at a time
		 * \author Mohammed Shaalan
		 */
		class Music:public Sound
		{
		public:
			///changes the volume of the current playing music
			void setVolume(int val) override{
				m_volume = val;
				Mix_VolumeMusic(m_volume);
				
			}

			/**
			 * \brief plays a music object in case of paused or stopped
			 * \param repeat if true will repreat infinitly (OPTIONAL default is true)
			 * \author Mohammed Shaalan
			 */
			void play(bool repeat = true) override{
				if(m_status == Status::STOPPED){
					if(repeat)
						Mix_PlayMusic(m_data,-1);
					else
						Mix_PlayMusic(m_data,1);

					m_status = Status::PLAYING;
				}else if(m_status == Status::PAUSED)
				{
					Mix_ResumeMusic();
					m_status = PLAYING;
				}
			}

			///pauses the palying music
			void pause() override{
				if(m_status == PLAYING){
					Mix_PauseMusic();
					m_status = Status::PAUSED;
				}
			}

			///stops the playing music
			void stop() override{
				if(m_status != STOPPED){
					Mix_HaltMusic();
					m_status = STOPPED;
				}
			}

		protected:
			///music data
			Mix_Music* m_data;

		public:
			///init constructor
			Music(Mix_Music* data):m_data(data)
			{
				m_status = STOPPED;
			}

			///destructor
			virtual ~Music()
			{
				if(m_data)
					Mix_FreeMusic(m_data);
			}

		};
		typedef std::shared_ptr<Music> MusicPtr;
	}
}