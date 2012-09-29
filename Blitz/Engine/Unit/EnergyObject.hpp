/*
 * EnergyObject.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "UnitObject.hpp"

namespace blitz {
	namespace unit {

		class EnergyObject: virtual public UnitObject
		{
		protected:
			float _energy;

		public:
			EnergyObject(void);
			~EnergyObject(void);

			float setEnergy(float value);
			float getEnergy() const;			
		};
	}
}