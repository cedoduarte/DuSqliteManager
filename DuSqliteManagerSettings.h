/**
 * @author Carlos Enrique Duarte Ortiz <carlosduarte.1@hotmail.com>
*/

#ifndef DUAJUSTES_H
#define DUAJUSTES_H

#include <QString>
#include <QVariant>

#define GFONT "GFONT"
#define KFONTTYPE "KFONTTYPE"
#define KFONTSIZE "KFONTSIZE"

namespace DuarteCorporation
{
// carga ajustes
QVariant DuSqliteManagerSettingsLoad(const QString &g, const QString &k,
                const QVariant &vd = QVariant());

// guarda ajustes
void DuSqliteManagerSettingsSave(const QString &g, const QString &k,
                                 const QVariant &v);
} // end namespace DuarteCorporation

#endif // DUAJUSTES_H

