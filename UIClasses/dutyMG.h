#ifndef DUTYMG_H
#define DUTYMG_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QResizeEvent>

class QTableView;

namespace Ui {
class DutyMG;
}

class DutyMG : public QWidget
{
    Q_OBJECT

public:
    explicit DutyMG(QWidget *parent = 0);
    ~DutyMG();
    void resizeEvent(QResizeEvent * event);
private:
    void initTableWidget();

private:
    Ui::DutyMG *ui;
    QTableView          *   m_dutyTableView;
    QAbstractItemModel  *   model;
};

#endif // DUTYMG_H
