/*
 * PassiveEnemy.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#include "PassiveEnemy.hpp"
#include <iostream>
namespace game {
	namespace unit {		
		PassiveEnemy::PassiveEnemy(const blitz::geometry::Triad &start)
		{			
			this->_state->current = this->_state->start = start;
			this->_state->box.set(-1.0f, 1.0f, 1.0f, -1.0f);
			this->_state->normal.set(0.0f, 0.0f, 1.0f);
			this->_state->velocity.set(0.0f, 0.0f, 0.f);
			this->_state->clear = *this->_state->color.set(1.0f, 1.0f, 1.0f, 1.0f);
			this->_damage = 0.1f;
			this->_health = 1.0f;
			this->_hitPlayer = false;
			this->_cutOff = -3.0f;
		}

		PassiveEnemy::~PassiveEnemy(void)
		{	
		}

		void PassiveEnemy::tick(const float& delta)
		{
			this->_completed = this->updateState(delta);
			if(this->_hitPlayer = this->_state->current.z >= this->_cutOff)
				this->_state->velocity.set(0.0f, 0.0f, 0.f);
		}

		bool PassiveEnemy::isComplete() const
		{
			return this->_completed;
		}		

		// Protected Methods

		void PassiveEnemy::reduceHealth(float damage)
		{			
			this->_health -= damage;
		}

		bool PassiveEnemy::hasHitPlayer()
		{
			return this->_hitPlayer;
		}
	}
}