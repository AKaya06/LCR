// Application Headers
#include "HomeScreenWidget.h"
#include "Dataset.h"
#include "JSONHelper.h"
#include "LCR.h"
#include "CreateChampionDialog.h"

// QtWidgets
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>

// QtCore
#include <QtCore/qstring.h>
#include <QtCore/qsettings.h>
#include <QtCore/qtimer.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonarray.h>

// QtGui
#include <QtGui/qfont.h>

// std
#include <random>


#define CONFIG_GENDERS_INDEX 0
#define CONFIG_RESOURCES_INDEX 1
#define CONFIG_ROLES_INDEX 2

HomeScreenWidget::HomeScreenWidget(): m_animationCount(0) {
	// Create Main Layout
	m_mainLayout = new QVBoxLayout(this);

	// Create Top Label
	m_welcomeLabel = new QLabel("Welcome to LCR!");

	// Create Left Box
	m_listLayoutW = new QWidget;
	m_listLayout = new QHBoxLayout(m_listLayoutW);

	m_rollWidgetLayoutW = new QWidget;
	m_rollWidgetLayout = new QVBoxLayout(m_rollWidgetLayoutW);
	m_rollListWidget = new QListWidget;
	
	m_rollButton = new QPushButton("Roll");
	m_rollButton->setObjectName("HSW_BTN_ROLL");
	m_rollButtonW = new QWidget;

	// Create Right Box
	m_outputWidgetLayoutW = new QWidget;
	m_outputWidgetLayout = new QVBoxLayout(m_outputWidgetLayoutW);
	
	m_yourChampion = new QLabel("Your Champion: ");
	m_champion = new Champion;
	
	m_championNameLabel = new QLabel;
	m_championRoleLabel = new QLabel;

	// Setup Layouts
	m_mainLayout->addWidget(m_welcomeLabel, 0, Qt::AlignCenter);
	m_mainLayout->addWidget(m_listLayoutW);

	m_listLayout->addWidget(m_rollWidgetLayoutW);
	m_listLayout->addStretch(1);
	m_listLayout->addWidget(m_outputWidgetLayoutW);

	m_rollWidgetLayout->addWidget(m_rollListWidget);
	m_rollWidgetLayout->addWidget(m_rollButton);

	m_outputWidgetLayout->addWidget(m_yourChampion, 0, Qt::AlignTop);

	// Initialize List
	m_timer = new QTimer(this);
	m_timer->setSingleShot(true);
	refreshRoleList();

	// Setup Labels
	QFont welcomeFont;
	welcomeFont.setBold(true);
	welcomeFont.setFamily("Arial");
	welcomeFont.setPixelSize(20);
	m_welcomeLabel->setFont(welcomeFont);
	m_welcomeLabel->setStyleSheet("QLabel { color: red; }");

	// Connect Signals
	connect(m_rollButton, &QPushButton::clicked, this, &HomeScreenWidget::rollChampion);
	connect(m_rollListWidget, &QListWidget::itemDoubleClicked, this, &HomeScreenWidget::showEditScreen);
	connect(m_timer, &QTimer::timeout, this, &HomeScreenWidget::setRolledChampion);
}

HomeScreenWidget::~HomeScreenWidget() {}

