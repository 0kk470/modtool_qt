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
  void OnCloseBtnClick();
  void OnMaxmizeBtnClick();
  void OnPageBtnClick(int idx);
  void OnModPathBtnClick();
  void OnUploadBtnClick();

private:
  Ui::MainWindow *ui;
  QButtonGroup* m_LeftBtnGroup;

  QPoint m_PrevPos;

private:
    void resizeEvent(QResizeEvent* event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

};
#endif // MAINWINDOW_H
