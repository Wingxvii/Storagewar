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

using namespace StorageWarTypes;

// Class representing an object which can be stored
class Object
{
public:
	Object();
	Object(EObjectType type);

	// Returns the object type
	const EObjectType getType() const;

	// Returns the type of the object as a char array
	const char* getName() const;

	// Returns the unique id of the object
	const int getID() const;

	// If the object requires refigeration
	const bool isRefrigerated() const;

protected:
	int m_ObjectID = -1;
	EObjectType m_Type = EObjectType::None;

private:
	// Gather our object types from a data table
	static void SetupObjectData();
	static bool m_objectTableSetup;
	static std::map<int, std::pair<std::string, bool>> m_objectData;

	static int m_Count;
};