/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[27];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 7), // "fileAct"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 8), // "QAction*"
QT_MOC_LITERAL(4, 29, 10), // "fileAction"
QT_MOC_LITERAL(5, 40, 7), // "editAct"
QT_MOC_LITERAL(6, 48, 10), // "editAction"
QT_MOC_LITERAL(7, 59, 7), // "drawAct"
QT_MOC_LITERAL(8, 67, 10), // "drawAction"
QT_MOC_LITERAL(9, 78, 7), // "viewAct"
QT_MOC_LITERAL(10, 86, 10), // "viewAction"
QT_MOC_LITERAL(11, 97, 9), // "filterAct"
QT_MOC_LITERAL(12, 107, 12), // "filterAction"
QT_MOC_LITERAL(13, 120, 9), // "searchAct"
QT_MOC_LITERAL(14, 130, 12), // "searchAction"
QT_MOC_LITERAL(15, 143, 7), // "helpAct"
QT_MOC_LITERAL(16, 151, 10), // "helpAction"
QT_MOC_LITERAL(17, 162, 10), // "closeEvent"
QT_MOC_LITERAL(18, 173, 12), // "QCloseEvent*"
QT_MOC_LITERAL(19, 186, 5), // "event"
QT_MOC_LITERAL(20, 192, 4), // "doIt"
QT_MOC_LITERAL(21, 197, 12), // "toolTracking"
QT_MOC_LITERAL(22, 210, 4), // "tool"
QT_MOC_LITERAL(23, 215, 18), // "imageDoubleClicked"
QT_MOC_LITERAL(24, 234, 4), // "path"
QT_MOC_LITERAL(25, 239, 16), // "applyPreferences"
QT_MOC_LITERAL(26, 256, 17) // "cancelPreferences"

    },
    "MainWindow\0fileAct\0\0QAction*\0fileAction\0"
    "editAct\0editAction\0drawAct\0drawAction\0"
    "viewAct\0viewAction\0filterAct\0filterAction\0"
    "searchAct\0searchAction\0helpAct\0"
    "helpAction\0closeEvent\0QCloseEvent*\0"
    "event\0doIt\0toolTracking\0tool\0"
    "imageDoubleClicked\0path\0applyPreferences\0"
    "cancelPreferences"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       5,    1,   82,    2, 0x08 /* Private */,
       7,    1,   85,    2, 0x08 /* Private */,
       9,    1,   88,    2, 0x08 /* Private */,
      11,    1,   91,    2, 0x08 /* Private */,
      13,    1,   94,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,
      17,    1,  100,    2, 0x08 /* Private */,
      20,    0,  103,    2, 0x08 /* Private */,
      21,    1,  104,    2, 0x08 /* Private */,
      23,    1,  107,    2, 0x08 /* Private */,
      25,    0,  110,    2, 0x08 /* Private */,
      26,    0,  111,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void, 0x80000000 | 3,    8,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, 0x80000000 | 3,   12,
    QMetaType::Void, 0x80000000 | 3,   14,
    QMetaType::Void, 0x80000000 | 3,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   22,
    QMetaType::Void, QMetaType::QString,   24,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fileAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 1: _t->editAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->drawAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 3: _t->viewAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 4: _t->filterAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 5: _t->searchAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 6: _t->helpAct((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 8: _t->doIt(); break;
        case 9: _t->toolTracking((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->imageDoubleClicked((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 11: _t->applyPreferences(); break;
        case 12: _t->cancelPreferences(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAction* >(); break;
            }
            break;
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
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
