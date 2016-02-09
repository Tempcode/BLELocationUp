#ifndef ANCHORMG_H
#define ANCHORMG_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QResizeEvent>

class QTableView;

namespace Ui {
class AnchorMG;
}

class AnchorMG : public QWidget
{
    Q_OBJECT

public:
    explicit AnchorMG(QWidget *parent = 0);
    ~AnchorMG();
    void resizeEvent(QResizeEvent * event);
private:
    void initTableWidget();

private:
    Ui::AnchorMG        *   ui;
    QTableView          *   m_anchorTableView;
    QAbstractItemModel  *   model;
};

#endif // ANCHORMG_H
