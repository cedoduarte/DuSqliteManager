/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerFindReplaceDialog.h"
#include "DuSqliteManagerFindDialog.h"

namespace DuarteCorporation
{
DuSqliteManagerFindDialog::DuSqliteManagerFindDialog(QWidget *parent)
    : DuSqliteManagerFindReplaceDialog(parent)
{
    ui->findReplaceForm->hideReplaceWidgets();
    setWindowTitle(tr("Find"));
}

void DuSqliteManagerFindDialog::writeSettings(QSettings &settings,
                                              const QString &prefix)
{
    DuSqliteManagerFindReplaceDialog::writeSettings(settings, prefix);
}

void DuSqliteManagerFindDialog::readSettings(QSettings &settings,
                                             const QString &prefix)
{
    DuSqliteManagerFindReplaceDialog::readSettings(settings, prefix);
}
} // end namespace DuarteCorporation
