#include "DuSqliteManagerMainWindow.h"
#include "DuSqliteManagerDefines.h"
#include <QApplication>

using namespace DuarteCorporation;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName(APPNAME);
    a.setApplicationVersion(APPVER);
    a.setOrganizationDomain(ORGDOM);
    a.setOrganizationName(ORGNAME);
    a.setStyle("fusion");
    DuSqliteManagerMainWindow w;
    w.show();
    return a.exec();
}
