#ifndef COMPORTMODEL_H
#define COMPORTMODEL_H

#include <QAbstractListModel>
#include <QSerialPortInfo>
#include <QFile>
#include <QTextStream>
#include <qqml.h>
#include <QDebug>

#define DEFAULT_SAVE_PATH "./port_config.txt"

class COMPortModel: public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT
private:
    QList<QSerialPortInfo> *__COM_info = nullptr;
    QVector<QVariant> *__COM_names_variant = nullptr;
    int __current_index = 0;
public:

    COMPortModel();
    ~COMPortModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;

public slots:
    void updateData();
    void saveData(QString path = DEFAULT_SAVE_PATH);

    bool setCurrentIndex(int value);
    int getCurrentIndex();
    QString getPortName(const int &index);
    QString getDeviceName(const int &index);
    QString getDeviceId(const int &index);
    QString getManufacturerName(const int &index);
    QString getManufacturerId(const int &index);
signals:
    void saveError(QString message);
};

#endif // COMPORTMODEL_H
