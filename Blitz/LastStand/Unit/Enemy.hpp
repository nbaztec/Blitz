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

			//void draw(void);
			//void tick(float delta);
			virtual bool isComplete() const;
			virtual void hit(blitz::unit::UnitObject& obj);

			// Feebacks
			bool hasHitPlayer();
		};
	}
}
