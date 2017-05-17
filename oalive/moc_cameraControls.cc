/****************************************************************************
** Meta object code from reading C++ file 'cameraControls.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "cameraControls.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'cameraControls.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CameraControls_t {
    QByteArrayData data[11];
    char stringdata0[176];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraControls_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraControls_t qt_meta_stringdata_CameraControls = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CameraControls"
QT_MOC_LITERAL(1, 15, 19), // "updateSliderControl"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 21), // "updateCheckboxControl"
QT_MOC_LITERAL(4, 58, 21), // "updateFrameRateSlider"
QT_MOC_LITERAL(5, 80, 16), // "frameRateChanged"
QT_MOC_LITERAL(6, 97, 15), // "getFPSNumerator"
QT_MOC_LITERAL(7, 113, 17), // "getFPSDenominator"
QT_MOC_LITERAL(8, 131, 12), // "buttonPushed"
QT_MOC_LITERAL(9, 144, 11), // "menuChanged"
QT_MOC_LITERAL(10, 156, 19) // "updateExposureUnits"

    },
    "CameraControls\0updateSliderControl\0\0"
    "updateCheckboxControl\0updateFrameRateSlider\0"
    "frameRateChanged\0getFPSNumerator\0"
    "getFPSDenominator\0buttonPushed\0"
    "menuChanged\0updateExposureUnits"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraControls[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       3,    1,   62,    2, 0x0a /* Public */,
       4,    0,   65,    2, 0x0a /* Public */,
       5,    0,   66,    2, 0x0a /* Public */,
       6,    0,   67,    2, 0x0a /* Public */,
       7,    0,   68,    2, 0x0a /* Public */,
       8,    1,   69,    2, 0x0a /* Public */,
       9,    1,   72,    2, 0x0a /* Public */,
      10,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int,
    QMetaType::Int,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void CameraControls::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraControls *_t = static_cast<CameraControls *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateSliderControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->updateCheckboxControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->updateFrameRateSlider(); break;
        case 3: _t->frameRateChanged(); break;
        case 4: { int _r = _t->getFPSNumerator();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: { int _r = _t->getFPSDenominator();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 6: _t->buttonPushed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->menuChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->updateExposureUnits(); break;
        default: ;
        }
    }
}

const QMetaObject CameraControls::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_CameraControls.data,
      qt_meta_data_CameraControls,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CameraControls::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraControls::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CameraControls.stringdata0))
        return static_cast<void*>(const_cast< CameraControls*>(this));
    return QWidget::qt_metacast(_clname);
}

int CameraControls::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
