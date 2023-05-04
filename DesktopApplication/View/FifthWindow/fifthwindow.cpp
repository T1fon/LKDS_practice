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
        QList<QString> textCust{"Код компании", "Наименование", "ИНН", "Регион", "Город"};
        return textCust;
    }
    else if(value == SECOND_TABLE)
    {
        QList<QString> textService{"ID ключа", "Код компании", "Регион", "Дата создания", "Номер ключа"};
        return textService;
    }
    else if (value == THIRD_TABLE)
    {
        QList<QString> textReg{"Код региона", "Наименование"};
        return textReg;
    }
    else{
        return QList<QString> ();
    }
}

QList<QString> FifthWindow::getTableName()
{
    QList<QString> textTable{"Компании", "Сервисные ключи", "Регионы"};
    return textTable;
}
