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
    QByteArrayData data[21];
    char stringdata[252];
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
QT_MOC_LITERAL(6, 54, 16),
QT_MOC_LITERAL(7, 71, 25),
QT_MOC_LITERAL(8, 97, 5),
QT_MOC_LITERAL(9, 103, 16),
QT_MOC_LITERAL(10, 120, 4),
QT_MOC_LITERAL(11, 125, 11),
QT_MOC_LITERAL(12, 137, 2),
QT_MOC_LITERAL(13, 140, 14),
QT_MOC_LITERAL(14, 155, 12),
QT_MOC_LITERAL(15, 168, 5),
QT_MOC_LITERAL(16, 174, 13),
QT_MOC_LITERAL(17, 188, 18),
QT_MOC_LITERAL(18, 207, 9),
QT_MOC_LITERAL(19, 217, 18),
QT_MOC_LITERAL(20, 236, 15)
    },
    "GlobalField\0citySelected\0\0City*\0city\0"
    "selectionDropped\0fieldCellPressed\0"
    "QGraphicsSceneMouseEvent*\0event\0"
    "GlobalFieldCell*\0cell\0timeChanged\0dt\0"
    "weatherChanged\0WeatherStamp\0value\0"
    "updateByTimer\0onSelectionChanged\0"
    "terminate\0setInteractionMode\0"
    "InteractionMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GlobalField[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    0,   62,    2, 0x06 /* Public */,
       6,    2,   63,    2, 0x06 /* Public */,
      11,    1,   68,    2, 0x06 /* Public */,
      13,    1,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      16,    0,   74,    2, 0x0a /* Public */,
      17,    0,   75,    2, 0x0a /* Public */,
      18,    0,   76,    2, 0x0a /* Public */,
      19,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9,    8,   10,
    QMetaType::Void, QMetaType::QDateTime,   12,
    QMetaType::Void, 0x80000000 | 14,   15,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   15,

       0        // eod
};

void GlobalField::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GlobalField *_t = static_cast<GlobalField *>(_o);
        switch (_id) {
        case 0: _t->citySelected((*reinterpret_cast< City*(*)>(_a[1]))); break;
        case 1: _t->selectionDropped(); break;
        case 2: _t->fieldCellPressed((*reinterpret_cast< QGraphicsSceneMouseEvent*(*)>(_a[1])),(*reinterpret_cast< GlobalFieldCell*(*)>(_a[2]))); break;
        case 3: _t->timeChanged((*reinterpret_cast< const QDateTime(*)>(_a[1]))); break;
        case 4: _t->weatherChanged((*reinterpret_cast< const WeatherStamp(*)>(_a[1]))); break;
        case 5: _t->updateByTimer(); break;
        case 6: _t->onSelectionChanged(); break;
        case 7: _t->terminate(); break;
        case 8: _t->setInteractionMode((*reinterpret_cast< InteractionMode(*)>(_a[1]))); break;
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
        {
            typedef void (GlobalField::*_t)(QGraphicsSceneMouseEvent * , GlobalFieldCell * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlobalField::fieldCellPressed)) {
                *result = 2;
            }
        }
        {
            typedef void (GlobalField::*_t)(const QDateTime & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlobalField::timeChanged)) {
                *result = 3;
            }
        }
        {
            typedef void (GlobalField::*_t)(const WeatherStamp & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&GlobalField::weatherChanged)) {
                *result = 4;
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
    if (!strcmp(_clname, "TimeDependent"))
        return static_cast< TimeDependent*>(const_cast< GlobalField*>(this));
    return QGraphicsScene::qt_metacast(_clname);
}

int GlobalField::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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

// SIGNAL 2
void GlobalField::fieldCellPressed(QGraphicsSceneMouseEvent * _t1, GlobalFieldCell * _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GlobalField::timeChanged(const QDateTime & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GlobalField::weatherChanged(const WeatherStamp & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_END_MOC_NAMESPACE
