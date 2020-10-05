/****************************************************************************
** Meta object code from reading C++ file 'playernetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RubberContractBridge/network/playernetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playernetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayerNetwork_t {
    QByteArrayData data[13];
    char stringdata0[115];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerNetwork_t qt_meta_stringdata_PlayerNetwork = {
    {
QT_MOC_LITERAL(0, 0, 13), // "PlayerNetwork"
QT_MOC_LITERAL(1, 14, 11), // "bidSelected"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "Bid"
QT_MOC_LITERAL(4, 31, 3), // "bid"
QT_MOC_LITERAL(5, 35, 12), // "moveSelected"
QT_MOC_LITERAL(6, 48, 4), // "Card"
QT_MOC_LITERAL(7, 53, 4), // "card"
QT_MOC_LITERAL(8, 58, 16), // "messageGenerated"
QT_MOC_LITERAL(9, 75, 3), // "msg"
QT_MOC_LITERAL(10, 79, 18), // "clientDisconnected"
QT_MOC_LITERAL(11, 98, 5), // "rxAll"
QT_MOC_LITERAL(12, 104, 10) // "pingClient"

    },
    "PlayerNetwork\0bidSelected\0\0Bid\0bid\0"
    "moveSelected\0Card\0card\0messageGenerated\0"
    "msg\0clientDisconnected\0rxAll\0pingClient"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerNetwork[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       8,    1,   50,    2, 0x06 /* Public */,
      10,    0,   53,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   54,    2, 0x08 /* Private */,
      12,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void PlayerNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlayerNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->bidSelected((*reinterpret_cast< Bid(*)>(_a[1]))); break;
        case 1: _t->moveSelected((*reinterpret_cast< Card(*)>(_a[1]))); break;
        case 2: _t->messageGenerated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->clientDisconnected(); break;
        case 4: _t->rxAll(); break;
        case 5: _t->pingClient(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerNetwork::*)(Bid );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerNetwork::bidSelected)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayerNetwork::*)(Card );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerNetwork::moveSelected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayerNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerNetwork::messageGenerated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PlayerNetwork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerNetwork::clientDisconnected)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayerNetwork::staticMetaObject = { {
    &Player::staticMetaObject,
    qt_meta_stringdata_PlayerNetwork.data,
    qt_meta_data_PlayerNetwork,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PlayerNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerNetwork.stringdata0))
        return static_cast<void*>(this);
    return Player::qt_metacast(_clname);
}

int PlayerNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = Player::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void PlayerNetwork::bidSelected(Bid _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerNetwork::moveSelected(Card _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayerNetwork::messageGenerated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void PlayerNetwork::clientDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
