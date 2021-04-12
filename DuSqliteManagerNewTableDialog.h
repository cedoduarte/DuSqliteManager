/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef DUNUEVATABLADIALOG_H
#define DUNUEVATABLADIALOG_H

#include <QDialog>

namespace Ui
{
class DuSqliteManagerNewTableDialog;
}

class QAction;

namespace DuarteCorporation
{
class DuSqliteManagerNewTableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DuSqliteManagerNewTableDialog(QWidget *parent = nullptr);
    ~DuSqliteManagerNewTableDialog();
    QString result() const;
private slots:
    void on_aceptar_clicked();
    void on_cancelar_clicked();
private:
    Ui::DuSqliteManagerNewTableDialog *ui;
    QAction *mActionAddField;
    QAction *mActionDeleteField;
};
} // end namespace DuarteCorporation

#endif // DUNUEVATABLADIALOG_H
