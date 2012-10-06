/*
 * HealthObject.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "UnitObject.hpp"

namespace blitz {
	namespace unit {

		class HealthObject: public virtual UnitObject
		{
		protected:
			float _health;

		public:
			HealthObject(void);
			virtual ~HealthObject(void);

			float setHealth(float value);
			float getHealth() const;			
		};
	}
}