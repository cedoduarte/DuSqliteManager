/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerEditDataDialog.h"
#include "DuSqliteManagerEditDataDialog.h"
#include <QSqlTableModel>

namespace DuarteCorporation
{
DuSqliteManagerEditDataDialog::DuSqliteManagerEditDataDialog(
        const QString &tableName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DuSqliteManagerEditDataDialog)
{
    ui->setupUi(this);
    mActionAppendRow = new QAction(QIcon(":"), tr("Agregar fila"), this);
    mActionDeleteRow = new QAction(QIcon(":"), tr("Eliminar fila"), this);
    ui->tableView->addActions({mActionAppendRow, mActionDeleteRow});

    setWindowTitle(tableName);
    mModel = new QSqlTableModel(this);
    mModel->setTable(tableName);
    mModel->select();
    ui->tableView->setModel(mModel);
    layout()->setMargin(0);

    connect(mActionAppendRow, &QAction::triggered, [&]() {
        mModel->insertRow(mModel->rowCount());
    });

    connect(mActionDeleteRow, &QAction::triggered, [&]() {
        mModel->removeRow(ui->tableView->currentIndex().row());
    });
}

DuSqliteManagerEditDataDialog::~DuSqliteManagerEditDataDialog()
{
    delete ui;
}
} // end namespace DuarteCorporation
