/*
 * SoundManager.hpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <al/al.h>
#include <al/alut.h>
#include <map>
#include <string>
#include <iostream>
#include "SoundFactory.hpp"

class SoundManager
{
protected:
	std::map<std::string, ALuint> _media;
public:
	SoundManager(void);
	virtual ~SoundManager(void);
	
	bool load(const char* key, const char* file);
	bool loadOgg(const char* key, const char* file);
	void remove(const char* key);
	bool has_texture(const char* key);
	ALuint operator[](const char* key);	
};