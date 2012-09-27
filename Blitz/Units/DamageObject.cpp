/*
 * DamageObject.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#include "DamageObject.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
	
		DamageObject::DamageObject(void)
		{			
			this->_damage = 0.0f;
		}

		DamageObject::~DamageObject(void)
		{			
		}

		float DamageObject::setDamage(float value)
		{
			return this->_damage = value;
		}
		
		float DamageObject::getDamage() const
		{
			return this->_damage;
		}
	}
}