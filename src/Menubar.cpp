#include "Menubar.h"
#include "ShowChampionDialog.h"
#include "CreateChampionDialog.h"
#include "LCR.h"
#include <cassert>
#include <QtCore/qfile.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qsettings.h>
#include "Exception.h"
#include <QtWidgets/qmessagebox.h>
#include <QtWidgets/qapplication.h>
#include "EditChampionDialog.h"
#include "SettingsDialog.h"

Menubar::Menubar() {
	QMenu * menu = addMenu("Champion");
	QAction* createAction = menu->addAction("Create");
	QAction* configAction = menu->addAction("Config");
	QAction* deleteAction = menu->addAction("Edit/Delete");

	QMenu* viewMenu = addMenu("View");
	QAction* settingsAction = viewMenu->addAction("Settings");

	QMenu * helpMenu = addMenu("Info");
	QAction* aboutAction = helpMenu->addAction("About");
	
	connect(createAction, &QAction::triggered, this, &Menubar::showCreateDialog);
	connect(configAction, &QAction::triggered, this, &Menubar::showConfigDialog);
	connect(deleteAction, &QAction::triggered, this, &Menubar::showEditDialog);
	connect(settingsAction, &QAction::triggered, this, &Menubar::showSettingsDialog);
	connect(aboutAction, &QAction::triggered, this, &Menubar::showAboutDialog);
}

Menubar::~Menubar() {

}

void Menubar::showCreateDialog(void) {
	CreateChampionDialog dia;
	try {
		dia.exec();
	}
	catch (const Exception& _e) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Create error", _e.message()
			, QMessageBox::StandardButton::Ok);
		messageBox.exec();
	}
	
	if (dia.dialogResult() == CreateChampionDialog::Ok) {
		dia.createChampion();
		LCR::instance()->setHomeScreen();
	}
}

void Menubar::showConfigDialog(void) {
	ShowChampionDialog dia;
	try {
		dia.exec();
	}
	catch (const Exception& _e) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Create error", _e.message()
			, QMessageBox::StandardButton::Ok);
		messageBox.exec();
	}

	if (dia.dialogResult() == ShowChampionDialog::Ok) {
		LCR::instance()->setHomeScreen();
	}
}

void Menubar::showEditDialog(void) {
	EditChampionDialog dia;
	try {
		dia.exec();
	}
	catch (const Exception& _e) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Edit Error", _e.message(), QMessageBox::StandardButton::Ok | QMessageBox::StandardButton::Cancel);
		messageBox.exec();
	}
}

void Menubar::showSettingsDialog(void) {
	SettingsDialog dia;
	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			dia.setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}
	dia.exec();
}

void Menubar::showAboutDialog(void) {
	QMessageBox messageBox(QMessageBox::Icon::Information, "About", "Creator: Ahmet Kaya\nGithub: AKaya06", QMessageBox::StandardButton::Ok);
	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			messageBox.setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}
	messageBox.exec();
}