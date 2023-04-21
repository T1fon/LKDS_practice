#include "COMPortModel.h"

COMPortModel::COMPortModel()
{
    __COM_names_variant = new QVector<QVariant>;
    __COM_info = new QList<QSerialPortInfo>;

   updateData();
}

COMPortModel::~COMPortModel()
{
    delete __COM_info;
    delete __COM_names_variant;
}

void COMPortModel::updateData(){
    *__COM_info = QSerialPortInfo::availablePorts();
    qDebug() << "DataUpdate";
    if(!removeRows(0,__COM_names_variant->size())){
        qDebug() << "Data no Add";
    }
    if(!insertRows(0,__COM_info->size())){
        qDebug() << "Data no remove";
    }
}
void COMPortModel::saveData(QString path){
    QFile file(path);
    file.open(QFile::WriteOnly);
    if(!file.isOpen()){
        //сигнал об ошибке
        emit saveError("File " + path + " not open");
        return;
    }

    QTextStream fout(&file);
    fout.seek(0);

    int count_field = 4;
    QString title[count_field];
    title[0] = "Device_Name:";
    title[1] = "Device_Id:";
    title[2] = "Manufacturer_Name:";
    title[3] = "Manufacturer_Id:";

    QString value[count_field];
    value[0] = __COM_info->at(__current_index).description();
    value[1] = QString().setNum(__COM_info->at(__current_index).productIdentifier());
    value[2] = __COM_info->at(__current_index).manufacturer();
    value[3] = QString().setNum(__COM_info->at(__current_index).vendorIdentifier());

    for(int i = 0; i < count_field; i++){
        value[i] = value[i].replace(' ','_');
        if(value[i] != ""){
            fout << title[i] << " " << value[i] << "\n";
        }
        else{
            fout << title[i] << " " << value[i] << "\n";
        }
    }

    file.close();
}
bool COMPortModel::setCurrentIndex(int value){
    if(value < 0){
        return false;
    }
    __current_index = value;
    return true;
}
int COMPortModel::getCurrentIndex(){
    return __current_index;
}
bool COMPortModel::setData(const QModelIndex &index, const QVariant &value, int role){
    emit dataChanged(index,index,{role});
    __COM_names_variant->push_back(value);
    return true;
}
bool COMPortModel::insertRows(int row, int count, const QModelIndex &parent){
    int row_count = rowCount();
    if(count == 0 || row > row_count){
        return false;
    }

    emit beginInsertRows(parent,row,row+count-1);
    for(int i = 0; i < count; i++){
        setData(createIndex(i,0),QVariant(__COM_info->at(i).portName()));
    }
    emit endInsertRows();
    return true;
}
bool COMPortModel::removeRows(int row, int count, const QModelIndex &parent){
    int row_count = rowCount();
    if(count == 0 || (row + count - 1) > row_count){
        return false;
    }

    emit beginRemoveRows(parent,row,row+count-1);
    __COM_names_variant->remove(row,count);
    emit endRemoveRows();
    return true;
}
int COMPortModel::rowCount(const QModelIndex &parent) const{
    return __COM_names_variant->size();
}
QVariant COMPortModel::data(const QModelIndex &index, int role)const{
    int temp_row = index.row();

    if(role != Qt::DisplayRole || !index.isValid() || temp_row >= rowCount()){
        return QVariant();
    }

    return __COM_names_variant->at(temp_row);
}
QHash<int, QByteArray> COMPortModel::roleNames()const{
    return {{Qt::DisplayRole,"display"}};
}

QString COMPortModel::getDeviceName(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString( __COM_info->at(index).description() );
}
QString COMPortModel::getPortName(const int &index){
    if(index >= rowCount()){
        return "";
    }
    return __COM_info->at(index).portName();
}
QString COMPortModel::getDeviceId(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString().setNum(__COM_info->at(index).productIdentifier());
}
QString COMPortModel::getManufacturerName(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString( __COM_info->at(index).manufacturer() );
}
QString COMPortModel::getManufacturerId(const int &index){
    if(index >= rowCount()){
        return "";
    }

    return QString().setNum(__COM_info->at(index).vendorIdentifier() );
}
