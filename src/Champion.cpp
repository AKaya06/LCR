#include "Champion.h"
#include <cassert>
#include <QtCore/qjsonarray.h>
#include "Exception.h"
#include "JSONHelper.h"

QString Champion::genderToString(Gender _gender) {
	switch (_gender)
	{
	case Champion::Male: return "Male";
	case Champion::Female: return "Female";
	case Champion::Other: return "Other";
	default: assert(0); throw Exception("Invalid gender provided");
	}
}

Champion::Gender Champion::stringToGender(const QString& _str) {
	if (_str == genderToString(Male)) return Male;
	else if (_str == genderToString(Female)) return Female;
	else if (_str == genderToString(Other)) return Other;
	else throw Exception("Cannot convert string \"" + _str + "\" to gender");
}

QString Champion::roleToString(Role _role) {
	switch (_role)
	{
	case Champion::Top: return "Top";
	case Champion::Jungle: return "Jungle";
	case Champion::Middle: return "Middle";
	case Champion::Bottom: return "Bottom";
	case Champion::Support: return "Support";
	default: assert(0); throw Exception("Invalid role provided");
	}
}

Champion::Role Champion::stringToRole(const QString& _str) {
	if (_str == roleToString(Top) || _str == "\"Top\"") return Top;
	else if (_str == roleToString(Jungle) || _str == "\"Jungle\"") return Jungle;
	else if (_str == roleToString(Middle) || _str == "\"Middle\"") return Middle;
	else if (_str == roleToString(Bottom) || _str == "\"Bottom\"") return Bottom;
	else if (_str == roleToString(Support) || _str == "\"Support\"") return Support;
	else throw Exception("Cannot convert \"" + _str + "\" to Role");
}

QString Champion::resourceToString(Resource _resource) {
	switch (_resource)
	{
	case Champion::Mana: return "Mana";
	case Champion::Energy: return "Energy";
	case Champion::Fury: return "Fury";
	case Champion::Shield: return "Shield";
	case Champion::Rage: return "Rage";
	case Champion::Heat: return "Heat";
	case Champion::Ferocity: return "Ferocity";
	case Champion::BloodWell: return "Blood Well";
	case Champion::Bloodthirst: return "Bloodthirst";
	case Champion::Flow: return "Flow";
	case Champion::Moonlight: return "Moonlight";
	case Champion::CrimsonRush: return "Crimson Rush";
	case Champion::Courage: return "Courage";
	case Champion::Grit: return "Grit";
	case Champion::Resourceless: return "Resourceless";
	case Champion::HealthCosts: return "Health Costs";
	default: assert(0); throw Exception("Invalid resource provided");
	}
}

Champion::Resource Champion::stringToResource(const QString& _str) {
	if (_str == resourceToString(Mana)) return Mana;
	else if (_str == resourceToString(Energy)) return Energy;
	else if (_str == resourceToString(Fury)) return Fury;
	else if (_str == resourceToString(Shield)) return Shield;
	else if (_str == resourceToString(Rage)) return Rage;
	else if (_str == resourceToString(Heat)) return Heat;
	else if (_str == resourceToString(Ferocity)) return Ferocity;
	else if (_str == resourceToString(BloodWell)) return BloodWell;
	else if (_str == resourceToString(Bloodthirst)) return Bloodthirst;
	else if (_str == resourceToString(Flow)) return Flow;
	else if (_str == resourceToString(Moonlight)) return Moonlight;
	else if (_str == resourceToString(CrimsonRush)) return CrimsonRush;
	else if (_str == resourceToString(Courage)) return Courage;
	else if (_str == resourceToString(Grit)) return Grit;
	else if (_str == resourceToString(Resourceless)) return Resourceless;
	else if (_str == resourceToString(HealthCosts)) return HealthCosts;
	else throw Exception("Cannot convert \"" + _str + "\" to resource");
}

Champion::Champion() : m_gender(Other), m_resource(Resourceless) {

}

Champion::Champion(const Champion& _other) : m_name(_other.m_name), m_gender(_other.m_gender), m_resource(_other.m_resource), m_roles(_other.m_roles) {
	
}

Champion::~Champion() {

}

Champion& Champion::operator=(const Champion& _other) {
	m_name = _other.m_name;
	m_gender = _other.m_gender;
	m_roles = _other.m_roles;
	m_resource = _other.m_resource;
	return *this;
}

void Champion::addRole(Role _role) {
	m_roles.push_back(_role); 
}

void Champion::addRoles(const QList<Role>& _roles) {
	// Add role if isn't already in list
	for (Role role : _roles) if (!m_roles.contains(role)) m_roles.push_back(role);
}

void Champion::addToJSONObject(QJsonObject& _obj) {
	// Set key's values
	_obj["Name"] = m_name;
	_obj["Gender"] = genderToString(m_gender);
	_obj["Resource"] = resourceToString(m_resource);
	QJsonArray rolesArr;
	for (Role role : m_roles) rolesArr.push_back(roleToString(role));
	_obj["Roles"] = rolesArr;
}

void Champion::setFromJSONObject(const QJsonObject& _obj) {
	// Check if all keys exist and have the right data type
	JSON_MEMCHECK(_obj, "Name", String);
	JSON_MEMCHECK(_obj, "Gender", String);
	JSON_MEMCHECK(_obj, "Resource", String);
	JSON_MEMCHECK(_obj, "Roles", Array);
	
	// Set champion's data to key values
	m_name = _obj["Name"].toString();
	m_gender = stringToGender(_obj["Gender"].toString());
	m_resource = stringToResource(_obj["Resource"].toString());
	QJsonArray rolesArr = _obj["Roles"].toArray();

	for (int i = 0; i < rolesArr.count(); i++) {
		if (!rolesArr[i].isString()) throw Exception("JSON Array entry is not a String");
		m_roles.push_back(stringToRole(rolesArr[i].toString()));
	}
	
}