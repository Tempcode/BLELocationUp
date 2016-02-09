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

#include "mainwindow.h"
#include "./CentralWidget/window.h"
#include "./UIClasses/configuration.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>

#define personnelM      ("人员管理")
#define dutyM           ("班次管理")
#define titleM          ("职务管理")
#define anchorM         ("锚点管理")
#define netM            ("网络配置")


MainWindow::MainWindow()
{
//Menus
    QMenuBar *menuBar = new QMenuBar;
    //File
    QMenu *menuFile = menuBar->addMenu(tr("文件"));
    QAction *pageSet = new QAction(menuFile);
    QAction *printPreview = new QAction(menuFile);
    QAction *pirnt = new QAction(menuFile);
    QAction *exit = new QAction(menuFile);
    pageSet->setText(tr("页面设置"));
    printPreview->setText(tr("打印预览"));
    pirnt->setText(tr("打印"));
    exit->setText(tr("退出"));
    menuFile->addAction(pageSet);
    menuFile->addAction(printPreview);
    menuFile->addAction(pirnt);
    menuFile->addAction(exit);
    //Edit
    QMenu *menuEdit = menuBar->addMenu(tr("编辑"));
    QAction *find = new QAction(menuEdit);
    find->setText(tr("查找"));
    menuEdit->addAction(find);
    //View
    QMenu *menuView = menuBar->addMenu(tr("视图"));
    QAction *records = new QAction(menuView);
    QAction *graphics = new QAction(menuView);
    QAction *showLeftTree = new QAction(menuView);
    records->setText(tr("记录"));
    graphics->setText(tr("图形"));
    showLeftTree->setText(tr("显示左侧树"));
    menuView->addAction(graphics);
    menuView->addAction(records);
    menuView->addAction(showLeftTree);
    //Configuration
    QMenu *menuConfiguration = menuBar->addMenu(tr("配置"));
    QAction *personnelMG = new QAction(menuConfiguration);
    QAction *dutyMG = new QAction(menuConfiguration);
    QAction * titleMG = new QAction(menuConfiguration);
    QAction *anchorMG = new QAction(menuConfiguration);
    QAction *netConfigMG = new QAction(menuConfiguration);
    personnelMG->setText(tr(personnelM));
    dutyMG->setText(tr(dutyM));
    titleMG->setText(tr(titleM));
    anchorMG->setText(tr(anchorM));
    netConfigMG->setText(tr(netM));
    menuConfiguration->addAction(personnelMG);
    menuConfiguration->addAction(dutyMG);
    menuConfiguration->addAction(titleMG);
    menuConfiguration->addAction(anchorMG);
    menuConfiguration->addAction(netConfigMG);
    //Help
    QMenu *menuHelp = menuBar->addMenu(tr("帮助"));
    QAction *about = new QAction(menuHelp);
    about->setText(tr("关于"));
    menuHelp->addAction(about);

//Toolbars

//Dock Widgets

//Status Bar
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->showMessage("BLELocation Ver:1.0", 0);
    setStatusBar(statusBar);

    setMenuBar(menuBar);
    setCentralWidget(new Window(this));

    m_configuration = new Configuration(this);
    m_configuration->hide();
    connect(menuConfiguration, SIGNAL(triggered(QAction*)), this, SLOT(showConfiguretion(QAction*)));
}

void MainWindow::showConfiguretion(QAction* action)
{
    m_configuration->show();
    if(personnelM == action->text())
    {
        m_configuration->setCurrentIndex(0);
    }else if(dutyM == action->text()){
        m_configuration->setCurrentIndex(1);
    }else if(titleM == action->text()){
        m_configuration->setCurrentIndex(2);
    }else if(anchorM == action->text()){
        m_configuration->setCurrentIndex(3);
    }else if(netM == action->text()){
        m_configuration->setCurrentIndex(4);
    }
}

