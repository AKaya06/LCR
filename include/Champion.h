#pragma once

// Qt Core Headers
#include <QtCore/qstring.h>
#include <QtCore/qlist.h>
#include <QtCore/qjsonobject.h>

//! Stores champion data
class Champion {
public:

	//! Champion's gender
	enum Gender {
		Male,
		Female,
		Other
	};

	//! Champion's role(s)
	enum Role {
		Top,
		Jungle,
		Middle,
		Bottom,
		Support
	};

	//! Champion's resource
	enum Resource {
		Mana = 1,
		Energy,
		Fury,
		Shield,
		Rage,
		Heat,
		Ferocity,
		BloodWell,
		Bloodthirst,
		Flow,
		Moonlight,
		CrimsonRush,
		Courage,
		Grit,
		Resourceless,
		HealthCosts
	};

	//! @brief Converts provided gender enum to QString
	//! @param _gender The enum, getting returned as QString
	static QString genderToString(Gender _gender);

	//! @brief Converts provided QString to gender enum
	//! @param _str The QString, getting returned as gender enum
	static Gender stringToGender(const QString& _str);

	//! @brief Converts provided role enum to QString
	//! @param _role The enum, getting returned as QString
	static QString roleToString(Role _role);

	//! @brief Converts provided QString to role enum
	//! @param _str The QString, getting returned as role enum
	static Role stringToRole(const QString& _str);

	//! @brief Converts provided resource enum to QString
	//! @param _resource The enum, getting returned as QString
	static QString resourceToString(Resource _resource);

	//! @brief Converts provided QString to resource enum
	//! @param _sre The QString, getting returned as resource enum
	static Resource stringToResource(const QString& _str);

	Champion();
	Champion(const Champion& _other);
	virtual ~Champion();

	//! @brief Sets name, gender, resource and roles from right to left
	//! @param _other Champion's data getting transfered to left side of =
	Champion& operator=(const Champion& _other);

	//! @brief Sets name of champion to provided QString
	//! @param _name Name of the champion
	void setName(const QString& _name) { m_name = _name; }

	//! @brief Returns name of the champion
	const QString& name(void) const { return m_name; }

	//! @brief Sets gender of champion to provided gender enum
	//! @param _gender Gender of the champion
	void setGender(Gender _gender) { m_gender = _gender; }

	//! @brief Returns gender of the champion
	Gender gender(void) const { return m_gender; }

	//! @brief Sets a list of roles as champion's roles
	//! @param _roles Champion's roles
	void setRoles(const QList<Role>& _roles) { m_roles = _roles; }

	//! @brief Returns roles of the champion
	const QList<Role>& roles(void) const { return m_roles; }

	//! @brief Adds a single role to champion's roles
	//! @param _role Role, getting added to champion's roles
	void addRole(Role _role); 

	//! @brief Adds a list of roles to champion's roles
	//! @param _roles Roles, getting added to champion's roles
	void addRoles(const QList<Role>& _roles);

	//! @brief Sets a resource as champion's resource
	//! @param _resource Resource, getting set as champion's resource
	void setResource(Resource _resource) { m_resource = _resource; }

	//! @brief Returns resource of the champion
	Resource resource(void) const { return m_resource; }
	
	//! @brief Adds name, gender, resource and roles to provided JSON object
	//! @param _obj JSON object to add name, gender, resource and roles to
	void addToJSONObject(QJsonObject& _obj);

	//! @brief Sets champion's name, gender, resource and roles from provided JSON object
	//! @param _obj JSON object to set name, gender, resource and roles from
	void setFromJSONObject(const QJsonObject& _obj);

private:
	QString m_name; //! @brief Champion's name
	Gender m_gender; //! @brief Champion's gender
	QList<Role> m_roles; //! @brief Champion's roles
	Resource m_resource; //! @brief Champion's resource
};