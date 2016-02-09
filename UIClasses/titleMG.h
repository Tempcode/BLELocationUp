#ifndef TITLEMG_H
#define TITLEMG_H

#include <QWidget>
#include <QAbstractItemModel>
#include <QResizeEvent>


class QTableView;

namespace Ui {
class TitleMG;
}

class TitleMG : public QWidget
{
    Q_OBJECT

public:
    explicit TitleMG(QWidget *parent = 0);
    ~TitleMG();
    void resizeEvent(QResizeEvent * event);
private:
    void initTableWidget();

private:
    Ui::TitleMG *ui;
    QTableView          *   m_titleTableView;
    QAbstractItemModel  *   model;
};

#endif // TITLEMG_H
