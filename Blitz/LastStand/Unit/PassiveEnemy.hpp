/*
 * PassiveEnemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "../../Engine/Core/Coordinate.hpp"
#include "../../Engine/Core/ColorAnimation.hpp"
#include "../../Engine/Unit/HealthObject.hpp"
#include "../../Engine/Unit/DamageObject.hpp"
#include "../../Engine/Unit/UnitObject.hpp"

namespace game {
	namespace unit {

		class PassiveEnemy: virtual public blitz::unit::HealthObject, virtual public blitz::unit::DamageObject
		{
		protected:
			float _cutOff;
			bool _hitPlayer;
			void reduceHealth(float damage);

		public:
			PassiveEnemy(const blitz::geometry::Triad &start);
			~PassiveEnemy(void);

			virtual void tick(const float& delta);
			virtual bool isComplete() const;

			// Feebacks
			virtual bool hasHitPlayer();
		};
	}
}
