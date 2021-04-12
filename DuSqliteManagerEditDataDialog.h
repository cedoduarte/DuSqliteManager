/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef DUSQLITEMANAGEREDITDATADIALOG_H
#define DUSQLITEMANAGEREDITDATADIALOG_H

#include <QDialog>

namespace Ui
{
class DuSqliteManagerEditDataDialog;
}

class QSqlTableModel;
class QAction;

namespace DuarteCorporation
{
class DuSqliteManagerEditDataDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DuSqliteManagerEditDataDialog(const QString &tableName,
                                           QWidget *parent = nullptr);
    ~DuSqliteManagerEditDataDialog();
private:
    Ui::DuSqliteManagerEditDataDialog *ui;
    QSqlTableModel *mModel;
    QAction *mActionAppendRow;
    QAction *mActionDeleteRow;
};
} // end namespace DuarteCorporation

#endif // DUSQLITEMANAGEREDITDATADIALOG_H
