#ifndef SOCKETWIFI_H
#define SOCKETWIFI_H

#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>


class socketWifi : public QObject
{
    Q_OBJECT
public:
    explicit socketWifi(QObject *parent = nullptr);
    void Test();
signals:

public slots:

private:
    QTcpSocket *socket;
};

#endif // SOCKETWIFI_H
