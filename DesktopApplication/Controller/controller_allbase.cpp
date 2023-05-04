#include "controller_allbase.h"

controller_allBase::controller_allBase(QObject *parent)
    : QAbstractTableModel(parent)
{
    __customNames << tr("Код компании") << tr("Наименование") << tr("ИНН") << tr("Регион") << tr("Город");
    __keyNames << tr("ID ключа")<< tr("Код компании") << tr("Регион") << tr("Дата создания") << tr("Номер ключа");
    __regNames  << tr("Код региона") << tr("Наименование");
    __customNamesSearch << tr("COD_CUST") << tr("NAME_CUSTOM") << tr("INN") << tr("KOD_REG") << tr("NAME_SITY");
    __keyNamesSearch << tr("ID_NUM")<< tr("KOD_CUST") << tr("KOD_REG") << tr("DATE") << tr("NUM_KEY");
    __regNamesSearch  << tr("KOD_REG") << tr("NAME_REG");
    __q = new QSqlQuery;
    __dispetcher = new Model_database;
    __customTable = new QVector<Custom>;
    __keyTable = new QVector<ServiceKey>;
    __regTable = new QVector<Region>;
    __dispetcher->connectToDataBase();
    if (__numTable == FIRST_TABLE)
        __query = "SELECT * FROM Custom";
    else if (__numTable == SECOND_TABLE)
        __query = "SELECT * FROM Service_Key";
    else if (__numTable == THIRD_TABLE)
        __query = "SELECT * FROM Region";
    //this->updateModel();
}

int controller_allBase::rowCount(const QModelIndex &) const
{
    if(__numTable == FIRST_TABLE)
        return __customTable->size();
    else if(__numTable == SECOND_TABLE)
        return __keyTable->size();
    else if(__numTable == THIRD_TABLE)
        return __regTable->size();
}

int controller_allBase::columnCount(const QModelIndex &) const
{
    if(__numTable == FIRST_TABLE)
        return CountofColumnsCustom;
    else if(__numTable == SECOND_TABLE)
        return CountofColumnsService;
    else if(__numTable == THIRD_TABLE)
        return CountofColumnsReg;
}

QVariant controller_allBase::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation != Qt::Horizontal || role != Qt::DisplayRole || section >= columnCount()){
        return QVariant();
    }
    if(__numTable == FIRST_TABLE)
        return __customNames.at(section);
    else if(__numTable == SECOND_TABLE)
        return __keyNames.at(section);
    else if(__numTable == THIRD_TABLE)
        return __regNames.at(section);
}

QHash<int, QByteArray> controller_allBase::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

QVariant controller_allBase::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int row = index.row();
    int col = index.column();

    if (row >= rowCount() || col >= columnCount() || role !=  Qt::DisplayRole){
        qDebug() << "Dataaaaaa";
        return QVariant();
    }
    if (__numTable == FIRST_TABLE)
    {
        switch (col)
        {
            case ColumnCodCust:
                return __customTable->at(row).CodCust;
                break;
            case ColumnNameCust:
                return __customTable->at(row).NameCust;
                break;
            case ColumnINNCust:
                return __customTable->at(row).Inn;
                break;
            case ColumnKodRegCust:
                return __customTable->at(row).KodReg;
                break;
            case ColumnNameSityCust:
                return __customTable->at(row).NameSity;
                break;
        }
    }
    else if (__numTable == SECOND_TABLE)
    {
        switch (col)
        {
            case ColumnIdNumKey:
                return __keyTable->at(row).IdNum;
                break;
            case ColumnKodCustKey:
                return __keyTable->at(row).KodCust;
                break;
            case ColumnRegKey:
                return __keyTable->at(row).KodReg;
                break;
            case ColumnDateKey:
                return __keyTable->at(row).Date;
                break;
            case ColumnNumKey:
                return __keyTable->at(row).NumKey;
                break;
        }
    }
    else if (__numTable == THIRD_TABLE)
    {
        switch(col)
        {
            case ColumnKodReg:
                return __regTable->at(row).KodReg;
                break;
            case ColumnNameReg:
                return __regTable->at(row).NameReg;
                break;
        }
    }
}
void controller_allBase::updateModel()
{
    Custom cus;
    ServiceKey sk;
    Region reg;
    __rows = 0;
    __dispetcher->connectToDataBase();
    qDebug() << "AAAAAAAAAAAAAA";
    /*if (__numTable == FIRST_TABLE)
        __query = "SELECT * FROM Custom";
    else if (__numTable == SECOND_TABLE)
        __query = "SELECT * FROM Service_Key";
    else if (__numTable == THIRD_TABLE)
        __query = "SELECT * FROM Region";*/
    qDebug() << __query;
    __q = __dispetcher->queryToDB(__query);

    for (; __q->next();)
    {
        if (__numTable == FIRST_TABLE)
        {
            cus.CodCust = __q->value("COD_CUST").toString();
            //qDebug() << "AAAAAAAAA Cod Cust" << cus.CodCust;
            __rows_cust = __q->value("COD_CUST").toInt();
            cus.NameCust = __q->value("NAME_CUSTOM").toString();
            cus.Inn = __q->value("INN").toString();
            cus.KodReg = __q->value("KOD_REG").toString();
            cus.NameSity = __q->value("NAME_SITY").toString();

         __customTable->push_back(cus);
        }
        else if (__numTable == SECOND_TABLE)
        {

            sk.IdNum = __q->value("ID_NUM").toString();
            sk.KodCust = __q->value("KOD_CUST").toString();
            sk.KodReg = __q->value("KOD_REG").toString();
            sk.Date = __q->value("DATE").toString();
            sk.NumKey = __q->value("NUM_KEY").toString();

         __keyTable->push_back(sk);
        }
        else if (__numTable == THIRD_TABLE)
        {
            reg.KodReg = __q->value("KOD_REG").toString();
            __rows_reg = __q->value("KOD_REG").toInt();
            reg.NameReg = __q->value("NAME_REG").toString();

            __regTable->push_back(reg);
        }

        __rows++;
    }
}

