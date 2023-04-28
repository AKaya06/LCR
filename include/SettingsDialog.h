#pragma once

// Qt Header
#include <QtCore/qjsonobject.h>
#include <QtWidgets/qdialog.h>

// Forward declarations
class QVBoxLayout;
class QHBoxLayout;
class QCheckBox;
class QPushButton;

//! Displays the application settings
class SettingsDialog : public QDialog
{
public:
	//! Dialog exit code
	enum DialogCode {
		Ok,
		Cancel,
		None
	};

	SettingsDialog();
	virtual ~SettingsDialog();

	//! @brief Adds the settings to the provided JSON object
	//! @param _obj The JSON object to add the settings to
	void addToJsonObject(QJsonObject& _obj) const;

	//! @brief Sets the play roll animation setting from the provided JSON object
	//! @param _obj The JSON object to set the setting from
	bool setFromJsonObject(const QJsonObject& _obj);

	//! @brief Returns the dialog exit code
	DialogCode dialogResult(void) const { return m_dialogCode; }

private slots:
	//! @brief Saves and stores the settings and closes the dialog window
	void slotOk(void);

	//! @brief Closes the dialog window
	void slotCancel(void);

private:
	QVBoxLayout* m_mainLayout; //! @brief Main layout

	QVBoxLayout* m_settingsLayout; //! @brief Layout that holds the settings contols

	QHBoxLayout* m_buttonLayout; //! @brief Layout that holds the buttons

	QCheckBox*   m_showRollAnimation; //! @brief Checkbox which sets the setting for playing the roll animation

	QPushButton* m_okButton; //! @brief Ok button
	QPushButton* m_cancelButton; //! @brief Cancel button

	DialogCode   m_dialogCode; //! @brief Dialog exit code
};