/****************************************************************************
** Meta object code from reading C++ file 'clientnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../RubberContractBridge/clientnetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientNetwork_t {
    QByteArrayData data[17];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientNetwork_t qt_meta_stringdata_ClientNetwork = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientNetwork"
QT_MOC_LITERAL(1, 14, 14), // "txRequestLogin"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 12), // "QHostAddress"
QT_MOC_LITERAL(4, 43, 8), // "serverIP"
QT_MOC_LITERAL(5, 52, 10), // "playerName"
QT_MOC_LITERAL(6, 63, 8), // "password"
QT_MOC_LITERAL(7, 72, 13), // "txBidSelected"
QT_MOC_LITERAL(8, 86, 3), // "Bid"
QT_MOC_LITERAL(9, 90, 3), // "bid"
QT_MOC_LITERAL(10, 94, 14), // "txMoveSelected"
QT_MOC_LITERAL(11, 109, 4), // "Move"
QT_MOC_LITERAL(12, 114, 4), // "move"
QT_MOC_LITERAL(13, 119, 9), // "txMessage"
QT_MOC_LITERAL(14, 129, 3), // "msg"
QT_MOC_LITERAL(15, 133, 5), // "rxAll"
QT_MOC_LITERAL(16, 139, 18) // "serverDisconnected"

    },
    "ClientNetwork\0txRequestLogin\0\0"
    "QHostAddress\0serverIP\0playerName\0"
    "password\0txBidSelected\0Bid\0bid\0"
    "txMoveSelected\0Move\0move\0txMessage\0"
    "msg\0rxAll\0serverDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientNetwork[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
      10,    1,   54,    2, 0x08 /* Private */,
      13,    1,   57,    2, 0x08 /* Private */,
      15,    0,   60,    2, 0x08 /* Private */,
      16,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ClientNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->txRequestLogin((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->txBidSelected((*reinterpret_cast< Bid(*)>(_a[1]))); break;
        case 2: _t->txMoveSelected((*reinterpret_cast< Move(*)>(_a[1]))); break;
        case 3: _t->txMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->rxAll(); break;
        case 5: _t->serverDisconnected(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientNetwork::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ClientNetwork.data,
    qt_meta_data_ClientNetwork,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientNetwork.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
