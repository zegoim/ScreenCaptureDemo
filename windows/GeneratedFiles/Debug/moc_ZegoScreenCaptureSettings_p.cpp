/****************************************************************************
** Meta object code from reading C++ file 'ZegoScreenCaptureSettings_p.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZegoScreenCaptureSettings_p.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoScreenCaptureSettings_p.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate_t {
    QByteArrayData data[16];
    char stringdata0[226];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate_t qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate = {
    {
QT_MOC_LITERAL(0, 0, 32), // "ZegoScreenCaptureSettingsPrivate"
QT_MOC_LITERAL(1, 33, 20), // "screenIndexChanged_p"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 5), // "index"
QT_MOC_LITERAL(4, 61, 20), // "windowIndexChanged_p"
QT_MOC_LITERAL(5, 82, 24), // "resolutionIndexChanged_p"
QT_MOC_LITERAL(6, 107, 26), // "boundingRectangleChanged_p"
QT_MOC_LITERAL(7, 134, 4), // "rect"
QT_MOC_LITERAL(8, 139, 18), // "rectangleChanged_p"
QT_MOC_LITERAL(9, 158, 11), // "appendLog_p"
QT_MOC_LITERAL(10, 170, 3), // "log"
QT_MOC_LITERAL(11, 174, 18), // "streamUrlChanged_p"
QT_MOC_LITERAL(12, 193, 4), // "rtmp"
QT_MOC_LITERAL(13, 198, 3), // "hls"
QT_MOC_LITERAL(14, 202, 20), // "windowCaptureChanged"
QT_MOC_LITERAL(15, 223, 2) // "id"

    },
    "ZegoScreenCaptureSettingsPrivate\0"
    "screenIndexChanged_p\0\0index\0"
    "windowIndexChanged_p\0resolutionIndexChanged_p\0"
    "boundingRectangleChanged_p\0rect\0"
    "rectangleChanged_p\0appendLog_p\0log\0"
    "streamUrlChanged_p\0rtmp\0hls\0"
    "windowCaptureChanged\0id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoScreenCaptureSettingsPrivate[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    1,   60,    2, 0x06 /* Public */,
       6,    1,   63,    2, 0x06 /* Public */,
       8,    1,   66,    2, 0x06 /* Public */,
       9,    1,   69,    2, 0x06 /* Public */,
      11,    2,   72,    2, 0x06 /* Public */,
      14,    1,   77,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QRect,    7,
    QMetaType::Void, QMetaType::QRect,    7,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   12,   13,
    QMetaType::Void, QMetaType::LongLong,   15,

       0        // eod
};

void ZegoScreenCaptureSettingsPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoScreenCaptureSettingsPrivate *_t = static_cast<ZegoScreenCaptureSettingsPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->screenIndexChanged_p((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->windowIndexChanged_p((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->resolutionIndexChanged_p((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->boundingRectangleChanged_p((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 4: _t->rectangleChanged_p((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 5: _t->appendLog_p((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->streamUrlChanged_p((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->windowCaptureChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::screenIndexChanged_p)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::windowIndexChanged_p)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::resolutionIndexChanged_p)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(QRect );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::boundingRectangleChanged_p)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(QRect );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::rectangleChanged_p)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::appendLog_p)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::streamUrlChanged_p)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ZegoScreenCaptureSettingsPrivate::*_t)(qint64 );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureSettingsPrivate::windowCaptureChanged)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject ZegoScreenCaptureSettingsPrivate::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate.data,
      qt_meta_data_ZegoScreenCaptureSettingsPrivate,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoScreenCaptureSettingsPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoScreenCaptureSettingsPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoScreenCaptureSettingsPrivate.stringdata0))
        return static_cast<void*>(const_cast< ZegoScreenCaptureSettingsPrivate*>(this));
    return QObject::qt_metacast(_clname);
}

int ZegoScreenCaptureSettingsPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ZegoScreenCaptureSettingsPrivate::screenIndexChanged_p(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ZegoScreenCaptureSettingsPrivate::windowIndexChanged_p(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ZegoScreenCaptureSettingsPrivate::resolutionIndexChanged_p(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ZegoScreenCaptureSettingsPrivate::boundingRectangleChanged_p(QRect _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ZegoScreenCaptureSettingsPrivate::rectangleChanged_p(QRect _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ZegoScreenCaptureSettingsPrivate::appendLog_p(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ZegoScreenCaptureSettingsPrivate::streamUrlChanged_p(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ZegoScreenCaptureSettingsPrivate::windowCaptureChanged(qint64 _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
