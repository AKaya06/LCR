#include "CreateChampionDialog.h"
#include "Dataset.h"
#include "Exception.h"
#include "LCR.h"

#include <QtWidgets/qlayout.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtextedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qcombobox.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qmessagebox.h>

#include <QtCore/qfile.h>

#include <cassert>

CreateChampionDialog::CreateChampionDialog() : m_dialogResult(None){
	// Create Window
	init();
}


CreateChampionDialog::CreateChampionDialog(Champion *_champion, const QString& _windowTitle) : m_dialogResult(None) {
	// Create Window
	init();

	// Add Delete Button
	m_buttonLayout->addWidget(m_DeleteButton);
	connect(m_DeleteButton, &QPushButton::clicked, this, &CreateChampionDialog::deleteChampion);

	// Setup Name Input
	m_nameInput->setText(_champion->name());

	// Set Window Title
	setWindowTitle(_windowTitle);

	// Setup Controls
	if (_champion->roles().contains(Champion::Top)) m_topBox->setChecked(true);
	if (_champion->roles().contains(Champion::Jungle)) m_jglBox->setChecked(true);
	if (_champion->roles().contains(Champion::Middle)) m_midBox->setChecked(true);
	if (_champion->roles().contains(Champion::Bottom)) m_botBox->setChecked(true);
	if (_champion->roles().contains(Champion::Support)) m_supBox->setChecked(true);

	m_genderBox->setCurrentText(Champion::genderToString(_champion->gender()));

	m_resourceBox->setCurrentText(Champion::resourceToString(_champion->resource()));
}

CreateChampionDialog::~CreateChampionDialog() {

}

Champion* CreateChampionDialog::createChampion(void) {
	// Create Champion
	Champion* ch = new Champion;
	// Setup Data
	QString name = m_nameInput->text();
	QString gender = m_genderBox->currentText();
	QList<Champion::Role> roles;

	if (m_topBox->isChecked()) roles.push_back(Champion::Top);
	if (m_jglBox->isChecked()) roles.push_back(Champion::Jungle);
	if (m_midBox->isChecked()) roles.push_back(Champion::Middle);
	if (m_botBox->isChecked()) roles.push_back(Champion::Bottom);
	if (m_supBox->isChecked()) roles.push_back(Champion::Support);

	QString resource = m_resourceBox->currentText();
	// Set Data
	ch->setName(name);
	ch->setGender(Champion::stringToGender(gender));
	ch->setRoles(roles);
	ch->setResource(Champion::stringToResource(resource));

	// Edit JSON file
	LCR_DB->editChampion(ch);
	LCR_DB->exportToFile("ChampionData.json");
	return ch;
}

CreateChampionDialog::DialogResult CreateChampionDialog::dialogResult(void) {
	return m_dialogResult;
}

void CreateChampionDialog::ok(void) {
	// Check whether every input control is checked at least once
	if (!m_topBox->isChecked() && !m_jglBox->isChecked() && !m_midBox->isChecked() && !m_botBox->isChecked() && !m_supBox->isChecked() || m_nameInput->text().isEmpty()) {
		// If not, throw Error Messagebox

		QMessageBox messageBox(QMessageBox::Icon::Warning, "Export error", "Couldn't create Champion. Invalid Input", QMessageBox::StandardButton::Ok);
		messageBox.exec();
		return;
	}
	// Set Dialog Code to Ok
	else	m_dialogResult = Ok;
	// Close Dialog
	close();
}

void CreateChampionDialog::cancel(void) {
	// Set Dialog Code to Cancel
	m_dialogResult = Cancel;
	// Close Dialog
	close();
}

void CreateChampionDialog::deleteChampion(void) {
	// Set Dialog Code to Delete
	m_dialogResult = Delete;
	// Close Dialog
	close();
}

