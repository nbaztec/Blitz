/*
 * SoundGenerator.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#ifndef NULL
#define NULL 0
#endif

#include <al/al.h>
#include <al/alut.h>

namespace blitz {
	class SoundGenerator
	{
	protected:
		ALuint* _sndSource;
		int _index;
		int _num;

	public:
		inline SoundGenerator()
		{	
			this->_num = 0;
		}

		inline virtual ~SoundGenerator()
		{
			if(this->_num)
			{
				alDeleteSources(this->_num, _sndSource);
				delete this->_sndSource;
			}
		}

		inline void createSoundSources(const int& num)
		{
			this->_num = num;
			this->_index = 0;
			this->_sndSource = new ALuint[num];
			alGenSources(this->_num, _sndSource);
		}

		inline void deleteSoundSources()
		{
			if(this->_num)
			{
				this->_num = 0;
				alDeleteSources(this->_num,  this->_sndSource);
				delete this->_sndSource;
			}
		}

		inline int setSourceIndex(int index)
		{
			return this->_index = index;
		}
		
		inline int getSourceIndex()
		{
			return this->_index;
		}

		inline int getSourceCount()
		{
			return this->_num;
		}		

		inline virtual void attachSound(ALuint buffer)
		{
			alSourcei(this->_sndSource[this->_index], AL_BUFFER, buffer);
		}

		inline virtual void attachAndPlaySound(ALuint buffer)
		{
			/*
			alSourceStop(this->_sndSource[this->_index]);
			alSourcei(this->_sndSource[this->_index], AL_BUFFER, buffer);
			alSourcePlay(this->_sndSource[this->_index]);
			*/
		}

		inline virtual void queueSound(ALuint buffer)
		{
			alSourceQueueBuffers(this->_sndSource[this->_index], 1, &buffer);
		}

		inline void getQueuedBuffers(ALuint* buffer)
		{
			alGetSourcei(this->_sndSource[this->_index], AL_BUFFERS_QUEUED, (ALint*)buffer);
		}
		
		inline virtual bool tryDequeueSounds(ALuint* buffer)
		{			
			ALint n = 0;
			alGetSourcei(this->_sndSource[this->_index], AL_BUFFERS_PROCESSED, &n);
			if(n)
			{
				alSourceUnqueueBuffers(this->_sndSource[this->_index], 1, buffer);
				return true;
			}
			else
				return false;
		}

		inline virtual void setVolume(const float& v)
		{
			alSourcef(this->_sndSource[this->_index], AL_GAIN, v);
		}

		inline virtual float getVolume()
		{
			ALfloat f = 0;
			alGetSourcef(this->_sndSource[this->_index], AL_GAIN, &f);
			return f;
		}

		inline virtual void setPosition(const float& x, const float& y, const float& z)
		{
			alSource3f(this->_sndSource[this->_index], AL_POSITION, x, y, z);
		}

		inline virtual void setVelocity(const float& x, const float& y, const float& z)
		{
			alSource3f(this->_sndSource[this->_index], AL_VELOCITY, x, y, z);
		}

		inline virtual void setDirection(const float& x, const float& y, const float& z)
		{
			alSource3f(this->_sndSource[this->_index], AL_DIRECTION, x, y, z);
		}
		
		inline virtual void setLooping(const bool& value)
		{
			alSourcei(this->_sndSource[this->_index], AL_LOOPING, value? 1: 0);
		}

		inline virtual void setPitch(const int& value)
		{
			alSourcei(this->_sndSource[this->_index], AL_PITCH, value);
		}

		inline virtual float getPitch()
		{
			ALfloat f = 0;
			alGetSourcef(this->_sndSource[this->_index], AL_PITCH, &f);
			return f;
		}
		inline virtual ALuint getAttachedBuffer()
		{
			ALint id = 0;
			alGetSourcei(this->_sndSource[this->_index], AL_BUFFER, &id);
			return (ALuint)id;
		}

		inline virtual void playSound(ALuint buffer)
		{
			alSourcePlay(this->_sndSource[this->_index]);
		}

		inline virtual void pauseSound(ALuint buffer)
		{
			alSourcePause(this->_sndSource[this->_index]);
		}

		inline virtual void stopSound(ALuint buffer)
		{
			alSourceStop(this->_sndSource[this->_index]);
		}
	};	
}