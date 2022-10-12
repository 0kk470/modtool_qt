#ifndef CSTEAMMANAGER_H
#define CSTEAMMANAGER_H
#include "steam_api.h"
#include "SteamApiData.h"
#include <QDebug>
#include <QObject>
#include <QMessageBox>

#define API_CHECK if(!IsInitialized())\
                    {\
                        qDebug("错误，Steam未初始化,无法调用对应API:%s",Q_FUNC_INFO);\
                        QMessageBox::critical(nullptr, "错误","Steam未初始化,无法进行该操作\n\n请尝试启动Steam客户端后重启该工具");\
                        emit signal_CallAPI_Fail(Q_FUNC_INFO);\
                        return false;\
                    }\
                    else{\
                        qDebug("调用成功 [%s]", Q_FUNC_INFO);\
                    }\

#define ISteamManager CSteamManager::GetInstance()

class CSteamManager:public QObject
{
  Q_OBJECT

private:
  CSteamManager();
  ~CSteamManager();
  CSteamManager(const CSteamManager &steamMgr);
  const CSteamManager &operator=(const CSteamManager &steamMgr);

public:
  static CSteamManager* GetInstance();
  void Init();
  bool IsInitialized() const;

  bool Send_CreateItem();
  bool Send_SubmitItemUpdate(const SteamUgc_UpdateDetail_t& detailInfo);
  EItemUpdateStatus GetItemUpdateProgress(UGCUpdateHandle_t handle, uint64 *punBytesProcessed, uint64* punBytesTotal);

signals:
  void signal_ItemCreateFail(EResult m_eResult);
  void signal_ItemCreateSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);

  void signal_ItemSubmitFail(EResult m_eResult);
  void signal_ItemSubmitSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);
  void signal_CallAPI_Fail(const QString& apiName);
  void signal_BeginItemUpdate(UGCUpdateHandle_t handler);

private:
  bool m_IsInit = false;

private:

  CCallResult<CSteamManager, CreateItemResult_t> m_CreateItemResult;
  void On_ItemCreate_Result(CreateItemResult_t *pCallback, bool bIOFailure);


  CCallResult<CSteamManager, SubmitItemUpdateResult_t> m_SubmitItemUpdateResult;
  void On_ItemSubmit_Result(SubmitItemUpdateResult_t *pCallback, bool bIOFailure);
};

#endif // CSTEAMMANAGER_H
