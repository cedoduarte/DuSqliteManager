/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#include "DuSqliteManagerSettings.h"
#include <QSettings>

namespace DuarteCorporation
{
QVariant DuSqliteManagerSettingsLoad(const QString &g, const QString &k,
                                     const QVariant &vd)
{
    QSettings S;
    S.beginGroup(g);
    auto val = S.value(k, vd);
    S.endGroup();
    return val;
}

void DuSqliteManagerSettingsSave(const QString &g, const QString &k,
                                 const QVariant &v)
{
    QSettings S;
    S.beginGroup(g);
    S.setValue(k, v);
    S.endGroup();
}
} // end namespace DuarteCorporation
