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
			this->_state->box.set(-0.5f, 0.5f, 0.5f, -0.5f);
			this->_state->normal.set(0.0f, 0.0f, -1.0f);
			this->_damage = 0.1f;
			this->_energy = 0.2f;
			
			geometry::Triad t = this->_state->current;
			std::cout << "BULLET: " << t.x << ", " << t.y << std::endl;

			//this->_state->velocity.set(0.0f, 0.0f, 50.f);
			//this->_state->rotation.magnitude = 200.0f;
			//this->_state->rotation.direction.set(0.0f, 0.0f, 1.0f);
			this->_animation.push_back(new state::LinearAnimation(this->_state, geometry::Triad(0.0f, 0.0f, -50.f)));
			this->_animation.push_back(new state::RotationAnimation(this->_state, geometry::Vector(0.0f, 0.0f, 1.0f, 200.0f)));
			//this->_animation.push_back(new state::ColorAnimation(this->_state, state::AnimationType::atColorBlink, geometry::Quad(1.0f, 0.0f, 0.0f, 1.0f), 0.0f, 0.2));
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
				
				glEnable( GL_TEXTURE_2D );
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glEnable(GL_DEPTH_TEST);

				glTranslatef(t.x, t.y, t.z);
				glRotatef(this->_state->angle, r.x, r.y, r.z);
				glColor4f(this->_state->color.a, this->_state->color.b, this->_state->color.c, this->_state->color.d);
				glBegin(GL_QUADS);          // Begin Drawing The Textured Quad
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
						glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
				glEnd();	

				glDisable( GL_TEXTURE_2D );
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glDisable(GL_DEPTH_TEST);

			glPopMatrix();
		}

		void PlasmaBullet::tick(float delta)
		{
			this->_completed = this->updateState(delta);
			geometry::Triad t= this->_state->start;
			t.z += 5.0f;
			//PlasmaBullet plane(t);
			//plane._state->normal = geometry::Triad(0.0f, 0.0f, -1.0f);
			//std::cout << this->_state->current.z << "\t" << this->collision(plane) << std::endl;
			
		}

		bool PlasmaBullet::isComplete() const
		{
			return this->_completed || this->_state->current.z < -70.0f;
		}

		bool PlasmaBullet::collision(UnitObject& obj)
		{
			bool passed = this->_state->normal.z > 0.0f? this->_state->current.z >= obj.getState()->current.z: this->_state->current.z <= obj.getState()->current.z;
			if(passed)
			{
				float tx1 = this->_state->current.x + this->_state->box.a;
				float tx2 = this->_state->current.x + this->_state->box.c;
				float ty1 = this->_state->current.y + this->_state->box.b;
				float ty2 = this->_state->current.y + this->_state->box.d;
				float ox1 = obj.getState()->current.x + obj.getState()->box.a;
				float ox2 = obj.getState()->current.x + obj.getState()->box.c;
				float oy1 = obj.getState()->current.y + obj.getState()->box.b;
				float oy2 = obj.getState()->current.y + obj.getState()->box.d;

				if(
						tx2 < ox1	// Projectile to left, Object to right
					||	tx1 > ox2	// Projectile to right, Object to left
					||	ty1 < oy2	// Projectile below, Object above
					||	ty2 > oy1	// Projectile above, Object below
					)
					return false;
				else
					return true;

				/*
				float dx = this->_state->start.x - obj.getState()->start.x;
				//std::cout << "- " << dx << ":\t" << this->_state->box.x << ", " << obj.getState()->box.x << std::endl;
				if(dx < 0.0f)	// Projectile to left, Object to right
				{
					if(-dx > this->_state->box.x)
						return false;
				}
				else			// Projectile to right, Object to left
				{
					if(dx > obj.getState()->box.x)
						return false;
				}
				float dy = this->_state->start.y - obj.getState()->start.y;
				//std::cout << "| " << dy << ":\t" << this->_state->box.y << ", " << obj.getState()->box.y << std::endl;
				if(dy < 0.0f)	// Projectile below, Object above
				{
					if(-dy > obj.getState()->box.y)
						return false;
				}
				else			// Projectile above, Object below
				{
					if(dy > this->_state->box.y)
						return false;
				}
				//obj.hit(*this);
				//this->_completed = true;
				return true;				
				*/
			}
			return false;
		}
	}
}