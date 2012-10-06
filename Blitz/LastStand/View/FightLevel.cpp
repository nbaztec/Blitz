/*
 * FightLevel.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "FightLevel.hpp"

namespace game {
	namespace view {
		FightLevel::FightLevel()
		{			
			this->createSoundSources(2);
			this->_hud = new HUD();
			this->_lastHitDuration = 0.0f;
			this->_screenHit = false;
		}

		FightLevel::~FightLevel()
		{
			delete this->_hud;
		}
		
		void FightLevel::renderCamera()
		{
			blitz::geometry::Triad lookAt = this->_camera->getCurrent();
			gluLookAt(	lookAt.x * 10.0f, lookAt.y * 5.0f, 0.0f,
						lookAt.x * 10.0f, lookAt.y * 5.0f, -50.0f,
						0.0f, 1.0f,  0.0f);
		}

		void FightLevel::renderBackground()
		{			
			glPushMatrix ();
				glLoadIdentity();		
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();		
					glLoadIdentity();			
					glDisable(GL_DEPTH_TEST);
					glEnable(GL_TEXTURE_2D);
					glBindTexture(GL_TEXTURE_2D, (*this->_texMgr)["background"].first());
					glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
					glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
							glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
							glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
							glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
					glEnd();			
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			glPopMatrix ();
		}

		void FightLevel::renderCrosshair()
		{			
			glEnable( GL_TEXTURE_2D );
				glEnable(GL_BLEND);
				glEnable(GL_ALPHA_TEST);
				glEnable(GL_DEPTH_TEST);

				glBindTexture(GL_TEXTURE_2D, (*this->_texMgr)["crosshair"].first());
				glPushMatrix();				// Crosshair
					glLoadIdentity();
					glTranslatef(0.0f, 0.0f, -2.0f);
					glColor4f(1.0f, 0.2f, 0.2f, 0.5f);
					glBegin(GL_QUADS);
						glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.1f,-0.1f, 0.0f);
						glTexCoord2f(1.0f, 0.0f); glVertex3f( 0.1f,-0.1f, 0.0f);
						glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.1f, 0.1f, 0.0f);
						glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.1f, 0.1f, 0.0f);
					glEnd();  
				glPopMatrix();
				glDisable( GL_TEXTURE_2D );
		}

		void FightLevel::renderHUD()
		{
			glDisable(GL_DEPTH_TEST);
			glPushMatrix();
				glLoadIdentity();		
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();		
					glLoadIdentity();
					/*
					glEnable(GL_TEXTURE_2D);	
					glBindTexture(GL_TEXTURE_2D, 0);
					//glTranslatef(0.0f, -1.0f, 0.0f);
					float xl = 0.75f;
					float xh =  1.0f;
					float yh = -0.5f;
					float yl = -1.0f;
					float pX = 0.02f;
					float pY = 0.02f;
					float w = (xh - xl);
					float h = (yh - yl);
					float cw = w - 2*pX;
					float ch = h - 2*pY;
					//glColor4f(0.1f, 0.1f, 0.1f, 0.75f);
					glColor4f(0.9f, 0.9f, 0.9f, 0.25f);
					glBegin(GL_QUADS);
							glTexCoord2f(0.0f, 0.0f); glVertex3f(xl, yh, 0.0f);
							glTexCoord2f(1.0f, 0.0f); glVertex3f(xh, yh, 0.0f);
							glTexCoord2f(1.0f, 1.0f); glVertex3f(xh, yl, 0.0f);
							glTexCoord2f(0.0f, 1.0f); glVertex3f(xl, yl, 0.0f);
					glEnd();

					glPushMatrix();
						glLoadIdentity();
						glTranslatef(xh-pX, yl+pY, 0.0f);
				
						float bw = 0.04f;
						float bh = 0.02f;
						float bp = 0.005f;
						// Health						
						//glColor4f(0.1f, 1.0f, 0.1f, 0.65f);
						float op = 0.65;
						glPushMatrix();
							glBegin(GL_QUADS);
								glColor4f(0.8f, 0.0f, 0.0f, op); 
								glVertex3f(0.0f, 0.0f, 0.0f);
								glVertex3f(-bw,  0.0f, 0.0f);

								glColor4f(0.0f, 0.0f, 0.0f, op); 
								glVertex3f(-bw, ch, 0.0f);
								glVertex3f(0.0f, ch, 0.0f);
							glEnd();
							/*
							for(int i=0; i<10; i++)
							{
								glBegin(GL_QUADS);												
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-bw,  -bh, 0.0f);
										glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -bh, 0.0f);						
										glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);						
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-bw,  0.0f, 0.0f);						
								glEnd();
								glTranslatef(0.0f, bh+bp, 0.0f);
							}
							*
						glPopMatrix();
						glTranslatef(-(bw+2*bp), 0.0f, 0.0f);
						// Energy
						glColor4f(0.1f, 1.0f, 1.0f, 0.65f);
						glPushMatrix();				
							for(int i=0; i<10; i++)
							{
								glBegin(GL_QUADS);												
										glTexCoord2f(0.0f, 0.0f); glVertex3f(-bw,  -bh, 0.0f);						
										glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, -bh, 0.0f);						
										glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);						
										glTexCoord2f(0.0f, 1.0f); glVertex3f(-bw,  0.0f, 0.0f);						
								glEnd();
								glTranslatef(0.0f, bh+bp, 0.0f);
							}
						glPopMatrix();
					
					glPopMatrix();			
					*/					
					this->_hud->setMetrics(0.85f, -1.0f, 1.0f, -0.5f, 0.02f, 0.02f);
					this->_hud->renderBox();
					this->_hud->align(Alignment::alRight|Alignment::alBottom);
					this->_hud->renderHealthBar(this->_currentPlayer->getHealth());
					glTranslatef(-0.06f, 0.0f, 0.0f);
					this->_hud->renderEnergyBar(dynamic_cast<game::unit::SpacePlayer*>(this->_currentPlayer)->getEnergy());
					glTranslatef(-0.1f, 0.0f, 0.0f);
					//this->_hud->setMetrics(0.5f, -1.0f, 1.0f, -0.5f, 0.02f, 0.02f);
					this->_hud->renderRadar((*this->_texMgr)["radar"].first(), 0.4f, 0.5f);
					glTranslatef(-0.2f, 0.0f, 0.0f);
					this->_hud->renderEnemyMap(this->_objects["enemy"], 100.0f, 100.0f, 0.4f, 0.5f);					
					this->_hud->renderMarkers(this->_camera->getCurrentNormalized().x, this->_camera->getCurrentNormalized().y);
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
		}

		void FightLevel::renderOverlay()
		{
			if(this->_screenHit)
			{
				glPushMatrix();
					glLoadIdentity();		
					glMatrixMode(GL_PROJECTION);
					glPushMatrix();		
						glLoadIdentity();				
						glEnable( GL_TEXTURE_2D );	
						glBindTexture(GL_TEXTURE_2D, 0);
						glColor4f(1.0f, 0.0f, 0.0f, 0.2f);
						glBegin(GL_QUADS);
								glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
								glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
								glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
								glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
						glEnd();			
					glPopMatrix();
					glMatrixMode(GL_MODELVIEW);
				glPopMatrix();			
			}			
		}

		void FightLevel::renderPlayers()
		{
			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->draw();
		}

		void FightLevel::tickCamera(const float& delta)
		{
		}

		void FightLevel::tickOverlay(const float& delta)
		{
			if(!(this->_screenHit && this->persistHitDraw(delta)))
				if(this->_screenHit = (this->getPlayerHits() > 0))
					this->decPlayerHits();
		}

		void FightLevel::tickPlayers(const float& delta)
		{
			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->tick(delta);
		}

		void FightLevel::tick(const float &delta)
		{			
			this->tickCamera(delta);
			this->tickOverlay(delta);

			this->tickPlayers(delta);

			blitz::unit::UnitObject *_t;
			for(std::map<std::string, std::vector<blitz::unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
			{
				for(std::vector<blitz::unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end();)
				{
					game::unit::PassiveEnemy* e = dynamic_cast<game::unit::PassiveEnemy*>(*it);
					if(e != NULL && e->hasHitPlayer())
					{
						this->setSourceIndex(1);					
						this->attachAndPlaySound((*this->_sndMgr)["player_hit"]);						
						e->markCompleted();
						if(dynamic_cast<game::unit::SpacePlayer*>(this->_currentPlayer)->gotHit(e->getDamage()) < 0.0f)
							; // Player DEAD
					}

					if((*it)->isComplete())
					{
						_t = *it;
						it = ito->second.erase(it);						
						delete _t;
					}
					else
					{
						(*it)->tick(delta);
						it++;
					}
				}
			}

			// Player-Plasma Hit
			for(std::vector<blitz::unit::UnitObject*>::iterator itb = this->_objects["player_fire"].begin(); itb != this->_objects["player_fire"].end(); itb++)
			{
				for(std::vector<blitz::unit::UnitObject*>::iterator ite = this->_objects["enemy"].begin(); ite != this->_objects["enemy"].end(); ite++)
				{
					blitz::unit::UnitObject* e = dynamic_cast<blitz::unit::UnitObject*>(*ite);
					if(e && (*itb)->collision(*(*ite)))
					{
						(*itb)->markCompleted();
						(*ite)->hit(**itb);								
						Log.debugln("Collided");
						break;
					}
				}
			}				
		}

		void FightLevel::draw(void)
		{
			this->callFirstRender();
			this->renderCamera();
			this->renderBackground();
			
			this->renderPlayers();

			for(std::map<std::string, std::vector<blitz::unit::UnitObject*>>::iterator ito = this->_objects.begin(); ito != this->_objects.end(); ito++)
			{
				glBindTexture(GL_TEXTURE_2D, this->_texMgr->operator[](ito->first.c_str()).first());
				if(ito->first == "enemy")
				{
					for(std::vector<blitz::unit::UnitObject*>::reverse_iterator it = ito->second.rbegin(); it != ito->second.rend(); it++)
						(*it)->draw();		
				}
				else
				{
					for(std::vector<blitz::unit::UnitObject*>::iterator it = ito->second.begin(); it != ito->second.end(); it++)
						(*it)->draw();		
				}
			}

			this->renderCrosshair();
			this->renderHUD();
			this->renderOverlay();
		}

		void FightLevel::onFirstRender()
		{
			this->setSourceIndex(0);
			this->setLooping(true);			
			this->attachAndPlaySound((*this->_sndMgr)["fight"]);
		}

		void FightLevel::spawnEnemy(const blitz::geometry::Triad &start, Model* model)
		{
			this->addUnit("enemy", new game::unit::SkeletonEnemy(start, model));
		}

		long FightLevel::getPlayerHits() const
		{			
			return dynamic_cast<game::unit::SpacePlayer*>(this->_currentPlayer)->numHits();
		}
	
		long FightLevel::decPlayerHits()
		{
			return dynamic_cast<game::unit::SpacePlayer*>(this->_currentPlayer)->decHit();
		}
	
		void FightLevel::resetPlayerHits()
		{			
			dynamic_cast<game::unit::SpacePlayer*>(this->_currentPlayer)->resetHits();
		}

		bool FightLevel::persistHitDraw(float delta)
		{
			this->_lastHitDuration += delta;
			if(this->_lastHitDuration < 0.1f)		
				return true;
			this->hitDrawReset();
			return false;
		}

		void FightLevel::hitDrawReset()
		{
			this->_lastHitDuration = 0.0f;
		}

		void FightLevel::keyPressed(int key)
		{
			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->keyPressed(key);
		}

		void FightLevel::keyReleased(int key)
		{
			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->keyReleased(key);
		}

		void FightLevel::mouseReleased(int button)
		{
			//blitz::geometry::Triad lookAt = this->_camera->getCurrent();
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:								
					//this->playerFire(blitz::geometry::Triad(lookAt.x * 10.0f, lookAt.y * 5.0f, 0.0f));					
					break;
				case GLFW_MOUSE_BUTTON_RIGHT:
					Model* m = (*this->_mdlMgr)["skeleton"];
					if(m != NULL)
					this->spawnEnemy(blitz::geometry::Triad(FightLevel::RAND.randFloat(-50.0f, 50.0f), 
						FightLevel::RAND.randFloat(-4.0f, 4.0f), -100.0f), m);					

					break;
			}

			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->mouseReleased(button);
		}

		void FightLevel::mouseMoved(int x, int y)
		{
			//this->_camera->updateNormalized(x, y);
			for(std::vector<blitz::unit::Player*>::iterator itp = this->_players.begin(); itp != this->_players.end(); itp++)
				(*itp)->mouseMoved(x, y);
		}
	}
}