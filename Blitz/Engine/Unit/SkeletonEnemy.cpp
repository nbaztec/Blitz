/*
 * SkeletonEnemy.cpp
 *
 *  Created on: Sep 22, 2012
 *      Author: Nisheeth
 */
 
#include "SkeletonEnemy.hpp"
#include <iostream>
namespace blitz {
	namespace unit {		
		SkeletonEnemy::SkeletonEnemy(const geometry::Triad &start, Model* model)
			:Enemy(start)
		{						
			this->_model = model;
			this->_state->current.y = this->_state->start.y += -2.0f;		// Offset for height adjust
			this->_state->box.set(-0.5f, 2.3f, 0.5f, -2.1f);
			//this->_state->velocity.z += 30.0f;
			this->_state->setColorClear(0.3f, 0.3f, 0.3f, 1.0f);
		}

		SkeletonEnemy::~SkeletonEnemy(void)
		{		
		}

		void SkeletonEnemy::draw(void)
		{	
			geometry::Triad t = this->_state->current;
			geometry::Triad r = this->_state->rotation.direction;
			glPushMatrix();
				//glTranslatef(1.1f, -2.0f, 0.0f);
				glTranslatef(t.x, t.y, t.z);				
				glRotatef(this->_state->angle, r.x, r.y, r.z);
				glColor4f(this->_state->color.a, this->_state->color.b, this->_state->color.c, this->_state->color.d);
				
				//glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
				
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

		void SkeletonEnemy::tick(float delta)
		{
			Enemy::tick(delta);
			//this->_model->onUpdate(delta);
		}
		
		void SkeletonEnemy::hit(UnitObject& obj)
		{			
			unit::DamageObject* d = dynamic_cast<unit::DamageObject*>(&obj);
			if(d)
			{
				this->reduceHealth(d->getDamage());
				if(this->_health <= 0.0f)
				{
					this->_state->velocity.set(0.0f, 0.0f, 0.0f);
				
					state::Animation* a = new state::ColorAnimation(this->_state, state::AnimationType::atColorBlink, geometry::Quad(1.0f, 0.0f, 0.0f, 1.0f), 1.0f);
					a->setTerminal(true);
					this->_animation.push_back(a);		
				}
				else
					this->_animation.push_back(new state::ColorAnimation(this->_state, state::AnimationType::atColorBlink, geometry::Quad(0.0f, 1.0f, 0.0f, 1.f), 0.2f));		
			}
		}
	}
}