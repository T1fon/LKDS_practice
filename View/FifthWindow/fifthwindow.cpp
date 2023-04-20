#include "fifthwindow.h"

FifthWindow::FifthWindow()
{

}

FifthWindow::~FifthWindow()
{

}

QList<QString> FifthWindow::getColumnName(int value)
{
    if(value == FIRST_TABLE)
    {
        QList<QString> textCust{"CodCust", "NameCust", "Inn", "KodReg", "NameCity"};
        return textCust;
    }
    else if(value == SECOND_TABLE)
    {
        QList<QString> textService{"IdNum", "KodCust", "RegKey", "DateKey", "NumKey"};
        return textService;
    }
    else if (value == THIRD_TABLE)
    {
        QList<QString> textReg{"KodReg", "NameReg"};
        return textReg;
    }
    else{
        return QList<QString> ();
    }
}

QList<QString> FifthWindow::getTableName()
{
    QList<QString> textTable{"Custom", "ServiceKey", "Region"};
    return textTable;
}
