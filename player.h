#pragma once

#include "object.h"
#include "storage.h"

#include <memory>

// Class representing a player in the game
class Player
{
public:
	Player(const char* name);

	// Store an object
	bool storeObject(const std::shared_ptr<Object>& object);

	// Create the storage capacity for this player
	void createInitialStorage(int refrigeratedCount, int nonRefrigeratedCount);

	// Retrieve an object
	std::shared_ptr<Object> retrieveObject(int objectID);

	// Diplay the contain of the player storage.
	void printStorage() const;

	// Get the name of the player
	const char* getName() const;

private:
	const char* m_Name;
	std::unique_ptr<Storage> m_Storage;
};