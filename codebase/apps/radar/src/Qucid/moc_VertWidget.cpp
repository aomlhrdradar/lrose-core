/****************************************************************************
** Meta object code from reading C++ file 'VertWidget.hh'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "VertWidget.hh"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VertWidget.hh' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSVertWidgetENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSVertWidgetENDCLASS = QtMocHelpers::stringData(
    "VertWidget",
    "severalBeamsProcessed",
    "",
    "unzoomView",
    "clear",
    "refresh",
    "resize",
    "width",
    "height",
    "paintEvent",
    "QPaintEvent*",
    "event"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSVertWidgetENDCLASS_t {
    uint offsetsAndSizes[24];
    char stringdata0[11];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[6];
    char stringdata5[8];
    char stringdata6[7];
    char stringdata7[6];
    char stringdata8[7];
    char stringdata9[11];
    char stringdata10[13];
    char stringdata11[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSVertWidgetENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSVertWidgetENDCLASS_t qt_meta_stringdata_CLASSVertWidgetENDCLASS = {
    {
        QT_MOC_LITERAL(0, 10),  // "VertWidget"
        QT_MOC_LITERAL(11, 21),  // "severalBeamsProcessed"
        QT_MOC_LITERAL(33, 0),  // ""
        QT_MOC_LITERAL(34, 10),  // "unzoomView"
        QT_MOC_LITERAL(45, 5),  // "clear"
        QT_MOC_LITERAL(51, 7),  // "refresh"
        QT_MOC_LITERAL(59, 6),  // "resize"
        QT_MOC_LITERAL(66, 5),  // "width"
        QT_MOC_LITERAL(72, 6),  // "height"
        QT_MOC_LITERAL(79, 10),  // "paintEvent"
        QT_MOC_LITERAL(90, 12),  // "QPaintEvent*"
        QT_MOC_LITERAL(103, 5)   // "event"
    },
    "VertWidget",
    "severalBeamsProcessed",
    "",
    "unzoomView",
    "clear",
    "refresh",
    "resize",
    "width",
    "height",
    "paintEvent",
    "QPaintEvent*",
    "event"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSVertWidgetENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    2,   54,    2, 0x0a,    5 /* Public */,
       9,    1,   59,    2, 0x0a,    8 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

Q_CONSTINIT const QMetaObject VertWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<CartWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSVertWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSVertWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSVertWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VertWidget, std::true_type>,
        // method 'severalBeamsProcessed'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unzoomView'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clear'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'refresh'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resize'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'paintEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QPaintEvent *, std::false_type>
    >,
    nullptr
} };

void VertWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VertWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->severalBeamsProcessed(); break;
        case 1: _t->unzoomView(); break;
        case 2: _t->clear(); break;
        case 3: _t->refresh(); break;
        case 4: _t->resize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 5: _t->paintEvent((*reinterpret_cast< std::add_pointer_t<QPaintEvent*>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VertWidget::*)();
            if (_t _q_method = &VertWidget::severalBeamsProcessed; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *VertWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VertWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSVertWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return CartWidget::qt_metacast(_clname);
}

int VertWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CartWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VertWidget::severalBeamsProcessed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
