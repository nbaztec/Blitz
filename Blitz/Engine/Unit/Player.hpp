/*
 * Player.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <string>
#include "../View/Level.hpp"
#include "../Core/Interface/InputListener.hpp"
#include "UnitObject.hpp"
#include "HealthObject.hpp"
#include "EnergyObject.hpp"

namespace blitz {
	namespace view {
		class Level;
	}
}

namespace blitz {
	namespace unit {
	
		class Player : public virtual blitz::unit::HealthObject, public blitz::InputListener {
		protected:
			blitz::view::Level* _level;
			int _id;
			std::string _name;

		public:
			Player(void);
			Player(const int& id, const std::string& name);

			virtual ~Player(void);

			void setLevel(blitz::view::Level* level);

			virtual void mousePressed(int button){}
			virtual void mouseReleased(int button){}
			virtual void mouseMoved(int x, int y){}
			virtual void mouseWheelMoved(int pos){}

			virtual void keyPressed(int key){}
			virtual void keyReleased(int key){}
			virtual void keyCharPressed(int character){}
			virtual void keyCharReleased(int character){}
		};
	}
}