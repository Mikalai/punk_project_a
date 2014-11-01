/****************************************************************************
** Meta object code from reading C++ file 'global_field.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/badziaha/global_field.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'global_field.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_GlobalField_t {
    QByteArrayData data[9];
    char stringdata[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GlobalField_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GlobalField_t qt_meta_stringdata_GlobalField = {
    {
QT_MOC_LITERAL(0, 0, 11),
QT_MOC_LITERAL(1, 12, 12),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 5),
QT_MOC_LITERAL(4, 32, 4),
QT_MOC_LITERAL(5, 37, 16),
QT_MOC_LITERAL(6, 54, 6),
QT_MOC_LITERAL(7, 61, 18),
QT_MOC_LITERAL(8, 80, 9)
    },
    "GlobalField\0citySelected\0\0City*\0city\0"
    "selectionDropped\0update\0onSelectionChanged\0"
    "terminate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlobalField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       5,    0,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   43,    2, 0x0a /* Public */,
       7,    0,   44,    2, 0x0a /* Public */,
       8,    0,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void GlobalField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GlobalField *_t = static_cast<GlobalField *>(_o);
        switch (_id) {
        case 0: _t->citySelected((*reinterpret_cast< City*(*)>(_a[1]))); break;
        case 1: _t->selectionDropped(); break;
        case 2: _t->update(); break;
        case 3: _t->onSelectionChanged(); break;
        case 4: _t->terminate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (GlobalField::*_t)(City * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlobalField::citySelected)) {
                *result = 0;
            }
        }
        {
            typedef void (GlobalField::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlobalField::selectionDropped)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject GlobalField::staticMetaObject = {
    { &QGraphicsScene::staticMetaObject, qt_meta_stringdata_GlobalField.data,
      qt_meta_data_GlobalField,  qt_static_metacall, 0, 0}
};


const QMetaObject *GlobalField::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GlobalField::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_GlobalField.stringdata))
        return static_cast<void*>(const_cast< GlobalField*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int GlobalField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void GlobalField::citySelected(City * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GlobalField::selectionDropped()
{
    QMetaObject::activate(this, &staticMetaObject, 1, 0);
}
QT_END_MOC_NAMESPACE
