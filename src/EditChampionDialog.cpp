// Application Headers
#include "EditChampionDialog.h"
#include "JSONHelper.h"
#include "Exception.h"
#include "Champion.h"
#include "CreateChampionDialog.h"
#include "Dataset.h"
#include "LCR.h"

// QtWidgets Headers
#include <QtWidgets/qlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qmessagebox.h>

// QtCore Headers
#include <QtCore/qfile.h>
#include <QtCore/qstringlist.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qstring.h>
#include <QtCore/qfile.h>

EditChampionDialog::EditChampionDialog() {
	// Create Layouts
	m_mainLayout = new QHBoxLayout(this);

	// Create Controls
	m_championsList = new QListWidget;

	// Setup Layouts
	m_mainLayout->addWidget(m_championsList);
	m_mainLayout->addStretch(1);

	// Setup Controls
	addItemsToList();

	// Setup Window
	setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
	setWindowTitle("Edit/Delete Champion");
	setMaximumSize(400, 300);
	setMinimumSize(400, 300);
	setWindowIcon(LCR::instance()->windowIcon());

	// Connect signals
	connect(m_championsList, &QListWidget::itemDoubleClicked, this, &EditChampionDialog::showUnderDialog);

	// Attatch stylesheet
	QFile stylesheet("stylesheet.qss");

	if (stylesheet.exists()) {
		if (stylesheet.open(QIODevice::ReadOnly)) {
			setStyleSheet(stylesheet.readAll());
			stylesheet.close();
		}
	}
}

EditChampionDialog::~EditChampionDialog() {

}

void EditChampionDialog::addItemsToList() {
	m_championsList->clear();
	m_championsList->addItems(champions());
}

QStringList EditChampionDialog::champions(void) {
	QStringList allChampions;
	
	// Open and Read JSON file
	QFile f("ChampionData.json");

	if (!f.open(QIODevice::ReadOnly)) {
		throw Exception("Couldn't open the file \"ChampionData.json\" for writing.");
	}

	QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
	f.close();

	QJsonObject obj = doc.object();
	JSON_MEMCHECK(obj, "Champions", Array);

	QJsonArray championsArray = obj["Champions"].toArray();

	// Put all champions in one stringlist
	for (int i = 0; i < championsArray.size(); i++) {
		allChampions.push_back(championsArray.at(i).toObject()["Name"].toString());
	}

	return allChampions;
}

void EditChampionDialog::showUnderDialog(QListWidgetItem* _item) {
	// Get champion which was clicked
	QString championName = _item->text();

	// Execute edit dialog
	CreateChampionDialog dia(LCR_DB->champion(championName), "Edit/Delete Champion");
	try {
		dia.exec();
	}
	catch (const Exception& _e) {
		QApplication::beep();
		QMessageBox messageBox(QMessageBox::Icon::Warning, "Edit Error", _e.message(), QMessageBox::StandardButton::Ok);
	}

	// Update Changes
	if (dia.dialogResult() == CreateChampionDialog::Ok) {
		Champion *champion = dia.createChampion();
		if (champion->name() != championName) {
			LCR_DB->forceDeleteChampion(championName);
		}
		addItemsToList();
		LCR::instance()->setHomeScreen();
	}
	else if (dia.dialogResult() == CreateChampionDialog::Delete) {
		LCR_DB->deleteChampion(championName);
		addItemsToList();
		LCR::instance()->setHomeScreen();
	}
}
