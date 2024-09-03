#include "player.h"

#include "assert.h"

Player::Player(const char* name) : m_Name(name)
{
}

bool Player::storeObject(std::shared_ptr<Object> object)
{
	assert(object);
	return m_Storage->storeObject(object);
}

void Player::CreateInitialStorage(int refridgeratedCount, int nonRefridgeratedCount)
{
	m_Storage = std::make_unique<Storage>();
	m_Storage->setMaxContainerCount(EContainerType::Refrigerated, refridgeratedCount);
	m_Storage->setMaxContainerCount(EContainerType::NonRefrigerated, nonRefridgeratedCount);
}

std::shared_ptr<Object> const Player::retrieveObject(int objectID)
{
	assert(objectID >= 0);
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
