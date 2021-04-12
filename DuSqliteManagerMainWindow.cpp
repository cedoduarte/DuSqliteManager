/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerMainWindow.h"
#include "DuSqliteManagerFindReplaceDialog.h"
#include "DuSqliteManagerPreferencesDialog.h"
#include "DuSqliteManagerNewTableDialog.h"
#include "DuSqliteManagerEditDataDialog.h"
#include "DuSqliteManagerMainWindow.h"
#include "DuSqliteManagerSettings.h"
#include <QUrl>
#include <QFile>
#include <QPrinter>
#include <QSqlError>
#include <QSqlQuery>
#include <QMimeData>
#include <QDropEvent>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>
#include <QPrintDialog>
#include <QSqlQueryModel>
#include <QDragMoveEvent>
#include <QTreeWidgetItem>
#include <QDragLeaveEvent>
#include <QDragEnterEvent>

using DuListItem = QListWidgetItem;

namespace DuarteCorporation
{
DuSqliteManagerMainWindow::DuSqliteManagerMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mQueryModel = new QSqlQueryModel(this);
    ui->tableView->setModel(mQueryModel);
    centralWidget()->layout()->setMargin(0);
    auto vfont = DuSqliteManagerSettingsLoad(GFONT, KFONTTYPE,
                                             ui->textEdit->font());
    ui->textEdit->setFont(vfont.value<QFont>());
    setAcceptDrops(true);
    connections();
}

DuSqliteManagerMainWindow::~DuSqliteManagerMainWindow()
{
    delete ui;
}

void DuSqliteManagerMainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void DuSqliteManagerMainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void DuSqliteManagerMainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    e->accept();
}

void DuSqliteManagerMainWindow::dropEvent(QDropEvent *e)
{
    auto data = e->mimeData();
    auto urls = data->urls();
    for (auto u : urls) {
        auto name = u.toLocalFile();
        auto baseitem = new DuTreeItem;
        baseitem->setIcon(0, QIcon(":base"));
        baseitem->setText(0, name);
        mDb.setDatabaseName(name);
        if (!mDb.open()) {
            QMessageBox::critical(this, "Error", QString("Error: No se ha" \
                                                         " podido abrir " \
                                  "la base de datos: %1").arg(name));
            return;
        }
        QSqlQuery qry;
        qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
        while (qry.next()) {
            auto tableitem = new DuTreeItem;
            tableitem->setIcon(0, QIcon(":tabla"));
            tableitem->setText(0, qry.value(0).toString());
            baseitem->addChild(tableitem);
        }
        ui->treeWidget->addTopLevelItem(baseitem);
    }
}

void DuSqliteManagerMainWindow::on_actionAbrir_base_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Abrir base de datos",
                                               QDir::currentPath(),
                                               "Base de datos (*.db);;" \
                                               "Cualquier tipo (*.*)");
    if (name.isEmpty())
        return;
    auto baseitem = new DuTreeItem;
    baseitem->setIcon(0, QIcon(":base"));
    baseitem->setText(0, name);
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Error: No se ha" \
                                                     " podido abrir " \
                              "la base de datos: %1").arg(name));
        return;
    }
    QSqlQuery qry;
    qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
    while (qry.next()) {
        auto tableitem = new DuTreeItem;
        tableitem->setIcon(0, QIcon(":tabla"));
        tableitem->setText(0, qry.value(0).toString());
        baseitem->addChild(tableitem);
    }
    ui->treeWidget->addTopLevelItem(baseitem);
}

void DuSqliteManagerMainWindow::on_actionGuardar_base_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Guardar base de datos",
                                               QDir::currentPath(),
                                               "Base de datos (*.db);;" \
                                               "Cualquier tipo (*.*)");
    if (name.isEmpty())
        return;
    auto baseitem = new DuTreeItem;
    baseitem->setIcon(0, QIcon(":base"));
    baseitem->setText(0, name);
    ui->treeWidget->addTopLevelItem(baseitem);
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Error: No se ha" \
                                                     " podido guardar " \
                              "la base de datos: %1").arg(name));
    }
}

