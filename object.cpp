#include "object.h"

#include "assert.h"

#include <fstream>
#include <sstream>

using namespace StorageWarTypes;

int Object::m_Count = 0;
bool Object::m_objectTableSetup = false;
std::map<int, std::pair<std::string, bool>> Object::m_objectData = std::map<int, std::pair<std::string, bool>>();

Object::Object()
{
	m_ObjectID = m_Count++;
	if (!m_objectTableSetup)
	{
		SetupObjectData();
	}
}

Object::Object(EObjectType type) : m_Type(type)
{
	m_ObjectID = m_Count++;
	if (!m_objectTableSetup)
	{
		SetupObjectData();
	}
}

EObjectType Object::getType() const
{
	return m_Type;
}

const char* Object::getName() const
{
	assert(m_objectData.size() > 0 && "Object::getName: Object data has not been setup");

	auto mapIterator = m_objectData.find((int)m_Type);

	assert(mapIterator != m_objectData.end() && "Object::getName: Object type not found from parsed data file");

	return mapIterator->second.first.c_str();
}

int Object::getID() const
{
	return m_ObjectID;
}

bool Object::isRefrigerated() const
{
	assert(m_objectData.size() > 0 && "Object::isRefrigerated: Object data has not been setup");

	auto mapIterator = m_objectData.find((int)m_Type);

	assert(mapIterator != m_objectData.end() && "Object::isRefrigerated: Object type not found from parsed data file");

	return mapIterator->second.second;
}

void Object::SetupObjectData()
{
	std::ifstream file("objectTypes.csv");

	if (!file.is_open())
	{
		printf("Error, could not open file.\n");
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::istringstream ss(line);
		std::string entry;

		int typeIndex;
		std::string name;
		bool isRefrigerated;

		std::getline(ss, entry, ',');
		typeIndex = std::stoi(entry);

		std::getline(ss, entry, ',');
		name = entry;

		std::getline(ss, entry, ',');
		isRefrigerated = (entry == "1");

		m_objectData.emplace(typeIndex, std::make_pair(name, isRefrigerated));
	}
	file.close();

	m_objectTableSetup = true;
}
