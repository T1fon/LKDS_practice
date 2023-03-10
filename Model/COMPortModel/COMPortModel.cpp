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

    for(int i = 0; i < __COM_info->size(); i++){
        __COM_names_variant->push_back(__COM_info->at(i).portName());
    }
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