Qt::ItemFlags controller_allBase::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool controller_allBase::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(__numTable == FIRST_TABLE)
    {
        if(__cust_display == nullptr)
            __cust_display = new Custom;
    }
    else if(__numTable == THIRD_TABLE)
    {
        if(__reg_display == nullptr)
            __reg_display = new Region;
    }

    int col = index.column();
    QString text = "";

    if (__numTable == FIRST_TABLE)
    {
        switch(col)
        {
        case ColumnCodCust:
            __cust_display->CodCust = text.setNum(__rows_cust + 1);
            break;
        case ColumnNameCust:
            __cust_display->NameCust = value.toString();
            break;
        case ColumnINNCust:
            __cust_display->Inn = value.toString();
            break;
        case ColumnKodRegCust:
            __cust_display->KodReg = value.toString();
            break;
        case ColumnNameSityCust:
            __cust_display->NameSity = value.toString();
            break;
        }
        if (index.isValid() && role == Qt::EditRole)
        {
           if((__cust_display->NameCust != "&") && (__cust_display->Inn != "&") && (__cust_display->KodReg != "&") && (__cust_display->NameSity != "&"))
           {
           emit dataChanged(index, index);
            __customTable->replace(index.row(), *__cust_display);
            delete __cust_display;
            return true;
           }
        }
        delete __cust_display;
        return false;

    }
    else if(__numTable == THIRD_TABLE)
    {
        switch (col) {
        case ColumnKodReg:
            __reg_display->KodReg = text.setNum(__rows_reg + 1);
            break;
        case ColumnNameReg:
            __reg_display->NameReg = value.toString();
            break;
        }
        if (index.isValid() && role == Qt::EditRole)
        {
           if(__reg_display->NameReg != "&")
           {
           emit dataChanged(index, index);
            __regTable->replace(index.row(), *__reg_display);
            delete __reg_display;
            return true;
           }
        }
        delete __reg_display;
     return false;

    }
}

bool controller_allBase::insertRows(int row, int count, const QModelIndex &parent)
{
    beginInsertRows(parent, row, count+row - 1);
    endInsertRows();
    return true;
}

bool controller_allBase::removeRows(int row, int count, const QModelIndex &parent)
{
    int row_count = rowCount();
    if (count == 0 || (row + count - 1) >= row_count){
        qDebug() << "LOXD";
        return false;
    }
    beginRemoveRows(parent, row, row + count - 1);
    if(__numTable == FIRST_TABLE)
        __customTable->remove(row, count);
    else if(__numTable == THIRD_TABLE)
        __regTable->remove(row, count);
    endRemoveRows();
    return true;

}

