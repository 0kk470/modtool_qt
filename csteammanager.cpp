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

void CSteamManager::Init()
{
    if(!SteamAPI_Init())
    {
        return;
    }
    m_IsInit = true;
}

bool CSteamManager::IsInitialized() const
{
    return m_IsInit;
}


void CSteamManager::Send_CreateItem()
{
    API_CHECK
    SteamAPICall_t hSteamAPICall = SteamUGC()->CreateItem(SteamUtils()->GetAppID() , k_EWorkshopFileTypeCommunity);
    m_CreateItemResult.Set(hSteamAPICall, this, &CSteamManager::On_ItemCreate_Result);
}

void CSteamManager::Send_SubmitItemUpdate(const SteamUgc_UpdateDetail_t& detailInfo)
{
    API_CHECK
    UGCUpdateHandle_t handle = SteamUGC()->StartItemUpdate(SteamUtils()->GetAppID(), detailInfo.m_nPublishedFileId);

    SteamUGC()->SetItemTitle(handle, detailInfo.itemTitle.c_str());
    SteamUGC()->SetItemDescription(handle, detailInfo.itemDescription.c_str());
    SteamUGC()->SetItemUpdateLanguage(handle, "English");
    SteamUGC()->SetItemVisibility(handle, detailInfo.visibilty);
    SteamUGC()->SetItemContent(handle, detailInfo.fileFolder.c_str());
    SteamUGC()->SetItemPreview(handle, detailInfo.previewImagePath.c_str());

    SteamAPICall_t submit_item_call = SteamUGC()->SubmitItemUpdate(handle, detailInfo.changeNote.c_str());
    m_SubmitItemUpdateResult.Set(submit_item_call, this, &CSteamManager::On_ItemSubmit_Result);
}

void CSteamManager::On_ItemCreate_Result(CreateItemResult_t *pCallback, bool bIOFailure)
{
    if(pCallback->m_eResult != k_EResultOK || bIOFailure)
    {
        qDebug("mod创建失败");
        emit signal_ItemCreateFail(pCallback->m_eResult);
        return;
    }
    qDebug("请求创建mod成功");
    emit signal_ItemCreateSuccess(pCallback->m_eResult, pCallback->m_nPublishedFileId);
}

void CSteamManager::On_ItemSubmit_Result(SubmitItemUpdateResult_t *pCallback, bool bIOFailure)
{
    if(pCallback->m_eResult != k_EResultOK || bIOFailure)
    {
        qDebug("mod更新失败");
        emit signal_ItemSubmitFail(pCallback->m_eResult);
        return;
    }
    qDebug("请求更新mod成功");
    emit signal_ItemSubmitSuccess(pCallback->m_eResult, pCallback->m_nPublishedFileId);
}
