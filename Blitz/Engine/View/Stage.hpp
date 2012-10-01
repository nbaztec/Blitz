/*
 * Stage.hpp
 *
 *  Created on: Aug 29, 2012
 *      Author: Nisheeth
 */

#pragma once

#include <vector>
#include <map>
#include <algorithm>

#include <GL/glfw.h>
#include "../Core/Interface/TickedPainter.hpp"
#include "../Core/Interface/InputListener.hpp"
#include "../Core/Coordinate.hpp"
#include "../Core/Camera.hpp"
#include "../Unit/UnitObject.hpp"
#include "../Util/TextureManager.hpp"
#include "../Util/ModelManager.hpp"
#include "Level.hpp"

namespace blitz {
	namespace view {
		class Stage : virtual public TickedPainter, virtual public InputListener {
		protected:
			std::map<std::string, std::vector<view::Level*>> _levels;
			TextureManager* _texMgr;
			ModelManager* _mdlMgr;
			Level* _currentLevel;
			Camera* _camera;

		public:			
			Stage();
			virtual ~Stage();
			void setTextureManager(TextureManager* texMgr);
			void setModelManager(ModelManager* mdlMgr);
			
			void setCamera(const geometry::Triad& current, const geometry::Dyad& screen, const geometry::Quad& bounds, bool fixed);
			Camera* getCamera() const;
			virtual void screenChanged(int width, int height);

			void addLevel(const std::string& key, view::Level* level);		
			Level* removeLevel(const std::string& key, const int& index);
			virtual Level* setLevel(const std::string& key, const int& index);
			virtual Level* setLevel(const std::string& key, const Level* level);

			virtual void mousePressed(int button);
			virtual void mouseReleased(int button);
			virtual void mouseMoved(int x, int y);
			virtual void mouseWheelMoved(int pos);						

			virtual void keyPressed(int key);
			virtual void keyReleased(int key);
			virtual void keyCharPressed(int character);
			virtual void keyCharReleased(int character);
		};
	}
}