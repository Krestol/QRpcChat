TEMPLATE = subdirs

SUBDIRS += \
    QRpc \
    Chat \
    ChatCommon

QRpc.file = QRpc/QRpc.pro
Chat.file = Chat/Chat.pro
ChatCommon.file = ChatCommon/ChatCommon.pro

Chat.depends = QRpc ChatCommon
