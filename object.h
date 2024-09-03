#pragma once

#include <map>
#include <string>
#include <utility>

namespace StorageWarTypes
{
	// Enum describes the type of object
	enum class EObjectType : int
	{
		None,
		Furniture,
		Electronic,
		Food,
		RefrigeratedFood,
		Medicine,
		RefrigeratedMedicine,
		MAX
	};

	// Enum describles the type of container
	enum class EContainerType : int
	{
		Refrigerated,
		NonRefrigerated,
		MAX
	};
}

// Class representing an object which can be stored
class Object
{
public:
	Object();
	explicit Object(StorageWarTypes::EObjectType type);

	// Returns the object type
	StorageWarTypes::EObjectType getType() const;

	// Returns the type of the object as a char array
	const char* getName() const;

	// Returns the unique id of the object
	int getID() const;

	// If the object requires refigeration
	bool isRefrigerated() const;

protected:
	int m_ObjectID = -1;
	StorageWarTypes::EObjectType m_Type = StorageWarTypes::EObjectType::None;

private:
	// Gather our object types from a data table
	static void SetupObjectData();

	static bool m_objectTableSetup;
	static std::map<int, std::pair<std::string, bool>> m_objectData;

	static int m_Count;
};