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
			this->_level = NULL;
		}

		Player::~Player() {
			
		}

		void Player::setLevel(blitz::view::Level* level)
		{
			this->_level = level;
		}

	}
}