int controller_allBase::getTableNum()
{
    if(__numTable == FIRST_TABLE)
        return 0;
    else if(__numTable == SECOND_TABLE)
        return 1;
    else if(__numTable == THIRD_TABLE)
        return 2;
    else return 0;
}

void controller_allBase::setTableNum(int value)
{
    //refreshTable();
    __numTable = value;
    if(__numTable == FIRST_TABLE)
       __query = "SELECT * FROM Custom";
    else if (__numTable == SECOND_TABLE)
       __query = "SELECT * FROM Service_Key";
    else if (__numTable == THIRD_TABLE)
       __query = "SELECT * FROM Region";
    refreshTable();
    //endResetModel();
    //updateModel();
}
void controller_allBase::setSecTabNum(int value)
{

    if(__numTable == FIRST_TABLE)
    {
        __secTabName = __customNamesSearch.at(value);
    }
    else if(__numTable == SECOND_TABLE)
    {

        __secTabName = __keyNamesSearch.at(value);
    }
    else if(__numTable == THIRD_TABLE)
    {
        __secTabName = __regNamesSearch.at(value);
    }
}

int controller_allBase::addCustomData(QString cust, QString inn, QString reg, QString city, bool flag)
{
    Custom buf;
    __dispetcher->connectToDataBase();


    __query = "SELECT * FROM Region WHERE NAME_REG = '" + reg +"'";
    //qDebug() << __query;
    __q = __dispetcher->queryToDB(__query);
    __q->next();

    if(__q->value("KOD_REG").toString() == "")
    {
        return -1;
    }
    QString t = "";
    if (!flag)
        buf.CodCust = t.setNum(__rows_cust +1);
    else
        buf.CodCust = __companyCodCust;
    buf.NameCust = cust;
    buf.Inn = inn;
    buf.KodReg = __q->value("KOD_REG").toString();
    buf.NameSity = city;
    qDebug() << flag;

    if (!flag)
    {
        __query = "INSERT INTO Custom (NAME_CUSTOM, INN, KOD_REG, NAME_SITY ) VALUES ( ' " + buf.NameCust + " ', '" + buf.Inn + "', '" + buf.KodReg + "' , '" + buf.NameSity + "')";
        //qDebug() << __query;
        __q = __dispetcher->queryToDB(__query);
        __customTable->push_back(buf);
        insertRows(__customTable->size(), 1);
       // beginResetModel();
        __rows_cust++;
        __rows++;
        //refreshTable();
        //updateModel();
        //endResetModel();
    }
    else
    {
        //UPDATE Custom SET NAME_CUSTOM = 1, INN = 2, KOD_REG = 3, NAME_SITY = 4 WHERE COD_CUST = 71
        qDebug() << "NAMECUST:" << buf.NameCust << "INN" << buf.Inn << "KOD_REG" << buf.KodReg << "NAME_SITY" << buf.NameSity << "CODCUST" << __companyCodCust;
      __query = "UPDATE Custom SET NAME_CUSTOM = '" + buf.NameCust + "', INN = '" + buf.Inn + "', KOD_REG = '" + buf.KodReg + "', NAME_SITY ='" + buf.NameSity + "' WHERE COD_CUST = '" + __companyCodCust + "'";
      __q = __dispetcher->queryToDB(__query);

      beginResetModel();
      __customTable->remove(__rowDelete);
      __customTable->push_back(buf);
        refreshTable();
      endResetModel();
    }
}

void controller_allBase::addRegData(QString kodreg, QString name, bool flag)
{
    Region buf;
    buf.KodReg = kodreg;
    buf.NameReg = name;
    qDebug() << "K=KODREG" << buf.KodReg << " NAMEREG" << buf.NameReg;

    if (!flag)
    {

        __query = "INSERT INTO Region (KOD_REG, NAME_REG) VALUES ( ' " + buf.KodReg + " ', '" + buf.NameReg + "')";
        qDebug() << __query;
        __dispetcher->connectToDataBase();
        __q = __dispetcher->queryToDB(__query);
        __regTable->push_back(buf);
        insertRows(__regTable->size(), 1);
        __rows_reg++;
        qDebug() << "SUCCES";
        //updateModel();
        //refreshTable();

    }
    else
    {
     __query = "UPDATE Region SET NAME_REG = '" + buf.NameReg + "' WHERE KOD_REG = '" + __regKodReg + "'";
      __q = __dispetcher->queryToDB(__query);

      beginResetModel();
      __regTable->remove(__rowDelete);
      __regTable->push_back(buf);
      //refreshTable();
      endResetModel();
      qDebug() << "SUCCES";
    }
}