void HomeScreenWidget::refreshRoleList() {
	m_rollListWidget->clear();

	QStringList championNameList;

	QSettings cfg("AKayaSolutions", "LCR");

	QJsonDocument doc = QJsonDocument::fromJson(cfg.value("Config").toByteArray());
	if (!doc.isObject()) return;
	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Genders", Array);
	JSON_MEMCHECK(obj, "Resources", Array);
	JSON_MEMCHECK(obj, "Roles", Array);

	QJsonArray genderArray = obj["Genders"].toArray();
	QJsonArray resourcesArray = obj["Resources"].toArray();
	QJsonArray rolesArray = obj["Roles"].toArray();

	QList<Champion::Gender> gendersList;
	QList<Champion::Resource> resourcesList;
	QList<Champion::Role> rolesList;

	for (int i = 0; i < genderArray.count(); i++) {
		JSON_ARRAYCHECK_TYPE(genderArray, i, String);
		gendersList.push_back(Champion::stringToGender(genderArray[i].toString()));
	}

	for (int i = 0; i < resourcesArray.count(); i++){
		JSON_ARRAYCHECK_TYPE(resourcesArray, i, String);
		resourcesList.push_back(Champion::stringToResource(resourcesArray[i].toString()));
	}

	for (int i = 0; i < rolesArray.count(); i++){
		JSON_ARRAYCHECK_TYPE(rolesArray, i, String);
		rolesList.push_back(Champion::stringToRole(rolesArray[i].toString()));
	}

	QList<Champion*>champions;

	for (Champion* champion : LCR_DB->champions()) {
		if (gendersList.contains(champion->gender()) &&
			resourcesList.contains(champion->resource()))
		{
			for (Champion::Role role : champion->roles()) {
				if (rolesList.contains(role)) {
					champions.append(champion);
					break;
				}
			}
		}
	}
	for (Champion* c : champions) championNameList.append(c->name()); 

	m_rollListWidget->addItems(championNameList);

	disableAllItems();
}


void HomeScreenWidget::disableAllItems() {
	for (int i = 0; i < m_rollListWidget->count(); i++) {
		m_rollListWidget->item(i)->setFlags(m_rollListWidget->item(i)->flags() & ~Qt::ItemIsSelectable);
	}
}

void HomeScreenWidget::rollChampion() {
	// Get configuration settings
	QSettings cfg("AKayaSolutions", "LCR");

	QJsonDocument doc = QJsonDocument::fromJson(cfg.value("Config").toByteArray());
	if (!doc.isObject()) return;
	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Genders", Array);
	JSON_MEMCHECK(obj, "Resources", Array);
	JSON_MEMCHECK(obj, "Roles", Array);

	QJsonArray genderArray = obj["Genders"].toArray();
	QJsonArray resourcesArray = obj["Resources"].toArray();
	QJsonArray rolesArray = obj["Roles"].toArray();

	QList<Champion::Gender> gendersList;
	QList<Champion::Resource> resourcesList;
	QList<Champion::Role> rolesList;

	for (QJsonValueRef val : genderArray) gendersList.push_back(Champion::stringToGender(val.toString()));
	for (QJsonValueRef val : resourcesArray) resourcesList.push_back(Champion::stringToResource(val.toString()));
	for (QJsonValueRef val : rolesArray) rolesList.push_back(Champion::stringToRole(val.toString()));

	// Add all eligble champions to champions list
	champions.clear();
	for (Champion* champion : LCR_DB->champions()) {
		bool containsGender = false;
		bool containsResource = false;
		bool containsRole = false;
		for (Champion::Gender gender : gendersList) {
			if (gender == champion->gender()) containsGender = true;
			if (containsGender) break;
		}
		if (containsGender) {
			for (Champion::Resource resource : resourcesList) {
				if (champion->resource() == resource) containsResource = true;
				if (containsResource) break;
			}
			if (containsResource) {
				for (Champion::Role role : rolesList) {
					if (champion->roles().contains(role)) containsRole = true;
					if (containsRole) break;
				}
			}
		}
		if (containsGender && containsResource && containsRole) {
			champions.push_back(champion);
		}
	}
	m_animationCount = 0;
	m_timer->start(20);
	if (champions.size() > 1) m_rollButton->setEnabled(false);
}

