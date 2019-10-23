#pragma once
#pragma once
#include "CACore.h"
#include "Load_Shape.h"
class Sample : public CACore
{
public:
    D3DXMATRIX m_tworld;

    Load_Shape m_loader;
    //HRESULT CreateVertexData();
    bool Init();
    bool Frame();
    bool Render();
    bool Release();
    //std::map<UINT,wstring> m_filename_map;
  //  std::vector<DX::PNCT_VERTEX2> m_pnct_List;
    //std::vector<DWORD> m_index_List;
    Sample();
    virtual ~Sample();

};

WINRUN_DEFAULT

