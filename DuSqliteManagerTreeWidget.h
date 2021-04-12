/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef DUTREEWIDGET_H
#define DUTREEWIDGET_H

#include <QTreeWidget>

class QAction;
using DuTreeItem = QTreeWidgetItem;

namespace DuarteCorporation
{
class DuSqliteManagerTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    enum Type
    {
        NULLPTR,
        TABLE,
        BASE
    };

    DuSqliteManagerTreeWidget(QWidget *parent = nullptr);
    Type type(DuTreeItem *item) const;

    Type type() const
    {
        return type(currentItem());
    }
signals:
    void newTable();
    void dropTable();
    void removeBase();
    void selectFrom();
    void editData();
private:
    QAction *mActionNewTable;
    QAction *mActionDeleteTable;
    QAction *mActionRemoveBase;
    QAction *mSELECT_FROM;
    QAction *mActionEditData;
};
} // end namespace DuarteCorporation

#endif // DUTREEWIDGET_H
