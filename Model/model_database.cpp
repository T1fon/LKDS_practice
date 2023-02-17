#include "model_database.h"

Model_database::Model_database(QObject *parent)
    : QObject{parent}
{
    __query = new QSqlQuery;
}


void Model_database::connectToDataBase()
{
    if (!QFile(DATABASE_WAY).exists())
    {
       qDebug() << "ERROR DataBase No Exist";
    }
    else
    {
        qDebug() << "Try to open";
        this->openDataBase();
    }
}

bool Model_database::openDataBase()
{
    __Db = QSqlDatabase::addDatabase("QSQLITE");
    __Db.setHostName(DATABASE_HOSTNAME);
    __Db.setDatabaseName(DATABASE_WAY);
    if(!__Db.isOpen())
    {

        if(__Db.open())
        {
            qDebug() << "Open";
            return true;
        }
        else
        {
            qDebug() << "DB NOT OPEN";
            return false;
        }
    }
    else
        qDebug() << "Ok";
}

bool Model_database::closeDataBase()
{
    if (__Db.isOpen())
        __Db.close();
}

QSqlQuery * Model_database::queryToDB(QString query)
{
    if(__query->exec(query))
        return __query;
    else
        qDebug() << "No Query";
}

Model_database::~Model_database()
{
    this->closeDataBase();
    delete __query;
}
