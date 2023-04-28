#pragma once
#include <QtWidgets/QMainWindow>
#include "Champion.h"
#include <QtCore/qstring.h>

class QWidget;
class Menubar;
class HomeScreenWidget;

class LCR : public QMainWindow
{
    Q_OBJECT

public:
	static LCR* instance();
	void setHomeScreen();

	void applyDefaultStyleSheet(const QString& _additionalStyle);

private:
	LCR();
	virtual ~LCR(void);
	Menubar* m_menubar;
	HomeScreenWidget* m_homeScreenWidget;
	QString m_stylesheet;
};