/****************************************************************************
** Meta object code from reading C++ file 'ZegoExternalCaptureFactory.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZegoExternalCaptureFactory.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoExternalCaptureFactory.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoExternalCaptureDevice_t {
    QByteArrayData data[1];
    char stringdata0[26];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoExternalCaptureDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoExternalCaptureDevice_t qt_meta_stringdata_ZegoExternalCaptureDevice = {
    {
QT_MOC_LITERAL(0, 0, 25) // "ZegoExternalCaptureDevice"

    },
    "ZegoExternalCaptureDevice"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoExternalCaptureDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ZegoExternalCaptureDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject ZegoExternalCaptureDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZegoExternalCaptureDevice.data,
      qt_meta_data_ZegoExternalCaptureDevice,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoExternalCaptureDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoExternalCaptureDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoExternalCaptureDevice.stringdata0))
        return static_cast<void*>(const_cast< ZegoExternalCaptureDevice*>(this));
    if (!strcmp(_clname, "AVE::VideoCaptureDevice"))
        return static_cast< AVE::VideoCaptureDevice*>(const_cast< ZegoExternalCaptureDevice*>(this));
    return QObject::qt_metacast(_clname);
}

int ZegoExternalCaptureDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
struct qt_meta_stringdata_ZegoExternalCaptureFactory_t {
    QByteArrayData data[4];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoExternalCaptureFactory_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoExternalCaptureFactory_t qt_meta_stringdata_ZegoExternalCaptureFactory = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ZegoExternalCaptureFactory"
QT_MOC_LITERAL(1, 27, 16), // "sigDeviceCreated"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 18) // "sigDeviceDestroyed"

    },
    "ZegoExternalCaptureFactory\0sigDeviceCreated\0"
    "\0sigDeviceDestroyed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoExternalCaptureFactory[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,
       3,    0,   25,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ZegoExternalCaptureFactory::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoExternalCaptureFactory *_t = static_cast<ZegoExternalCaptureFactory *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sigDeviceCreated(); break;
        case 1: _t->sigDeviceDestroyed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoExternalCaptureFactory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoExternalCaptureFactory::sigDeviceCreated)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ZegoExternalCaptureFactory::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoExternalCaptureFactory::sigDeviceDestroyed)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ZegoExternalCaptureFactory::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ZegoExternalCaptureFactory.data,
      qt_meta_data_ZegoExternalCaptureFactory,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoExternalCaptureFactory::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoExternalCaptureFactory::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoExternalCaptureFactory.stringdata0))
        return static_cast<void*>(const_cast< ZegoExternalCaptureFactory*>(this));
    if (!strcmp(_clname, "AVE::VideoCaptureFactory"))
        return static_cast< AVE::VideoCaptureFactory*>(const_cast< ZegoExternalCaptureFactory*>(this));
    return QObject::qt_metacast(_clname);
}

int ZegoExternalCaptureFactory::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ZegoExternalCaptureFactory::sigDeviceCreated()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ZegoExternalCaptureFactory::sigDeviceDestroyed()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
