/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

namespace Ui
{
class MainWindow;
}

class QSqlQueryModel;

namespace DuarteCorporation
{
class DuSqliteManagerMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit DuSqliteManagerMainWindow(QWidget *parent = nullptr);
    ~DuSqliteManagerMainWindow();
protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);
private slots:
    void on_actionPegar_triggered();
    void on_actionQuitar_triggered();
    void on_actionCopiar_triggered();
    void on_actionCortar_triggered();
    void on_actionManual_triggered();
    void on_actionEjecutar_triggered();
    void on_actionImprimir_triggered();
    void on_actionAbrir_SQL_triggered();
    void on_actionAbrir_base_triggered();
    void on_actionGuardar_SQL_triggered();
    void on_actionGuardar_base_triggered();
    void on_actionPreferencias_triggered();
    void on_actionBuscar_y_reemplazar_triggered();
    void on_actionAcerca_de_DuSQLiteManager_triggered();
    void on_treeWidget_clicked(const QModelIndex &index);
private:
    void connections();

    Ui::MainWindow *ui;
    QSqlDatabase mDb;
    QSqlQueryModel *mQueryModel;
};
} // end namespace DuarteCorporation

#endif // MAINWINDOW_H
