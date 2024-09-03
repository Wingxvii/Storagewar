#include "container.h"
#include "player.h"

#include <assert.h>
#include <iostream>
#include <random>

std::shared_ptr<Object> generateRandomObject();

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
	// Setup maximum storage counts
	const int refrigeratedContainerCount = 8;
	const int nonRefrigeratedContainerCount = 16;

	std::vector<std::shared_ptr<Player>> players;
	players.push_back(std::make_shared<Player>("Player1"));
	players.push_back(std::make_shared<Player>("Player2"));

	for (const std::shared_ptr<Player>& player : players)
	{
		player->createInitialStorage(refrigeratedContainerCount, nonRefrigeratedContainerCount);
	}

	bool isGameRunning = true;
	int currentPlayerIndex = 0;
	int winningPlayerIndex = -1;
	do
	{
		// find opponent player index
		const int nextPlayerIndex = (currentPlayerIndex + 1) % players.size();
		const std::shared_ptr<Player>& currentPlayer = players[currentPlayerIndex];
		std::printf("%s to play\n", currentPlayer->getName());

		// spawn random object
		std::shared_ptr<Object> randomObject = generateRandomObject();
		std::printf("%s spawned\n", randomObject->getName());

		// player handle new object
		if (currentPlayer->storeObject(randomObject))
		{
			std::printf("%s successfully stored the object.\n", currentPlayer->getName());
		}
		else
		{
			std::printf("%s was not able to store %s\n", currentPlayer->getName(), randomObject->getName());
			winningPlayerIndex = nextPlayerIndex;
			isGameRunning = false;
			// We dont need to do the next part if the game has been won
			break;
		}

		// player pick object
		std::shared_ptr<Object> objectToSend = nullptr;
		std::printf("%s: Pick an object by ObjectID to send to your opponent\n", currentPlayer->getName());
		do 
		{
			currentPlayer->printStorage();
			int idToRetrieve;
			std::printf("Enter a valid ObjectID: ");
			std::cin >> idToRetrieve;

			// Validate the input is an int
			if (std::cin.fail())
			{
				std::printf("Invalid character entered, please enter a number.\n");
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
			else
			{
				objectToSend = currentPlayer->retrieveObject(idToRetrieve);
				if (objectToSend.get() == nullptr) 
				{
					std::printf("Invalid ObjectID %i. Please try again.\n", idToRetrieve);
				}
			}
		} while (!objectToSend);

		// player send new object to opponent
		const std::shared_ptr<Player>& opponent = players[nextPlayerIndex];
		if (opponent->storeObject(objectToSend))
		{
			std::printf("%s successfully stored the object.\n", opponent->getName());
		}
		else
		{
			std::printf("%s was not able to store %s\n", opponent->getName(), objectToSend->getName());
			isGameRunning = false;
			winningPlayerIndex = currentPlayerIndex;
		}
		// player end of turn
		std::printf("\n-------------------------\nEnd of turn\n-------------------------\n");

		// Change to other player's turn
		currentPlayerIndex = nextPlayerIndex;
	} while (isGameRunning);

	std::printf("%s won the game!\n", players[winningPlayerIndex]->getName());
}

std::shared_ptr<Object> generateRandomObject()
{
	// Seed with a real random value, if available
	std::random_device device;

	// Choose a random number between 1 and 6
	std::default_random_engine engine(device());
	std::uniform_int_distribution<int> uniformDist(1, static_cast<int>(StorageWarTypes::EObjectType::MAX) - 1);

	const int randomNumber = uniformDist(engine);

	std::shared_ptr<Object> randomObject = std::make_shared<Object>(static_cast<StorageWarTypes::EObjectType>(randomNumber));

	assert(randomObject.get() && "Main::generateRandomObject random object is invalid");
	return randomObject;
}