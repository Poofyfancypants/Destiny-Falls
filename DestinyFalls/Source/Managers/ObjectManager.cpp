#include "stdafx.h"
#include "ObjectManager.h"
#include "../Game Objects/iObject.h"
#include <cassert>

void ObjectManager::AddObject(iObject* pObject, unsigned int bucket)
{
	assert(pObject != nullptr && "ObjectManager::AddObject - parameter cannot be null");

	if (bucket >= m_tObjects.size())
		m_tObjects.resize(bucket + 1);

	m_tObjects[bucket].push_back(pObject);

	pObject->AddRef();
}

void ObjectManager::RemoveObject(iObject* pObject, unsigned int bucket)
{

	ObjectVector& vec = m_tObjects[bucket];

	for (unsigned int i = 0; i < vec.size(); i++)
	{
		if (vec[i] == pObject)
		{
			vec.erase(vec.begin() + i);
			pObject->Release();
			break;
		}
	}
}

void ObjectManager::RemoveObject(iObject* pObject)
{
	for (unsigned int i = 0; i < m_tObjects.size(); i++)
	{
		ObjectVector& vec = m_tObjects[i];

		for (unsigned int i = 0; i < vec.size(); i++)
		{
			if (vec[i] == pObject)
			{
				vec.erase(vec.begin() + i);
				pObject->Release();
				return;
			}
		}

	}
}

void ObjectManager::RemoveAll(unsigned int bucket)
{
	// Lock the iterator
	m_bIterating = true;
	{
		// Release the reference to EVERY entity
		ObjectVector& vec = m_tObjects[bucket];
		for (unsigned int i = 0; i < vec.size(); i++)
		{
			vec[i]->Release();
			vec[i] = nullptr;
		}

		vec.clear();
	}
	// Unlock the iterator
	m_bIterating = false;
}

void ObjectManager::RemoveAll(void)
{

	// Lock the iterator
	m_bIterating = true;
	{
		// Release every entity
		for (unsigned int bucket = 0; bucket < m_tObjects.size(); bucket++)
		{
			ObjectVector& vec = m_tObjects[bucket];
			for (unsigned int i = 0; i < vec.size(); i++)
			{
				vec[i]->Release();
				vec[i] = nullptr;
			}
		}
	}
	// Unlock the iterator
	m_bIterating = false;


	// Collapse the table
	m_tObjects.clear();
}

void ObjectManager::UpdateAll(float elapsedTime)
{
	// Validate the iteration state
	assert(m_bIterating == false && "ObjectManager::UpdateAll - cannot update while iterating");

	// Lock the iterator
	m_bIterating = true;
	{
		// Update every entity
		for (unsigned int bucket = 0; bucket < m_tObjects.size(); bucket++)
		{
			ObjectVector& vec = m_tObjects[bucket];
			for (unsigned int i = 0; i < vec.size(); i++)
				vec[i]->Update(elapsedTime);
		}
	}
	// Unlock the iterator
	m_bIterating = false;
}

void ObjectManager::RenderAll(void)
{
	// Validate the iteration state
	assert(m_bIterating == false && "ObjectManager::RenderAll - cannot render while iterating");

	// Lock the iterator
	m_bIterating = true;
	{
		// Render every entity
		for (unsigned int bucket = 0; bucket < m_tObjects.size(); bucket++)
		{
			ObjectVector& vec = m_tObjects[bucket];
			for (unsigned int i = 0; i < vec.size(); i++)
				vec[i]->Render();
		}
	}
	// Unlock the iterator
	m_bIterating = false;
}

void ObjectManager::CheckCollisions(unsigned int bucket1, unsigned int bucket2)
{
	assert(m_bIterating == false && "ObjectManager::CheckCollisions - cannot collide while iterating");

	if (bucket1 >= m_tObjects.size() || bucket2 >= m_tObjects.size()
		|| m_tObjects[bucket1].size() == 0 || m_tObjects[bucket2].size() == 0)
		return;

}
