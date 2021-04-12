/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerFindReplaceForm.h"
#include "DuSqliteManagerFindReplaceForm.h"
#include <QTextEdit>
#include <QSettings>
#include <QRegExp>
#include <QDebug>
#include <QtGui>

#define TEXT_TO_FIND "textToFind"
#define TEXT_TO_REPLACE "textToReplace"
#define DOWN_RADIO "downRadio"
#define UP_RADIO "upRadio"
#define CASE_CHECK "caseCheck"
#define WHOLE_CHECK "wholeCheck"
#define REGEXP_CHECK "regexpCheck"

namespace DuarteCorporation
{
DuSqliteManagerFindReplaceForm::DuSqliteManagerFindReplaceForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DuSqliteManagerFindReplaceForm)
    , mTextEdit(nullptr)
{
    ui->setupUi(this);
    ui->errorLabel->setText("");
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this,
            SLOT(textToFindChanged()));
    connect(ui->textToFind, SIGNAL(textChanged(QString)), this,
            SLOT(validateRegExp(QString)));
    connect(ui->regexCheckBox, SIGNAL(toggled(bool)), this,
            SLOT(regexpSelected(bool)));
    connect(ui->findButton, SIGNAL(clicked()), this,
            SLOT(find()));
    connect(ui->closeButton, SIGNAL(clicked()), parent,
            SLOT(close()));
    connect(ui->replaceButton, SIGNAL(clicked()), this,
            SLOT(replace()));
    connect(ui->replaceAllButton, SIGNAL(clicked()), this,
            SLOT(replaceAll()));
}

DuSqliteManagerFindReplaceForm::~DuSqliteManagerFindReplaceForm()
{
    delete ui;
}

void DuSqliteManagerFindReplaceForm::hideReplaceWidgets()
{
    ui->replaceLabel->setVisible(false);
    ui->textToReplace->setVisible(false);
    ui->replaceButton->setVisible(false);
    ui->replaceAllButton->setVisible(false);
}

void DuSqliteManagerFindReplaceForm::setTextEdit(QTextEdit *textEdit)
{
    mTextEdit = textEdit;
    connect(mTextEdit, SIGNAL(copyAvailable(bool)), ui->replaceButton,
            SLOT(setEnabled(bool)));
    connect(mTextEdit, SIGNAL(copyAvailable(bool)), ui->replaceAllButton,
            SLOT(setEnabled(bool)));
}

void DuSqliteManagerFindReplaceForm::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    if (e->type() == QEvent::LanguageChange) {
        ui->retranslateUi(this);
    }
}

void DuSqliteManagerFindReplaceForm::textToFindChanged()
{
    ui->findButton->setEnabled(ui->textToFind->text().size() > 0);
}

void DuSqliteManagerFindReplaceForm::regexpSelected(bool sel) {
    if (sel) {
        validateRegExp(ui->textToFind->text());
    } else {
        validateRegExp("");
    }
}

void DuSqliteManagerFindReplaceForm::validateRegExp(const QString &text)
{
    if (!ui->regexCheckBox->isChecked() || text.size() == 0) {
        ui->errorLabel->setText("");
        return; // nothing to validate
    }

    QRegExp reg(text,
                (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive
                                               : Qt::CaseInsensitive));

    if (reg.isValid()) {
        showError("");
    } else {
        showError(reg.errorString());
    }
}

void DuSqliteManagerFindReplaceForm::showError(const QString &error) {
    if (error == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600;" \
                                " color:#ff0000;\">" +
                                error +
                                "</spam>");
    }
}

void DuSqliteManagerFindReplaceForm::showMessage(const QString &message)
{
    if (message == "") {
        ui->errorLabel->setText("");
    } else {
        ui->errorLabel->setText("<span style=\" font-weight:600;" \
                                " color:green;\">" +
                                message +
                                "</spam>");
    }
}

void DuSqliteManagerFindReplaceForm::find()
{
    find(ui->downRadioButton->isChecked());
}

void DuSqliteManagerFindReplaceForm::find(bool next)
{
    if (!mTextEdit)
        return; // TODO: show some warning?

    // backward search
    bool back = !next;
    const QString &toSearch = ui->textToFind->text();
    bool result = false;
    QTextDocument::FindFlags flags;

    if (back)
        flags |= QTextDocument::FindBackward;
    if (ui->caseCheckBox->isChecked())
        flags |= QTextDocument::FindCaseSensitively;
    if (ui->wholeCheckBox->isChecked())
        flags |= QTextDocument::FindWholeWords;

    if (ui->regexCheckBox->isChecked()) {
        QRegExp reg(toSearch,
                    (ui->caseCheckBox->isChecked() ? Qt::CaseSensitive
                                                   : Qt::CaseInsensitive));

        qDebug() << "searching for regexp: " << reg.pattern();

        mTextCursor = mTextEdit->document()->find(reg, mTextCursor, flags);
        mTextEdit->setTextCursor(mTextCursor);
        result = (!mTextCursor.isNull());
    } else {
        qDebug() << "searching for: " << toSearch;

        result = mTextEdit->find(toSearch, flags);
    }

    if (result) {
        showError("");
    } else {
        showError(tr("no match found"));
        // move to the beginning of the document for the next find
        mTextCursor.setPosition(0);
        mTextEdit->setTextCursor(mTextCursor);
    }
}

void DuSqliteManagerFindReplaceForm::replace()
{
    if (!mTextEdit->textCursor().hasSelection()) {
        find();
    } else {
        mTextEdit->textCursor().insertText(ui->textToReplace->text());
        find();
    }
}

void DuSqliteManagerFindReplaceForm::replaceAll()
{
    int i = 0;
    while (mTextEdit->textCursor().hasSelection()){
        mTextEdit->textCursor().insertText(ui->textToReplace->text());
        find();
        i++;
    }
    showMessage(tr("Replaced %1 occurrence(s)").arg(i));
}

void DuSqliteManagerFindReplaceForm::writeSettings(QSettings &settings,
                                                   const QString &prefix)
{
    settings.beginGroup(prefix);
    settings.setValue(TEXT_TO_FIND, ui->textToFind->text());
    settings.setValue(TEXT_TO_REPLACE, ui->textToReplace->text());
    settings.setValue(DOWN_RADIO, ui->downRadioButton->isChecked());
    settings.setValue(UP_RADIO, ui->upRadioButton->isChecked());
    settings.setValue(CASE_CHECK, ui->caseCheckBox->isChecked());
    settings.setValue(WHOLE_CHECK, ui->wholeCheckBox->isChecked());
    settings.setValue(REGEXP_CHECK, ui->regexCheckBox->isChecked());
    settings.endGroup();
}

void DuSqliteManagerFindReplaceForm::readSettings(QSettings &settings,
                                                  const QString &prefix)
{
    settings.beginGroup(prefix);
    ui->textToFind->setText(settings.value(TEXT_TO_FIND, "").toString());
    ui->textToReplace->setText(settings.value(TEXT_TO_REPLACE, "").toString());
    ui->downRadioButton->setChecked(settings.value(DOWN_RADIO, true).toBool());
    ui->upRadioButton->setChecked(settings.value(UP_RADIO, false).toBool());
    ui->caseCheckBox->setChecked(settings.value(CASE_CHECK, false).toBool());
    ui->wholeCheckBox->setChecked(settings.value(WHOLE_CHECK, false).toBool());
    ui->regexCheckBox->setChecked(settings.value(REGEXP_CHECK, false).toBool());
    settings.endGroup();
}
} // end namespace DuarteCorporation
