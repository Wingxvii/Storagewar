#pragma once

#include <string>

// TODO: fix this instead of ignoring it
#pragma warning( disable : 4250 )

// TODO: put all of this into a namespace
//TODO: since we have an enum for object type, we dont need this, use the enum instead
using ObjectType = std::string;

// TODO: theres no need to specify this, only makes it harder to read and more confusing, since ObjectType is also a string. Just use string.
// TODO: also this should just be an int and convert it to string when printing, instead of storing it as a string
using ObjectID = std::string;

// TODO: since we dont need this to know if a player has won anymore, we dont need this. There are better ways to validate the object id
static const ObjectID INVALID_OBJECT_ID = "INVALID_OBJECT_ID";

// TODO: a max doesnt work with char type enums, change to int
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

// TODO: Maybe use a dictionary or a function
static std::string ObjectTypes[(char)(EObjectType::MAX)] = {
	"Furniture",
	"Electronic",
	"Food",
	"RefrigeratedFood",
	"Medicine",
	"RefrigeratedMedicine",
};

// TODO: we dont need this, we can just use the enum itself
#define OT(t)						ObjectTypes[(char)t]
#define OT_Furniture				OT(EObjectType::Furniture)
#define OT_Electronic				OT(EObjectType::Electronic)
#define OT_Food						OT(EObjectType::Food)
#define OT_RefrigeratedFood			OT(EObjectType::RefrigeratedFood)
#define OT_Medicine					OT(EObjectType::Medicine)
#define OT_RefrigeratedMedicine		OT(EObjectType::RefrigeratedMedicine)

// TODO: This isnt an interface so remove the I for clarity, instead use abstract
class IObject
{
public:
	// TODO: we dont need to pass in objectid, since we want to determine that using the count
	IObject(ObjectID objectID) { m_ObjectID = objectID; }
	// TODO: this doesnt do anything, so we can just remove it
	virtual ~IObject() { m_ObjectID = INVALID_OBJECT_ID; }

	// TODO: this asks for ObjectType, but is return INVALID_OBJECT_ID
	// TODO: since this is being implemented, it is not pure virtual, we should remove the '= 0'
	virtual const ObjectType getType() const = 0 { return INVALID_OBJECT_ID; }
	virtual const ObjectID getID() const { return m_ObjectID; };

	// TODO: move this to the constructor
	static IObject* const CreateObject(ObjectType objectType);
protected:
	ObjectID m_ObjectID;
private:
	static int m_Count;
};

// TODO: this should be part of the interface, not another class
class Object : public IObject
{
public:
	Object(ObjectID objectID) : IObject(objectID) {}
	// TODO: Since the interface needs a pure virtual function, we can make this pure virtual
	virtual const bool isRefrigerated() const { return false; }
};

// TODO: we dont need virtual, since we wont have multiple inheritance anymore
struct FurnitureObject : public virtual Object
{
	FurnitureObject(ObjectID objectID) : Object(objectID) {}
	// TODO: Save type as a variable, also as the enum, then return the enum instead of hardcoding it here
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

// TODO: This should also be abstract
class RefrigeratedObject : public virtual Object
{
public:
	RefrigeratedObject(ObjectID objectID) : Object(objectID) {}

	// TODO: Remove this function, so the child is forced to implement it
	const ObjectType getType() const { return "Refrigerated"; }

	// TODO: we can use final here, since a refigerated object is DEFINATELY refigerated
	virtual const bool isRefrigerated() const override { return true; }

	// TODO: this is never used, but it might be later so comment it out
	const float getTemperature() const { return m_temperature; }

private:
	// TODO: same with this
	float m_temperature = 0.f;
};

// TODO: a non-refigerated object adds nothing new, so we can just use the original class (in thas case foodobject)
struct NonRefrigeratedFoodObject : FoodObject
{
	NonRefrigeratedFoodObject(ObjectID objectID) : Object(objectID), FoodObject(objectID) {}
	const ObjectType getType() const { return "NonRefrigeratedFood"; }
};

// TODO: Just inherit RefigeratedObject, theres nothing from foodObject we need
struct RefrigeratedFoodObject : RefrigeratedObject, FoodObject
{
	RefrigeratedFoodObject(ObjectID objectID) : Object(objectID), RefrigeratedObject(objectID), FoodObject(objectID) {}
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
