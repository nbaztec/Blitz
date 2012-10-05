/*
 * SoundManager.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#include "SoundManager.hpp"

SoundManager::SoundManager(void)
{
}

SoundManager::~SoundManager(void)
{
	std::map<std::string, ALuint>::iterator it;
	while(!this->_media.empty())
	{				
		it = this->_media.begin();
		alDeleteBuffers(1, &it->second);
		this->_media.erase(it);
	}
}

ALuint SoundManager::operator[](const char* key)
{	
	if(this->_media.find(key) != this->_media.end())
		return this->_media[key];
	else
		return NULL;
}

bool SoundManager::load(const char* key, const char* file)
{
	ALuint uiBuffer;
	alGenBuffers(1, &uiBuffer);
	if(uiBuffer = alutCreateBufferFromFile(file))
	{
		//std::cout << "Loaded file: " << file << std::endl;
		this->_media[key] = uiBuffer;
		return true;
	}
	else
	{
		std::cout << "Error loading file: " << file << std::endl;
		alDeleteBuffers(1, &uiBuffer);
		return false;
	}
}

bool SoundManager::loadOgg(const char* key, const char* file)
{
	ALenum format;                          // The sound data format
    ALsizei freq;                           // The frequency of the sound data
    std::vector<char> bufferData;           // The sound buffer data from file
	if(SoundFactory::LoadOgg(file, bufferData, format, freq))
	{
		ALuint uiBuffer;
		alGenBuffers(1, &uiBuffer);
		alBufferData(uiBuffer, format, &bufferData[0], static_cast<ALsizei>(bufferData.size()), freq);
		if(uiBuffer)
		{
			//std::cout << "Loaded file: " << file << std::endl;
			this->_media[key] = uiBuffer;
			return true;
		}
		else
		{
			std::cout << "Error loading file: " << file << std::endl;
			alDeleteBuffers(1, &uiBuffer);
			return false;
		}
	}
	else
	{
		std::cout << "Error loading file: " << file << std::endl;
		return false;
	}	
}

void SoundManager::remove(const char* key)
{
	std::map<std::string, ALuint>::iterator it = this->_media.find(key);
	if(it != this->_media.end())
	{
		alDeleteBuffers(1, &it->second);
		this->_media.erase(it);
	}
}

bool SoundManager::has_texture(const char* key)
{
	return this->_media.find(key) != this->_media.end();
}