void CreateChampionDialog::init() {
	// Create Layouts
	m_mainLayout = new QVBoxLayout(this);

	m_ButtonLayoutW = new QWidget;
	m_buttonLayout = new QHBoxLayout(m_ButtonLayoutW);

	m_nameInputW = new QWidget;
	m_nameInputLayout = new QHBoxLayout(m_nameInputW);

	m_roleW = new QWidget;
	m_roleLayout = new QVBoxLayout(m_roleW);

	m_genderW = new QWidget;
	m_genderLayout = new QHBoxLayout(m_genderW);

	m_resourceW = new QWidget;
	m_resourceLayout = new QHBoxLayout(m_resourceW);

	// Create Controls
	m_nameLabel = new QLabel("Name:");
	m_nameInput = new QLineEdit;

	m_roleLabel = new QLabel("Roles:");
	m_topBox = new QCheckBox("Top");
	m_jglBox = new QCheckBox("Jungle");
	m_midBox = new QCheckBox("Middle");
	m_botBox = new QCheckBox("Bottom");
	m_supBox = new QCheckBox("Support");

	m_genderLabel = new QLabel("Gender:");
	m_genderBox = new QComboBox;

	m_resourceLabel = new QLabel("Resource:");
	m_resourceBox = new QComboBox;

	m_OkButton = new QPushButton("OK");
	m_CancelButton = new QPushButton("Cancel");
	m_DeleteButton = new QPushButton("Delete");

	// Setup Layouts
	m_mainLayout->addWidget(m_nameInputW);
	m_mainLayout->addWidget(m_roleW);
	m_mainLayout->addWidget(m_genderW);
	m_mainLayout->addWidget(m_resourceW);
	m_mainLayout->addWidget(m_ButtonLayoutW);

	m_nameInputLayout->addWidget(m_nameLabel);
	m_nameInputLayout->addWidget(m_nameInput);

	m_roleLayout->addWidget(m_roleLabel);
	m_roleLayout->addWidget(m_topBox);
	m_roleLayout->addWidget(m_jglBox);
	m_roleLayout->addWidget(m_midBox);
	m_roleLayout->addWidget(m_botBox);
	m_roleLayout->addWidget(m_supBox);

	m_genderLayout->addWidget(m_genderLabel);
	m_genderLayout->addWidget(m_genderBox);

	m_resourceLayout->addWidget(m_resourceLabel);
	m_resourceLayout->addWidget(m_resourceBox);

	m_buttonLayout->addWidget(m_OkButton);
	m_buttonLayout->addWidget(m_CancelButton);

	// Setup Window
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle("Create Champion");
	setMaximumSize(400, 350);
	setMinimumSize(400, 350);
	setWindowIcon(LCR::instance()->windowIcon());

	// Setup Comboboxes
	QStringList genders = { Champion::genderToString(Champion::Gender::Male), Champion::genderToString(Champion::Gender::Female), Champion::genderToString(Champion::Gender::Other) };
	m_genderBox->addItems(genders);

	QStringList resources = { Champion::resourceToString(Champion::Resource::BloodWell), Champion::resourceToString(Champion::Resource::Courage), Champion::resourceToString(Champion::Resource::CrimsonRush), Champion::resourceToString(Champion::Resource::Energy), Champion::resourceToString(Champion::Resource::Ferocity), Champion::resourceToString(Champion::Resource::Flow), Champion::resourceToString(Champion::Resource::Fury), Champion::resourceToString(Champion::Resource::Grit), Champion::resourceToString(Champion::HealthCosts), Champion::resourceToString(Champion::Resource::Heat), Champion::resourceToString(Champion::Resource::Mana), Champion::resourceToString(Champion::Resource::Moonlight), Champion::resourceToString(Champion::Resource::Rage), Champion::resourceToString(Champion::Resource::Resourceless), Champion::resourceToString(Champion::Resource::Shield) };
	m_resourceBox->addItems(resources);

	// Connect Signals
	connect(m_OkButton, &QPushButton::clicked, this, &CreateChampionDialog::ok);
	connect(m_CancelButton, &QPushButton::clicked, this, &CreateChampionDialog::cancel);

	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}
}