void DuSqliteManagerMainWindow::on_actionAbrir_SQL_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Abrir SQL",
                                               QDir::currentPath(),
                                               "Archivo SQL (*.sql);;" \
                                               "Cualquier tipo (*.*)");
    if (name.isEmpty())
        return;
    QFile F(name);
    if (!F.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", QString("Error: %1").
                              arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    ui->textEdit->setText(S.readAll());
    F.close();
}

void DuSqliteManagerMainWindow::on_actionGuardar_SQL_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Guardar SQL",
                                               QDir::currentPath(),
                                               "Archivo SQL (*.sql);;" \
                                               "Cualquier tipo (*.*)");
    if (name.isEmpty())
        return;
    QFile F(name);
    if (!F.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", QString("Error: %1").
                              arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    S << ui->textEdit->toPlainText();
    F.flush();
    F.close();
}

void DuSqliteManagerMainWindow::on_actionImprimir_triggered()
{
    QPrintDialog P(this);
    if (P.exec() == QDialog::Rejected) {
        return;
    }
    ui->textEdit->print(P.printer());
}

void DuSqliteManagerMainWindow::on_actionQuitar_triggered()
{
    close();
}

void DuSqliteManagerMainWindow::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}

void DuSqliteManagerMainWindow::on_actionCortar_triggered()
{
    ui->textEdit->cut();
}

void DuSqliteManagerMainWindow::on_actionPegar_triggered()
{
    ui->textEdit->paste();
}

void DuSqliteManagerMainWindow::on_actionEjecutar_triggered()
{
    auto sql = ui->textEdit->toPlainText();
    if (sql.startsWith("select", Qt::CaseInsensitive)) {
        mQueryModel->setQuery(sql);
    } else if (sql.startsWith("create table", Qt::CaseInsensitive)) {
        QSqlQuery qry;
        if (!qry.exec(sql)) {
            ui->listWidget->addItem(new DuListItem(QIcon(":fallo"), sql));
            return;
        }
        ui->listWidget->addItem(new DuListItem(QIcon(":correcto"), sql));
        auto base = mDb.databaseName();
        int i, size = ui->treeWidget->topLevelItemCount();
        for (i = 0; i < size; ++i) {
            if (ui->treeWidget->topLevelItem(i)->text(0).toLower()
                    == base.toLower()) {
                break;
            }
        }
        auto baseitem = ui->treeWidget->topLevelItem(i);
        auto createtable = QString("create table ");
        if (sql.contains("if not exists", Qt::CaseInsensitive)) {
            createtable = QString("create table if not exists ");
        }
        int pos1 = createtable.size();
        int pos2 = sql.indexOf("(", pos1);
        auto table = sql.mid(pos1, pos2-pos1);
        table = table.mid(0, table.indexOf(" "));
        size = baseitem->childCount();
        for (i = 0; i < size; ++i) {
            if (baseitem->child(i)->text(0).toLower() == table.toLower()) {
                return;
            }
        }
        auto tablaitem = new DuTreeItem;
        tablaitem->setIcon(0, QIcon(":tabla"));
        tablaitem->setText(0, table);
        baseitem->addChild(tablaitem);
    } else if (sql.startsWith("drop table", Qt::CaseInsensitive)) {
        QSqlQuery qry;
        if (!qry.exec(sql)) {
            ui->listWidget->addItem(new DuListItem(QIcon(":fallo"), sql));
            return;
        }
        ui->listWidget->addItem(new DuListItem(QIcon(":correcto"), sql));
        auto base = mDb.databaseName();
        int i, tam = ui->treeWidget->topLevelItemCount();
        for (i = 0; i < tam; ++i) {
            if (ui->treeWidget->topLevelItem(i)->text(0).toLower()
                    == base.toLower()) {
                break;
            }
        }
        auto baseitem = ui->treeWidget->topLevelItem(i);
        tam = baseitem->childCount();
        auto droptable = QString("drop table");
        auto tabla = sql.mid(droptable.size());
        tabla = tabla.mid(1);
        for (i = 0; i < tam; ++i) {
            if (baseitem->child(i)->text(0).toLower() == tabla.toLower()) {
                break;
            }
        }
        baseitem->removeChild(baseitem->child(i));
    } else {
        QSqlQuery qry;
        if (!qry.exec(sql)) {
            ui->listWidget->addItem(new DuListItem(QIcon(":fallo"), sql));
            return;
        }
        ui->listWidget->addItem(new DuListItem(QIcon(":correcto"), sql));
    }
}

