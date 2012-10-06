/*
 * Player.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "Player.hpp"

namespace blitz {
	namespace unit {

		Player::Player() {			
			this->_id = 0;
			this->_name = "Default Player";
			this->_level = NULL;
		}
		
		Player::Player(const int& id, const std::string& name) {
			this->_id = id;
			this->_name = name;
			this->_level = NULL;
		}

		Player::~Player() {
			Log.debug("Destroying Player");
		}
		
		void Player::setLevel(blitz::view::Level* level)
		{
			this->_level = level;
		}
	}
}