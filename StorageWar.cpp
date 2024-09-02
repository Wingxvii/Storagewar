#include "container.h"
#include "object.h"
#include "player.h"
#include "storage.h"

#include <assert.h>
#include <list>
#include <random>
#include <stdio.h>
#include <iostream>

// TODO: move these to the main function, they arent used anywhere else
#define NON_REFRIGERATED_CONTAINER_COUNT	16
#define REFRIGERATED_CONTAINER_COUNT		8

// TODO: Include variable names for clarity
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
	// TODO: use smart pointers for players
	std::vector<Player*> players;

	// TODO: Do we really need a loop to create 2 players?
	for (int playerNum = 0; playerNum < 2; ++playerNum)
	{
		// TODO: remove buffer because it's not needed, name players a better way
		static char buffer[10];
		sprintf_s(buffer, "Player%0d", playerNum);
		//TODO: weak pointer
		Player* player = new Player(buffer);
		// TODO: Move responsibility for creating the storage to the player
		player->m_Storage = createStorage(NON_REFRIGERATED_CONTAINER_COUNT, REFRIGERATED_CONTAINER_COUNT);
		// TODO: This does nothing, so we should remove it
		generateInitialStorageState(player->m_Storage);

		players.push_back(player);
	}
	//TODO: Validate players

	bool isGameRunning = true;
	// TODO: We dont need this since we have a player array list
	int playerIndex = 0;
	// TODO: either make all player indexes unsigned or make this -1
	int winningPlayerIndex = 0xFFFFFFFF;
	do
	{
		// TODO: we dont need to loop through player turns, since we already have a do while loop
		// Each players play in turn
		for (playerIndex = 0; playerIndex < 2; ++playerIndex)
		{
			// TODO: Use modulus instead to loop the player array list
			// find opponent player index
			int opponentIndex = playerIndex + 1;
			if (opponentIndex >= players.size())
			{
				opponentIndex = 0;
			}

			//TODO: weak pointer
			Player* currentPlayer = players[playerIndex];
			//TODO: since name is always converted to cstr, we should just store it as a cstr. We dont need to compare or resize, cstr is good enough
			std::printf("%s to play\n", currentPlayer->m_Name.c_str());

			// spawn random object
			// TODO: make this a smart pointer also
			Object* object = generateRandomObjectType();
			//TODO: store type as cstr also
			std::printf("%s spawned\n", object->getType().c_str());

			// TODO: we dont need these brackets
			// player handle new object
			{
				// TODO: player should not be responsible for giving objectID, we should just get this from the object itself
				ObjectID objectID = currentPlayer->storeObject(object);
				// TODO: Check the return of store object instead of this
				if (objectID == INVALID_OBJECT_ID)
				{
					std::printf("%s was not able to store %s\n", currentPlayer->m_Name.c_str(), object->getType().c_str());
					winningPlayerIndex = opponentIndex;
					isGameRunning = false;
					// TODO: dont need to break, since we'll have 1 player per turn
					break;
				}
				else
				{
					std::printf("%s successfully stored the object.\n", currentPlayer->m_Name.c_str());
				}
			}

			// player pick object
			// TODO: weak pointer
			Object* objectToSend = nullptr;
			std::printf("%s: Pick an object by ObjectID to send to your opponent\n", currentPlayer->m_Name.c_str());
			do {
				currentPlayer->displayStorage();
				ObjectID idToRetrieve;
				printf("Enter a valid ObjectID: ");
				std::cin >> idToRetrieve;

				//TODO: weak pointer
				Object* const retrievedObject = currentPlayer->retrieveObject(idToRetrieve);
				// TODO: check if this is a nullptr for clarity
				if (!retrievedObject) {
					std::printf("Invalid ObjectID %s. Please try again.\n", idToRetrieve.c_str());
				}
				else
				{
					objectToSend = retrievedObject;
				}
				// TODO: check if this is a nullptr for clarity
			} while (!objectToSend);

			// player send new object to opponent
			Player* opponent = players[opponentIndex];
			// TODO: dont need these brackets
			{
				// TODO: check function return bool instead of invalid_object_id
				ObjectID objectID = opponent->storeObject(objectToSend);
				if (objectID == INVALID_OBJECT_ID)
				{
					std::printf("%s was not able to store %s\n", opponent->m_Name.c_str(), objectToSend->getType().c_str());
					isGameRunning = false;
					winningPlayerIndex = playerIndex;
					// TODO: dont need to break
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

	// TODO: move validation to before the game ends
	assert(winningPlayerIndex != 0xFFFFFFFF);

	std::printf("%s won the game!\n", players[winningPlayerIndex]->m_Name.c_str());

	// TODO: We dont need this since we have smart pointers
	for (auto player : players)
	{
		delete player;
	}
}

// TODO: these dont need to be reference
Storage createStorage(const short& nonRefrigeratedContainerCount, const short& refrigeratedContainerCount)
{
	// TODO: smart pointer
	Storage createdStorage;

	createdStorage.setMaxContainerCount(CT_NonRefrigerated, nonRefrigeratedContainerCount);

	//TODO: Get rid of this for loop, since setMaxContainerCount will replace it
	for (int i = 0; i < nonRefrigeratedContainerCount; i++)
	{
		createdStorage.addContainer(CT_NonRefrigerated);
	}

	createdStorage.setMaxContainerCount(CT_Refrigerated, refrigeratedContainerCount);

	//TODO: Get rid of this for loop, since setMaxContainerCount will replace it
	for (int i = 0; i < refrigeratedContainerCount; i++)
	{
		createdStorage.addContainer(CT_Refrigerated);
	}

	return createdStorage;
}

// TODO: Get rid of this
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

	//TODO: validate results first, then index object types instead of using a switch statement
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
