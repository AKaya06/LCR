#include "LCR.h"
#include "Dataset.h"
#include "Champion.h"
#include "MyList.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	srand(time(NULL));
	LCR::instance()->show();
    return a.exec();
}
