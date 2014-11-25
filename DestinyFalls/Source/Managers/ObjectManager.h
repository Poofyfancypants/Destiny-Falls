#pragma once

#include <vector>

class iObject;

class ObjectManager
{
public:
	ObjectManager(void) = default;
	~ObjectManager(void) = default;

	void AddObject(iObject* pObject, unsigned int bucket);
	void RemoveObject(iObject* pObject, unsigned int bucket);
	void RemoveObject(iObject* pObject);
	void RemoveAll(unsigned int bucket);
	void RemoveAll(void);

	void UpdateAll(float elapsedTime);
	void RenderAll(void);

	unsigned int GetNumObjects();

	void CheckCollisions(unsigned int bucket1, unsigned int bucket2);

private:
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator= (const ObjectManager&) = delete;

	typedef std::vector<iObject*> ObjectVector;
	typedef std::vector<ObjectVector> ObjectTable;

	ObjectTable m_tObjects;
	bool		m_bIterating = false;
};