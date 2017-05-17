/****************************************************************************
** Meta object code from reading C++ file 'controlWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "controlWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlWidget_t {
    QByteArrayData data[11];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlWidget_t qt_meta_stringdata_ControlWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ControlWidget"
QT_MOC_LITERAL(1, 14, 19), // "exposureMenuChanged"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 19), // "intervalMenuChanged"
QT_MOC_LITERAL(4, 55, 16), // "frameRateChanged"
QT_MOC_LITERAL(5, 72, 14), // "updateExposure"
QT_MOC_LITERAL(6, 87, 10), // "updateGain"
QT_MOC_LITERAL(7, 98, 23), // "updateSelectableControl"
QT_MOC_LITERAL(8, 122, 24), // "updateSelectableCheckbox"
QT_MOC_LITERAL(9, 147, 21), // "setSelectableControl1"
QT_MOC_LITERAL(10, 169, 21) // "setSelectableControl2"

    },
    "ControlWidget\0exposureMenuChanged\0\0"
    "intervalMenuChanged\0frameRateChanged\0"
    "updateExposure\0updateGain\0"
    "updateSelectableControl\0"
    "updateSelectableCheckbox\0setSelectableControl1\0"
    "setSelectableControl2"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlWidget[] = {

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
       5,    1,   66,    2, 0x0a /* Public */,
       6,    1,   69,    2, 0x0a /* Public */,
       7,    1,   72,    2, 0x0a /* Public */,
       8,    1,   75,    2, 0x0a /* Public */,
       9,    1,   78,    2, 0x0a /* Public */,
      10,    1,   81,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ControlWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlWidget *_t = static_cast<ControlWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->exposureMenuChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->intervalMenuChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->frameRateChanged(); break;
        case 3: _t->updateExposure((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->updateGain((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateSelectableControl((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->updateSelectableCheckbox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->setSelectableControl1((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->setSelectableControl2((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject ControlWidget::staticMetaObject = {
    { &QGroupBox::staticMetaObject, qt_meta_stringdata_ControlWidget.data,
      qt_meta_data_ControlWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ControlWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ControlWidget.stringdata0))
        return static_cast<void*>(const_cast< ControlWidget*>(this));
    return QGroupBox::qt_metacast(_clname);
}

int ControlWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGroupBox::qt_metacall(_c, _id, _a);
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
