#include "storage.h"
#include <algorithm>

Storage::Storage()
{
	for (auto type : ContainerTypes)
	{
		m_Count.insert(std::pair<ContainerType, int>(type, 0));
	}
}

Storage::~Storage()
{
	for (auto container : m_nonRefrigeratedContainers)
	{
		delete container;
	}
	for (auto container : m_refrigeratedContainers)
	{
		delete container;
	}
}

Storage::Storage(Storage&& other)
{
	std::swap(m_Count, other.m_Count);
	std::swap(m_refrigeratedContainers, other.m_refrigeratedContainers);
	std::swap(m_nonRefrigeratedContainers, other.m_nonRefrigeratedContainers);
	std::swap(m_StatAccess, other.m_StatAccess);

	other.m_Count.clear();
	for (auto type : ContainerTypes)
	{
		other.m_Count.insert(std::pair<ContainerType, int>(type, 0));
	}
	other.m_refrigeratedContainers.clear();
	other.m_nonRefrigeratedContainers.clear();
	other.m_StatAccess.clear();
}

Storage& Storage::operator=(Storage&& other)
{
	if (this != &other)
	{
		for (auto container : m_nonRefrigeratedContainers)
		{
			delete container;
		}
		for (auto container : m_refrigeratedContainers)
		{
			delete container;
		}

		std::swap(m_Count, other.m_Count);
		std::swap(m_refrigeratedContainers, other.m_refrigeratedContainers);
		std::swap(m_nonRefrigeratedContainers, other.m_nonRefrigeratedContainers);
		std::swap(m_StatAccess, other.m_StatAccess);

		other.m_Count.clear();
		for (auto type : ContainerTypes)
		{
			other.m_Count.insert(std::pair<ContainerType, int>(type, 0));
		}
		other.m_refrigeratedContainers.clear();
		other.m_nonRefrigeratedContainers.clear();
		other.m_StatAccess.clear();
	}

	return *this;
}

void Storage::setMaxContainerCount(ContainerType type, int count)
{
	auto it = m_Count.find(type);
	if (it != m_Count.end())
	{
		m_Count[type] = count;
	}
}

const ContainerID Storage::addContainer(ContainerType type)
{
	if (m_Count.find(type) == m_Count.end())
	{
		return INVALID_CONTAINER_ID;
	}

	const int maxCount = m_Count[type];

	if (type == CT_Refrigerated && m_refrigeratedContainers.size() >= maxCount)
	{
		return 	INVALID_CONTAINER_ID;
	}
	if (type == CT_NonRefrigerated && m_nonRefrigeratedContainers.size() >= maxCount)
	{
		return 	INVALID_CONTAINER_ID;
	}

	AbstractContainer* container = AbstractContainer::CreateContainer(type);

	if (container == nullptr)
	{
		return INVALID_CONTAINER_ID;
	}

	if (container->getType() == CT_Refrigerated)
	{
		m_refrigeratedContainers.push_back(container);
	}
	else if (container->getType() == CT_NonRefrigerated)
	{
		m_nonRefrigeratedContainers.push_back(container);
	}

	return container->getId();
}

const bool Storage::removeContainer(ContainerID id)
{
	bool isFound = false;

	for (auto iter = m_refrigeratedContainers.begin(); iter != m_refrigeratedContainers.end(); ++iter)
	{
		if ((*iter)->getId() == id)
		{
			isFound = true;
			m_refrigeratedContainers.erase(iter);
			break;
		}
	}

	if (isFound == false)
	{
		for (auto iter = m_nonRefrigeratedContainers.begin(); iter != m_nonRefrigeratedContainers.end(); ++iter)
		{
			if ((*iter)->getId() == id)
			{
				isFound = true;
				m_nonRefrigeratedContainers.erase(iter);
				break;
			}
		}
	}

	return isFound;
}

const bool Storage::isObjectInStorage(ObjectID objectID) const
{
	// TODO: just find in the array lists instead of doing all this

	auto isInStoragePred = [=](AbstractContainer* container) {
		if (!container)
		{
			return false;
		}
		return container->getStoredObjectID() == objectID;
		};
	auto iter = std::find_if(m_nonRefrigeratedContainers.cbegin(), m_nonRefrigeratedContainers.cend(), isInStoragePred);
	if (iter != m_nonRefrigeratedContainers.cend())
	{
		bool isFound = false;
		for (auto elem : m_StatAccess)
		{
			if (elem.first == (*iter)->getId())
			{
				isFound = true;
				elem.second++;
			}
		}
		if (!isFound)
		{
			m_StatAccess.push_back(std::make_pair((*iter)->getId(), 1));
		}

		return true;
	}
	iter = std::find_if(m_refrigeratedContainers.cbegin(), m_refrigeratedContainers.cend(), isInStoragePred);
	if (iter != m_refrigeratedContainers.cend())
	{
		bool isFound = false;
		for (auto elem : m_StatAccess)
		{
			if (elem.first == (*iter)->getId())
			{
				isFound = true;
				elem.second++;
			}
		}
		if (!isFound)
		{
			m_StatAccess.push_back(std::make_pair((*iter)->getId(), 1));
		}

		return true;
	}
	return false;
}

Object* const Storage::retrieveObject(ObjectID objectID)
{
	// TODO: just find in the array lists instead of doing all this

	Object* retrievedObject = nullptr;
	if (!isObjectInStorage(objectID))
	{
		return retrievedObject;
	}

	// TODO: ??????
#define ROFC(C)\
	for (auto container = C.begin(); container != C.end(); ++container)\
	{\
		if ((*container)->getStoredObjectID() == objectID)\
		{\
			retrievedObject = (*container)->retrieveObject();\
			bool isFound = false;\
			for (auto elem : m_StatAccess)\
			{\
				if (elem.first == (*container)->getId())\
				{\
					isFound = true;\
					elem.second++;\
				}\
			}\
			if (!isFound)\
			{\
				m_StatAccess.push_back(std::make_pair((*container)->getId(), 1));\
			}\
		}\
		if(retrievedObject)\
			break;\
	}

	ROFC(m_refrigeratedContainers);
	if (!retrievedObject)
	{
		ROFC(m_nonRefrigeratedContainers);
	}

	return retrievedObject;
}

void Storage::displayContainer() const
{
	std::printf("Display the content the storage\n");
	std::printf("Refrigerated content:\n");
	for (auto container : m_refrigeratedContainers) {
		if (container->getStoredObjectID() != INVALID_OBJECT_ID)
		{
			printf("ObjectID: %s \t\t %s\n", container->getStoredObjectID().c_str(), container->getStoredObjectType().c_str());
		}
	}
	std::printf("\nNonRefrigerated content:\n");
	for (auto container : m_nonRefrigeratedContainers) {
		if (container->getStoredObjectID() != INVALID_OBJECT_ID)
		{
			printf("ObjectID: %s \t\t %s\n", container->getStoredObjectID().c_str(), container->getStoredObjectType().c_str());
		}
	}
	std::printf("-----------\n");
}
