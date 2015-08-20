#pragma once

#include<memory>
namespace Break
{
	namespace Audio
	{

		///represents a sound
		class Sound
		{	
		public:
			///sound status
			enum Status
			{
				PLAYING=0, PAUSED=1, STOPPED=2
			};

			Sound()
			{
				m_volume = 1;
				m_status = STOPPED;
			}

			virtual ~Sound()
			{
				
			}

			///return current status
			Status getStatus()
			{
				return m_status;
			}

			///return volume
			int getVolume()
			{
				return m_volume;
			}

			///set sound volume
			virtual void setVolume(int val)=0;

			///plays current sound
			virtual void play(bool repeat=false)=0;

			///pauses sound
			virtual void pause()=0;

			///stops sound
			virtual void stop()=0;

		protected:
			///sound volume
			int m_volume;
			///sound status
			Status m_status;
		};
		typedef std::shared_ptr<Sound> SoundPtr;
	}
}