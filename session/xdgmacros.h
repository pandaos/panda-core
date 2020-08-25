#ifndef QTXDG_MACROS_H
#define QTXDG_MACROS_H

#ifdef __cplusplus
#  include <QtCore/qglobal.h>
#  ifndef QTXDG_DEPRECATED
#    define QTXDG_DEPRECATED Q_DECL_DEPRECATED
#  endif
#endif

#ifdef QTXDG_COMPILATION
    #define QTXDG_API    Q_DECL_EXPORT
#else
    #define QTXDG_API    Q_DECL_IMPORT
#endif

#if defined(QTXDG_COMPILATION) && defined(QTXDG_TESTS)
#    define QTXDG_AUTOTEST Q_DECL_EXPORT /* Build library,tests enabled */
#elif defined(QTXDG_BUILDING_TESTS)      /* Build the tests */
#    define QTXDG_AUTOTEST Q_DECL_IMPORT
#else
#    define QTXDG_AUTOTEST               /* Building library, tests disabled */
#endif

#ifndef QL1S
#define QL1S(x) QLatin1String(x)
#endif

#ifndef QL1C
#define QL1C(x) QLatin1Char(x)
#endif

#ifndef QSL
#define QSL(x) QStringLiteral(x)
#endif

#ifndef QBAL
#define QBAL(x) QByteArrayLiteral(x)
#endif

#endif // QTXDG_MACROS_H
