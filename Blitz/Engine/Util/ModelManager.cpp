/*
 * ModelManager.cpp
 *
 *  Created on: Sep 20, 2012
 *      Author: Nisheeth
 */
 
#include "ModelManager.hpp"

ModelManager::ModelManager(void)
{
}

ModelManager::~ModelManager(void)
{
	std::map<std::string, Model*>::iterator it;
	while(!this->_models.empty())
	{				
		it = this->_models.begin();		
		it->second->onShutdown();
		delete it->second;
		this->_models.erase(it);
	}
}

Model* ModelManager::operator[](const char* key)
{
	
	if(this->_models.find(key) != this->_models.end())
		return this->_models[key];
	else
		return NULL;
}

void ModelManager::load(const char* key, const char* dir)
{
	Model* pModel = new Model();	
	pModel->setPath(dir);
	if(!pModel->onInit())
	{
		delete pModel;
		std::cerr << "Model initialization failed! (skeleton)" << std::endl;		
	}
	else
	{
		std::cout << "Model loaded! (" << key << ")" << std::endl;
		this->_models[key] = pModel;
	}
}

void ModelManager::remove(const char* key)
{
	this->_models.erase(this->_models.find(key));
}

bool ModelManager::has_texture(const char* key)
{
	return this->_models.find(key) != this->_models.end();
}

void ModelManager::updateModels(const float& delta)
{
	for(std::map<std::string, Model*>::iterator it = this->_models.begin(); it != this->_models.end(); it++)
		it->second->onUpdate(delta);
}