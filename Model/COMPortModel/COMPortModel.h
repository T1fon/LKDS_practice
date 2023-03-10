#ifndef COMPORTMODEL_H
#define COMPORTMODEL_H

#include <QAbstractListModel>
#include <QSerialPortInfo>
#include <qqml.h>
#include <QDebug>

class COMPortModel: public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
private:
    QList<QSerialPortInfo> *__COM_info = nullptr;
    QVector<QVariant> *__COM_names_variant = nullptr;
public:

    COMPortModel();
    ~COMPortModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void updateData();

    QString getDeviceName(const int &index);
    QString getDeviceId(const int &index);
    QString getManufacturerName(const int &index);
    QString getManufacturerId(const int &index);
};

#endif // COMPORTMODEL_H
