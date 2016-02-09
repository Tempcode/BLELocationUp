#ifndef TUNNEL_H
#define TUNNEL_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPoint>
#include <QString>
#include <QWidget>
#include <QVector>

typedef struct tagCardInfo
{
    QPoint      Pos;
    QString     Info;
}CardInfo;

class Tunnel
{
public:
    Tunnel();

public:
    void paint(QPainter *painter, QPaintEvent *event);

public slots:
    void updateCardsInfo(QVector<CardInfo>   * cardsInfo);
    void setShowInfo(bool show);

private:
    QBrush                  background;
    QBrush                  circleBrush;
    QFont                   textFontTunnel;
    QFont                   textFontTunnelPos;
    QPen                    rectsPen;
    QPen                    textPenTunnel;
    QPen                    textPenTunnelPos;
    QPen                    posPointPen;
    QPen                    posInfoPen;
    QVector<CardInfo>   *   m_cardsInfo;
    bool                    m_showInfo;
};

#endif // TUNNEL_H
