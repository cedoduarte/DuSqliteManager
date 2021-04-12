/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef DUPREFERENCIASDIALOG_H
#define DUPREFERENCIASDIALOG_H

#include <QDialog>
#include <QFont>

namespace Ui
{
class DuSqliteManagerPreferencesDialog;
}

namespace DuarteCorporation
{
class DuSqliteManagerPreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DuSqliteManagerPreferencesDialog(QWidget *parent = nullptr);
    ~DuSqliteManagerPreferencesDialog();
signals:
    void fontSelected(QFont);
private slots:
    void on_aplicar_clicked();
    void on_aceptar_clicked();
private:
    Ui::DuSqliteManagerPreferencesDialog *ui;
};
} // end namespace DuarteCorporation

#endif // DUPREFERENCIASDIALOG_H
