/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include "DuSqliteManagerFindReplaceDialog.h"

namespace DuarteCorporation
{
class DuSqliteManagerFindDialog : public DuSqliteManagerFindReplaceDialog
{
    Q_OBJECT
public:
    DuSqliteManagerFindDialog(QWidget *parent = nullptr);
    virtual void writeSettings(QSettings &settings,
             const QString &prefix = "FindDialog");
    virtual void readSettings(QSettings &settings,
             const QString &prefix = "FindDialog");
};
} // end namespace DuarteCorporation

#endif // FINDDIALOG_H
