/*
 * PlasmaBullet.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "..\Core\Coordinate.hpp"
#include "..\Core\Object.hpp"
#include "..\Core\LinearAnimation.hpp"
#include "..\Core\RotationAnimation.hpp"
#include "..\Core\ColorAnimation.hpp"

#include "DamageObject.hpp"
#include "EnergyObject.hpp"

namespace blitz {
	namespace unit {

		class PlasmaBullet: public DamageObject, public EnergyObject
		{
		public:
			PlasmaBullet(const geometry::Triad &start);
			~PlasmaBullet(void);

			void draw(void);
			void tick(float delta);
			virtual bool isComplete() const;
			virtual bool collision(Object& obj);
		};
	}
}