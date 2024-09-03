#include "player.h"

#include "assert.h"

using namespace StorageWarTypes;

Player::Player(const char* name) : m_Name(name)
{
}

bool Player::storeObject(const std::shared_ptr<Object>& object)
{
	assert(object && "Player::storeObject: object invalid");
	return m_Storage->storeObject(object);
}

void Player::createInitialStorage(int refrigeratedCount, int nonRefrigeratedCount)
{
	m_Storage = std::make_unique<Storage>();
	m_Storage->setMaxContainerCount(EContainerType::Refrigerated, refrigeratedCount);
	m_Storage->setMaxContainerCount(EContainerType::NonRefrigerated, nonRefrigeratedCount);
}

std::shared_ptr<Object> Player::retrieveObject(int objectID)
{
	assert(objectID >= 0 && "Player::retrieveObject: objectID is invalid");
	return m_Storage->retrieveObjectByID(objectID);
}

void Player::printStorage() const
{
	m_Storage->printContents();
}

const char* Player::getName() const
{
	return m_Name;
}