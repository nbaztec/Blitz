/*
 * Randomizer.cpp
 *
 *  Created on: Sep 16, 2012
 *      Author: Nisheeth
 */
 
#include "Randomizer.hpp"

Randomizer::Randomizer(void)
{		
}

Randomizer::~Randomizer(void)
{
}

float Randomizer::randFloat()
{
	return this->randFloat(0.0f, 1.0f);
}

float Randomizer::randFloat(float min, float max)
{
	std::uniform_real_distribution<double> distribution(min, max);
	return float(distribution(this->_generator));
}

float Randomizer::randFloat(float max)
{
	return this->randFloat(0.0f, max);
}

int Randomizer::randInt(int min, int max)
{
	std::uniform_int_distribution<int> distribution(min, max);
	return distribution(this->_generator);
}

int Randomizer::randInt(int max)
{
	return this->randInt(0, max);
}