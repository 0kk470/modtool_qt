#ifndef CSTEAMMANAGER_H
#define CSTEAMMANAGER_H
#include "steam_api.h"
#include "SteamApiData.h"
#include <QMessageBox>
#include <QDebug>
#include <QObject>

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

  /* Steam消息发送 Api*/
  void Send_CreateItem();

  void Send_SubmitItemUpdate(const SteamUgc_UpdateDetail_t& detailInfo);
  /* Steam消息发送 Api*/

signals:
  void signal_ItemCreateFail(EResult m_eResult);
  void signal_ItemCreateSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);

  void signal_ItemSubmitFail(EResult m_eResult);
  void signal_ItemSubmitSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);

private:
  /* SteamApi消息回调开始*/
  //创建新工坊物品
  CCallResult<CSteamManager, CreateItemResult_t> m_CreateItemResult;
  void On_ItemCreate_Result(CreateItemResult_t *pCallback, bool bIOFailure);

  //更新工坊物品
  CCallResult<CSteamManager, SubmitItemUpdateResult_t> m_SubmitItemUpdateResult;
  void On_ItemSubmit_Result(SubmitItemUpdateResult_t *pCallback, bool bIOFailure);
  /* SteamApi消息回调结束*/
};

#define ISteamManager CSteamManager::GetInstance()

#endif // CSTEAMMANAGER_H
