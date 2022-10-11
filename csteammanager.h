#ifndef CSTEAMMANAGER_H
#define CSTEAMMANAGER_H
#include "steam_api.h"
#include "SteamApiData.h"
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


  void Send_CreateItem();
  void Send_SubmitItemUpdate(const SteamUgc_UpdateDetail_t& detailInfo);

signals:
  void signal_ItemCreateFail(EResult m_eResult);
  void signal_ItemCreateSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);

  void signal_ItemSubmitFail(EResult m_eResult);
  void signal_ItemSubmitSuccess(EResult m_eResult, PublishedFileId_t m_nPublishedFileId);

private:

  CCallResult<CSteamManager, CreateItemResult_t> m_CreateItemResult;
  void On_ItemCreate_Result(CreateItemResult_t *pCallback, bool bIOFailure);


  CCallResult<CSteamManager, SubmitItemUpdateResult_t> m_SubmitItemUpdateResult;
  void On_ItemSubmit_Result(SubmitItemUpdateResult_t *pCallback, bool bIOFailure);
};

#define ISteamManager CSteamManager::GetInstance()

#endif // CSTEAMMANAGER_H
