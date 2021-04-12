/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef FINDREPLACEDIALOG_H
#define FINDREPLACEDIALOG_H

#include <QDialog>

namespace Ui
{
class DuSqliteManagerFindReplaceDialog;
}

class QTextEdit;
class QSettings;

namespace DuarteCorporation
{
class DuSqliteManagerFindReplaceDialog : public QDialog
{
    Q_OBJECT
public:
    DuSqliteManagerFindReplaceDialog(QWidget *parent = nullptr);
    virtual ~DuSqliteManagerFindReplaceDialog();
    void setTextEdit(QTextEdit *textEdit);
    virtual void writeSettings(QSettings &settings,
       const QString &prefix = "FindReplaceDialog");
    virtual void readSettings(QSettings &settings,
       const QString &prefix = "FindReplaceDialog");
public slots:
    void findNext();
    void findPrev();
protected:
    void changeEvent(QEvent *e);

    Ui::DuSqliteManagerFindReplaceDialog *ui;
};
} // end namespace DuarteCorporation

#endif // FINDREPLACEDIALOG_H
