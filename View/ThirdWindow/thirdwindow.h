#ifndef THIRDWINDOW_H
#define THIRDWINDOW_H
#include <qqml.h>
#include <QObject>

class ThirdWindow : public QObject
{
public:
   explicit ThirdWindow(QObject *parent = nullptr);
};

#endif // THIRDWINDOW_H
