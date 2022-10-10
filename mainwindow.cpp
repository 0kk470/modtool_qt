#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::CustomizeWindowHint);
    connect(ui->bn_close, &QPushButton::clicked, this, &MainWindow::OnCloseBtnClick);
    connect(ui->bn_min, &QPushButton::clicked, this, &MainWindow::showMinimized);
    connect(ui->bn_max, &QPushButton::clicked, this, &MainWindow::OnMaxmizeBtnClick);

    m_LeftBtnGroup = new QButtonGroup(this);
    m_LeftBtnGroup->addButton(ui->bn_home, 0);
    m_LeftBtnGroup->addButton(ui->bn_cloud, 1);
    connect(m_LeftBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::OnPageBtnClick);
    if ( !SteamAPI_Init() )
    {
        QMessageBox::warning(this,"提示", "Steam Api初始化失败, Steam相关功能将失效");
        qDebug( "Fatal Error - Steam must be running to play this game (SteamAPI_Init() failed).\n" );
        ui->lab_user->setText("No Steam User");
    }
    else
    {
        const char* pchName = SteamFriends()->GetPersonaName();
        ui->lab_user->setText(pchName);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    if(isMaximized())
    {
        ui->bn_max->setIcon(QIcon("icons/1x/restore.png"));
    }
    else
    {
        ui->bn_max->setIcon(QIcon("icons/1x/max.png"));
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    m_PrevPos = QCursor::pos();
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::MouseButton::LeftButton)
    {
       if(isMaximized())
           return;
       auto offset = m_PrevPos - QCursor::pos();
       m_PrevPos = QCursor::pos();
       move(pos() - offset);
    }
}


void MainWindow::OnMaxmizeBtnClick()
{
    if(isMaximized())
    {
        showNormal();
    }
    else if(!isMinimized())
    {
        showMaximized();
    }
}

void MainWindow::OnCloseBtnClick()
{
    qApp->quit();
}

void MainWindow::OnPageBtnClick(int idx)
{
    auto btns = m_LeftBtnGroup->buttons();
    for(auto i = 0;i < btns.size(); ++i )
    {
        btns[i]->setChecked(i == idx);
    }
    for(auto i = 0; i < ui->stackedWidget->count(); ++i)
    {
        ui->stackedWidget->widget(i)->setVisible(i == idx);
    }
}


