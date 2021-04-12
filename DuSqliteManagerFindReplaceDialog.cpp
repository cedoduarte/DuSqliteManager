/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerFindReplaceDialog.h"
#include "DuSqliteManagerFindReplaceDialog.h"

namespace DuarteCorporation
{
DuSqliteManagerFindReplaceDialog::DuSqliteManagerFindReplaceDialog(
        QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DuSqliteManagerFindReplaceDialog)
{
    ui->setupUi(this);
}

DuSqliteManagerFindReplaceDialog::~DuSqliteManagerFindReplaceDialog()
{
    delete ui;
}

void DuSqliteManagerFindReplaceDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void DuSqliteManagerFindReplaceDialog::setTextEdit(QTextEdit *textEdit)
{
    ui->findReplaceForm->setTextEdit(textEdit);
}

void DuSqliteManagerFindReplaceDialog::writeSettings(QSettings &settings,
                                      const QString &prefix)
{
    ui->findReplaceForm->writeSettings(settings, prefix);
}

void DuSqliteManagerFindReplaceDialog::readSettings(QSettings &settings,
                                     const QString &prefix)
{
    ui->findReplaceForm->readSettings(settings, prefix);
}

void DuSqliteManagerFindReplaceDialog::findNext()
{
    ui->findReplaceForm->findNext();
}

void DuSqliteManagerFindReplaceDialog::findPrev()
{
    ui->findReplaceForm->findPrev();
}
} // end namespace DuarteCorporation
