#pragma once

namespace qRpc
{
    class ServerEmulated;
    class ClientBase : public QObject
    {
        Q_OBJECT

    public:
        explicit ClientBase(QObject* parent);
        virtual ~ClientBase(){}

    signals:
        void Connected();

    protected:
        ServerEmulated* GetRemoteServer(int port, const QString& host, QObject* parent);
        QMetaObject::Connection connect(QObject* sender, const char* signal, QObject* receiver, const char* method, Qt::ConnectionType type = Qt::AutoConnection);

        QMetaObject::Connection connect(const QObject *sender, const char *signal, const char *method, Qt::ConnectionType type);
        QMetaObject::Connection connect(const QObject *sender, const QMetaMethod &signal,
                            const QObject *receiver, const QMetaMethod &method,
                            Qt::ConnectionType type = Qt::AutoConnection);

        template <typename Func1, typename Func2>
        static inline typename QtPrivate::QEnableIf<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0 &&
                                                    !QtPrivate::FunctionPointer<Func2>::IsPointerToMemberFunction, QMetaObject::Connection>::Type
                connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, const QObject *context, Func2 slot,
                        Qt::ConnectionType type = Qt::AutoConnection)
        {
            return QObject::connect(sender, signal, context, slot, type);
        }

        template <typename Func1, typename Func2>
        static inline typename QtPrivate::QEnableIf<int(QtPrivate::FunctionPointer<Func2>::ArgumentCount) >= 0, QMetaObject::Connection>::Type
                connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal, Func2 slot)
        {
            return QObject::connect(sender, signal, sender, slot, Qt::DirectConnection);
        }

        template <typename Func1, typename Func2>
        static inline QMetaObject::Connection connect(const typename QtPrivate::FunctionPointer<Func1>::Object *sender, Func1 signal,
                                         const typename QtPrivate::FunctionPointer<Func2>::Object *receiver, Func2 slot,
                                         Qt::ConnectionType type = Qt::AutoConnection)
        {
             return QObject::connect(sender, signal, receiver, slot, type);
        }
    };
}
