#ifndef CONTROLLER_KEYTABLE_H
#define CONTROLLER_KEYTABLE_H
#define PAGE_THIRD_WINDOW 2
#include <QObject>
#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>
#include <../Model/model_database.h>
#include <QMap>
#include <QVector>

struct TableDisplayServiceKey
{
    QString KodCust;
    QString IdNum;
    QString Date;
    QString NumKey;
};

class Controller_KeyTable : public QAbstractTableModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)
    enum {
            ColumnKodCust = 0,
            ColumnIdNum,
            ColumnDate,
            ColumnNumKey,
            CountofColumnsService
        };
public:
    Controller_KeyTable(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;
    ~Controller_KeyTable();

public slots:
    void updateModel();

private:
    Model_database * __dispetcher;
    QStringList __columnNames;
    QSqlQuery *__q;
    QVector<TableDisplayServiceKey> *__serviceNames;
    int __rows = 0;
    int __page = PAGE_THIRD_WINDOW;
    QString __query;
};

#endif // CONTROLLER_KEYTABLE_H
