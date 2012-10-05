/*
 * SkeletonEnemy.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#include "SkeletonEnemy.hpp"
#include <iostream>
namespace game {
	namespace unit {		
		SkeletonEnemy::SkeletonEnemy(const blitz::geometry::Triad &start, Model* model)
			:PassiveEnemy(start)
		{						
			this->createSoundSources(1);

			this->_model = model;
			this->_state->current.y = this->_state->start.y += -2.0f;		// Offset for height adjust
			this->_state->box.set(-0.5f, 2.3f, 0.5f, -2.1f);
			this->_state->velocity.z += 10.0f;
			this->_state->setColorClear(0.3f, 0.3f, 0.3f, 1.0f);
			this->_health=1.0f;			
		}

		SkeletonEnemy::~SkeletonEnemy(void)
		{		
		}

		void SkeletonEnemy::draw(void)
		{	
			glPushMatrix();
				//glTranslatef(1.1f, -2.0f, 0.0f);
				
				//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				this->applyTransforms();
				const GLfloat lightPosition[] = { 1.0f, -1.0f, 1.0f, 1.0f };
				glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
				//const GLfloat lightColorAmbient[] = { 0.3f, 0.3f, 0.3f, 1.0f };
				const GLfloat lightColorAmbient[] = { this->_state->color.a, this->_state->color.b, this->_state->color.c, this->_state->color.d };
				glLightfv(GL_LIGHT0, GL_AMBIENT, lightColorAmbient);
				const GLfloat lightColorDiffuse[] = { 0.52f, 0.5f, 0.5f, 1.0f };
				glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDiffuse);
				const GLfloat lightColorSpecular[] = { 0.1f, 0.1f, 0.1f, 1.0f };
				glLightfv(GL_LIGHT0, GL_SPECULAR, lightColorSpecular);
				
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_BLEND);
				glDisable(GL_ALPHA_TEST);
				glEnable(GL_ALPHA);				

				glPushMatrix();
					glTranslatef(0, -2.1f, 0.0f);
					glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
					glScalef(0.025f, 0.025f, 0.025f);								
					this->_model->onRender();
				glPopMatrix();
				glDisable(GL_ALPHA);
				/*
				glPushMatrix();
					//glLoadIdentity();
					//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					geometry::Quad q = this->_state->box;
					glBegin(GL_QUADS);
						glVertex3f(q.a, q.b, 0.0f);
						glVertex3f(q.c, q.b, 0.0f);
						glVertex3f(q.c, q.d, 0.0f);
						glVertex3f(q.a, q.d, 0.0f);
					glEnd();
				glPopMatrix();
				*/				
			glPopMatrix();
		}
	
		void SkeletonEnemy::hit(UnitObject& obj)
		{			
			blitz::unit::DamageObject* d = dynamic_cast<blitz::unit::DamageObject*>(&obj);
			if(d && this->_health > 0.0f)
			{
				this->reduceHealth(d->getDamage());
				if(this->_health <= 0.0f)
				{
					this->_state->velocity.set(0.0f, 0.0f, 0.0f);
					blitz::state::Animation* a = new blitz::state::ColorAnimation(this->_state, blitz::state::AnimationType::atColorBlink, blitz::geometry::Quad(1.0f, 0.0f, 0.0f, 0.0f), 1.0f);
					a->setTerminal(true);
					this->_animation.push_back(a);
					this->attachAndPlaySound((*this->_sndMgr)["enemy_die"]);
				}
				else
				{
					this->attachAndPlaySound((*this->_sndMgr)["enemy_hit"]);
					this->_animation.push_back(new blitz::state::ColorAnimation(this->_state, blitz::state::AnimationType::atColorBlink, blitz::geometry::Quad(0.0f, 1.0f, 0.0f, 1.f), 0.2f));		
				}
			}
		}		
	}
}