void controller_allBase::chooseRow(int row)
{
    __checkTouch = true;
    __rowDelete = row;
    if(row >= rowCount()){
        return;
    }
    qDebug() << "ROWWW" << __rowDelete;
    if(__numTable == FIRST_TABLE)
    {
        Custom bufer;
        bufer = __customTable->at(row);
        __companyCodCust = bufer.CodCust;
        __companyCity = bufer.NameSity;
        __companyInn = bufer.Inn;
        __companyReg = bufer.KodReg;
    }
    else if(__numTable == THIRD_TABLE)
    {
        Region bufer;
        bufer = __regTable->at(row);
                qDebug() << "К=KODREG" << bufer.KodReg << " NAMEREG" << bufer.NameReg;
        __regKodReg = bufer.KodReg;
        __regNameReg = bufer.NameReg;
    }

}

void controller_allBase::redactProfile(int row)
{
    if(row >= rowCount()){
        return;
    }
    if (__numTable == FIRST_TABLE)
    {
        QString buf;
        Custom bufer;
        bufer = __customTable->at(row);
        qDebug() << "REG SECWIN" << bufer.KodReg;
        __companyCity = bufer.NameSity;
        __companyInn = bufer.Inn;
        __companyName = bufer.NameCust;
        __companyCodCust = bufer.CodCust;
        buf = bufer.KodReg;
        __dispetcher->connectToDataBase();
        __query = "SELECT * FROM REGION WHERE KOD_REG = " + buf;
        __q = __dispetcher->queryToDB(__query);
        __q->next();
        __companyReg = __q->value("NAME_REG").toString();
    }
    else if (__numTable == THIRD_TABLE)
    {
        Region bufer;
        bufer = __regTable->at(row);
                qDebug() << "К=KODREG" << bufer.KodReg << " NAMEREG" << bufer.NameReg;
        __regKodReg = bufer.KodReg;
        __regNameReg = bufer.NameReg;
    }
}

QString controller_allBase::checkCity()
{
    return __companyCity;
}

QString controller_allBase::checkCodCust()
{
    return __companyCodCust;
}

QString controller_allBase::checkReg()
{
    return __companyReg;
}

QString controller_allBase::checkInn()
{
    return __companyInn;
}

QString controller_allBase::checkName()
{
    return __companyName;
}

int controller_allBase::checkTable()
{
    return __numTable;
}

QString controller_allBase::checkRegKodReg()
{
    return __regKodReg;
}

QString controller_allBase::checkRegNameReg()
{
    return __regNameReg;
}
bool controller_allBase::checkTouchFlag()
{
    return __checkTouch;
}

void controller_allBase::refreshTable()
{
    __dispetcher->connectToDataBase();
    if (__numTable == 0){
        __query = "SELECT * FROM Custom";
        __customTable->clear();
    }
    else if(__numTable == 1){
        __keyTable->clear();
        __query = "SELECT * FROM Service_Key";
    }
    else if (__numTable == 2 || __numTable == 3){
        __query = "SELECT * FROM Region";
        __regTable->clear();
    }
    beginResetModel();
    this->updateModel();
    endResetModel();
}

void controller_allBase::deleteRow()
{
    __dispetcher->connectToDataBase();
    __query = "";
    if(__rowDelete >= rowCount()){
        return;
    }

    if (__numTable == FIRST_TABLE)
    {
        Custom buf;
        buf = __customTable->at(__rowDelete);
        __query = "DELETE FROM Custom WHERE COD_CUST = '" + buf.CodCust + "'";
    }
    else if (__numTable == THIRD_TABLE)
    {
        Region buf;
        buf = __regTable->at(__rowDelete);
        __query = "DELETE FROM Region WHERE KOD_REG = '" + buf.KodReg + "'";
    }
    __dispetcher->queryToDB(__query);
    removeRows(__rowDelete, 1);
}

