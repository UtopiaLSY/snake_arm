/****************************************************************************
** Meta object code from reading C++ file 'screen.h'
**
** Created: Fri Jun 21 22:26:47 2019
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "screen.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screen.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Screen[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       8,    7,    7,    7, 0x08,
      21,    7,    7,    7, 0x08,
      33,    7,    7,    7, 0x08,
      45,    7,    7,    7, 0x08,
      60,    7,    7,    7, 0x08,
      70,    7,    7,    7, 0x08,
      82,    7,    7,    7, 0x08,
      94,    7,    7,    7, 0x08,
     108,    7,    7,    7, 0x08,
     123,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Screen[] = {
    "Screen\0\0my_timeout()\0startGame()\0"
    "pauseGame()\0continueGame()\0speedUp()\0"
    "speedDown()\0upClicked()\0downClicked()\0"
    "rightClicked()\0leftClicked()\0"
};

const QMetaObject Screen::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Screen,
      qt_meta_data_Screen, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Screen::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Screen::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Screen::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Screen))
        return static_cast<void*>(const_cast< Screen*>(this));
    return QWidget::qt_metacast(_clname);
}

int Screen::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: my_timeout(); break;
        case 1: startGame(); break;
        case 2: pauseGame(); break;
        case 3: continueGame(); break;
        case 4: speedUp(); break;
        case 5: speedDown(); break;
        case 6: upClicked(); break;
        case 7: downClicked(); break;
        case 8: rightClicked(); break;
        case 9: leftClicked(); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
