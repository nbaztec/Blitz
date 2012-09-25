/*
 * Enemy.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#include "Enemy.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
		Enemy::Enemy(const geometry::Triad &start)
		{			
			this->_state = new state::State();
			this->_state->current = this->_state->start = start;
			this->_state->box.set(2.0f, 2.0f);
			this->_state->normal.set(0.0f, 0.0f, -1.0f);
			this->_state->velocity.set(0.0f, 0.0f, -5.f);			
		}

		Enemy::~Enemy(void)
		{			
		}

		void Enemy::draw(void)
		{	
			geometry::Triad t = this->_state->current;
			geometry::Triad r = this->_state->rotation.direction;
			glPushMatrix();
			glTranslatef(t.x, -t.y, -t.z);
				glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
				glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
				glEnd();	
			glPopMatrix();
		}

		void Enemy::tick(float delta)
		{
			this->updateState(delta);					
		}

		bool Enemy::isComplete() const
		{
			return this->_state->current.z <= -10.0f;
		}
	}
}