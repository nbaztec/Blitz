/*
 * PlasmaBullet.hpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "../../Engine/Core/Coordinate.hpp"
#include "../../Engine/Core/LinearAnimation.hpp"
#include "../../Engine/Core/RotationAnimation.hpp"
#include "../../Engine/Core/ColorAnimation.hpp"
#include "../../Engine/Util/LogManager.hpp"
#include "../../Engine/Core/State.hpp"
#include "../../Engine/Unit/UnitObject.hpp"
#include "../../Engine/Unit/DamageObject.hpp"
#include "../../Engine/Unit/EnergyObject.hpp"

namespace game {
	namespace unit {

		class PlasmaBullet: public blitz::unit::DamageObject, public blitz::unit::EnergyObject
		{
		protected:
			virtual void onFirstRender();
		public:
			PlasmaBullet(const blitz::geometry::Triad &start);
			~PlasmaBullet(void);

			virtual void draw(void);
			virtual void tick(const float& delta);
			virtual bool isComplete() const;
			virtual bool collision(blitz::unit::UnitObject& obj);
		};
	}
}