/****************************************************************************
** Meta object code from reading C++ file 'spinboxaction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../spinboxaction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'spinboxaction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SpinBoxAction_t {
    QByteArrayData data[6];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SpinBoxAction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SpinBoxAction_t qt_meta_stringdata_SpinBoxAction = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SpinBoxAction"
QT_MOC_LITERAL(1, 14, 8), // "increase"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "dicrease"
QT_MOC_LITERAL(4, 33, 8), // "setValue"
QT_MOC_LITERAL(5, 42, 5) // "value"

    },
    "SpinBoxAction\0increase\0\0dicrease\0"
    "setValue\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SpinBoxAction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x0a /* Public */,
       3,    0,   35,    2, 0x0a /* Public */,
       4,    1,   36,    2, 0x0a /* Public */,
       4,    1,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void SpinBoxAction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SpinBoxAction *_t = static_cast<SpinBoxAction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->increase(); break;
        case 1: _t->dicrease(); break;
        case 2: _t->setValue((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject SpinBoxAction::staticMetaObject = {
    { &QWidgetAction::staticMetaObject, qt_meta_stringdata_SpinBoxAction.data,
      qt_meta_data_SpinBoxAction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SpinBoxAction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SpinBoxAction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SpinBoxAction.stringdata0))
        return static_cast<void*>(const_cast< SpinBoxAction*>(this));
    return QWidgetAction::qt_metacast(_clname);
}

int SpinBoxAction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidgetAction::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
