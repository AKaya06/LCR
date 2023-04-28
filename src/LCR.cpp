// Application Header
#include "LCR.h"
#include "Menubar.h"
#include "CreateChampionDialog.h"
#include "ShowChampionDialog.h"
#include "Dataset.h"
#include "Exception.h"
#include "HomeScreenWidget.h"
#include "JSONHelper.h"

// QtWidgets
#include <QtWidgets/qmessagebox.h>

//QtCore
#include <QtCore/qfile.h>

static LCR* g_instance{ nullptr };

LCR* LCR::instance() {
	if (g_instance == nullptr) g_instance = new LCR;
	return g_instance;
}

void LCR::setHomeScreen() {
	m_homeScreenWidget->refreshRoleList();
	// Setup Window
	setWindowIcon(QIcon(":/LCR.png"));
	setCentralWidget(m_homeScreenWidget);
	setMenuBar(m_menubar);
	setMaximumSize(400, 300);
	setMinimumSize(400, 300);
}

void LCR::applyDefaultStyleSheet(const QString& _additionalStyle) {
	setStyleSheet(m_stylesheet + _additionalStyle);
}

LCR::LCR() {
	// Import Data
	try {
		Dataset::instance()->importFromFile("ChampionData.json");
	}
	catch (const Exception& _e) {
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Import error", _e.message()
		, QMessageBox::StandardButton::Ok);
		messageBox.exec();
	}
	m_menubar = new Menubar();
	m_homeScreenWidget = new HomeScreenWidget;

	setHomeScreen();
	
	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			m_stylesheet = stylesheet.readAll();
			stylesheet.close();
			applyDefaultStyleSheet("");
		}
	}
}

LCR::~LCR(void) {

}

