/****************************************************************************
** Meta object code from reading C++ file 'viewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "viewWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'viewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ViewWidget_t {
    QByteArrayData data[13];
    char stringdata0[195];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ViewWidget_t qt_meta_stringdata_ViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ViewWidget"
QT_MOC_LITERAL(1, 11, 16), // "updateFrameCount"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 21), // "updateActualFrameRate"
QT_MOC_LITERAL(4, 51, 17), // "updateTemperature"
QT_MOC_LITERAL(5, 69, 19), // "updateDroppedFrames"
QT_MOC_LITERAL(6, 89, 14), // "updateProgress"
QT_MOC_LITERAL(7, 104, 15), // "updateHistogram"
QT_MOC_LITERAL(8, 120, 13), // "updateDisplay"
QT_MOC_LITERAL(9, 134, 13), // "stopRecording"
QT_MOC_LITERAL(10, 148, 15), // "recentreReticle"
QT_MOC_LITERAL(11, 164, 15), // "derotateReticle"
QT_MOC_LITERAL(12, 180, 14) // "setMonoPalette"

    },
    "ViewWidget\0updateFrameCount\0\0"
    "updateActualFrameRate\0updateTemperature\0"
    "updateDroppedFrames\0updateProgress\0"
    "updateHistogram\0updateDisplay\0"
    "stopRecording\0recentreReticle\0"
    "derotateReticle\0setMonoPalette"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ViewWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       3,    1,   72,    2, 0x06 /* Public */,
       4,    0,   75,    2, 0x06 /* Public */,
       5,    0,   76,    2, 0x06 /* Public */,
       6,    1,   77,    2, 0x06 /* Public */,
       7,    0,   80,    2, 0x06 /* Public */,
       8,    0,   81,    2, 0x06 /* Public */,
       9,    0,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QColor,    2,

       0        // eod
};

void ViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ViewWidget *_t = static_cast<ViewWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateFrameCount((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: _t->updateActualFrameRate((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 2: _t->updateTemperature(); break;
        case 3: _t->updateDroppedFrames(); break;
        case 4: _t->updateProgress((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: _t->updateHistogram(); break;
        case 6: _t->updateDisplay(); break;
        case 7: _t->stopRecording(); break;
        case 8: _t->recentreReticle(); break;
        case 9: _t->derotateReticle(); break;
        case 10: _t->setMonoPalette((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ViewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateFrameCount)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateActualFrameRate)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateTemperature)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateDroppedFrames)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateProgress)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateHistogram)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::updateDisplay)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ViewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ViewWidget::stopRecording)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject ViewWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_ViewWidget.data,
      qt_meta_data_ViewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ViewWidget.stringdata0))
        return static_cast<void*>(const_cast< ViewWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int ViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ViewWidget::updateFrameCount(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ViewWidget::updateActualFrameRate(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ViewWidget::updateTemperature()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ViewWidget::updateDroppedFrames()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void ViewWidget::updateProgress(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ViewWidget::updateHistogram()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void ViewWidget::updateDisplay()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void ViewWidget::stopRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
