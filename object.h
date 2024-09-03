#pragma once

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
	static int m_Count;
};