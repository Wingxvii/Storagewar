#include "object.h"

int IObject::m_Count = 0;

// TODO: This will all be removed
IObject* const IObject::CreateObject(ObjectType o)
{
	if (o == "Furniture")
	{
		return new FurnitureObject(std::to_string(m_Count++));
	}
	else if (o == "Electronic")
	{
		return new ElectronicObject(std::to_string(m_Count++));
	}
	else if (o == "Food")
	{
		return new FoodObject(std::to_string(m_Count++));
	}
	else if (o == "RefrigeratedFood")
	{
		return static_cast<RefrigeratedObject*>(new RefrigeratedFoodObject(std::to_string(m_Count++)));
	}
	else if (o == "Medicine")
	{
		return new MedicineObject(std::to_string(m_Count++));
	}
	else if (o == "RefrigeratedMedicine")
	{
		return static_cast<RefrigeratedObject*>(new RefrigeratedMedicineObject(std::to_string(m_Count++)));
	}
	else
	{
		return nullptr;
	}
}
