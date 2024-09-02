#pragma once

#include "storage.h"
#include "object.h"

#include <string>
// TODO: change this to a class, theres no reason for this to be a struct 
struct Player
{
	// TODO: Move these to private
	// TODO: Change this to char*
	const std::string m_Name;
	// TODO: Smart pointer
	Storage m_Storage;

	Player(const char* name) : m_Name(name)
	{}

	//TODO: returning the object ID is unexpected, we should return a bool instead with the results of the storage attempt
	// Store an object
	ObjectID storeObject(Object* object);

	// Retrieve an object
	Object* const retrieveObject(ObjectID objectID);
	// Diplay the contain of the player storage.
	// TODO: Rename this to PrintStorage for clarity
	void displayStorage() const;
};
