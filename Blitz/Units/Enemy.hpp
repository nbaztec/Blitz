/*
 * Enemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "..\Core\Coordinate.hpp"
#include "..\Core\Object.hpp"
#include "..\Core\ColorAnimation.hpp"

#include "HealthObject.hpp"
#include "DamageObject.hpp"

namespace blitz {
	namespace unit {

		class Enemy: public HealthObject
		{
		protected:			
			bool _hitPlayer;

			void reduceHealth(float damage);
		public:
			Enemy(const geometry::Triad &start);
			~Enemy(void);

			void draw(void);
			void tick(float delta);
			virtual bool isComplete() const;
			virtual void hit(Object& obj);

			// Feebacks
			bool hasHitPlayer();
		};
	}
}
