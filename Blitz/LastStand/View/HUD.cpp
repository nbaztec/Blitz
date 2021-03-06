/*
 * HUD.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */
#include <iostream>
#include "HUD.hpp"

namespace game {
	namespace view {
		HUD::HUD()	
		{
			
		}

		HUD::~HUD()
		{			
		}	
		
		void HUD::setMetrics(const float& xl, const float& yl, const float& xh, const float& yh, const float& padX, const float& padY)
		{
			this->_xLow = xl;
			this->_yLow = yl;
			this->_xHigh = xh;
			this->_yHigh = yh;
			this->_padX = padX;
			this->_padY = padY;
			this->_width = (xh - xl);
			this->_height = (yh - yl);
			this->_realWidth = this->_width - 2*padX;
			this->_realHeight = this->_height - 2*padY;			
		}

		void HUD::tick(const float &delta)
		{
			
		}

		void HUD::draw(void)
		{
			/*
			glDisable(GL_DEPTH_TEST);
			glPushMatrix();
				glLoadIdentity();		
				glMatrixMode(GL_PROJECTION);
				glPushMatrix();		
					glLoadIdentity();
					this->renderBox();
					this->renderEnergyBar();
					this->renderHealthBar();
					this->renderMiniMap();				
				glPopMatrix();
				glMatrixMode(GL_MODELVIEW);
			glPopMatrix();
			*/
		}

		void HUD::align(int direction)
		{
			float tx = 0.0f;
			float ty = 0.0f;

			if(direction & Alignment::alLeft)
				tx = this->_xLow + this->_padX;
			else if(direction & Alignment::alRight)
				tx = this->_xHigh - this->_padX;
			if(direction & Alignment::alTop)
				ty = this->_yHigh - this->_padY;
			else if(direction & Alignment::alBottom)
				ty = this->_yLow + this->_padY;
			glTranslatef(tx, ty, 0.0f);
		}		

		void HUD:: renderBox()
		{
			glColor4f(0.9f, 0.9f, 0.9f, 0.25f);
			glBegin(GL_QUADS);
				glTexCoord2f(0.0f, 0.0f); glVertex3f(this->_xLow, this->_yHigh, 0.0f);
				glTexCoord2f(1.0f, 0.0f); glVertex3f(this->_xHigh, this->_yHigh, 0.0f);
				glTexCoord2f(1.0f, 1.0f); glVertex3f(this->_xHigh, this->_yLow, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(this->_xLow, this->_yLow, 0.0f);
			glEnd();
		}

		void HUD:: renderHealthBar(const float& health)
		{
			glPushMatrix();
				float v = std::max(health, 0.0f);
				float op = 0.65f;
				float bw = 0.04f;
				glBegin(GL_QUADS);
					glColor4f(0.9f, 0.0f, 0.0f, op); 
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(-bw,  0.0f, 0.0f);

					glColor4f(0.1f, 0.0f, 0.0f, op); 
					glVertex3f(-bw, this->_realHeight*v, 0.0f);
					glVertex3f(0.0f, this->_realHeight*v, 0.0f);
				glEnd();				
			glPopMatrix();
		}

		void HUD:: renderEnergyBar(const float& energy)
		{
			glPushMatrix();
				float v = std::max(energy, 0.0f);
				float op = 0.65f;
				float bw = 0.04f;
				glBegin(GL_QUADS);
					glColor4f(0.0f, 0.9f, 0.9f, op); 
					glVertex3f(0.0f, 0.0f, 0.0f);
					glVertex3f(-bw,  0.0f, 0.0f);

					glColor4f(0.0f, 0.1f, 0.1f, op); 
					glVertex3f(-bw, this->_realHeight*v, 0.0f);
					glVertex3f(0.0f, this->_realHeight*v, 0.0f);
				glEnd();
			glPopMatrix();
		}

		void HUD:: renderRadar(GLuint texture, const float& width, const float& height)
		{
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texture);
			glPushMatrix();
			glBegin(GL_QUADS);												
				glTexCoord2f(1.0f, 1.0f); glVertex3f(-width,  height, 0.0f);
				glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f, height, 0.0f);						
				glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);						
				glTexCoord2f(1.0f, 0.0f); glVertex3f(-width,  0.0f, 0.0f);						
			glEnd();
			glPopMatrix();
			glDisable(GL_TEXTURE_2D);
		}

		void HUD::renderMarkers(const float& x, const float& y)
		{
			glPushMatrix();
				glTranslatef(x*0.13f, 0.0f, 0.0f);
				glEnable(GL_SMOOTH);
				glBegin(GL_TRIANGLES);
					glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
					glVertex3f(-0.01f, 0.0f, 0.0f);
					glVertex3f(0.01f, 0.0f, 0.0f);
					glVertex3f(0.0f, 0.018f, 0.0f);
				glEnd();
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.2f, y*0.14f + 0.3f, 0.0f);
				glRotatef(-90.0f, 0.0f, 0.0f, 1.0f);
				glEnable(GL_SMOOTH);
				glBegin(GL_TRIANGLES);
					glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
					glVertex3f(0.012f, 0.0f, 0.0f);
					glVertex3f(-0.012f, 0.0f, 0.0f);
					glVertex3f(0.0f, 0.018f, 0.0f);
				glEnd();
			glPopMatrix();
		}

		void HUD::renderEnemyMap(std::vector<blitz::unit::UnitObject*>& enemyList, const float& mapWidth, const float& mapHeight, const float& radarWidth, const float& radarHeight)
		{
			glPushMatrix();
				glEnable(GL_POINT_SMOOTH);				
				glPointSize(6.0f);
				glColor3f(1.0f, 0.2f, 0.2f);				
				for(std::vector<blitz::unit::UnitObject*>::iterator ite = enemyList.begin(); ite != enemyList.end(); ite++)
				{
					glPushMatrix();										
						glBegin(GL_POINTS);
							float x = ((*ite)->getState()->current.x/mapWidth)*0.26f;
							float y = -((*ite)->getState()->current.z/mapHeight)*radarHeight;
							glVertex3f(x, y, 0.0f);
						glEnd();
					glPopMatrix();
				}
			glPopMatrix();
		}

	}
}