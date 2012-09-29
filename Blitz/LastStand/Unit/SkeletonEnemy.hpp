/*
 * SkeletonEnemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "../../Engine/Core/Coordinate.hpp"
#include "../../Engine/Unit/UnitObject.hpp"
#include "../../Engine/Core/ColorAnimation.hpp"

#include "../../Engine/Util/cal3d/model.h"

#include "Enemy.hpp"

namespace game {
	namespace unit {

		class SkeletonEnemy: public Enemy
		{
		protected:
			Model* _model;
		public:
			SkeletonEnemy(const blitz::geometry::Triad &start, Model* model);
			~SkeletonEnemy(void);

			//void draw(void);
			//virtual void tick(float delta);
			virtual void hit(blitz::unit::UnitObject& obj);
		};
	}
}
