#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTabWidget>
#include <QMessageBox>
#include <QButtonGroup>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QCursor>
#include <QFileDialog>
#include <QSettings>
#include <QWebEngineView>
#include "overlaywidget.h"
#include "csteammanager.h"
#include "steam_api.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
  void OnUpdate();
  void OnCloseBtnClick();
  void OnMaxmizeBtnClick();
  void OnPageBtnClick(int idx);
  void OnVisibilityBtnClick(int idx);
  void OnModPathBtnClick();
  void OnUploadBtnClick();
  void OnPerviewPathBtnClick();

  //Steam回调
  void OnItemCreateFail(EResult m_eResult);
  void OnItemCreateSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);
  void OnItemSubmitFail(EResult m_eResult);
  void OnItemSubmitSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);
  void OnBeginUpdateItem(UGCUpdateHandle_t handle);
  void OnCallApiFail(const QString& apiName);
private:
  Ui::MainWindow *ui;
  QButtonGroup* m_LeftBtnGroup;
  QButtonGroup* m_VisibilityGroup;
  LoadingOverlay* m_UploadingMask;
  QPoint m_PrevPos;
  QTimer* m_UpdateTimer;
  UGCUpdateHandle_t m_uploadHandle;

private:
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void SubmitMod(PublishedFileId_t modId);
    void SaveModSettings(PublishedFileId_t modId);
    void LoadModSettings();
    void InitPageButtons();
    void InitVisibilityButtons();
    void CheckSteamInit();
    void HideUploadMask();
    bool IsUploading();
    QString GetUploadProgressText(EItemUpdateStatus status, uint64 bytesDone, uint64 bytesTotal);
};
#endif // MAINWINDOW_H
