#pragma once

// QtWidgets Headers
#include <QtWidgets/qdialog.h>

// Forward Declarations
class QHBoxLayout;
class QListWidget;
class QListWidgetItem;
class QStringList;

//! Displays a dialog for editing an existing champion
class EditChampionDialog : public QDialog {
	Q_OBJECT
public:
	EditChampionDialog(void);
	virtual ~EditChampionDialog(void);

	//! @brief refreshes the champions ListWidget
	void addItemsToList();

	//! @brief returns all champions in JSON file
	QStringList champions(void);

private slots:
	//! @brief Displays another CreateChampionDialog to edit a Champion
	void showUnderDialog(QListWidgetItem* _item);

private:
	QHBoxLayout*		m_mainLayout;

	QListWidget*		m_championsList;

};