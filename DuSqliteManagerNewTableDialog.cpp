/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "ui_DuSqliteManagerNewTableDialog.h"
#include "DuSqliteManagerNewTableDialog.h"
#include <QRadioButton>
#include <QCheckBox>
#include <QComboBox>
#include <QAction>

namespace DuarteCorporation
{
DuSqliteManagerNewTableDialog::DuSqliteManagerNewTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DuSqliteManagerNewTableDialog)
{
    ui->setupUi(this);
    mActionAddField = new QAction(QIcon(":"), tr("Agregar"), this);
    mActionDeleteField = new QAction(QIcon(":"), tr("Eliminar"), this);
    ui->tableWidget->addActions({mActionAddField, mActionDeleteField});

    auto newComboBox = [&](QWidget *parent) {
        auto combo = new QComboBox(parent);
        combo->addItems({"INTEGER", "DOUBLE", "TEXT", "DATE", "TIME", "BOOL"});
        return combo;
    };

    connect(mActionAddField, &QAction::triggered, [&]() {
        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setCellWidget(rowCount, 1, newComboBox(this));
        ui->tableWidget->setCellWidget(rowCount, 2, new QRadioButton(this));
        ui->tableWidget->setCellWidget(rowCount, 3, new QCheckBox(this));
        ui->tableWidget->setCellWidget(rowCount, 4, new QCheckBox(this));
    });

    connect(mActionDeleteField, &QAction::triggered, [&]() {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    });
}

DuSqliteManagerNewTableDialog::~DuSqliteManagerNewTableDialog()
{
    delete ui;
}

QString DuSqliteManagerNewTableDialog::result() const
{
    QString res = QString("CREATE TABLE IF NOT EXISTS %1 (").
            arg(ui->nombre->text());
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i < rowCount; ++i) {
        auto name = ui->tableWidget->item(i, 0)->text();
        auto type = static_cast<QComboBox *>
                (ui->tableWidget->cellWidget(i, 1))->currentText();
        bool pk = static_cast<QRadioButton *>
                (ui->tableWidget->cellWidget(i, 2))->isChecked();
        bool nn = static_cast<QCheckBox *>
                (ui->tableWidget->cellWidget(i, 3))->isChecked();
        bool ai = static_cast<QCheckBox *>
                (ui->tableWidget->cellWidget(i, 4))->isChecked();
        res += name + " " + type;
        if (pk) {
            res += " PRIMARY KEY";
        }
        if (ai) {
            res += " AUTOINCREMENT";
        }
        if (nn) {
            res += " NOT NULL";
        }
        res += ",";
    }
    res[res.size()-1] = ')';
    return res;
}

void DuSqliteManagerNewTableDialog::on_aceptar_clicked()
{
    accept();
}

void DuSqliteManagerNewTableDialog::on_cancelar_clicked()
{
    reject();
}
} // end namespace DuarteCorporation
