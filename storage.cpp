#include "storage.h"

#include <algorithm>
#include <assert.h>

using namespace StorageWarTypes;

void Storage::setMaxContainerCount(EContainerType type, int count)
{
	assert(count >= 0 && "Storage::setMaxContainerCount: count is less than 0");

	if (type == EContainerType::Refrigerated)
	{
		m_maxRefrigeratedContainerSize = count;
	}
	else if (type == EContainerType::NonRefrigerated)
	{
		m_maxNonRefrigeratedContainerSize = count;
	}
}


bool Storage::storeObject(const std::shared_ptr<Object>& object)
{
	assert(object.get() && "Storage::storeObject: object is invalid");

	if (object->isRefrigerated() && m_refrigeratedContainer.size() < m_maxRefrigeratedContainerSize)
	{
		m_refrigeratedContainer.push_back(object);
		return true;
	}
	else if (m_nonRefrigeratedContainer.size() < m_maxNonRefrigeratedContainerSize)
	{
		m_nonRefrigeratedContainer.push_back(object);
		return true;
	}

	return false;
}

std::shared_ptr<Object> Storage::retrieveObjectByID(int objectID)
{
	std::shared_ptr<Object> foundObject = nullptr;

	auto iter = std::find_if(m_nonRefrigeratedContainer.cbegin(), m_nonRefrigeratedContainer.cend(), [objectID](const std::shared_ptr<Object>& object)
		{
			return object->getID() == objectID;
		});
	if (iter != m_nonRefrigeratedContainer.cend())
	{
		foundObject = *iter;
		m_nonRefrigeratedContainer.erase(iter);
	}

	iter = std::find_if(m_refrigeratedContainer.cbegin(), m_refrigeratedContainer.cend(), [objectID](const std::shared_ptr<Object>& object)
		{
			return object->getID() == objectID;
		});
	if (iter != m_refrigeratedContainer.cend())
	{
		foundObject = *iter;
		m_refrigeratedContainer.erase(iter);
	}

	return foundObject;
}

void Storage::printContents() const
{
	std::printf("Display the content the storage\n");
	std::printf("	Refrigerated content:\n");
	for (const auto& object : m_refrigeratedContainer) {
		printf("	ObjectID: %i \t\t %s\n", object->getID(), object->getName());
	}
	std::printf("\n	NonRefrigerated content:\n");
	for (const auto& object : m_nonRefrigeratedContainer) {
		printf("	ObjectID: %i \t\t %s\n", object->getID(), object->getName());
	}
	std::printf("-----------\n");
}