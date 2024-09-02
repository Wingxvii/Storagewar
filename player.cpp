#include "player.h"

#include "assert.h"

ObjectID Player::storeObject(Object* object)
{
	assert(object);
	// TODO: Return the results of the storage attempt, rather than the id
	return m_Storage.storeObject(object);
}

Object* const Player::retrieveObject(ObjectID objectID)
{
	if (objectID == INVALID_OBJECT_ID)
	{
		return nullptr;
	}

	return m_Storage.retrieveObject(objectID);
}

void Player::displayStorage() const
{
	m_Storage.displayContainer();
}
