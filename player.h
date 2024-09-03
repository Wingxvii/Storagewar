#pragma once

#include "storage.h"
#include "object.h"

#include <memory>

using namespace StorageWarTypes;

class Player
{
public:

	Player(const char* name);

	// Store an object
	bool storeObject(std::shared_ptr<Object> object);

	void CreateInitialStorage(int refridgeratedCount, int nonRefridgeratedCount);

	// Retrieve an object
	std::shared_ptr<Object> const retrieveObject(int objectID);
	// Diplay the contain of the player storage.
	void printStorage() const;

	const char* getName() const;

private:
	const char* m_Name;
	std::unique_ptr<Storage> m_Storage;

};