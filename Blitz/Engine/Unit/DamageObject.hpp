/*
 * DamageObject.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "UnitObject.hpp"

namespace blitz {
	namespace unit {

		class DamageObject: virtual public UnitObject
		{
		protected:
			float _damage;

		public:
			DamageObject(void);
			~DamageObject(void);

			float setDamage(float value);
			float getDamage() const;			
		};
	}
}