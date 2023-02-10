#ifndef CONTROLLER_DATABASEMANAGER_H
#define CONTROLLER_DATABASEMANAGER_H

#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QAbstractTableModel>
#include <../Model/model_database.h>


class Controller_DatabaseManager : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:

    enum {
            ColumnCodCust = 0,
            ColumnNameCust,
            ColumnINN,
            CountKodReg,
            ColumnNameSity
        };

    Controller_DatabaseManager(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;
    ~Controller_DatabaseManager();

signals:

public slots:
    void updateModel();
    int getId(int row);

private:
    QStringList __columnNames;
    QSqlQuery *__q;
    Model_database * __dispetcher;

};

#endif // CONTROLLER_DATABASEMANAGER_H
