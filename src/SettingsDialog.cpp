// Application Header
#include "SettingsDialog.h"
#include "LCR.h"

// Qt Core Header
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonvalue.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qsettings.h>

// Qt Widgets Header
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qpushbutton.h>

SettingsDialog::SettingsDialog() : m_dialogCode(None) {
	// Create Main Layout
	m_mainLayout = new QVBoxLayout(this);

	// Create Layouts
	m_settingsLayout = new QVBoxLayout;

	m_buttonLayout = new QHBoxLayout;

	// Create Controls
	m_showRollAnimation = new QCheckBox("Play Roll Animation");

	m_okButton = new QPushButton("Ok");
	m_cancelButton = new QPushButton("Cancel");

	// Setup Controls
	QSettings settings("AKayaSolutions", "LCR");
	QJsonDocument doc = QJsonDocument::fromJson(settings.value("Settings").toByteArray());

	if (doc.isObject()) setFromJsonObject(doc.object());

	// Setup Layouts
	m_mainLayout->addLayout(m_settingsLayout);
	m_mainLayout->addLayout(m_buttonLayout);

	m_settingsLayout->addWidget(m_showRollAnimation);

	m_buttonLayout->addWidget(m_okButton);
	m_buttonLayout->addWidget(m_cancelButton);

	// Setup Window
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setMaximumSize(200, 100);
	setMinimumSize(200, 100);
	setWindowIcon(LCR::instance()->windowIcon());

	// Connect Signals
	connect(m_okButton, &QPushButton::clicked, this, &SettingsDialog::slotOk);
	connect(m_cancelButton, &QPushButton::clicked, this, &SettingsDialog::slotCancel);
}

SettingsDialog::~SettingsDialog() {

}

void SettingsDialog::addToJsonObject(QJsonObject& _obj) const {
	_obj["Animation"] = m_showRollAnimation->isChecked();
}

bool SettingsDialog::setFromJsonObject(const QJsonObject& _obj) {
	if (!_obj.contains("Animation")) return false;
	if (!_obj["Animation"].isBool()) return false;

	m_showRollAnimation->setCheckState((_obj["Animation"].toBool() ? Qt::Checked : Qt::Unchecked));
	return true;
}

void SettingsDialog::slotOk(void) {
	// Set the dialog code
	m_dialogCode = Ok;
	
	// Store settings in JSON format
	QJsonObject settingsObj;
	addToJsonObject(settingsObj);
	QJsonDocument doc(settingsObj);
	QByteArray data = doc.toJson(QJsonDocument::Compact);

	// Save settings
	QSettings settings("AKayaSolutions", "LCR");
	settings.setValue("Settings", data);

	// Close dialog window
	close();
}

void SettingsDialog::slotCancel(void) {
	m_dialogCode = Cancel;
	close();
}