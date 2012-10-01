/*
 * SkeletonEnemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "../../Engine/Core/Coordinate.hpp"
#include "../../Engine/Unit/HealthObject.hpp"
#include "../../Engine/Core/ColorAnimation.hpp"

#include "../../Engine/Util/cal3d/model.h"

#include "PassiveEnemy.hpp"

namespace game {
	namespace unit {

		class SkeletonEnemy: public PassiveEnemy
		{
		protected:
			Model* _model;
		public:
			SkeletonEnemy(const blitz::geometry::Triad &start, Model* model);
			~SkeletonEnemy(void);

			virtual void draw(void);
			virtual void hit(blitz::unit::UnitObject& obj);
		};
	}
}
