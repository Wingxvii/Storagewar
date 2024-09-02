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
	// TODO: dont need vitural final here, they cancel eachother out
	virtual ~Storage() final;

	// TODO: we dont need any of these, plus they are confusing, unrealistic, and not doing what you would expect them to
	Storage(const Storage& other) = delete;
	Storage& operator=(const Storage& other) = delete;
	Storage(Storage&& other);
	Storage& operator=(Storage&& other);

	// TODO: use the enum here
	// Set the maximum container count.
	void setMaxContainerCount(ContainerType type, int count);

	// TODO: remove these two functions, and use max containers instead
	// add a container
	const ContainerID addContainer(ContainerType type);
	// remove a container
	const bool removeContainer(ContainerID id);

	// TODO: Rename this to printContents for clarity
	// Displayer the contain on the storage.
	void displayContainer() const;

	// TODO: Move implementation to cpp file
	// Store an object of a given type.
	// TODO: Since we already include object, just use the object class
	template< class TYPE >
	const ObjectID storeObject(TYPE* object)
	{
		// TODO: Validate using assert instead of returning something that is supposed let a player win the game
		ObjectID storedID = INVALID_OBJECT_ID;
		if (!object)
		{
			return storedID;
		}

		if (object->isRefrigerated())
		{
			// TODO: just use an array list here
			for (auto container : m_refrigeratedContainers)
			{
				if (container->isEmpty())
				{
					storedID = container->storeObject(object);
					break;
				}
			}
		}
		else
		{
			for (auto container : m_nonRefrigeratedContainers)
			{
				if (container->isEmpty())
				{
					storedID = container->storeObject(object);
					break;
				}
			}
		}

		// TODO: return if successful
		return storedID;
	}

	// Return true if the object is in storage
	const bool isObjectInStorage(ObjectID objectID) const;
	// retrieve an object.
	Object* const retrieveObject(ObjectID objectID);

private:
	// TODO: dont need to store and manage this, just get the count of the array lists
	// number of container
	std::map<ContainerType, int> m_Count;

	//TODO: Change these to the array list of all stored objects instead
	// list of refrigerated container
	std::list<AbstractContainer*> m_refrigeratedContainers;
	// list of non refrigerated container.
	std::list<AbstractContainer*> m_nonRefrigeratedContainers;

	// TODO: This is not used anymore
	mutable std::vector<std::pair<ContainerID, int>> m_StatAccess;
};
