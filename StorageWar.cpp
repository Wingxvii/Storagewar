#include "container.h"
#include "object.h"
#include "player.h"
#include "storage.h"

#include <assert.h>
#include <list>
#include <random>
#include <stdio.h>
#include <iostream>

#define NON_REFREGIRATED_CONTAINER_COUNT	16
#define REFREGIRATED_CONTAINER_COUNT		8

Storage createStorage(const short&, const short&);
void generateInitialStorageState(Storage&);
Object* generateRandomObjectType();

/**************************************************************************/
/* StorageWars is a turn-based Tetris-like game where two opponents must  */
/* manage their storage while trying to fill the opponent's one. Each     */
/* turn, a new object is spawned and must be either stored or sent to the */
/* opponent's storage. If stored, the player can choose a stored object   */
/* and send it out to the opponent. The first player that gets a container*/
/* fully loaded container that requires dropping an object looses.        */
/**************************************************************************/

int main()
{
	std::vector<Player*> players;

	for (int i = 0; i < 2; ++i)
	{
		static char buffer[10];
		sprintf_s(buffer, "Player%0d", i);
		Player* player = new Player(buffer);
		player->m_Storage = createStorage(NON_REFREGIRATED_CONTAINER_COUNT, REFREGIRATED_CONTAINER_COUNT);

		generateInitialStorageState(player->m_Storage);

		players.push_back(player);
	}

	bool isGameRunning = true;
	int playerIndex = 0;
	int winningPlayerIndex = 0xFFFFFFFF;
	do
	{
		// Each players play in turn
		for (playerIndex = 0; playerIndex < 2; ++playerIndex)
		{
			// find opponent player index
			int opponentIndex = playerIndex + 1;
			if (opponentIndex >= players.size())
			{
				opponentIndex = 0;
			}

			Player* p = players[playerIndex];
			std::printf("%s to play\n", p->m_Name.c_str());

			// spawn random object
			Object* object = generateRandomObjectType();
			std::printf("%s spawned\n", object->getType().c_str());

			// player handle new object
			{
				ObjectID objecID = p->storeObject(object);
				if (objecID == INVALID_OBJECT_ID)
				{
					std::printf("%s was not able to store %s\n", p->m_Name.c_str(), object->getType().c_str());
					winningPlayerIndex = opponentIndex;
					isGameRunning = false;
					break;
				}
				else
				{
					std::printf("%s successfully stored the object.\n", p->m_Name.c_str());
				}
			}

			// player pick object
			Object* objetToSend = nullptr;
			std::printf("%s: Pick an object by ObjectID to send to your opponent\n", p->m_Name.c_str());
			do {
				p->displayStorage();
				ObjectID idToRetrieve;
				printf("Enter a valid ObjectID: ");
				std::cin >> idToRetrieve;
				Object* const retrievedObject = p->retrieveObject(idToRetrieve);
				if (!retrievedObject) {
					std::printf("Invalid ObjectID %s. Please try again.\n", idToRetrieve.c_str());
				}
				else
				{
					objetToSend = retrievedObject;
				}
			} while (!objetToSend);

			// player send new object to opponent
			Player* opponent = players[opponentIndex];
			{
				ObjectID objecID = opponent->storeObject(objetToSend);
				if (objecID == INVALID_OBJECT_ID)
				{
					std::printf("%s was not able to store %s\n", opponent->m_Name.c_str(), objetToSend->getType().c_str());
					isGameRunning = false;
					winningPlayerIndex = playerIndex;
					break;
				}
				else
				{
					std::printf("%s successfully stored the object.\n", opponent->m_Name.c_str());
				}
			}
			// player end of turn
			std::printf("\n-------------------------\nEnd of turn\n-------------------------\n");
		}
	} while (isGameRunning);
	assert(winningPlayerIndex != 0xFFFFFFFF);

	std::printf("%s won the game!\n", players[winningPlayerIndex]->m_Name.c_str());

	for (auto player : players)
	{
		delete player;
	}
}

Storage createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount)
{
	Storage s;

	s.setMaxContainerCount(CT_NonRefrigerated, nonRefrigeratedContainerCount);

	for (int i = 0; i < nonRefrigeratedContainerCount; i++)
	{
		s.addContainer(CT_NonRefrigerated);
	}

	s.setMaxContainerCount(CT_Refrigerated, refrigeratedContainerCount);

	for (int i = 0; i < refrigeratedContainerCount; i++)
	{
		s.addContainer(CT_Refrigerated);
	}

	return s;
}

void generateInitialStorageState(Storage& s)
{

}

Object* generateRandomObjectType()
{
	// Seed with a real random value, if available
	std::random_device device;

	// Choose a random mean between 1 and 6
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniformDist(0, static_cast<int>(EObjectType::MAX) - 1);

	const int randomNumber = uniformDist(engine);

	Object* randomObject = nullptr;
	switch (randomNumber)
	{
	case 0:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::Furniture)]));
		break;
	case 1:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::Electronic)]));
		break;
	case 2:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::Food)]));
		break;
	case 3:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::RefrigeratedFood)]));
		break;
	case 4:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::Medicine)]));
		break;
	case 5:
		randomObject = static_cast<Object*>(IObject::CreateObject(ObjectTypes[static_cast<int>(EObjectType::RefrigeratedMedicine)]));
		break;
	default:
		assert(false);
		break;
	}

	assert(randomObject);
	return randomObject;
}
