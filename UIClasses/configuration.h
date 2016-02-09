#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QWidget>

class QSplitter;
class QPaintEvent;
class QHBoxLayout;
class QStackedWidget;

class AnchorMG;
class DutyMG;
class NetConfigMG;
class PersonnelMG;
class TitleMG;

namespace Ui {
class Configuration;
}

class Configuration : public QWidget
{
    Q_OBJECT

public:
    explicit Configuration(QWidget *parent = 0);
    ~Configuration();

    void paintEvent(QPaintEvent * evet);

public slots:
    void setCurrentIndex(int index);
    void setGroupBoxTitle(QString title);

private slots:

private:
    Ui::Configuration   *   ui;
    QHBoxLayout         *   m_mainLayout;
    QHBoxLayout         *   m_groupBoxLayout;
    QSplitter           *   m_splitter;
    QStackedWidget      *   m_stackedWidget;

    PersonnelMG         *   m_personnelWidget;
    DutyMG              *   m_dutyWidget;
    TitleMG             *   m_titleWidget;
    AnchorMG            *   m_anchorWidget;
    NetConfigMG         *   m_netConfigWidget;

};

#endif // CONFIGURATION_H
