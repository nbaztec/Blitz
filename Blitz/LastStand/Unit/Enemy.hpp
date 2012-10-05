/*
 * Enemy.hpp
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
#include "../../Engine/Util/LogManager.hpp"

namespace game {
	namespace unit {

		class Enemy: public blitz::unit::HealthObject
		{
		protected:			
			bool _hitPlayer;
			void reduceHealth(float damage);

		public:
			Enemy(const blitz::geometry::Triad &start);
			~Enemy(void);

			virtual void draw(void);
			virtual void tick(const float& delta);
			virtual bool isComplete() const;
			virtual void hit(blitz::unit::UnitObject& obj);

			// Feebacks
			virtual bool hasHitPlayer();
		};
	}
}