void DuSqliteManagerMainWindow::on_actionPreferencias_triggered()
{
    DuSqliteManagerPreferencesDialog p(this);
    connect(&p, &DuSqliteManagerPreferencesDialog::fontSelected,
            [&](const QFont &f) {
        ui->textEdit->setFont(f);
        DuSqliteManagerSettingsSave(GFONT, KFONTTYPE, f);
        // duSave(GFONT, KFONTSIZE, f.pointSizeF());
    });
    p.exec();
}

void DuSqliteManagerMainWindow::on_actionManual_triggered()
{
    // TODO: ESTO SE QUEDA ASÍ
}

void DuSqliteManagerMainWindow::on_actionAcerca_de_DuSQLiteManager_triggered()
{
    QMessageBox::about(this, "DuSQLiteManager",
                       "Autor: Carlos Enrique Duarte Ortiz\n" \
                       "Compañía: DuarteCorporation\n" \
                       "Fecha: 2 de enero de 2015\n" \
                       "Software: DuSQLiteManager");
}

void DuSqliteManagerMainWindow::on_actionBuscar_y_reemplazar_triggered()
{
    DuSqliteManagerFindReplaceDialog F(this);
    F.setTextEdit(ui->textEdit);
    F.exec();
}

void DuSqliteManagerMainWindow::on_treeWidget_clicked(const QModelIndex &index)
{
    if (index.parent().isValid()) {
        return;
    }
    auto name = index.data().toString();
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Error: No se ha" \
                                                     " podido abrir " \
                              "la base de datos: %1").arg(name));
    }
}

void DuSqliteManagerMainWindow::connections()
{
    connect(ui->treeWidget, &DuSqliteManagerTreeWidget::newTable, [&]() {
        if (ui->treeWidget->type() == DuSqliteManagerTreeWidget::BASE) {
            DuSqliteManagerNewTableDialog D(this);
            if (D.exec() == QDialog::Rejected) {
                return;
            }
            // agregar el código SQL para generar esa tabla
            ui->textEdit->setPlainText(D.result());
        } else {
            QMessageBox::warning(this, "Advertencia",
                                 "Esta función solo está permitida" \
                                 " cuando se selecciona una base de datos");
        }
    });

    connect(ui->treeWidget, &DuSqliteManagerTreeWidget::dropTable, [&]() {
        if (ui->treeWidget->type() == DuSqliteManagerTreeWidget::TABLE) {
            ui->textEdit->setPlainText(QString("DROP TABLE %1").
                   arg(ui->treeWidget->currentItem()->text(0)));
        } else {
            QMessageBox::warning(this, "Advertencia",
                                 "Esta función solo está permitida" \
                                 " cuando se selecciona una tabla");
            return;
        }
    });

    connect(ui->treeWidget, &DuSqliteManagerTreeWidget::removeBase, [&]() {
        if (ui->treeWidget->type() == DuSqliteManagerTreeWidget::BASE) {
            delete ui->treeWidget->currentItem();
        } else {
            QMessageBox::warning(this, "Advertencia",
                                 "Esta función solo está permitida" \
                                 " cuando se selecciona una base de datos");
        }
    });

    connect(ui->treeWidget, &DuSqliteManagerTreeWidget::selectFrom, [&]() {
        if (ui->treeWidget->type() == DuSqliteManagerTreeWidget::TABLE) {
            ui->textEdit->setPlainText(QString("SELECT * FROM %1").
                                       arg(ui->treeWidget->currentItem()
                                           ->text(0)));
        } else {
            QMessageBox::warning(this, "Advertencia",
                                 "Esta función solo está permitida" \
                                 " cuando se selecciona una tabla");
        }
    });

    connect(ui->treeWidget, &DuSqliteManagerTreeWidget::editData, [&]() {
        if (ui->treeWidget->type() == DuSqliteManagerTreeWidget::TABLE) {
            DuSqliteManagerEditDataDialog D(ui->treeWidget->currentItem()
                                            ->text(0), this);
            D.exec();
        } else {
            QMessageBox::warning(this, "Advertencia",
                                 "Esta función solo está permitida" \
                                 " cuando se selecciona una tabla");
        }
    });
}
} // end namespace DuarteCorporation
