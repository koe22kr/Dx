#include "CATexture.h"
#pragma once

class CATexture_Mgr : public CASingleton<CATexture_Mgr>
{
    friend class CASingleton<CATexture_Mgr>;
    typedef std::map<int, CATexture*>::iterator ITOR;
    // 사전식 컨테이너 < 키, 값 >
    std::map<int, CATexture*>   m_List;
    int			m_iNumSound;
public:
    bool		Init();
    bool		Frame();
    bool		Render();
    bool		Release();
    int         Load(ID3D11Device* pDevice, T_STR pFilePath);
    CATexture*	GetPtr(int iKey);
    bool		Delete(int iKey);
    bool		Apply(ID3D11DeviceContext* pContext,
        UINT iKey,
        UINT iSlot);
private:
    CATexture_Mgr();
public:
    ~CATexture_Mgr();
};
#define I_TextureMgr CATexture_Mgr::GetInstance()

