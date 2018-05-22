#include "Scene.h"
#include "AVDirector.h"

Scene::Scene(void)
{
}


Scene::~Scene(void)
{
}

void Scene::addObject(AVBase* object)
{
	m_vector.push_back(object);
}

void Scene::deleteObject(AVBase* object)
{
	for(int i = 0; i < m_vector.size(); i++)
	{
		if( m_vector[i] == object )
			m_vector.erase(m_vector.begin()+i);
	}
}

void Scene::deleteAllObject()
{
	m_vector.clear();
}

void Scene::InnerUpdate()
{
	std::vector<AVBase*>::iterator iter;

	for(iter = m_vector.begin(); iter != m_vector.end(); iter++)
	{
		(*iter)->Update();
		(*iter)->Render();
	}
}

void Scene::ChangeScene(Scene* scene, bool isDelete)
{
	if(isDelete) 
	{
		delete AVDirector::GetDiector()->GetScene();
		AVDirector::GetDiector()->SetScene(NULL);
	}
	AVDirector::GetDiector()->SetScene(scene);
}