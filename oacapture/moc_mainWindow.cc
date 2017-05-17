/****************************************************************************
** Meta object code from reading C++ file 'mainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[53];
    char stringdata0[837];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 13), // "connectCamera"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 16), // "disconnectCamera"
QT_MOC_LITERAL(4, 43, 13), // "rescanCameras"
QT_MOC_LITERAL(5, 57, 18), // "connectFilterWheel"
QT_MOC_LITERAL(6, 76, 21), // "disconnectFilterWheel"
QT_MOC_LITERAL(7, 98, 20), // "warmResetFilterWheel"
QT_MOC_LITERAL(8, 119, 20), // "coldResetFilterWheel"
QT_MOC_LITERAL(9, 140, 18), // "rescanFilterWheels"
QT_MOC_LITERAL(10, 159, 12), // "connectTimer"
QT_MOC_LITERAL(11, 172, 15), // "disconnectTimer"
QT_MOC_LITERAL(12, 188, 10), // "resetTimer"
QT_MOC_LITERAL(13, 199, 12), // "rescanTimers"
QT_MOC_LITERAL(14, 212, 4), // "quit"
QT_MOC_LITERAL(15, 217, 12), // "setNightMode"
QT_MOC_LITERAL(16, 230, 15), // "enableHistogram"
QT_MOC_LITERAL(17, 246, 15), // "histogramClosed"
QT_MOC_LITERAL(18, 262, 13), // "enableReticle"
QT_MOC_LITERAL(19, 276, 14), // "enableFocusAid"
QT_MOC_LITERAL(20, 291, 11), // "enableFlipX"
QT_MOC_LITERAL(21, 303, 11), // "enableFlipY"
QT_MOC_LITERAL(22, 315, 14), // "enableDemosaic"
QT_MOC_LITERAL(23, 330, 11), // "aboutDialog"
QT_MOC_LITERAL(24, 342, 17), // "doGeneralSettings"
QT_MOC_LITERAL(25, 360, 17), // "doCaptureSettings"
QT_MOC_LITERAL(26, 378, 16), // "doCameraSettings"
QT_MOC_LITERAL(27, 395, 17), // "doProfileSettings"
QT_MOC_LITERAL(28, 413, 16), // "doFilterSettings"
QT_MOC_LITERAL(29, 430, 18), // "doDemosaicSettings"
QT_MOC_LITERAL(30, 449, 14), // "doFITSSettings"
QT_MOC_LITERAL(31, 464, 15), // "doTimerSettings"
QT_MOC_LITERAL(32, 480, 17), // "doAutorunSettings"
QT_MOC_LITERAL(33, 498, 19), // "doHistogramSettings"
QT_MOC_LITERAL(34, 518, 12), // "doCameraMenu"
QT_MOC_LITERAL(35, 531, 17), // "doFilterWheelMenu"
QT_MOC_LITERAL(36, 549, 11), // "doTimerMenu"
QT_MOC_LITERAL(37, 561, 19), // "closeSettingsWindow"
QT_MOC_LITERAL(38, 581, 14), // "settingsClosed"
QT_MOC_LITERAL(39, 596, 18), // "changePreviewState"
QT_MOC_LITERAL(40, 615, 14), // "doHideControls"
QT_MOC_LITERAL(41, 630, 26), // "advancedFilterWheelHandler"
QT_MOC_LITERAL(42, 657, 18), // "advancedPTRHandler"
QT_MOC_LITERAL(43, 676, 19), // "closeAdvancedWindow"
QT_MOC_LITERAL(44, 696, 14), // "advancedClosed"
QT_MOC_LITERAL(45, 711, 19), // "doColouriseSettings"
QT_MOC_LITERAL(46, 731, 17), // "setCapturedFrames"
QT_MOC_LITERAL(47, 749, 18), // "setActualFrameRate"
QT_MOC_LITERAL(48, 768, 14), // "setTemperature"
QT_MOC_LITERAL(49, 783, 16), // "setDroppedFrames"
QT_MOC_LITERAL(50, 800, 11), // "setProgress"
QT_MOC_LITERAL(51, 812, 6), // "reveal"
QT_MOC_LITERAL(52, 819, 17) // "showStatusMessage"

    },
    "MainWindow\0connectCamera\0\0disconnectCamera\0"
    "rescanCameras\0connectFilterWheel\0"
    "disconnectFilterWheel\0warmResetFilterWheel\0"
    "coldResetFilterWheel\0rescanFilterWheels\0"
    "connectTimer\0disconnectTimer\0resetTimer\0"
    "rescanTimers\0quit\0setNightMode\0"
    "enableHistogram\0histogramClosed\0"
    "enableReticle\0enableFocusAid\0enableFlipX\0"
    "enableFlipY\0enableDemosaic\0aboutDialog\0"
    "doGeneralSettings\0doCaptureSettings\0"
    "doCameraSettings\0doProfileSettings\0"
    "doFilterSettings\0doDemosaicSettings\0"
    "doFITSSettings\0doTimerSettings\0"
    "doAutorunSettings\0doHistogramSettings\0"
    "doCameraMenu\0doFilterWheelMenu\0"
    "doTimerMenu\0closeSettingsWindow\0"
    "settingsClosed\0changePreviewState\0"
    "doHideControls\0advancedFilterWheelHandler\0"
    "advancedPTRHandler\0closeAdvancedWindow\0"
    "advancedClosed\0doColouriseSettings\0"
    "setCapturedFrames\0setActualFrameRate\0"
    "setTemperature\0setDroppedFrames\0"
    "setProgress\0reveal\0showStatusMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      51,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  269,    2, 0x0a /* Public */,
       3,    0,  272,    2, 0x0a /* Public */,
       4,    0,  273,    2, 0x0a /* Public */,
       5,    1,  274,    2, 0x0a /* Public */,
       6,    0,  277,    2, 0x0a /* Public */,
       7,    0,  278,    2, 0x0a /* Public */,
       8,    0,  279,    2, 0x0a /* Public */,
       9,    0,  280,    2, 0x0a /* Public */,
      10,    1,  281,    2, 0x0a /* Public */,
      11,    0,  284,    2, 0x0a /* Public */,
      12,    0,  285,    2, 0x0a /* Public */,
      13,    0,  286,    2, 0x0a /* Public */,
      14,    0,  287,    2, 0x0a /* Public */,
      15,    1,  288,    2, 0x0a /* Public */,
      16,    0,  291,    2, 0x0a /* Public */,
      17,    0,  292,    2, 0x0a /* Public */,
      18,    0,  293,    2, 0x0a /* Public */,
      19,    0,  294,    2, 0x0a /* Public */,
      20,    0,  295,    2, 0x0a /* Public */,
      21,    0,  296,    2, 0x0a /* Public */,
      22,    0,  297,    2, 0x0a /* Public */,
      23,    0,  298,    2, 0x0a /* Public */,
      24,    0,  299,    2, 0x0a /* Public */,
      25,    0,  300,    2, 0x0a /* Public */,
      26,    0,  301,    2, 0x0a /* Public */,
      27,    0,  302,    2, 0x0a /* Public */,
      28,    0,  303,    2, 0x0a /* Public */,
      29,    0,  304,    2, 0x0a /* Public */,
      30,    0,  305,    2, 0x0a /* Public */,
      31,    0,  306,    2, 0x0a /* Public */,
      32,    0,  307,    2, 0x0a /* Public */,
      33,    0,  308,    2, 0x0a /* Public */,
      34,    1,  309,    2, 0x0a /* Public */,
      35,    1,  312,    2, 0x0a /* Public */,
      36,    1,  315,    2, 0x0a /* Public */,
      37,    0,  318,    2, 0x0a /* Public */,
      38,    0,  319,    2, 0x0a /* Public */,
      39,    1,  320,    2, 0x0a /* Public */,
      40,    0,  323,    2, 0x0a /* Public */,
      41,    1,  324,    2, 0x0a /* Public */,
      42,    0,  327,    2, 0x0a /* Public */,
      43,    0,  328,    2, 0x0a /* Public */,
      44,    0,  329,    2, 0x0a /* Public */,
      45,    0,  330,    2, 0x0a /* Public */,
      46,    1,  331,    2, 0x0a /* Public */,
      47,    1,  334,    2, 0x0a /* Public */,
      48,    0,  337,    2, 0x0a /* Public */,
      49,    0,  338,    2, 0x0a /* Public */,
      50,    1,  339,    2, 0x0a /* Public */,
      51,    0,  342,    2, 0x0a /* Public */,
      52,    1,  343,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::UInt,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectCamera((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->disconnectCamera(); break;
        case 2: _t->rescanCameras(); break;
        case 3: _t->connectFilterWheel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->disconnectFilterWheel(); break;
        case 5: _t->warmResetFilterWheel(); break;
        case 6: _t->coldResetFilterWheel(); break;
        case 7: _t->rescanFilterWheels(); break;
        case 8: _t->connectTimer((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->disconnectTimer(); break;
        case 10: _t->resetTimer(); break;
        case 11: _t->rescanTimers(); break;
        case 12: _t->quit(); break;
        case 13: _t->setNightMode((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->enableHistogram(); break;
        case 15: _t->histogramClosed(); break;
        case 16: _t->enableReticle(); break;
        case 17: _t->enableFocusAid(); break;
        case 18: _t->enableFlipX(); break;
        case 19: _t->enableFlipY(); break;
        case 20: _t->enableDemosaic(); break;
        case 21: _t->aboutDialog(); break;
        case 22: _t->doGeneralSettings(); break;
        case 23: _t->doCaptureSettings(); break;
        case 24: _t->doCameraSettings(); break;
        case 25: _t->doProfileSettings(); break;
        case 26: _t->doFilterSettings(); break;
        case 27: _t->doDemosaicSettings(); break;
        case 28: _t->doFITSSettings(); break;
        case 29: _t->doTimerSettings(); break;
        case 30: _t->doAutorunSettings(); break;
        case 31: _t->doHistogramSettings(); break;
        case 32: _t->doCameraMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 33: _t->doFilterWheelMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 34: _t->doTimerMenu((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 35: _t->closeSettingsWindow(); break;
        case 36: _t->settingsClosed(); break;
        case 37: _t->changePreviewState((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 38: _t->doHideControls(); break;
        case 39: _t->advancedFilterWheelHandler((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->advancedPTRHandler(); break;
        case 41: _t->closeAdvancedWindow(); break;
        case 42: _t->advancedClosed(); break;
        case 43: _t->doColouriseSettings(); break;
        case 44: _t->setCapturedFrames((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 45: _t->setActualFrameRate((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 46: _t->setTemperature(); break;
        case 47: _t->setDroppedFrames(); break;
        case 48: _t->setProgress((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 49: _t->reveal(); break;
        case 50: _t->showStatusMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 51)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 51;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 51)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 51;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
