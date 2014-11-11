#include "stdafx.h"
#include "ObjectManager.h"
#include "../Game Objects/iObject.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
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
	//Classic SGD Collisions

	assert(m_bIterating == false && "ObjectManager::CheckCollisions - cannot collide while iterating");

	if (bucket1 >= m_tObjects.size() || bucket2 >= m_tObjects.size()
		|| m_tObjects[bucket1].size() == 0 || m_tObjects[bucket2].size() == 0)
		return;

	m_bIterating = true;

	if (bucket1 != bucket2)
	{
		ObjectVector* Vec1 = &m_tObjects[bucket1];
		ObjectVector* Vec2 = &m_tObjects[bucket2];

		if (Vec2->size() < Vec1->size())
		{
			ObjectVector* temp = Vec1;
			Vec1 = Vec2;
			Vec2 = temp;
		}

		ObjectVector& vec1 = *Vec1;
		ObjectVector& vec2 = *Vec2;

		for (unsigned int i = 0; i < vec1.size(); i++)
		{
			for (unsigned int j = 0; j < vec2.size(); j++)
			{
				if (vec1[i] == vec2[j])
					continue;

				SGD::Rectangle object1 = vec1[i]->GetRect();
				SGD::Rectangle object2 = vec2[j]->GetRect();

				if (object1.IsIntersecting(object2) == true)
				{
					vec1[i]->HandleCollision(vec2[j]);
					vec2[j]->HandleCollision(vec1[i]);
				}
			}
		}
	}
	else
	{
		ObjectVector& vec = m_tObjects[bucket1];

		for (unsigned int i = 0; i < vec.size()-1; i++)
		{
			for (unsigned int j = 0; j < vec.size(); j++)
			{
				if (vec[i] == vec[j])
					continue;

				SGD::Rectangle object1 = vec[i]->GetRect();
				SGD::Rectangle object2 = vec[j]->GetRect();

				if (object1.IsIntersecting(object2) == true)
				{
					vec[i]->HandleCollision(vec[j]);
					vec[j]->HandleCollision(vec[i]);
				}
			}
		}
	}
	m_bIterating = false;
}
