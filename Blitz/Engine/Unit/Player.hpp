/*
 * Player.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include "../View/Level.hpp"
#include "../Core/Interface/TickedPainter.hpp"
#include "../Core/Interface/InputListener.hpp"
#include "../Core/Interface/SoundGenerator.hpp"
#include "HealthObject.hpp"
#include "EnergyObject.hpp"

namespace blitz {
	namespace unit {
	
		class Player : public virtual blitz::TickedPainter, public virtual blitz::InputListener, public virtual blitz::SoundGenerator, public virtual blitz::unit::HealthObject {
		protected:
			blitz::view::Level* _level;
		public:
			Player();
			virtual ~Player();

			void setLevel(blitz::view::Level* level);
		};
	}
}