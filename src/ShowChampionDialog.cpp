#include "ShowChampionDialog.h"
#include "Champion.h"
#include "Dataset.h"
#include "Exception.h"
#include "LCR.h"

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qapplication.h>

#include <QtCore/QJsonObject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qsettings.h>
#include <QtCore/qfile.h>

#include <cassert>

#define NUMBER_OF_RESOURCES resourcesList.size()

ShowChampionDialog::ShowChampionDialog() : m_dialogAnswer(None) {
	try
	{
		LCR_DB->importSettings();
	}
	catch (const Exception& _e) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Import error", _e.message()
			, QMessageBox::StandardButton::Ok);
		messageBox.exec();
	}
	

	// Create Layouts
	m_mainLayout = new QHBoxLayout(this);

	m_checkBoxLayoutW = new QWidget;
	m_checkBoxLayout = new QVBoxLayout(m_checkBoxLayoutW);

	m_listButtonsLayoutW = new QWidget;
	m_listButtonsLayout = new QVBoxLayout(m_listButtonsLayoutW);

	m_buttonLayoutW = new QWidget;
	m_buttonLayout = new QHBoxLayout(m_buttonLayoutW);

	// Create Controls
	m_topBox = new QCheckBox("Top");
	m_jglBox = new QCheckBox("Jungle");
	m_midBox = new QCheckBox("Middle");
	m_botBox = new QCheckBox("Bottom");
	m_supBox = new QCheckBox("Support");
	m_maleBox = new QCheckBox("Male");
	m_femaleBox = new QCheckBox("Female");
	m_otherBox = new QCheckBox("Other");

	m_resourcesList = new QListWidget;
	m_okButton = new QPushButton("OK");
	m_cancelButton = new QPushButton("Cancel");

	// Setup Layouts
	m_mainLayout->addWidget(m_checkBoxLayoutW);
	m_mainLayout->addWidget(m_listButtonsLayoutW);

	m_checkBoxLayout->addWidget(m_topBox);
	m_checkBoxLayout->addWidget(m_jglBox);
	m_checkBoxLayout->addWidget(m_midBox);
	m_checkBoxLayout->addWidget(m_botBox);
	m_checkBoxLayout->addWidget(m_supBox);
	m_checkBoxLayout->addStretch(1);
	m_checkBoxLayout->addWidget(m_maleBox);
	m_checkBoxLayout->addWidget(m_femaleBox);
	m_checkBoxLayout->addWidget(m_otherBox);

	m_listButtonsLayout->addWidget(m_resourcesList);
	m_listButtonsLayout->addWidget(m_buttonLayoutW);

	m_buttonLayout->addWidget(m_okButton);
	m_buttonLayout->addWidget(m_cancelButton);

	// Setup Controls
	QStringList resourcesList {
		"Check All",
		"Mana",
		"Energy",
		"Fury",
		"Shield",
		"Rage",
		"Heat",
		"Ferocity",
		"Blood Well",
		"Flow",
		"Moonlight",
		"Crimson Rush",
		"Courage",
		"Grit",
		"Resourceless",
		"Health Costs" };

	m_resourcesList->addItems(resourcesList);
	
	for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
		m_resourcesList->item(i)->setCheckState(Qt::Unchecked);
	}

	QList<Champion::Role> rolesRoll = LCR_DB->rolesToRoll();
	QList<Champion::Resource> resourcesRoll = LCR_DB->resourcesToRoll();
	QList<Champion::Gender> gendersRoll = LCR_DB->gendersToRoll();

	for (Champion::Resource resource : resourcesRoll) m_resourcesList->item(resource)->setCheckState(Qt::Checked);
	if (resourcesRoll.size() == 15) m_resourcesList->item(0)->setCheckState(Qt::Checked);

	for (Champion::Role role : rolesRoll) {
		switch (role)
		{
		case Champion::Top: m_topBox->setChecked(true);
			break;
		case Champion::Jungle: m_jglBox->setChecked(true);
			break;
		case Champion::Middle: m_midBox->setChecked(true);
			break;
		case Champion::Bottom: m_botBox->setChecked(true);
			break;
		case Champion::Support: m_supBox->setChecked(true);
			break;
		default: assert(0); return;
			break;
		}
	}

	for (Champion::Gender gender : gendersRoll) {
		switch (gender)
		{
		case Champion::Male: m_maleBox->setChecked(true);
			break;
		case Champion::Female: m_femaleBox->setChecked(true);
			break;
		case Champion::Other: m_otherBox->setChecked(true);
			break;
		default: assert(0); return;
			break;
		}
	}

	// Setup Window
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle("Configuration Editor");
	setMaximumSize(400, 300);
	setMinimumSize(400, 300);
	setWindowIcon(LCR::instance()->windowIcon());

	// Connect Signals
	connect(m_resourcesList, &QListWidget::itemDoubleClicked, this, &ShowChampionDialog::toggleCheckState);
	connect(m_resourcesList, &QListWidget::itemClicked, this, &ShowChampionDialog::toggleCheckAll);
	connect(m_okButton, &QPushButton::clicked, this, &ShowChampionDialog::ok);
	connect(m_cancelButton, &QPushButton::clicked, this, &ShowChampionDialog::cancel);

	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}

}

