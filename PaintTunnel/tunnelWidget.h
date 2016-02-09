#ifndef TUNNELWIDGET_H
#define TUNNELWIDGET_H

#include <QWidget>
#include <QTimer>

class Tunnel;

class TunnelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TunnelWidget(Tunnel *tunnel, QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

signals:

public slots:
    void animate();

private:
    Tunnel *tunnel;
};

#endif // TUNNELWIDGET_H
