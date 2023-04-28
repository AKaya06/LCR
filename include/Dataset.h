#pragma once

// Application Headers 
#include "Champion.h"

// QtCore Headers
#include <QtCore/qlist.h>

#define LCR_DB Dataset::instance()

//! @brief Singleton class, storing all champions and config data
class Dataset {
public:
	//! @brief Creates and/or returns dataset instance
	static Dataset* instance(void);

	//! @brief Destroys dataset instance
	static void deleteInstance(void);

	//! @brief Sets champions to provided QList
	//! @param _list List to set champions to
	void setChampions(const QList<Champion*>& _list) { m_champions = _list; }

	//! @brief Adds a champion to the champions list
	//! @param _champion Champion, getting added to the list
	void addChampion(Champion* _champion);

	//! @brief Returns all added champions
	const QList<Champion*>& champions(void) const { return m_champions; }

	//! @brief Returns a single champion by name
	//! @param _championName Name of the champion, getting returned
	Champion* champion(const QString& _championName);

	//! @brief Edits champion data to the data provided
	//! @param _champion Champion to set the data from
	void editChampion(Champion* champion);

	//! @brief Deletes champion by name
	//! @param _championName Name of the champion being deleted
	void deleteChampion(const QString& _championName);

	//! @brief Deletes champion by name without opening messagebox
	//! @param _championName Name of the champion being deleted
	void forceDeleteChampion(const QString& _championName);

	//! @brief Sets the roles getting rolled when pressing "Roll" button
	//! @param _list Roles, getting rolled
	void setRolesToRoll(const QList<Champion::Role>& _list) { m_rolesRoll = _list; }
	
	//! @brief Adds a role getting rolled when pressing "Roll" button
	//! @param _role Role getting added for being rolled
	void addRoleToRoll(const Champion::Role& _role);
	
	//! @brief Returns roles, being rolled
	const QList<Champion::Role>& rolesToRoll(void) const { return m_rolesRoll; }

	//! @brief Sets the genders getting rolled when pressing "Roll" button
	//! @param _list Genders, being rolled
	void setGendersToRoll(const QList<Champion::Gender>& _list) { m_gendersRoll = _list; }
	
	//! @brief Adds a gender getting rolled when pressing "Roll" button
	//! @param _gender Gender getting added for being rolled
	void addGenderToRoll(const Champion::Gender& _gender);
	
	//! @brief Returns genders, being rolled
	const QList<Champion::Gender>& gendersToRoll(void) const { return m_gendersRoll; }

	//! @brief Sets the resources getting rolled when pressing "Roll" button
	//! @param _list Resources, being rolled
	void setResourcesToRoll(const QList<Champion::Resource>& _list) { m_resourcesRoll = _list; }
	
	//! @brief Adds a resource getting rolled when pressing "Roll" button
	//! @param _resource Resource getting added for being rolled
	void addResourceToRoll(const Champion::Resource& _resource);
	
	//! @brief Returns resources, being rolled
	const QList<Champion::Resource>& resourcesToRoll(void) const { return m_resourcesRoll; }

	//! @brief Exports all champions and their data in JSON format to provided file path
	//! @param _filePath The file, being written to
	void exportToFile(const QString& _filePath);
	
	//! @brief Imports champion data from JSON file
	//! @param _filePath The file, being read
	void importFromFile(const QString& _filePath);

	//! @brief Imports config settings
	void importSettings(void);

private:
	Dataset();
	virtual ~Dataset();
	QList<Champion*> m_champions; //! @brief All added champions
	QList<Champion::Role> m_rolesRoll; //! @brief All roles being rolled when "Roll" button is pressed
	QList<Champion::Gender> m_gendersRoll; //! @brief All genders being rolled when "Roll" button is pressed
	QList<Champion::Resource> m_resourcesRoll; //! @brief All resources being rolled when "Roll" button is pressed

	
};