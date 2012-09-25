/*
 * Enemy.hpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include "..\Core\Coordinate.hpp"
#include "..\Core\Object.hpp"

namespace blitz {
	namespace unit {

		class Enemy: public Object
		{
		public:
			Enemy(const geometry::Triad &start);
			~Enemy(void);

			void draw(void);
			void tick(float delta);
			virtual bool isComplete() const;
		};
	}
}