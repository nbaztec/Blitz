/*
 * DamageObject.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "..\Core\Object.hpp"

namespace blitz {
	namespace unit {

		class DamageObject: virtual public Object
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