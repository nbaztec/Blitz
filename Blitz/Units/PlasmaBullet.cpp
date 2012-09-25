/*
 * PlasmaBullet.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#include "PlasmaBullet.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
	
		PlasmaBullet::PlasmaBullet(const geometry::Triad &start)
		{			
			this->_state = new state::State();
			this->_state->current = this->_state->start = start;
			this->_state->box.set(1.5f, 1.5f);
			this->_state->normal.set(0.0f, 0.0f, 1.0f);
			//this->_state->velocity.set(0.0f, 0.0f, 50.f);
			//this->_state->rotation.magnitude = 200.0f;
			//this->_state->rotation.direction.set(0.0f, 0.0f, 1.0f);
			this->_animation.push_back(new state::LinearAnimation(this->_state, state::AnimationType::atTranslate, geometry::Triad(0.0f, 0.0f, 50.f)));
			this->_animation.push_back(new state::RotationAnimation(this->_state, state::AnimationType::atRotate, geometry::Vector(0.0f, 0.0f, 1.0f, 200.0f)));
			this->_animation.push_back(new state::ColorAnimation(this->_state, state::AnimationType::atColorBlink, geometry::Quad(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.2));
			//this->_animation.push_back(new state::Animation(this->_state, state::AnimationType::atTranslate, geometry::Triad(0.0f, 0.0f, 10.f), 2.0f));
			//this->_animation.push_back(new state::Animation(this->_state, state::AnimationType::atRotate, geometry::Triad(0.0f, 0.0f, 10.f), 2.0f));
		}

		PlasmaBullet::~PlasmaBullet(void)
		{			
		}

		void PlasmaBullet::draw(void)
		{	
			geometry::Triad t = this->_state->current;
			geometry::Triad r = this->_state->rotation.direction;
			glPushMatrix();
			glTranslatef(t.x, -t.y, -t.z);
			glRotatef(this->_state->angle, r.x, r.y, r.z);
			glColor4f(this->_state->color.a, this->_state->color.b, this->_state->color.c, this->_state->color.d);
				glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
				glEnd();	
			glPopMatrix();
		}

		void PlasmaBullet::tick(float delta)
		{
			this->updateState(delta);
			geometry::Triad t= this->_state->start;
			t.z += 5.0f;
			//PlasmaBullet plane(t);
			//plane._state->normal = geometry::Triad(0.0f, 0.0f, -1.0f);
			//std::cout << this->_state->current.z << "\t" << this->collision(plane) << std::endl;
			
		}

		bool PlasmaBullet::isComplete() const
		{
			return this->_state->current.z > 30.0f;
		}

		bool PlasmaBullet::collision(const Object& obj)
		{
			bool passed = this->_state->normal.z > 0.0f? this->_state->current.z >= obj.getState()->current.z: this->_state->current.z <= obj.getState()->current.z;
			if(passed)
			{
				float dx = this->_state->start.x - obj.getState()->start.x;
				if(dx < 0.0f)
				{
					if(-dx > this->_state->box.x)
						return false;
				}
				else
				{
					if(dx > obj.getState()->box.x)
						return false;
				}
				float dy = this->_state->start.y - obj.getState()->start.y;
				if(dy < 0.0f)
				{
					if(-dy > this->_state->box.y)
						return false;
				}
				else
				{
					if(dy > obj.getState()->box.y)
						return false;
				}				
				return true;				
			}
			return false;
		}
	}
}