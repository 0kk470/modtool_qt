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
    connect(ui->bn_max, &QPushButton::clicked, this, &MainWindow::showMaximized);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnCloseBtnClick()
{
    qApp->quit();
}


