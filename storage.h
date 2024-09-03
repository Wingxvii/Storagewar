#pragma once

#include "container.h"
#include "object.h"

#include <memory>
#include <vector>

using namespace StorageWarTypes;

// Class used to store up to a maximum amount of refrigerated and non-refrigerated objects
class Storage
{
public:
	// Set the maximum container count.
	void setMaxContainerCount(EContainerType type, int count);

	// Displayer the contain on the storage.
	void printContents() const;

	// Store an object into it's container, if possible.
	const bool storeObject(std::shared_ptr<Object> object);

	// retrieve an object, erasing it from it's container
	std::shared_ptr<Object> const retrieveObjectByID(int objectID);

private:
	// list of refrigerated objects
	std::vector<std::shared_ptr<Object>> m_refrigeratedContainer;
	// list of non refrigerated objects.
	std::vector<std::shared_ptr<Object>> m_nonRefrigeratedContainer;

	int m_maxRefrigeratedContainerSize = 0;
	int m_maxNonRefrigeratedContainerSize = 0;
};