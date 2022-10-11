#ifndef CSTEAMMANAGER_H
#define CSTEAMMANAGER_H
#include "steam_api.h"
#include <QDebug>

class CSteamManager
{
private:
  CSteamManager();
  ~CSteamManager();
  CSteamManager(const CSteamManager &steamMgr);
  const CSteamManager &operator=(const CSteamManager &steamMgr);

public:
  static CSteamManager* GetInstance();
  void CreateItem();

private:
  void onItemCreated(CreateItemResult_t *pCallback, bool bIOFailure);
  void onItemSubmitted(SubmitItemUpdateResult_t *pCallback, bool bIOFailure);

  CCallResult<CSteamManager, CreateItemResult_t> m_CreateItemResult;
  CCallResult<CSteamManager, SubmitItemUpdateResult_t> m_SubmitItemUpdateResult;
};

#define ISteamManager CSteamManager::GetInstance()

#endif // CSTEAMMANAGER_H
