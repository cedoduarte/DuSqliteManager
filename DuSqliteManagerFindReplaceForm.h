/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef FINDREPLACEFORM_H
#define FINDREPLACEFORM_H

#include <QWidget>
#include <QTextCursor>

namespace Ui
{
class DuSqliteManagerFindReplaceForm;
}

class QTextEdit;
class QSettings;

namespace DuarteCorporation
{
class DuSqliteManagerFindReplaceForm : public QWidget
{
    Q_OBJECT
public:
    DuSqliteManagerFindReplaceForm(QWidget *parent = nullptr);
    virtual ~DuSqliteManagerFindReplaceForm();
    void setTextEdit(QTextEdit *textEdit);
    void hideReplaceWidgets();

    virtual void writeSettings(QSettings &settings,
       const QString &prefix = "FindReplaceDialog");

    virtual void readSettings(QSettings &settings,
       const QString &prefix = "FindReplaceDialog");
public slots:
    void find(bool down);
    void find();

    void findNext()
    {
        find(true);
    }

    void findPrev()
    {
        find(false);
    }

    void replace();
    void replaceAll();
protected:
    void changeEvent(QEvent *e);
    void showError(const QString &error);
    void showMessage(const QString &message);
protected slots:
    void textToFindChanged();
    void validateRegExp(const QString &text);
    void regexpSelected(bool sel);
protected:
    Ui::DuSqliteManagerFindReplaceForm *ui;
    QTextCursor mTextCursor;
    QTextEdit *mTextEdit;
};
} // end namespace DuarteCorporation

#endif // FINDREPLACEFORM_H
