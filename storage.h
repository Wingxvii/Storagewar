#pragma once

#include "container.h"
#include "object.h"
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

class Storage
{
public:
	Storage();
	virtual ~Storage() final;
	Storage(const Storage& other) = delete;
	Storage& operator=(const Storage& other) = delete;
	Storage(Storage&& other);
	Storage& operator=(Storage&& other);

	// Set the maximum container count.
	void setMaxContainerCount(ContainerType type, int count);
	// add a container
	const ContainerID addContainer(ContainerType type);
	// remove a container
	const bool removeContainer(ContainerID id);
	// Displayer the contain on the storage.
	void displayContainer() const;

	// Store an object of a given type.
	template< class TYPE >
	const ObjectID storeObject(TYPE* object)
	{
		ObjectID storedID = INVALID_OBJECT_ID;
		if (!object)
		{
			return storedID;
		}

		if (object->isRefrigerated())
		{
			for (auto elem : m_refrigeratedContainers)
			{
				if (elem->isEmpty())
				{
					storedID = elem->storeObject(object);
					break;
				}
			}
		}
		else
		{
			for (auto elem : m_nonRefrigeratedContainers)
			{
				if (elem->isEmpty())
				{
					storedID = elem->storeObject(object);
					break;
				}
			}
		}

		return storedID;
	}

	// Return true if the object is in storage
	const bool isObjectInStorage(ObjectID objectID) const;
	// retrieve an object.
	Object* const retrieveObject(ObjectID objectID);

private:
	// number of container
	std::map<ContainerType, int> m_Count;
	// list of refrigerated container
	std::list<AbstractContainer*> m_refrigeratedContainers;
	// list of non refrigerated container.
	std::list<AbstractContainer*> m_nonRefrigeratedContainers;

	mutable std::vector<std::pair<ContainerID, int>> m_StatAccess;
};
