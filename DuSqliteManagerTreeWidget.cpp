/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "DuSqliteManagerTreeWidget.h"
#include <QMouseEvent>
#include <QAction>

namespace DuarteCorporation
{
DuSqliteManagerTreeWidget::DuSqliteManagerTreeWidget(QWidget *parent)
    : QTreeWidget(parent)
{
    mActionNewTable = new QAction(QIcon(":tabla"), tr("Nueva tabla"), this);
    mActionDeleteTable = new QAction(QIcon(":"), tr("Eliminar tabla"), this);
    mActionRemoveBase = new QAction(QIcon(":"), tr("Remover base"), this);
    mSELECT_FROM = new QAction(QIcon(":"), tr("SELECT * FROM"), this);
    mActionEditData = new QAction(QIcon(":"), tr("Editar datos"), this);
    auto separator = new QAction(this);
    separator->setSeparator(true);

    addActions({ mActionNewTable, mActionRemoveBase, separator,
                 mActionDeleteTable, mActionEditData, mSELECT_FROM,  });

    connect(mActionNewTable, &QAction::triggered, [&]() {
        emit newTable();
    });

    connect(mActionDeleteTable, &QAction::triggered, [&]() {
        emit dropTable();
    });

    connect(mActionRemoveBase, &QAction::triggered, [&]() {
        emit removeBase();
    });

    connect(mSELECT_FROM, &QAction::triggered, [&]() {
        emit selectFrom();
    });

    connect(mActionEditData, &QAction::triggered, [&]() {
        emit editData();
    });
}

DuSqliteManagerTreeWidget::Type DuSqliteManagerTreeWidget::type(
        DuTreeItem *item) const
{
    if (item == nullptr) {
        return NULLPTR;
    }
    auto padre = item->parent();
    if (padre == nullptr) {
        return BASE;
    }
    return TABLE;
}
} // end namespace DuarteCorporation
