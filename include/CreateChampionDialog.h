#pragma once

// Application Headers
#include "Champion.h"

// QtCore Headers
#include <QtCore/qstring.h>

// QtWidget Headers
#include <QtWidgets/qdialog.h>

// Forward declarations
class QWidget;
class QPushButton;
class QVBoxLayout;
class QHBoxLayout;
class QTextEdit;
class QLabel;
class QLineEdit;
class QComboBox;
class QCheckBox;

//! Displays a champion creation dialog
class CreateChampionDialog : public QDialog
{
	Q_OBJECT
public:
	CreateChampionDialog();
	CreateChampionDialog(Champion* _champion, const QString& _windowTitle = "Create Champion");
	virtual ~CreateChampionDialog();

	//! Dialog exit code
	enum DialogResult {
		None,
		Cancel,
		Ok,
		Delete
	};

	//! @brief Returns champion described in the dialog
	Champion* createChampion(void);

	//! @brief Returns the dialog exit code
	DialogResult dialogResult(void);

private slots:
	//! @brief Closes dialog with exit code "Ok"
	void ok(void);

	//! @brief Closes dialog with exit code "Cancel"
	void cancel(void);

	//! Closes dialog with exit code "Delete"
	void deleteChampion(void);


private:
	DialogResult        m_dialogResult;	 //! @brief Dialog exit code

	QVBoxLayout*		m_mainLayout;	 //! @brief Main Layout

	QPushButton*		m_OkButton;		 //! @brief Ok Button
	QPushButton*		m_CancelButton;  //! @brief Cancel Button
	QPushButton*		m_DeleteButton;  //! @brief Delete Button
	QWidget*			m_ButtonLayoutW; //! @brief Button Layout Widget
	QHBoxLayout*		m_buttonLayout;  //! @brief Buttom Layout

	QLabel*				m_nameLabel;	   //! @brief Name Label
		QLineEdit*			m_nameInput;   //! @brief Name Input Line
	QHBoxLayout*		m_nameInputLayout; //! @brief Name Input Layout
	QWidget*			m_nameInputW;	   //! @brief Name Input Widget

	QLabel*				m_roleLabel;  //! @brief Role Label
		QCheckBox*			m_topBox; //! @brief Top Checkbox
		QCheckBox*			m_jglBox; //! @brief Jungle Checkbox
		QCheckBox*			m_midBox; //! @brief Middle Checkbox
		QCheckBox*			m_botBox; //! @brief Bottom Checkbox
		QCheckBox*			m_supBox; //! @brief Support Checkbox
	QVBoxLayout*		m_roleLayout; //! @brief Role Layout
	QWidget*			m_roleW;	  //! @brief Role Widget

	QLabel*				m_genderLabel; //! @brief Gender Label
	QComboBox*			m_genderBox;   //! @brief Gender Combobox
	QHBoxLayout*		m_genderLayout;//! @brief Gender Layout
	QWidget*			m_genderW;	   //! @brief Gender Widget

	QLabel*				m_resourceLabel; //! @brief Resource Label
	QComboBox*			m_resourceBox;	 //! @brief Resource Combobox
	QHBoxLayout*		m_resourceLayout;//! @brief Resource Layout
	QWidget*			m_resourceW;	 //! @brief Resource Widget


	//! @brief Initialize Window
	void init();

};
