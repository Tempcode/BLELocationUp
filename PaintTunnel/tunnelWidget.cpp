#include "tunnelWidget.h"
#include "tunnel.h"
#include <QPainter>

TunnelWidget::TunnelWidget(Tunnel *tunnel, QWidget *parent)
    : QWidget(parent), tunnel(tunnel)
{
}

void TunnelWidget::animate()
{
    update();
}

void TunnelWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    tunnel->paint(&painter, event);
    painter.end();
}