void controller_allBase::pushDataToFile(QString path)
{

    __filedate = new QVector<QMap<QString, QString>>;
    QMap<QString, QString> bufmap;
    QString fullpath = path + ".csv";
    QVector<QString> headername;
    QString bufstring;
    if(__numTable == FIRST_TABLE)
    {
        bufstring = "Код компании";
        headername.push_back(bufstring);
        bufstring = "Название компании";
        headername.push_back(bufstring);
        bufstring = "ИНН";
        headername.push_back(bufstring);
        bufstring = "Код Региона";
        headername.push_back(bufstring);
        bufstring = "Название города";
        headername.push_back(bufstring);
        bufstring.clear();

        Custom bufer;

        for (int i = 0; i < headername.size(); i++)
        {
            bufstring = headername.at(i);
            bufmap[bufstring] = bufstring;
        }
        __filedate->push_back(bufmap);

        for(int i = 0; i < __customTable->size(); i++)
        {
            bufer = __customTable->at(i);
            bufmap["Код компании"] = bufer.CodCust;
            bufmap["Название компании"] = bufer.NameCust;
            bufmap["ИНН"] = bufer.Inn;
            bufmap["Код Региона"] = bufer.KodReg;
            bufmap["Название города"] = bufer.NameSity;
            __filedate->push_back(bufmap);

        }

    }
    else if (__numTable == SECOND_TABLE)
    {
        ServiceKey bufer;

        bufstring = "Код компании";
        headername.push_back(bufstring);
        bufstring = "ID ключа";
        headername.push_back(bufstring);
        bufstring = "Дата записи";
        headername.push_back(bufstring);
        bufstring = "Номер ключа";
        headername.push_back(bufstring);
        bufstring = "Код региона";
        headername.push_back(bufstring);
        bufstring.clear();

        for (int i = 0; i < headername.size(); i++)
        {
            bufstring = headername.at(i);
            bufmap[bufstring] = bufstring;
        }
        __filedate->push_back(bufmap);

        for (int i = 0; i < __keyTable->size(); i++)
        {
            bufer = __keyTable->at(i);
            bufmap["Код компании"] = bufer.KodCust;
            bufmap["ID ключа"] = bufer.IdNum;
            bufmap["Дата записи"] = bufer.Date;
            bufmap["Номер ключа"] = bufer.NumKey;
            bufmap["Код региона"] = bufer.KodReg;
            __filedate->push_back(bufmap);
        }

    }
    else if (__numTable == THIRD_TABLE)
    {
        Region bufer;

        bufstring = "Код региона";
        headername.push_back(bufstring);
        bufstring = "Название региона";
        headername.push_back(bufstring);
        bufstring.clear();

        for (int i = 0; i < headername.size(); i++)
        {
            bufstring = headername.at(i);
            bufmap[bufstring] = bufstring;
        }
        __filedate->push_back(bufmap);

        for(int i = 0; i < __regTable->size(); i++)
        {
            bufer = __regTable->at(i);
            bufmap["Код региона"] = bufer.KodReg;
            bufmap["Название региона"] =bufer.NameReg;
            __filedate->push_back(bufmap);

        }

    }

    QFile file(fullpath);
    file.open(QFile::WriteOnly);
    if(!file.isOpen())
    {
        return;
    }

    QTextStream fout(&file);
    fout.seek(0);

    for (int i = 0; i < __filedate->size(); i++)
    {
        for(int j = 0; j < headername.size(); j++)
        {
            bufmap = __filedate->at(i);
            bufstring = headername.at(j);
            fout << bufmap[bufstring] << ";";
        }
        fout << "\n";
    }

    file.close();

}

void controller_allBase::search(QString text)
{
    __dispetcher->connectToDataBase();
    if(__numTable == FIRST_TABLE)
    {
        qDebug() << __secTabName << text;
        __query = "SELECT * FROM Custom WHERE " + __secTabName + " LIKE '%" +text + "%'";
        __customTable->clear();
    }
    else if(__numTable == SECOND_TABLE)
    {
        __query = "SELECT * FROM Service_key WHERE " + __secTabName + " LIKE '%" +text + "%'";
        __keyTable->clear();
    }
    else if (__numTable == THIRD_TABLE)
    {
        __query = "SELECT * FROM Region WHERE " + __secTabName + " LIKE '%" +text + "%'";
        __regTable->clear();
    }

    //__q = __dispetcher->queryToDB(__query);

    beginResetModel();
    this->updateModel();
    endResetModel();
}
controller_allBase::~controller_allBase()
{
    delete __q;
    delete __dispetcher;
    delete __customTable;
    delete __keyTable;
    delete __regTable;
    delete __filedate;
}
