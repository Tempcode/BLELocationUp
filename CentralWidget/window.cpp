/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "./PaintTunnel/tunnelWidget.h"
#include "window.h"
#include "mainwindow.h"
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>
#include <QPushButton>
#include <QDesktopWidget>
#include <QApplication>
#include <QMessageBox>
#include <QGroupBox>

Window::Window(MainWindow *mw)
    : QWidget(mw)
{
    m_mainLayout = new QHBoxLayout(this);
    m_rightLayout = new QVBoxLayout();
    QWidget *rightWidget = new QWidget();
    QGroupBox *groupBoxViewFunc = new QGroupBox(tr("视图功能"));
    m_leftHSplitter = new QSplitter(Qt::Horizontal);
    m_leftHSplitter->setHandleWidth(5);

    QTimer *timerUpdate = new QTimer(this);
    m_leftTree = new QTreeWidget(this);
    updateTreeWidget();
    connect(timerUpdate, SIGNAL(timeout()), this, SLOT(updateTreeWidget()));

    m_showPosInfo = new QPushButton(tr("显示信息"));
    m_rightButtonsLayout = new QGridLayout();
    TunnelWidget *  tunnelWidget = new TunnelWidget(&tunnel);
    m_rightVSplitter = new QSplitter(Qt::Vertical);
    m_rightVSplitter->setHandleWidth(5);

    m_rightButtonsLayout->addWidget(m_showPosInfo);
    groupBoxViewFunc->setLayout(m_rightButtonsLayout);

    m_rightVSplitter->addWidget(tunnelWidget);
    m_rightVSplitter->addWidget(groupBoxViewFunc);

    m_rightLayout->addWidget(m_rightVSplitter);

    rightWidget->setLayout(m_rightLayout);

    m_leftHSplitter->addWidget(m_leftTree);
    m_leftHSplitter->addWidget(rightWidget);
    m_leftHSplitter->setStretchFactor(0,1);
    m_leftHSplitter->setStretchFactor(1,9);
    m_mainLayout->addWidget(m_leftHSplitter);
    setLayout(m_mainLayout);
    timerUpdate->start(2000);
}

void Window::updateTreeWidget()
{
    m_leftTree->setColumnCount(2);
    QStringList treeHeaders;
    treeHeaders << "职务" << "姓名";
    m_leftTree->setHeaderLabels(treeHeaders);
    m_leftTree->setColumnWidth(0, 50);
    m_leftTree->setColumnWidth(1, 75);
}

QSlider *Window::createSlider()
{
    QSlider *slider = new QSlider(Qt::Vertical);
    slider->setRange(0, 360 * 16);
    slider->setSingleStep(16);
    slider->setPageStep(15 * 16);
    slider->setTickInterval(15 * 16);
    slider->setTickPosition(QSlider::TicksRight);
    return slider;
}

void Window::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
