#pragma once

#include <string>

#pragma warning( disable : 4250 )

using ObjectType = std::string;
using ObjectID = std::string;
static const ObjectID INVALID_OBJECT_ID = "INVALID_OBJECT_ID";

enum class EObjectType : char
{
	Furniture,
	Electronic,
	Food,
	RefrigeratedFood,
	Medicine,
	RefrigeratedMedicine,
	MAX
};

static std::string ObjectTypes[(char)(EObjectType::MAX)] = {
	"Furniture",
	"Electronic",
	"Food",
	"RefrigeratedFood",
	"Medicine",
	"RefrigeratedMedicine",
};

#define OT(t)						ObjectTypes[(char)t]
#define OT_Furniture				OT(EObjectType::Furniture)
#define OT_Electronic				OT(EObjectType::Electronic)
#define OT_Food						OT(EObjectType::Food)
#define OT_RefrigeratedFood			OT(EObjectType::RefrigeratedFood)
#define OT_Medicine					OT(EObjectType::Medicine)
#define OT_RefrigeratedMedicine		OT(EObjectType::RefrigeratedMedicine)

class IObject
{
public:
	IObject(ObjectID objectID) { m_ObjectID = objectID; }
	virtual ~IObject() { m_ObjectID = INVALID_OBJECT_ID; }

	virtual const ObjectType getType() const = 0 { return INVALID_OBJECT_ID; }
	virtual const ObjectID getID() const { return m_ObjectID; };

	static IObject* const  CreateObject(ObjectType objectType);
protected:
	ObjectID m_ObjectID;
private:
	static int m_Count;
};

class Object : public IObject
{
public:
	Object(ObjectID objectID) : IObject(objectID) {}
	virtual const bool isRefrigerated() const { return false; }
};

struct FurnitureObject : public virtual Object
{
	FurnitureObject(ObjectID objectID) : Object(objectID) {}
	const ObjectType getType() const { return "Furniture"; }
};

struct ElectronicObject : public virtual Object
{
	ElectronicObject(ObjectID objectID) : Object(objectID) {}
	const ObjectType getType() const { return "Electronic"; }
};

struct FoodObject : virtual Object
{
	FoodObject(ObjectID objectID) : Object(objectID) {}
	const ObjectType getType() const { return "Food"; }
};

struct MedicineObject : virtual Object
{
	MedicineObject(ObjectID objectID) : Object(objectID) {}
	const ObjectType getType() const { return "Medicine"; }
};

class RefrigeratedObject : public virtual Object
{
public:
	RefrigeratedObject(ObjectID objectID) : Object(objectID) {}
	const ObjectType getType() const { return "Refrigerated"; }
	virtual const bool isRefrigerated() const override { return true; }

	const float getTemperature() const { return m_temperature; }

private:
	float m_temperature = 0.f;
};

struct NonRegrigaratedFoodObject : FoodObject
{
	NonRegrigaratedFoodObject(ObjectID objectID) : Object(objectID), FoodObject(objectID) {}
	const ObjectType getType() const { return "NonRefrigeratedFood"; }
};

struct RegrigaratedFoodObject : RefrigeratedObject, FoodObject
{
	RegrigaratedFoodObject(ObjectID objectID) : Object(objectID), RefrigeratedObject(objectID), FoodObject(objectID) {}
	const ObjectType getType() const { return "RefrigeratedFood"; }
};

struct NonRefrigeratedMedicineObject : MedicineObject
{
	NonRefrigeratedMedicineObject(ObjectID objectID) : Object(objectID), MedicineObject(objectID) {}
	const ObjectType getType() const { return "NonRefrigeratedMedicine"; }
};

struct RefrigeratedMedicineObject : RefrigeratedObject, MedicineObject
{
	RefrigeratedMedicineObject(ObjectID objectID) : Object(objectID), RefrigeratedObject(objectID), MedicineObject(objectID) {}
	const ObjectType getType() const { return "RefrigeratedMedicine"; }
};

struct NonRefrigeratedFurnitureObject : FurnitureObject
{
	NonRefrigeratedFurnitureObject(ObjectID objectID) : Object(objectID), FurnitureObject(objectID) {}
	const ObjectType getType() const { return "NonRefrigeratedFurniture"; }
};

struct NonRefrigeratedElectronicObject : ElectronicObject
{
	NonRefrigeratedElectronicObject(ObjectID objectID) : Object(objectID), ElectronicObject(objectID) {}
	const ObjectType getType() const { return "NonRefrigeratedElectronic"; }
};
