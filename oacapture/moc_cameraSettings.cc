/****************************************************************************
** Meta object code from reading C++ file 'cameraSettings.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cameraSettings.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraSettings.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraSettings_t {
    QByteArrayData data[7];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraSettings_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraSettings_t qt_meta_stringdata_CameraSettings = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CameraSettings"
QT_MOC_LITERAL(1, 15, 19), // "updateSliderControl"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 21), // "updateCheckboxControl"
QT_MOC_LITERAL(4, 58, 12), // "buttonPushed"
QT_MOC_LITERAL(5, 71, 11), // "menuChanged"
QT_MOC_LITERAL(6, 83, 16) // "frameRateChanged"

    },
    "CameraSettings\0updateSliderControl\0\0"
    "updateCheckboxControl\0buttonPushed\0"
    "menuChanged\0frameRateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraSettings[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x0a /* Public */,
       3,    1,   42,    2, 0x0a /* Public */,
       4,    1,   45,    2, 0x0a /* Public */,
       5,    1,   48,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void CameraSettings::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraSettings *_t = static_cast<CameraSettings *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSliderControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateCheckboxControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->buttonPushed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->menuChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->frameRateChanged(); break;
        default: ;
        }
    }
}

const QMetaObject CameraSettings::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraSettings.data,
      qt_meta_data_CameraSettings,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraSettings::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraSettings::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraSettings.stringdata0))
        return static_cast<void*>(const_cast< CameraSettings*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraSettings::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
