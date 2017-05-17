/****************************************************************************
** Meta object code from reading C++ file 'previewWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "previewWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'previewWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PreviewWidget_t {
    QByteArrayData data[13];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PreviewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PreviewWidget_t qt_meta_stringdata_PreviewWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PreviewWidget"
QT_MOC_LITERAL(1, 14, 16), // "updateFrameCount"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 21), // "updateActualFrameRate"
QT_MOC_LITERAL(4, 54, 17), // "updateTemperature"
QT_MOC_LITERAL(5, 72, 19), // "updateDroppedFrames"
QT_MOC_LITERAL(6, 92, 14), // "updateProgress"
QT_MOC_LITERAL(7, 107, 15), // "updateHistogram"
QT_MOC_LITERAL(8, 123, 13), // "updateDisplay"
QT_MOC_LITERAL(9, 137, 13), // "stopRecording"
QT_MOC_LITERAL(10, 151, 15), // "recentreReticle"
QT_MOC_LITERAL(11, 167, 15), // "derotateReticle"
QT_MOC_LITERAL(12, 183, 14) // "setMonoPalette"

    },
    "PreviewWidget\0updateFrameCount\0\0"
    "updateActualFrameRate\0updateTemperature\0"
    "updateDroppedFrames\0updateProgress\0"
    "updateHistogram\0updateDisplay\0"
    "stopRecording\0recentreReticle\0"
    "derotateReticle\0setMonoPalette"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PreviewWidget[] = {

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

void PreviewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PreviewWidget *_t = static_cast<PreviewWidget *>(_o);
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
            typedef void (PreviewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateFrameCount)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateActualFrameRate)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateTemperature)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateDroppedFrames)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)(unsigned int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateProgress)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateHistogram)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::updateDisplay)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (PreviewWidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PreviewWidget::stopRecording)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject PreviewWidget::staticMetaObject = {
    { &QFrame::staticMetaObject, qt_meta_stringdata_PreviewWidget.data,
      qt_meta_data_PreviewWidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PreviewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PreviewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PreviewWidget.stringdata0))
        return static_cast<void*>(const_cast< PreviewWidget*>(this));
    return QFrame::qt_metacast(_clname);
}

int PreviewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void PreviewWidget::updateFrameCount(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PreviewWidget::updateActualFrameRate(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PreviewWidget::updateTemperature()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PreviewWidget::updateDroppedFrames()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void PreviewWidget::updateProgress(unsigned int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void PreviewWidget::updateHistogram()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void PreviewWidget::updateDisplay()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void PreviewWidget::stopRecording()
{
    QMetaObject::activate(this, &staticMetaObject, 7, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
