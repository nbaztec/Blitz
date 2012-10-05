/*
 * SpacePlayer.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include "../../Engine/Unit/Player.hpp"


namespace game {
	namespace unit {
	
		class SpacePlayer : public blitz::unit::Player {
		protected:
			
		public:
			SpacePlayer();
			virtual ~SpacePlayer();

			virtual void draw(void);
			virtual void tick(const float& delta);
		};
	}
}