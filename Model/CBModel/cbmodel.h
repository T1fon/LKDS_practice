#ifndef CBMODEL_H
#define CBMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <qqml.h>

#define FIRST_TABLE_C 0
#define SECOND_TABLE_C 1
#define THIRD_TABLE_C 2

class CBModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    CBModel();
    ~CBModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;

public slots:
    void updateData(int numTable);
    QString getValue(int row);

private:
    QList<QString> *__tableCB, *__textCB;
    int __numTable = 0;
    QVector<QVariant> *__CBM_names_variant = nullptr;

};

#endif // CBMODEL_H
