#include "stdafx.h"
#include "Utils.h"

namespace
{
    void ExtractTypes(const QString& signature, std::vector<QString>& types)
    {
        QString type;
        int templateDepth = 0;
        const size_t len = signature.size();
        for (size_t i = signature.indexOf('(') + 1; i < len; ++i)
        {
            const QChar ch = signature.at(i);
            if (ch == ')' || (ch == ',' && templateDepth == 0))
            {
                type.remove('&');
                types.push_back(type);
                type.clear();
                continue;
            }
            if (ch == '<')
            {
                ++templateDepth;
            }
            else if (ch == '>')
            {
                --templateDepth;
            }
            type += ch;
        }
    }

    template <typename T>
    void AddTLikeQVariant(QDataStream& out, std::vector<QVariant>& argv)
    {
        T a;
        out >> a;
        argv.push_back(QVariant(a));
    }

}

void qRpc::utils::WriteToStreamLikeQVariant(const char* type, int indx, void** argv, QDataStream& out)
{
   /* QString*/ QVariant str;
    /*int*/ QVariant i;
    /*QTime*/ QVariant time;
   /*
    switch(QMetaType::type(type))
    {
    case QMetaType::Bool:
        out << *reinterpret_cast<bool(*)>(argv[indx]);
        break;

    case QMetaType::Int:
        i = *reinterpret_cast<int(*)>(argv[indx]);
        out << i;
        break;

    case QMetaType::UInt:
        out << *reinterpret_cast<unsigned int(*)>(argv[indx]);
        break;

    case QMetaType::Double:
        out << *reinterpret_cast<double(*)>(argv[indx]);
        break;

    case QMetaType::QChar:
        out << *reinterpret_cast<QChar(*)>(argv[indx]);
        break;

    case QMetaType::QString:
        str = *reinterpret_cast<QString(*)>(argv[indx]);
        out << str;
        break;

    case QMetaType::QByteArray:
        out << *reinterpret_cast<QByteArray(*)>(argv[indx]);
        break;

    case QMetaType::QTime:
        time = *reinterpret_cast<QTime(*)>(argv[indx]);
        out << time;
        break;

    default:
        break;
    }
    */
    switch(QMetaType::type(type))
    {
    case QMetaType::Bool:
        out << QVariant(*reinterpret_cast<bool(*)>(argv[indx]));
        break;

    case QMetaType::Int:
        i = QVariant(*reinterpret_cast<int(*)>(argv[indx]));
        out << i;
        break;

    case QMetaType::QString:
        str = QVariant(*reinterpret_cast<QString(*)>(argv[indx]));
        out << str;
        break;

    case QMetaType::QTime:
        time = QVariant(*reinterpret_cast<QTime(*)>(argv[indx]));
        out << time;
        break;

    default:
        break;
    }
}

void qRpc::utils::ParseArgs(const QString& signature, std::vector<QString>& args)
{
    int end = signature.indexOf(')');
    int indx = signature.indexOf('(');
    if (end - indx != 1)
    {
        ExtractTypes(signature, args);
    }
}


QString qRpc::utils::GetNormalizedSignature(const QString& signature)
{
    return QMetaObject::normalizedSignature(signature.toStdString().data() + 1);
}

void qRpc::utils::CastToVoidStar(const std::vector<QVariant>& argv, std::vector<void*>& castToVoid)
{
    castToVoid.push_back(Q_NULLPTR);
    for (auto& arg : argv)
    {
       castToVoid.push_back(const_cast<void*>(reinterpret_cast<const void*>(arg.data())));
    }
}

void qRpc::utils::ExecuteSlotBySignature(const QString& signature, QDataStream& inStream, std::vector<QVariant>& argv, QObject* receiver)
{
    int slotIndx = receiver->metaObject()->indexOfSlot(signature.toStdString().data());
    assert(slotIndx != -1);

    std::vector<QString> args;
    ParseArgs(signature.toStdString().data(), args);

    for (auto& arg : args)
    {
        QVariant type;
        inStream >> type;
        argv.push_back(type);
    }

    std::vector<void*> castToVoid;
    CastToVoidStar(argv, castToVoid);

    receiver->qt_metacall(QMetaObject::InvokeMetaMethod, slotIndx, &castToVoid[0]);
}
