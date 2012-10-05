/*
 * SoundFactory.cpp
 *
 *  Created on: Sep 1, 2012
 *      Author: Nisheeth
 */

#include "SoundFactory.hpp"


// This function loads a .ogg file into a memory buffer and returns
// the format and frequency.
bool SoundFactory::LoadOgg(const char* file, std::vector<char> &buffer, ALenum &format, ALsizei &freq)
{
	const int BUFFER_SIZE = 32768;			// 32KB
	int endian = 0;                         // 0 for Little-Endian, 1 for Big-Endian
	int bitStream;
	long bytes;
	char array[BUFFER_SIZE];				// Local fixed size array 32KB
	FILE *f;

	// Open for reading
	f = fopen(file, "rb");

	if (f == NULL)
	{
		Log.setSingleLine(false);
		Log.error("Cannot open ") << file;
		Log.newline();
		Log.setSingleLine(true);		
		
		return false;
	}
	
	vorbis_info *pInfo;
	OggVorbis_File oggFile;

	// Try opening the given file
	if (ov_open(f, &oggFile, NULL, 0) != 0)
	{		
		Log.setSingleLine(false);
		Log.error("Error opening file ") << file << " for decoding.";
		Log.newline();
		Log.setSingleLine(true);
		return false;
	}
	
	// Get some information about the OGG file
	pInfo = ov_info(&oggFile, -1);

	// Check the number of channels... always use 16-bit samples
	if (pInfo->channels == 1)
		format = AL_FORMAT_MONO16;
	else
		format = AL_FORMAT_STEREO16;

	// The frequency of the sampling rate
	freq = pInfo->rate;

	// Keep reading until all is read
	do
	{
		// Read up to a buffer's worth of decoded sound data
		bytes = ov_read(&oggFile, array, BUFFER_SIZE, endian, 2, 1, &bitStream);
		if (bytes < 0)
		{
			ov_clear(&oggFile);
			Log.setSingleLine(false);
			Log.error("Error decoding ") << file;
			Log.newline();
			Log.setSingleLine(true);		
			return false;
		}

		// Append to end of buffer
		buffer.insert(buffer.end(), array, array + bytes);
	}
	while (bytes > 0);

	// Clean up!
	ov_clear(&oggFile);

	return true;
}