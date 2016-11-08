TEMPLATE = subdirs

SUBDIRS += \
    QRpc \
    Chat \
    ChatCommon

QRpc.file = QRpc/QRpc.pro
Chat.file = Chat/Chat.pro

Chat.depends = QRpc
