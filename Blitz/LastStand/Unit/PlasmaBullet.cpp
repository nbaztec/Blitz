/*
 * PlasmaBullet.cpp
 *
 *  Created on: Sep 18, 2012
 *      Author: Nisheeth
 */
 
#include "PlasmaBullet.hpp"
#include <iostream>
namespace game {
	namespace unit {		
	
		PlasmaBullet::PlasmaBullet(const blitz::geometry::Triad &start)
		{			
			this->createSoundSources(1);
			this->_state = new blitz::state::State();
			this->_state->current = this->_state->start = start;
			this->_state->box.set(-0.5f, 0.5f, 0.5f, -0.5f);
			this->_state->normal.set(0.0f, 0.0f, -1.0f);
			this->_damage = 0.1f;
			this->_energy = 0.2f;
			
			this->setVolume(0.5f);

			blitz::geometry::Triad t = this->_state->current;
			Log.setSingleLine(true);
			Log.debug("") << "Bullet: " << t.x << ", " << t.y;
			Log.newline();
			Log.setSingleLine(false);

			this->_animation.push_back(new blitz::state::LinearAnimation(this->_state, blitz::geometry::Triad(0.0f, 0.0f, -50.f)));
			this->_animation.push_back(new blitz::state::RotationAnimation(this->_state, blitz::geometry::Vector(0.0f, 0.0f, 1.0f, 200.0f)));					
		}

		PlasmaBullet::~PlasmaBullet(void)
		{			
		}
		
		void PlasmaBullet::onFirstRender()
		{
			this->attachAndPlaySound((*this->_sndMgr)["player_fire"]);
		}

		void PlasmaBullet::draw(void)
		{	
			this->callFirstRender();

			blitz::geometry::Triad t = this->_state->current;
			blitz::geometry::Triad r = this->_state->rotation.direction;
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

		void PlasmaBullet::tick(const float& delta)
		{
			this->_completed = this->updateState(delta);			
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
			}
			return false;
		}
	}
}