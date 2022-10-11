#ifndef STEAMAPIDATA_H
#define STEAMAPIDATA_H
#include "steam_api.h"
#include <string>
struct SteamUgc_UpdateDetail_t
{
    PublishedFileId_t m_nPublishedFileId;
    std::string itemTitle;
    std::string itemDescription;

    std::string fileFolder;
    std::string previewImagePath;
    std::string changeNote;
    ERemoteStoragePublishedFileVisibility visibilty;
};
#endif // STEAMAPIDATA_H
