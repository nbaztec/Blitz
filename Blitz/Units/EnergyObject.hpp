/*
 * EnergyObject.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "..\Core\Object.hpp"

namespace blitz {
	namespace unit {

		class EnergyObject: virtual public Object
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