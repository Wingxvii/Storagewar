#pragma once

#include "object.h"
#include "storage.h"

#include <memory>

using namespace StorageWarTypes;

// Class representing a player in the game
class Player
{
public:
	Player(const char* name);

	// Store an object
	bool storeObject(std::shared_ptr<Object> object);

	// Create the storage capacity for this player
	void CreateInitialStorage(int refridgeratedCount, int nonRefridgeratedCount);

	// Retrieve an object
	std::shared_ptr<Object> const retrieveObject(int objectID);

	// Diplay the contain of the player storage.
	void printStorage() const;

	// Get the name of the player
	const char* getName() const;

private:
	const char* m_Name;
	std::unique_ptr<Storage> m_Storage;

};