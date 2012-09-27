/*
 * EnergyObject.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#include "EnergyObject.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
	
		EnergyObject::EnergyObject(void)
		{			
			this->_energy = 0.0f;
		}

		EnergyObject::~EnergyObject(void)
		{			
		}

		float EnergyObject::setEnergy(float value)
		{
			return this->_energy = value;
		}
		
		float EnergyObject::getEnergy() const
		{
			return this->_energy;
		}
	}
}