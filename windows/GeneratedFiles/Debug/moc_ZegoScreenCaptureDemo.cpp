/****************************************************************************
** Meta object code from reading C++ file 'ZegoScreenCaptureDemo.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ZegoScreenCaptureDemo.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ZegoScreenCaptureDemo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ZegoScreenCaptureDemo_t {
    QByteArrayData data[13];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ZegoScreenCaptureDemo_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ZegoScreenCaptureDemo_t qt_meta_stringdata_ZegoScreenCaptureDemo = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ZegoScreenCaptureDemo"
QT_MOC_LITERAL(1, 22, 18), // "SetThumbnailWindow"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 2), // "id"
QT_MOC_LITERAL(4, 45, 26), // "onBoundingRectangleChanged"
QT_MOC_LITERAL(5, 72, 4), // "rect"
QT_MOC_LITERAL(6, 77, 18), // "onRectangleChanged"
QT_MOC_LITERAL(7, 96, 11), // "onAppendLog"
QT_MOC_LITERAL(8, 108, 3), // "log"
QT_MOC_LITERAL(9, 112, 18), // "onStreamUrlChanged"
QT_MOC_LITERAL(10, 131, 4), // "rtmp"
QT_MOC_LITERAL(11, 136, 3), // "hls"
QT_MOC_LITERAL(12, 140, 19) // "onOpenThumbnailView"

    },
    "ZegoScreenCaptureDemo\0SetThumbnailWindow\0"
    "\0id\0onBoundingRectangleChanged\0rect\0"
    "onRectangleChanged\0onAppendLog\0log\0"
    "onStreamUrlChanged\0rtmp\0hls\0"
    "onOpenThumbnailView"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ZegoScreenCaptureDemo[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x05 /* Protected */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   47,    2, 0x09 /* Protected */,
       6,    1,   50,    2, 0x09 /* Protected */,
       7,    1,   53,    2, 0x09 /* Protected */,
       9,    2,   56,    2, 0x09 /* Protected */,
      12,    0,   61,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QRect,    5,
    QMetaType::Void, QMetaType::QRect,    5,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,

       0        // eod
};

void ZegoScreenCaptureDemo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ZegoScreenCaptureDemo *_t = static_cast<ZegoScreenCaptureDemo *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetThumbnailWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onBoundingRectangleChanged((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 2: _t->onRectangleChanged((*reinterpret_cast< QRect(*)>(_a[1]))); break;
        case 3: _t->onAppendLog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onStreamUrlChanged((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->onOpenThumbnailView(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ZegoScreenCaptureDemo::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ZegoScreenCaptureDemo::SetThumbnailWindow)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ZegoScreenCaptureDemo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ZegoScreenCaptureDemo.data,
      qt_meta_data_ZegoScreenCaptureDemo,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ZegoScreenCaptureDemo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ZegoScreenCaptureDemo::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ZegoScreenCaptureDemo.stringdata0))
        return static_cast<void*>(const_cast< ZegoScreenCaptureDemo*>(this));
    return QWidget::qt_metacast(_clname);
}

int ZegoScreenCaptureDemo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ZegoScreenCaptureDemo::SetThumbnailWindow(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
