/****************************************************************************
** Meta object code from reading C++ file 'inventory_form.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../source/badziaha/forms/inventory_form.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'inventory_form.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_InventoryForm_t {
    QByteArrayData data[9];
    char stringdata[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InventoryForm_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InventoryForm_t qt_meta_stringdata_InventoryForm = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 6),
QT_MOC_LITERAL(2, 21, 0),
QT_MOC_LITERAL(3, 22, 10),
QT_MOC_LITERAL(4, 33, 14),
QT_MOC_LITERAL(5, 48, 5),
QT_MOC_LITERAL(6, 54, 19),
QT_MOC_LITERAL(7, 74, 5),
QT_MOC_LITERAL(8, 80, 27)
    },
    "InventoryForm\0toggle\0\0Character*\0"
    "clothesClicked\0index\0customMenuRequested\0"
    "point\0equippedCustomMenuRequested"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InventoryForm[] = {

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
       1,    1,   34,    2, 0x0a /* Public */,
       4,    1,   37,    2, 0x0a /* Public */,
       6,    1,   40,    2, 0x0a /* Public */,
       8,    1,   43,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QModelIndex,    5,
    QMetaType::Void, QMetaType::QPoint,    7,
    QMetaType::Void, QMetaType::QPoint,    7,

       0        // eod
};

void InventoryForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        InventoryForm *_t = static_cast<InventoryForm *>(_o);
        switch (_id) {
        case 0: _t->toggle((*reinterpret_cast< Character*(*)>(_a[1]))); break;
        case 1: _t->clothesClicked((*reinterpret_cast< QModelIndex(*)>(_a[1]))); break;
        case 2: _t->customMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 3: _t->equippedCustomMenuRequested((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject InventoryForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_InventoryForm.data,
      qt_meta_data_InventoryForm,  qt_static_metacall, 0, 0}
};


const QMetaObject *InventoryForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InventoryForm::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_InventoryForm.stringdata))
        return static_cast<void*>(const_cast< InventoryForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int InventoryForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
