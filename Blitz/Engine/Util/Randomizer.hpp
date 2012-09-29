/*
 * Randomizer.hpp
 *
 *  Created on: Sep 16, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <random>

class Randomizer
{
private:
	std::default_random_engine _generator;	

public:
	Randomizer(void);
	virtual ~Randomizer(void);
	float randFloat();
	float randFloat(float min, float max);
	float randFloat(float max);
	int randInt(int min, int max);
	int randInt(int max);	
};