ShowChampionDialog::~ShowChampionDialog() {

}

void ShowChampionDialog::addToJsonObject(QJsonObject& _obj) {
	QJsonArray rolesArray;
	if (m_topBox->isChecked()) rolesArray.push_back("Top");
	if (m_jglBox->isChecked()) rolesArray.push_back("Jungle");
	if (m_midBox->isChecked()) rolesArray.push_back("Middle");
	if (m_botBox->isChecked()) rolesArray.push_back("Bottom");
	if (m_supBox->isChecked()) rolesArray.push_back("Support");

	QJsonArray genderArray;
	if (m_maleBox->isChecked()) genderArray.push_back("Male");
	if (m_femaleBox->isChecked()) genderArray.push_back("Female");
	if (m_otherBox->isChecked()) genderArray.push_back("Other");

	QJsonArray resourcesArray;
	for (int i = 1; i < 16; i++) {
		if (m_resourcesList->item(i)->checkState() == Qt::Checked) {
			QString text = m_resourcesList->item(i)->text();
			resourcesArray.push_back(text);
		}
	}

	_obj["Roles"] = rolesArray;
	_obj["Genders"] = genderArray;
	_obj["Resources"] = resourcesArray;
}

void ShowChampionDialog::toggleCheckState(QListWidgetItem* _item) {
	if (_item->checkState() == Qt::Checked) _item->setCheckState(Qt::Unchecked);
	else _item->setCheckState(Qt::Checked);
}

void ShowChampionDialog::toggleCheckAll(QListWidgetItem* _item) {
	if (_item->text() == "Check All" && _item->checkState() == Qt::Checked) {
		for (int i = 0; i < 16; i++) {
			m_resourcesList->item(i)->setCheckState(Qt::Checked);
		}
	} else if (_item->text() == "Check All" && _item->checkState() == Qt::Unchecked) {
		for (int i = 0; i < 16; i++) {
			m_resourcesList->item(i)->setCheckState(Qt::Unchecked);
		}
	}
	for (int i = 1; i < 16; i++) {
		if (m_resourcesList->item(i)->checkState() == Qt::Unchecked) {
			m_resourcesList->item(0)->setCheckState(Qt::Unchecked);
			return;
		}
	}
	m_resourcesList->item(0)->setCheckState(Qt::Checked);
}

void ShowChampionDialog::ok(void) {
	bool oneChecked = false;
	for (int i = 0; i < 16; i++) {
		if (m_resourcesList->item(i)->checkState() == Qt::Checked) oneChecked = true;
	}
	if (
		!oneChecked || 
		!m_topBox->isChecked() && 
		!m_jglBox->isChecked() && 
		!m_midBox->isChecked() && 
		!m_botBox->isChecked() && 
		!m_supBox->isChecked() || 
		!m_maleBox->isChecked() && 
		!m_femaleBox->isChecked() && 
		!m_otherBox->isChecked()
		) {
		m_dialogAnswer = Cancel;
		close();
		throw Exception("All input fields must be checked at least once");
	}
	m_dialogAnswer = Ok;
	QJsonObject settingsObj;
	addToJsonObject(settingsObj);
	QJsonDocument doc(settingsObj);
	QByteArray data = doc.toJson(QJsonDocument::Compact);
	QSettings cfg("AKayaSolutions", "LCR");
	cfg.setValue("Config", data);
	close();
}

void ShowChampionDialog::cancel(void) {
	m_dialogAnswer = Cancel;
	close();
}