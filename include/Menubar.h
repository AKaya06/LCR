#pragma once
#include <QtWidgets/qmenubar.h>

class LCR;

class Menubar : public QMenuBar
{
	Q_OBJECT
public:
	Menubar();
	virtual ~Menubar();


private slots:
	void showCreateDialog(void);
	void showConfigDialog(void);
	void showEditDialog(void);

	void showSettingsDialog(void);

	void showAboutDialog(void);


private:

};
