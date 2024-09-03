#include "object.h"

int Object::m_Count = 0;

Object::Object()
{
	m_ObjectID = m_Count++;
}

Object::Object(EObjectType type)
{
	m_ObjectID = m_Count++;
	m_Type = type;
}

const EObjectType Object::getType() const
{
	return m_Type;
}

const char* Object::getName() const
{
	// TODO: maybe parse a data table for this for scaleability and accessibility
	switch (m_Type)
	{
	case EObjectType::Furniture:
		return "Furniture";
		break;
	case EObjectType::Electronic:
		return "Electronic";
		break;
	case EObjectType::Food:
		return "Food";
		break;
	case EObjectType::RefrigeratedFood:
		return "RefrigeratedFood";
		break;
	case EObjectType::Medicine:
		return "Medicine";
		break;
	case EObjectType::RefrigeratedMedicine:
		return "RefrigeratedMedicine";
		break;
	default:
		return "\0";
		break;
	}
}

const int Object::getID() const
{
	return m_ObjectID;
}

const bool Object::isRefrigerated() const
{
	// TODO: maybe parse a data table for this for scaleability and accessibility
	return m_Type == EObjectType::RefrigeratedFood || m_Type == EObjectType::RefrigeratedMedicine;
}