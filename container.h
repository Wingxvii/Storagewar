#pragma once

// TODO: We dont need this entire class, remove it all and just use the storage

#include <string>
#include "object.h"

using ContainerType = std::string;
using ContainerID = std::string;
static const ContainerID INVALID_CONTAINER_ID = "INVALID_OBJECT_ID";

enum class EContainerType : char
{
	Refrigerated,
	NonRefrigerated,
	MAX
};

static std::string ContainerTypes[(char)(EContainerType::MAX)] = {
	"Refrigerated",
	"NonRefrigerated"
};

#define CT(t)				ContainerTypes[(char)t]
#define CT_NonRefrigerated	CT(EContainerType::NonRefrigerated)
#define CT_Refrigerated		CT(EContainerType::Refrigerated)

class AbstractContainer
{
public:
	AbstractContainer(ContainerID id) : m_id(id), m_isEmpty(true), m_isRefrigerated(false) {
		m_obj = nullptr;
	}
	virtual ~AbstractContainer() = 0 {};

	// Return true if refrigerated.
	const bool isRefrigerated() const { return m_isRefrigerated; }
	// Return true if empty.
	const bool isEmpty() const { return m_isEmpty; }
	// Return the type of the container
	virtual const ContainerType getType() const = 0;

	// Store an object.
	template< typename Object >
	const ObjectID storeObject(Object* object)
	{
		m_isEmpty = false;
		m_obj = object;
		return m_obj->getID();
	}

	// Return the object ID	
	ObjectID getStoredObjectID() const;
	// Return the object type
	ObjectType getStoredObjectType() const;
	// Retrieve an object.
	Object* const retrieveObject();

	// Return an ID
	ContainerID getId() const { return m_id; }

	// Create a container.
	static AbstractContainer* CreateContainer(ContainerType type);

protected:
	ContainerID m_id;
	bool m_isRefrigerated;
	bool m_isEmpty;
	Object* m_obj;
private:
	static int m_containerCounter;
};

class RefrigeratedContainer : public AbstractContainer
{
public:
	RefrigeratedContainer(ContainerID id);
	virtual ~RefrigeratedContainer() override;

	virtual const ContainerType getType() const override;
};

class NonRefrigeratedContainer : public AbstractContainer
{
public:
	NonRefrigeratedContainer(ContainerID id);
	virtual ~NonRefrigeratedContainer() override;

	virtual const ContainerType getType() const override;
};
