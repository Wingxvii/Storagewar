#pragma once

namespace StorageWarTypes
{
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

	enum class EContainerType : int
	{
		Refrigerated,
		NonRefrigerated,
		MAX
	};
}

using namespace StorageWarTypes;

class Object
{
public:
	Object();
	Object(EObjectType type);

	const EObjectType getType() const;
	const char* getName() const;
	const int getID() const;

	const bool isRefrigerated() const;

protected:
	int m_ObjectID = -1;
	EObjectType m_Type = EObjectType::None;

private:
	static int m_Count;
};