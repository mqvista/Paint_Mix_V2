    #ifndef DRIVERGC_GLOBAL_H
#define DRIVERGC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DRIVERGC_LIBRARY)
#  define DRIVERGCSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DRIVERGCSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DRIVERGC_GLOBAL_H
