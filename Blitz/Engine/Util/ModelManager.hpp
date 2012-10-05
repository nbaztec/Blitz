/*
 * ModelManager.hpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#pragma once

#include <GL/glfw.h>
#include <map>
#include "cal3d/model.h"

class ModelManager
{
protected:
	std::map<std::string, Model*> _models;
public:
	ModelManager(void);
	virtual ~ModelManager(void);
	
	bool load(const char* key, const char* dir);
	void remove(const char* key);
	bool has_texture(const char* key);
	Model* operator[](const char* key);
	void updateModels(const float& delta);
};