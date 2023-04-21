#ifndef MODEL_DATABASE_H
#define MODEL_DATABASE_H

#include <QObject>
#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QString>

#define DATABASE_HOSTNAME "NameDataBase"
#define DATABASE_NAME "LKDS_Base.db"
#define DATABASE_WAY "DataBase/LKDS_Base.db"

class Model_database : public QObject
{
    Q_OBJECT
public:
    explicit Model_database(QObject *parent = nullptr);
    ~Model_database();


    bool isOpen();
    void connectToDataBase();
    QSqlQuery * queryToDB(QString query);


private:
    QSqlDatabase __Db;
    QSqlQuery* __query = nullptr;
    bool closeDataBase();
    bool openDataBase();
signals:

};

#endif // MODEL_DATABASE_H
