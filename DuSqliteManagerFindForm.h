/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef FINDFORM_H
#define FINDFORM_H

#include <QWidget>
#include <QTextCursor>
#include "DuSqliteManagerFindReplaceForm.h"

namespace DuarteCorporation
{
class DuSqliteManagerFindForm : public DuSqliteManagerFindReplaceForm
{
    Q_OBJECT
public:
    DuSqliteManagerFindForm(QWidget *parent = nullptr);
    virtual void writeSettings(QSettings &settings,
             const QString &prefix = "FindDialog");
    virtual void readSettings(QSettings &settings,
             const QString &prefix = "FindDialog");
protected:
    void changeEvent(QEvent *e);
};
} // end namespace DuarteCorporation

#endif // FINDFORM_H
