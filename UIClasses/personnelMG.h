#ifndef PERSONNELMG_H
#define PERSONNELMG_H

#include <QWidget>
#include <QResizeEvent>

class QTableView;
class QAbstractItemModel;

namespace Ui {
class PersonnelMG;
}

class PersonnelMG : public QWidget
{
    Q_OBJECT

public:
    explicit PersonnelMG(QWidget *parent = 0);
    ~PersonnelMG();
    void resizeEvent(QResizeEvent * event);

private:
    void initTableView();

private:
    Ui::PersonnelMG     *   ui;
    QTableView          *   m_personnelTableView;
    QAbstractItemModel  *   model;
};

#endif // PERSONNELMG_H
