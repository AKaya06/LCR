#pragma once
#include <QtWidgets/qwidget.h>
#include "Champion.h"

class QVBoxLayout;
class QHBoxLayout;
class QLabel;
class QListWidget;
class QPushButton;
class QSettings;

class HomeScreenWidget : public QWidget
{
	Q_OBJECT
public:
	HomeScreenWidget();
	virtual ~HomeScreenWidget();

	void refreshRoleList();

	void disableAllItems();
	
private slots:
	void rollChampion(void);
	void setRolledChampion(void);

private:
	Champion*			m_champion;

	QVBoxLayout*		m_mainLayout;

	QLabel*				m_welcomeLabel;

	QHBoxLayout*		m_listLayout;
	QWidget*			m_listLayoutW;

	QVBoxLayout*		m_rollWidgetLayout;
	QListWidget*		m_rollListWidget;
	QWidget*			m_rollWidgetLayoutW;

	QPushButton*		m_rollButton;
	QWidget*			m_rollButtonW;

	QVBoxLayout*		m_outputWidgetLayout;
	QWidget*			m_outputWidgetLayoutW;
	QLabel*				m_yourChampion;
	QLabel*				m_championNameLabel;
	QLabel*				m_championRoleLabel;

	QTimer*				m_timer;
	QList<Champion*>	champions;

	int					m_animationCount;
};
