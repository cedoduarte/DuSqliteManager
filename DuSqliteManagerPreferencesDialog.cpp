#include "ui_DuSqliteManagerPreferencesDialog.h"
#include "DuSqliteManagerPreferencesDialog.h"
#include "DuSqliteManagerSettings.h"

namespace DuarteCorporation
{
DuSqliteManagerPreferencesDialog::DuSqliteManagerPreferencesDialog(
        QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DuSqliteManagerPreferencesDialog)
{
    ui->setupUi(this);
    auto vfont = DuSqliteManagerSettingsLoad(GFONT, KFONTTYPE);
    ui->fontComboBox->setCurrentFont(vfont.value<QFont>());
    ui->doubleSpinBox->setValue(vfont.value<QFont>().pointSizeF());
}

DuSqliteManagerPreferencesDialog::~DuSqliteManagerPreferencesDialog()
{
    delete ui;
}

void DuSqliteManagerPreferencesDialog::on_aplicar_clicked()
{
    auto f = ui->fontComboBox->currentFont();
    f.setPointSizeF(ui->doubleSpinBox->value());
    emit fontSelected(f);
}

void DuSqliteManagerPreferencesDialog::on_aceptar_clicked()
{
    on_aplicar_clicked();
    accept();
}
} // end namespace DuarteCorporation
