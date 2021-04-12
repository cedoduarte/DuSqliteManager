/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerFindReplaceForm.h"
#include "DuSqliteManagerFindForm.h"
#include <QTextEdit>
#include <QRegExp>
#include <QtGui>

namespace DuarteCorporation
{
DuSqliteManagerFindForm::DuSqliteManagerFindForm(QWidget *parent)
    : DuSqliteManagerFindReplaceForm(parent)
{
    hideReplaceWidgets();
}

void DuSqliteManagerFindForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void DuSqliteManagerFindForm::writeSettings(QSettings &settings,
                                            const QString &prefix)
{
    DuSqliteManagerFindReplaceForm::writeSettings(settings, prefix);
}

void DuSqliteManagerFindForm::readSettings(QSettings &settings,
                                           const QString &prefix)
{
    DuSqliteManagerFindReplaceForm::readSettings(settings, prefix);
}
} // end namespace DuarteCorporation
