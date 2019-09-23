#include "CATexture_Mgr.h"

bool		CATexture_Mgr::Init()
{
    return true;
}
bool    CATexture_Mgr::Apply(
    ID3D11DeviceContext* pContext,
    UINT iKey,
    UINT iSlot)
{
    GetPtr(iKey)->Apply(pContext, iSlot);
    return true;
}
CATexture*		CATexture_Mgr::GetPtr(int iKey)
{
    ITOR itor = m_List.find(iKey);
    if (itor != m_List.end())
    {
        CATexture* pData = (*itor).second;
        return pData;
    }
    return nullptr;
}
bool		CATexture_Mgr::Delete(int iKey)
{
    ITOR itor = m_List.find(iKey);
    if (itor != m_List.end())
    {
        CATexture* pData = (*itor).second;
        pData->Release();
        delete pData;
        m_List.erase(itor);
        return true;
    }
    return false;
}
bool		CATexture_Mgr::Render()
{
    for (ITOR itor = m_List.begin(); itor != m_List.end(); itor++)
    {
        CATexture* pData = (*itor).second;
        pData->Render();
    }
    return true;
};

int        CATexture_Mgr::Load(
    ID3D11Device* pDevice, T_STR FilePath)
{
    // fullpath split
    if (FilePath.empty()) return -1;

    TCHAR Drive[MAX_PATH] = { 0, };
    TCHAR Dir[MAX_PATH] = { 0, };
    TCHAR Name[MAX_PATH] = { 0, };
    TCHAR Ext[MAX_PATH] = { 0, };
    _tsplitpath_s(FilePath.c_str(),
        Drive, Dir, Name, Ext);

    T_STR filename = Name;
    filename += Ext;

    T_STR path = Drive;
    path += Dir;

    // 중복제거
    for (ITOR itor = m_List.begin();
        itor != m_List.end();
        itor++)
    {
        CATexture* pData = (*itor).second;
        if (pData->m_szName == filename)
        {
            return pData->m_iIndex;
        }
    }
    CATexture* pData = new CATexture;
    if (pData->Load(pDevice, FilePath) == false)
    {
        delete pData;
        return -1;
    }
    pData->m_szName = filename;
    pData->m_szPath = path;
    pData->m_iIndex = m_iNumSound++;
    m_List.insert(make_pair(pData->m_iIndex, pData));
    return pData->m_iIndex;
}


bool		CATexture_Mgr::Frame()
{
    return true;
};

bool		CATexture_Mgr::Release()
{
    //1)
    for (ITOR itor = m_List.begin(); itor != m_List.end();)
    {
        CATexture* pData = (*itor).second;
        pData->Release();
        delete pData;
        itor = m_List.erase(itor);
    }
    m_List.clear();
    return true;
};

CATexture_Mgr::CATexture_Mgr()
{
    m_iNumSound = 0;
}


CATexture_Mgr::~CATexture_Mgr()
{
    Release();
}

