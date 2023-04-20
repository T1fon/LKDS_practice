#ifndef CBMODEL_SECWIN_H
#define CBMODEL_SECWIN_H

#include <QObject>
#include <QAbstractListModel>
#include <qqml.h>
#include "../Model/model_database.h"

class CBModel_secwin : public QAbstractListModel
{
public:
    CBModel_secwin();
    ~CBModel_secwin();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole)override;
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex())override;
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex())override;

public slots:
    void updateData(QString text);
    QString getValue(int row);

private:
    QSqlQuery *__q;
    Model_database * __dispetcher;
    QString __query;
    QVector<QVariant> *__CBMSW_names_variant = nullptr;
    QList<QString> *__regCB;

};

#endif // CBMODEL_SECWIN_H
