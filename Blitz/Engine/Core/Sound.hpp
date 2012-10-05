/*
 * Sound.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <al/al.h>
#include <al/alut.h>

namespace blitz {

	class Sound 
	{
	public:
		void ac()
		{
			ALuint buffer = alureCreateBufferFromFile("file.ogg");
		}
	};
	
}