#ifndef CONTROLLER_DATABASEMANAGER_H
#define CONTROLLER_DATABASEMANAGER_H
#define PAGE_SECOND_WINDOW 1
#define PAGE_THIRD_WINDOW 2

#include <QObject>
#include <QSqlQueryModel>
#include <qqml.h>
#include <QStringList>
#include <QAbstractTableModel>
#include <../Model/model_database.h>
#include <QMap>
#include <QVector>


struct TableDisplay
{
    QString CodCust;
    QString NameCust;
    QString Inn;
    QString KodReg;
    QString NameSity;
};
struct TableDisplayServiceKey
{
    QString KodCust;
    QString IdNum;
    QString Date;
    QString NumKey;
};

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
            ColumnNameSity,
            CountofColumnsCustom
        };

    enum {
            ColumnKodCust = 0,
            ColumnIdNum,
            ColumnDate,
            ColumnNumKey,
            CountofColumnsService
        };


    Controller_DatabaseManager(QObject *parent = nullptr);
    int rowCount(const QModelIndex & = QModelIndex()) const override;
    int columnCount(const QModelIndex & = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;
    ~Controller_DatabaseManager();


signals:
    void sendToQml();

public slots:
    void updateModel();
    void changeToSecond();
    void changeToThird();

private:
    QStringList __columnNames;
    QSqlQuery *__q;
    Model_database * __dispetcher;
    QVector<TableDisplay> *__rowNames;
    QVector<TableDisplayServiceKey> *__serviceNames;
    int __rows = 0;
    int __page = 0;
    QString __query;
};

#endif // CONTROLLER_DATABASEMANAGER_H
