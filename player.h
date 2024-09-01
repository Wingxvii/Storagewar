#pragma once

#include "storage.h"
#include "object.h"

#include <string>

struct Player
{
	const std::string m_Name;
	Storage m_Storage;

	Player(const char* name) : m_Name(name)
	{}

	// Store an object
	ObjectID storeObject(Object* object);
	// Retrieve an object
	Object* const retrieveObject(ObjectID objectID);
	// Diplay the contain of the player storage.
	void displayStorage() const;
};
