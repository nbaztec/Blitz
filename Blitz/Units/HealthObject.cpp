/*
 * HealthObject.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#include "HealthObject.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
	
		HealthObject::HealthObject(void)
		{			
			this->_health = 0.0f;
		}

		HealthObject::~HealthObject(void)
		{			
		}

		float HealthObject::setHealth(float value)
		{
			return this->_health = value;
		}
		
		float HealthObject::getHealth() const
		{
			return this->_health;
		}
	}
}