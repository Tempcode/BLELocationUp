#ifndef NETCONFIGMG_H
#define NETCONFIGMG_H

#include <QWidget>

namespace Ui {
class NetConfigMG;
}

class NetConfigMG : public QWidget
{
    Q_OBJECT

public:
    explicit NetConfigMG(QWidget *parent = 0);
    ~NetConfigMG();

private:
    Ui::NetConfigMG *ui;
};

#endif // NETCONFIGMG_H