void HomeScreenWidget::setRolledChampion(void) {
	// Get configuration settings
	QSettings cfg("AKayaSolutions", "LCR");
	QJsonDocument doc = QJsonDocument::fromJson(cfg.value("Config").toByteArray());
	if (!doc.isObject()) return;
	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Roles", Array);

	QJsonArray rolesArray = obj["Roles"].toArray();
	QList<Champion::Role> rolesList;
	for (QJsonValueRef val : rolesArray) rolesList.push_back(Champion::stringToRole(val.toString()));

	//Roll champions and show in application
	if (champions.size() > 1) {
		int randomNumber = rand() % champions.size();
		m_champion = champions[randomNumber];
		m_championNameLabel->setText((QString)"Champion:\n" + m_champion->name());

		QStringList ChampionRolesInConfig;

		for (Champion::Role role : m_champion->roles()) {
			if (rolesList.contains(role)) {
				ChampionRolesInConfig.push_back(Champion::roleToString(role));
			}
		}
		int randomRole = rand() % (ChampionRolesInConfig.size());
		m_championRoleLabel->setText((QString)"Role:\n" + ChampionRolesInConfig.at(randomRole));
	}
	else if (champions.size() == 1) {
		m_champion = champions.at(0);
		m_championNameLabel->setText((QString)"Champion:\n" + m_champion->name());

		QStringList ChampionRolesInConfig;

		for (Champion::Role role : m_champion->roles()) {
			if (rolesList.contains(role)) {
				ChampionRolesInConfig.push_back(Champion::roleToString(role));
			}
		}
		int randomRole = rand() % (ChampionRolesInConfig.size());
		m_championRoleLabel->setText((QString)"Role:\n" + ChampionRolesInConfig.at(randomRole));
	}
	else {
		m_championNameLabel->setText("No corresponding\nChampion found!");
		m_championRoleLabel->setText("");
	}
	m_outputWidgetLayout->addWidget(m_championNameLabel);
	m_outputWidgetLayout->addWidget(m_championRoleLabel, 1, Qt::AlignTop);
	m_animationCount++;

	QSettings settings("AKayaSolutions", "LCR");
	QString playAnimation = settings.value("Settings").toString();

	if (champions.size() > 1) {
		if (m_animationCount < 80) m_timer->start(20);
		else if (m_animationCount < 90) m_timer->start(100);
		else if (m_animationCount < 97) m_timer->start(250);
		else if (m_animationCount < 99) m_timer->start(1000);
		else if (m_animationCount < 100) m_timer->start(2000);
		else m_rollButton->setEnabled(true);

		if (m_animationCount < 100 && playAnimation == "{\"Animation\":true}") {

			int r = rand() % 256;
			int g = rand() % 256;
			int b = rand() % 256;

			LCR::instance()->applyDefaultStyleSheet("QMainWindow{ background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QMenuBar { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QListWidget { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "#HSW_BTN_ROLL::disabled { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QMenu { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QMenu::item { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QMenu::item:selected { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }"
				+ "QScrollBar::vertical { background-color: rgb("
				+ QString::number(r) + ", "
				+ QString::number(g) + ", "
				+ QString::number(b) + "); }");
		}
		else LCR::instance()->applyDefaultStyleSheet("");
	}
}

void HomeScreenWidget::showEditScreen(QListWidgetItem* _item) {
	// Get champion which was clicked
	QString championName = _item->text();

	// Execute edit dialog
	CreateChampionDialog dia(LCR_DB->champion(championName), "Edit/Delete Champion");
	try {
		dia.exec();
	}
	catch (const Exception& _e) {
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Edit Error", _e.message(), QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
		messageBox.exec();
	}

	// Update Changes
	if (dia.dialogResult() == CreateChampionDialog::Ok) {
		Champion* champion = dia.createChampion();
		if (champion->name() != championName) {
			LCR_DB->forceDeleteChampion(championName);
		}
		refreshRoleList();
		LCR::instance()->setHomeScreen();
	}
	else if (dia.dialogResult() == CreateChampionDialog::Delete) {
		LCR_DB->deleteChampion(championName);
		refreshRoleList();
		LCR::instance()->setHomeScreen();
	}
}