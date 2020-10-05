/****************************************************************************
** Meta object code from reading C++ file 'clientnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../RubberContractBridge/network/clientnetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientNetwork_t {
    QByteArrayData data[32];
    char stringdata0[375];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientNetwork_t qt_meta_stringdata_ClientNetwork = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ClientNetwork"
QT_MOC_LITERAL(1, 14, 14), // "serverNotFound"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 6), // "reason"
QT_MOC_LITERAL(4, 37, 13), // "notifyBidTurn"
QT_MOC_LITERAL(5, 51, 14), // "notifyMoveTurn"
QT_MOC_LITERAL(6, 66, 17), // "notifyBidRejected"
QT_MOC_LITERAL(7, 84, 18), // "notifyMoveRejected"
QT_MOC_LITERAL(8, 103, 11), // "loginResult"
QT_MOC_LITERAL(9, 115, 15), // "loginSuccessful"
QT_MOC_LITERAL(10, 131, 15), // "updateGameState"
QT_MOC_LITERAL(11, 147, 9), // "GameState"
QT_MOC_LITERAL(12, 157, 9), // "gameState"
QT_MOC_LITERAL(13, 167, 15), // "messageReceived"
QT_MOC_LITERAL(14, 183, 6), // "source"
QT_MOC_LITERAL(15, 190, 3), // "msg"
QT_MOC_LITERAL(16, 194, 18), // "serverDisconnected"
QT_MOC_LITERAL(17, 213, 14), // "gameTerminated"
QT_MOC_LITERAL(18, 228, 14), // "txRequestLogin"
QT_MOC_LITERAL(19, 243, 12), // "QHostAddress"
QT_MOC_LITERAL(20, 256, 8), // "serverIP"
QT_MOC_LITERAL(21, 265, 10), // "playerName"
QT_MOC_LITERAL(22, 276, 8), // "password"
QT_MOC_LITERAL(23, 285, 13), // "txBidSelected"
QT_MOC_LITERAL(24, 299, 3), // "Bid"
QT_MOC_LITERAL(25, 303, 3), // "bid"
QT_MOC_LITERAL(26, 307, 14), // "txMoveSelected"
QT_MOC_LITERAL(27, 322, 4), // "Card"
QT_MOC_LITERAL(28, 327, 4), // "card"
QT_MOC_LITERAL(29, 332, 9), // "txMessage"
QT_MOC_LITERAL(30, 342, 5), // "rxAll"
QT_MOC_LITERAL(31, 348, 26) // "internalServerDisconnected"

    },
    "ClientNetwork\0serverNotFound\0\0reason\0"
    "notifyBidTurn\0notifyMoveTurn\0"
    "notifyBidRejected\0notifyMoveRejected\0"
    "loginResult\0loginSuccessful\0updateGameState\0"
    "GameState\0gameState\0messageReceived\0"
    "source\0msg\0serverDisconnected\0"
    "gameTerminated\0txRequestLogin\0"
    "QHostAddress\0serverIP\0playerName\0"
    "password\0txBidSelected\0Bid\0bid\0"
    "txMoveSelected\0Card\0card\0txMessage\0"
    "rxAll\0internalServerDisconnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientNetwork[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    0,   97,    2, 0x06 /* Public */,
       5,    0,   98,    2, 0x06 /* Public */,
       6,    1,   99,    2, 0x06 /* Public */,
       7,    1,  102,    2, 0x06 /* Public */,
       8,    2,  105,    2, 0x06 /* Public */,
      10,    1,  110,    2, 0x06 /* Public */,
      13,    2,  113,    2, 0x06 /* Public */,
      16,    0,  118,    2, 0x06 /* Public */,
      17,    1,  119,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    3,  122,    2, 0x0a /* Public */,
      23,    1,  129,    2, 0x0a /* Public */,
      26,    1,  132,    2, 0x0a /* Public */,
      29,    1,  135,    2, 0x0a /* Public */,
      30,    0,  138,    2, 0x08 /* Private */,
      31,    0,  139,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,    9,    3,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   14,   15,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 19, QMetaType::QString, QMetaType::QString,   20,   21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, 0x80000000 | 27,   28,
    QMetaType::Void, QMetaType::QString,   15,
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
        case 0: _t->serverNotFound((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->notifyBidTurn(); break;
        case 2: _t->notifyMoveTurn(); break;
        case 3: _t->notifyBidRejected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->notifyMoveRejected((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->loginResult((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 6: _t->updateGameState((*reinterpret_cast< GameState(*)>(_a[1]))); break;
        case 7: _t->messageReceived((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->serverDisconnected(); break;
        case 9: _t->gameTerminated((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->txRequestLogin((*reinterpret_cast< QHostAddress(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 11: _t->txBidSelected((*reinterpret_cast< Bid(*)>(_a[1]))); break;
        case 12: _t->txMoveSelected((*reinterpret_cast< Card(*)>(_a[1]))); break;
        case 13: _t->txMessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 14: _t->rxAll(); break;
        case 15: _t->internalServerDisconnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ClientNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::serverNotFound)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::notifyBidTurn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::notifyMoveTurn)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::notifyBidRejected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::notifyMoveRejected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(bool , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::loginResult)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(GameState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::updateGameState)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::messageReceived)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::serverDisconnected)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ClientNetwork::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientNetwork::gameTerminated)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientNetwork::staticMetaObject = { {
    &QObject::staticMetaObject,
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ClientNetwork::serverNotFound(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientNetwork::notifyBidTurn()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ClientNetwork::notifyMoveTurn()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ClientNetwork::notifyBidRejected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ClientNetwork::notifyMoveRejected(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ClientNetwork::loginResult(bool _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ClientNetwork::updateGameState(GameState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ClientNetwork::messageReceived(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ClientNetwork::serverDisconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void ClientNetwork::gameTerminated(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
