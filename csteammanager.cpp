#include "csteammanager.h"

CSteamManager::CSteamManager()
{

}

CSteamManager::~CSteamManager()
{

}

CSteamManager* CSteamManager::GetInstance()
{
    static CSteamManager _instance;
    return &_instance;
}


//We create a new Item by providing the game ID and we specify we are creating a normal mod that can be subscribed to
void CSteamManager::CreateItem()
{
  qDebug("Creating item...");

  SteamAPICall_t hSteamAPICall = SteamUGC()->CreateItem(SteamUtils()->GetAppID() , k_EWorkshopFileTypeCommunity);
  m_CreateItemResult.Set(hSteamAPICall, this, &CSteamManager::onItemCreated);
}

//Once the mod was created, we can grab the id from the callback params and then customize it with the UGCUpdateHandle_t before making another API call to SubmitItemUpdate
void CSteamManager::onItemCreated(CreateItemResult_t *pCallback, bool bIOFailure)
{
  if(pCallback->m_eResult == k_EResultOK)
  {
    qDebug("Item created!");
  }
    if(pCallback->m_bUserNeedsToAcceptWorkshopLegalAgreement)
    {
      SteamFriends()->ActivateGameOverlayToWebPage("steam://url/CommunityFilePage/");
    }

    UGCUpdateHandle_t handle = SteamUGC()->StartItemUpdate(SteamUtils()->GetAppID(), pCallback->m_nPublishedFileId);

    SteamUGC()->SetItemTitle(handle, "Title test");
    SteamUGC()->SetItemDescription(handle, "Description test");
    SteamUGC()->SetItemUpdateLanguage(handle, "None");
    SteamUGC()->SetItemMetadata(handle, "Test metadata");
    SteamUGC()->SetItemVisibility(handle, k_ERemoteStoragePublishedFileVisibilityPublic);

    SteamParamStringArray_t *pTags = new SteamParamStringArray_t();
    pTags->m_ppStrings = new const char*[1];
    pTags->m_ppStrings[0] = "stage";
    pTags->m_nNumStrings = 1;
    SteamUGC()->SetItemTags(handle, pTags);
    SteamUGC()->AddItemKeyValueTag(handle, "test_key", "test_value");
    auto mod_directory= "/home/turupawn/ModExample";
    SteamUGC()->SetItemContent(handle, mod_directory);
    auto preview_image = "/home/turupawn/ModExample/preview.png";
    SteamUGC()->SetItemPreview(handle, preview_image);

    auto pchChangeNote = "This is a changelog";

    SteamAPICall_t submit_item_call = SteamUGC()->SubmitItemUpdate(handle, pchChangeNote);
    m_SubmitItemUpdateResult.Set(submit_item_call, this, &CSteamManager::onItemSubmitted);
}

void CSteamManager::onItemSubmitted(SubmitItemUpdateResult_t *pCallback, bool bIOFailure)
{
  if(pCallback->m_eResult != k_EResultOK || bIOFailure)
  {
    qDebug("Item update submitted created!");
  }
}
