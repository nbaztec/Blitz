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

namespace blitz {
	namespace unit {

		class Enemy: public Object
		{
		private:
			float _health;
			bool _hitPlayer;

			void reduceHealth();
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
