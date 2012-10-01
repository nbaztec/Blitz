/*
 * SkeletonEnemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "../Core/Coordinate.hpp"
#include "UnitObject.hpp"
#include "../Core/ColorAnimation.hpp"

#include "Enemy.hpp"
#include "../Util/cal3d/model.h"

namespace blitz {
	namespace unit {

		class SkeletonEnemy: public Enemy
		{
		protected:
			Model* _model;
		public:
			SkeletonEnemy(const geometry::Triad &start, Model* model);
			~SkeletonEnemy(void);

			void draw(void);
			virtual void tick(float delta);
			virtual void hit(UnitObject& obj);
		};
	}
}
