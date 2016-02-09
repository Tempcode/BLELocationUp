#include "tunnel.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>
#include <QVector>
#include <QRect>

Tunnel::Tunnel()
{
    QLinearGradient gradient(QPointF(50, -20), QPointF(80, 20));
    gradient.setColorAt(0.0, Qt::lightGray);
    gradient.setColorAt(1.0, QColor(100, 100, 100));

    background = QBrush(QColor(210, 210, 210));
    circleBrush = QBrush(gradient);
    rectsPen = QPen(Qt::black);
    rectsPen.setWidth(1);

    textPenTunnel = QPen(Qt::gray);
    textPenTunnelPos = QPen(Qt::darkGray);
    posPointPen = QPen(Qt::black);
    posPointPen.setWidth(4);

    textFontTunnel.setItalic(true);

    m_cardsInfo = new QVector<CardInfo>;
    m_showInfo = true;
}

void Tunnel::setShowInfo(bool show)
{
    m_showInfo = show;
}

void Tunnel::updateCardsInfo(QVector<CardInfo>   * cardsInfo)
{
    m_cardsInfo = cardsInfo;
}

void Tunnel::paint(QPainter *painter, QPaintEvent *event)
{
    QRect paintRect = event->rect();
    textFontTunnel.setPixelSize(0.20*(paintRect.height()));
    textFontTunnelPos.setPixelSize(0.05*(paintRect.height()));

//! [1]背景颜色及移位
    painter->fillRect(paintRect, background);
    painter->translate(0.1* paintRect.width(), 0.24 * paintRect.height());
    painter->save();
//! [1]

//! [2]//隧道长方体
    QVector<QRect> rects;
    QRect leftTunnel(0, 0, 0.8*(paintRect.width()), 0.25*(paintRect.height()) );
    QRect rightTunnel(0, 0.27*paintRect.height(), 0.8*(paintRect.width()), 0.25*(paintRect.height()) );


    rects << leftTunnel << rightTunnel;
    painter->setPen(rectsPen);
    painter->drawRects( rects );
//! [2]

//! [3]//隧道说明文字
    painter->setPen(textPenTunnel);
    painter->setFont(textFontTunnel);
    painter->drawText(leftTunnel, Qt::AlignCenter, QStringLiteral("左 洞"));
    painter->drawText(rightTunnel, Qt::AlignCenter, QStringLiteral("右 洞"));

    painter->setPen(textPenTunnelPos);
    painter->setFont(textFontTunnelPos);
    painter->drawText(leftTunnel.x()-0.10*(paintRect.height()),
                      leftTunnel.y()+leftTunnel.height()/2,
                      QStringLiteral("洞口"));
    painter->drawText(leftTunnel.x()+leftTunnel.width(),
                      leftTunnel.y()+leftTunnel.height()/2, QStringLiteral("掌子面"));

    painter->drawText(rightTunnel.x()-0.10*(paintRect.height()),
                      rightTunnel.y()+rightTunnel.height()/2,
                      QStringLiteral("洞口"));
    painter->drawText(rightTunnel.x()+rightTunnel.width(),
                      rightTunnel.y()+rightTunnel.height()/2,QStringLiteral("掌子面"));
    painter->restore();
//! [3]

//! [4]//绘制点及其文字
    for(int i = 0; i < m_cardsInfo->count(); i++)
    {
        painter->setPen(posPointPen);
        painter->drawPoint(m_cardsInfo->at(i).Pos);
        if(m_showInfo)
        {
            painter->setPen(posInfoPen);
            painter->drawText(m_cardsInfo->at(i).Pos.x()+4,
                              m_cardsInfo->at(i).Pos.y()+4,
                              m_cardsInfo->at(i).Info);
        }
    }
//! [4]

}
