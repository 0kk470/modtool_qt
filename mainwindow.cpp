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
    connect(ui->browser_btn, &QPushButton::clicked, this, &MainWindow::OnModPathBtnClick);
    connect(ui->preview_btn, &QPushButton::clicked, this, &MainWindow::OnPerviewPathBtnClick);
    connect(ui->bn_upload_2, &QPushButton::clicked, this, &MainWindow::OnUploadBtnClick);
    connect(ISteamManager, &CSteamManager::signal_ItemCreateSuccess, this, &MainWindow::OnItemCreateSuccess);
    connect(ISteamManager, &CSteamManager::signal_ItemCreateFail, this, &MainWindow::OnItemCreateFail);
    connect(ISteamManager, &CSteamManager::signal_ItemSubmitSuccess, this, &MainWindow::OnItemSubmitSuccess);
    connect(ISteamManager, &CSteamManager::signal_ItemSubmitFail, this, &MainWindow::OnItemSubmitFail);

    InitPageButtons();
    CheckSteamInit();
    LoadModSettings();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitPageButtons()
{
    m_LeftBtnGroup = new QButtonGroup(this);
    m_LeftBtnGroup->addButton(ui->bn_home, 0);
    m_LeftBtnGroup->addButton(ui->bn_cloud, 1);
    for(auto btn: m_LeftBtnGroup->buttons())
    {
        btn->setCheckable(true);
    }
    connect(m_LeftBtnGroup, QOverload<int>::of(&QButtonGroup::buttonClicked), this, &MainWindow::OnPageBtnClick);
}

void MainWindow::CheckSteamInit()
{
    if (!ISteamManager->IsInitialized())
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

void MainWindow::SaveModSettings(PublishedFileId_t m_nPublishedFileId)
{
    QSettings settings;
    settings.setValue("mod/mod_id", m_nPublishedFileId);
    settings.setValue("mod/mod_name", ui->mod_name_input->text());
    settings.setValue("mod/description", ui->textEdit_des->toPlainText());
    settings.setValue("mod/note", ui->textEdit_note->toPlainText());
    settings.setValue("mod/modContentPath", ui->file_path->text());
    settings.setValue("mod/previewImgPath", ui->preview_path->text());
    settings.sync();
}

void MainWindow::LoadModSettings()
{
    QSettings settings;
    qDebug() << settings.value("mod/mod_id").value<QString>();
    ui->modid_input->setText(settings.value("mod/mod_id").toString());
    ui->mod_name_input->setText(settings.value("mod/mod_name").toString());
    ui->textEdit_des->setText(settings.value("mod/description").toString());
    ui->textEdit_note->setText(settings.value("mod/note").toString());
    ui->file_path->setText(settings.value("mod/modContentPath").toString());;
    ui->preview_path->setText(settings.value("mod/previewImgPath").toString());
    //detail.visibilty = k_ERemoteStoragePublishedFileVisibilityUnlisted;
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
    //    auto btns = m_LeftBtnGroup->buttons();
    //    for(auto i = 0;i < btns.size(); ++i )
    //    {
    //        btns[i]->setChecked(i == idx);
    //    }
    for(auto i = 0; i < ui->stackedWidget->count(); ++i)
    {
        ui->stackedWidget->widget(i)->setVisible(i == idx);
    }
}

void MainWindow::OnModPathBtnClick()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    ui->file_path->setText(dirName);
}

void MainWindow::OnPerviewPathBtnClick()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Image"),
                                                    "/home",
                                                    tr("Images (*.png *.jpg)"));
    ui->preview_path->setText(filePath);
}

void MainWindow::OnUploadBtnClick()
{
    PublishedFileId_t modId = 0;
    bool isValidId = false;
    modId = ui->modid_input->text().toULong(&isValidId);
    if(!isValidId || modId <= 0)
    {
        ISteamManager->Send_CreateItem();
    }
    else
    {
        SubmitMod(modId);
    }
}

void MainWindow::SubmitMod(PublishedFileId_t modId)
{
    SteamUgc_UpdateDetail_t detail;
    detail.itemTitle = ui->mod_name_input->text().toStdString();
    detail.itemDescription = ui->textEdit_des->toPlainText().toStdString();
    detail.changeNote = ui->textEdit_note->toPlainText().toStdString();
    detail.fileFolder = ui->file_path->text().toStdString();
    detail.previewImagePath = ui->preview_path->text().toStdString();
    detail.m_nPublishedFileId = modId;
    detail.visibilty = k_ERemoteStoragePublishedFileVisibilityUnlisted;
    ISteamManager->Send_SubmitItemUpdate(detail);
}

void MainWindow::OnItemCreateFail(EResult m_eResult)
{
    auto msg = QString("创建WorkShopItem 失败\n 错误码EResult:{%1}").arg(m_eResult);
    QMessageBox::critical(this,"错误", msg);
}

void MainWindow::OnItemCreateSuccess(EResult m_eResult, PublishedFileId_t publishedId)
{
    QString modId = QString("%1").arg(publishedId);
    ui->modid_input->setText(modId);
    SubmitMod(publishedId);
}

void MainWindow::OnItemSubmitFail(EResult m_eResult)
{
    auto msg = QString("提交WorkShopItem 失败\n 错误码EResult:{%1}").arg(m_eResult);
    QMessageBox::critical(this, "错误", msg);
}

void MainWindow::OnItemSubmitSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId)
{
    auto msg = QString("提交WorkShopItem 成功");
    QMessageBox::information(this, "提交成功", msg);
    SaveModSettings(m_nPublishedFileId);
}


