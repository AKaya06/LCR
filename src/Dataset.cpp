// Application Headers
#include "Dataset.h"
#include "JSONHelper.h"
#include "Exception.h"

// QtCore Headers
#include <QtCore/qfile.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qlist.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qsettings.h>

// QtWidgets Headers
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qpushbutton.h>

static Dataset* g_instance{ nullptr };

Dataset* Dataset::instance() {
	if (g_instance == nullptr) g_instance = new Dataset;
	return g_instance;
}

void Dataset::deleteInstance(void) {
	if (g_instance) delete g_instance;
	g_instance = nullptr;
}

void Dataset::addChampion(Champion* _champion) {
	m_champions.push_back(_champion);
}

Champion* Dataset::champion(const QString& _championName) {
	for (Champion* champion : m_champions) if (champion->name() == _championName) return champion;
	return nullptr;
}

void Dataset::editChampion(Champion* champion) {
	// Go through list and search champion
	for (Champion* ch : m_champions) {
		if (champion->name() == ch->name()) {
			// When champion was found, set data
			ch->setGender(champion->gender());
			ch->setResource(champion->resource());
			ch->setRoles(champion->roles());
			return;
		}
	}
	// If champion wasn't found (name was changed), add to champions list
	LCR_DB->addChampion(champion);
}

void Dataset::deleteChampion(const QString& _championName) {
	
	// Create message box asking if user is sure they want to delete the champion 
	QMessageBox messageBox(QMessageBox::Icon::Warning, "Delete Champion", "Are you sure you want to delete this champion? This action is irreversible.");

	QPushButton *YesButton = messageBox.addButton("Yes", QMessageBox::AcceptRole);
	messageBox.addButton("No", QMessageBox::RejectRole);

	// Setting stylesheet of messagebox
	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			messageBox.setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}

	messageBox.exec();

	// If yes was pressed, delete champion from champions list
	if (messageBox.clickedButton()->text() == YesButton->text()) {
		for (Champion* champion : m_champions) {
			if (_championName == champion->name()) {
				m_champions.removeOne(champion);
			}
		}
	}
	LCR_DB->exportToFile("ChampionData.json");
}

void Dataset::forceDeleteChampion(const QString& _championName) {
	
	// Searching champions list for champion that needs to be deleted
	for (Champion* champion : m_champions) {
		if (_championName == champion->name()) {
			// Delete champion from champions list
			m_champions.removeOne(champion);
		}
	}
	LCR_DB->exportToFile("ChampionData.json");
}

void Dataset::addRoleToRoll(const Champion::Role& _role) {
	m_rolesRoll.push_back(_role);
}

void Dataset::addGenderToRoll(const Champion::Gender& _gender) {
	m_gendersRoll.push_back(_gender);
}

void Dataset::addResourceToRoll(const Champion::Resource& _resource) {
	m_resourcesRoll.push_back(_resource);
}

void Dataset::exportToFile(const QString& _filePath) {
	// Collect Data
	QJsonObject obj;
	QJsonArray championArray;
	for (Champion* champion : m_champions) {
		QJsonObject championObj;
		champion->addToJSONObject(championObj);
		championArray.push_back(championObj);
	}
	obj["Champions"] = championArray;
	QJsonDocument doc(obj);

	// Open File
	QFile f(_filePath);

	if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Export error", "Couldn't open the file \""
		+ _filePath + "\" for writing.", QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
		messageBox.exec();
		return;
	}

	f.write(doc.toJson(QJsonDocument::Indented));
	f.close();
}

void Dataset::importFromFile(const QString& _filePath) {

	// Delete all champions from champions list
	m_champions.clear();

	// Read JSON file
	QFile f(_filePath);
	if (!f.open(QIODevice::ReadOnly)) throw Exception("Couldn't open the file \"" + _filePath + "\" for reading.");

	QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
	f.close();
	if (!doc.isObject()) throw Exception("File \"" + _filePath + "\" is not a valid JSON-Document");

	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Champions", Array);

	QJsonArray championsArray = obj["Champions"].toArray();

	// Add every champion from provided file to champions list
	for (int i = 0; i < championsArray.size(); i++) {
		Champion* champion = new Champion;

		if (!championsArray[i].isObject()) throw Exception("JSON array entry is not an object");

		QJsonObject championObj = championsArray[i].toObject();

		JSON_MEMCHECK(championObj, "Gender", String);
		JSON_MEMCHECK(championObj, "Name", String);
		JSON_MEMCHECK(championObj, "Resource", String);
		JSON_MEMCHECK(championObj, "Roles", Array);

		champion->setGender(Champion::stringToGender(championsArray.at(i)["Gender"].toString()));
		champion->setName(championsArray.at(i)["Name"].toString());
		champion->setResource(Champion::stringToResource(championsArray.at(i)["Resource"].toString()));

		QList<Champion::Role> roleList;

		QJsonArray rolesArray = championObj["Roles"].toArray();

		for (int j = 0; j < rolesArray.size(); j++) {
			if (!rolesArray[j].isString()) throw Exception("Role array entry for champion" + champion->name() + " is not a string");
			roleList.push_back(Champion::stringToRole(rolesArray[j].toString()));
		}
		champion->setRoles(roleList);
		m_champions.push_back(champion);
	}
}


void Dataset::importSettings(void) {
	// Read config settings
	QJsonDocument doc = QJsonDocument::fromJson(QSettings("AKayaSolutions", "LCR").value("Config").toByteArray());
	if (!doc.isObject()) return;
	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Genders", Array);
	JSON_MEMCHECK(obj, "Resources", Array);
	JSON_MEMCHECK(obj, "Roles", Array);

	// Set all config data from settings
	QJsonArray genderArray = obj["Genders"].toArray();
	QJsonArray resourcesArray = obj["Resources"].toArray();
	QJsonArray rolesArray = obj["Roles"].toArray();

	QList<Champion::Gender> gendersList;
	QList<Champion::Resource> resourcesList;
	QList<Champion::Role> rolesList;

	for (QJsonValueRef val : genderArray) gendersList.push_back(Champion::stringToGender(val.toString()));
	for (QJsonValueRef val : resourcesArray) resourcesList.push_back(Champion::stringToResource(val.toString()));
	for (QJsonValueRef val : rolesArray) rolesList.push_back(Champion::stringToRole(val.toString()));

	LCR_DB->setGendersToRoll(gendersList);
	LCR_DB->setResourcesToRoll(resourcesList);
	LCR_DB->setRolesToRoll(rolesList);
}

Dataset::Dataset(){

}

Dataset::~Dataset() {

}