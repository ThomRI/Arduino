/****************************************************************************
** Meta object code from reading C++ file 'ArduinoInterfacer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/ArduinoInterfacer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArduinoInterfacer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ArduinoInterfacer_t {
    QByteArrayData data[10];
    char stringdata0[78];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArduinoInterfacer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArduinoInterfacer_t qt_meta_stringdata_ArduinoInterfacer = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ArduinoInterfacer"
QT_MOC_LITERAL(1, 18, 6), // "pushed"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "QList<float>"
QT_MOC_LITERAL(4, 39, 6), // "values"
QT_MOC_LITERAL(5, 46, 7), // "sendCmd"
QT_MOC_LITERAL(6, 54, 3), // "cmd"
QT_MOC_LITERAL(7, 58, 4), // "send"
QT_MOC_LITERAL(8, 63, 5), // "value"
QT_MOC_LITERAL(9, 69, 8) // "received"

    },
    "ArduinoInterfacer\0pushed\0\0QList<float>\0"
    "values\0sendCmd\0cmd\0send\0value\0received"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArduinoInterfacer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   37,    2, 0x0a /* Public */,
       7,    1,   40,    2, 0x0a /* Public */,
       9,    0,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Bool, QMetaType::Char,    6,
    QMetaType::Bool, QMetaType::Float,    8,
    QMetaType::Void,

       0        // eod
};

void ArduinoInterfacer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArduinoInterfacer *_t = static_cast<ArduinoInterfacer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->pushed((*reinterpret_cast< const QList<float>(*)>(_a[1]))); break;
        case 1: { bool _r = _t->sendCmd((*reinterpret_cast< const char(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: { bool _r = _t->send((*reinterpret_cast< const float(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 3: _t->received(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<float> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ArduinoInterfacer::*)(const QList<float> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ArduinoInterfacer::pushed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ArduinoInterfacer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ArduinoInterfacer.data,
      qt_meta_data_ArduinoInterfacer,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ArduinoInterfacer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArduinoInterfacer::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ArduinoInterfacer.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ArduinoInterfacer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ArduinoInterfacer::pushed(const QList<float> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
