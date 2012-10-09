/*
 * SpacePlayer.cpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#include "SpacePlayer.hpp"

namespace game {
	namespace unit {

		SpacePlayer::SpacePlayer() 
		{			
			this->createSoundSources(1);
			this->_strafeStep = 0.1f;
			this->_isCrouched = false;
			this->_numHits = 0;
			this->_health = this->_energy = 1.0f;
			this->_regenEnergy = 0.05f;
			this->_regenHealth = 0.01f;
		}

		SpacePlayer::~SpacePlayer() 
		{
			Log.debug("Destroying SpacePlayer");
		}

		void SpacePlayer::draw(void)
		{							
		}

		void SpacePlayer::tick(const float& delta)
		{
			if(this->_health < 1.0f)
				this->_health = min(this->_health + delta*this->_regenHealth, 1.0f);
			if(this->_energy < 1.0f)
				this->_energy = min(this->_energy + delta*this->_regenEnergy, 1.0f);
		}

		bool SpacePlayer::collision(blitz::unit::UnitObject& obj)
		{
			return obj.getState()->current.z > -3.0f;
		}

		void SpacePlayer::hit(UnitObject& obj) 
		{
			this->_numHits++;			
			blitz::unit::DamageObject* dmgObj = dynamic_cast<blitz::unit::DamageObject*>(&obj);
			if(dmgObj)
			{
				if(this->_health -= dmgObj->getDamage())
				{
					this->attachAndPlaySound((*this->_sndMgr)["player_hit"]);
				}
			}
		}
		
		long SpacePlayer::decHit()
		{
			return this->_numHits > 0? --this->_numHits : 0;
		}

		long SpacePlayer::numHits() const
		{
			return this->_numHits;
		}

		void SpacePlayer::resetHits()
		{
			this->_numHits = 0;			
		}

		void SpacePlayer::fireBullet()
		{
			if((this->_energy - 0.1f) >= 0)
			{
				this->_energy -= 0.1f;
				blitz::geometry::Triad lookAt = this->_level->getCamera()->getCurrent();
				this->_level->addUnit("player_fire", new game::unit::PlasmaBullet(blitz::geometry::Triad(lookAt.x * 10.0f, lookAt.y * 5.0f, 0.0f)));
			}
			else
				this->attachAndPlaySound((*this->_sndMgr)["player_empty"]);
		}

		void SpacePlayer::moveLeft()
		{
			this->_level->getCamera()->updateNormalized(-this->_strafeStep, 0.0f);
		}

		void SpacePlayer::moveRight()
		{
			this->_level->getCamera()->updateNormalized(this->_strafeStep, 0.0f);
		}

		void SpacePlayer::doCrouch(const bool& action)
		{
			if(action)
			{
				if(!this->_isCrouched)
				{
					this->_isCrouched = true;
					this->_level->getCamera()->updateNormalized(0.0f, -5.0f*this->_strafeStep);
				}
			}
			else
			{
				this->_isCrouched = false;
				this->_level->getCamera()->updateNormalized(0.0f, +5.0f*this->_strafeStep);
			}
		}

		void SpacePlayer::doJump()
		{
			this->_level->getCamera()->updateNormalized(0.0f, -this->_strafeStep);
		}

		void SpacePlayer::mousePressed(int button)
		{
		}

		void SpacePlayer::mouseReleased(int button)
		{
			switch(button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:								
					this->fireBullet();
					break;
			}
		}

		void SpacePlayer::mouseMoved(int x, int y)
		{
			this->_level->getCamera()->updateNormalized(x, y);
		}

		void SpacePlayer::keyPressed(int key)
		{			
			switch(key)
			{	
			case 'W':
				this->doJump();
				break;
			case 'A':
				this->moveLeft();
				break;
			case 'S':
				this->doCrouch(true);
				break;
			case 'D':
				this->moveRight();
				break;
			}
		}

		void SpacePlayer::keyReleased(int key)
		{			
			blitz::Camera* camera = this->_level->getCamera();
			switch(key)
			{	
			case 'S':
				this->doCrouch(false);
				break;
			}			
		}
	}
}