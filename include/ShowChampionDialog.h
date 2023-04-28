#pragma once
#include <QtWidgets/qdialog.h>

class QWidget;
class QHBoxLayout;
class QVBoxLayout;
class QCheckBox;
class QListWidget;
class QPushButton;
class QListWidgetItem;
class QJsonObject;

class ShowChampionDialog : public QDialog
{
	Q_OBJECT
public:
	ShowChampionDialog();
	virtual ~ShowChampionDialog();

	enum DialogCode {
		Ok,
		Cancel,
		None
	};

	void addToJsonObject(QJsonObject& _obj);

	DialogCode dialogResult() const { return m_dialogAnswer; }

private slots:
	void toggleCheckState(QListWidgetItem* _item);
	void toggleCheckAll(QListWidgetItem* _item);
	void ok(void);
	void cancel(void);

private:
	DialogCode			m_dialogAnswer;

	QHBoxLayout*		m_mainLayout;

	QVBoxLayout*		m_checkBoxLayout;
	QWidget*			m_checkBoxLayoutW;
		QCheckBox*			m_topBox;
		QCheckBox*			m_jglBox;
		QCheckBox*			m_midBox;
		QCheckBox*			m_botBox;
		QCheckBox*			m_supBox;
		QCheckBox*			m_maleBox;
		QCheckBox*			m_femaleBox;
		QCheckBox*			m_otherBox;

	QVBoxLayout*		m_listButtonsLayout;
	QWidget*			m_listButtonsLayoutW;
		QListWidget*		m_resourcesList;

	QHBoxLayout*		m_buttonLayout;
	QWidget*			m_buttonLayoutW;
	QPushButton*		m_okButton;
	QPushButton*		m_cancelButton;

	QList<QString>m_itemList;
};
