#include "CATexture.h"

bool    CATexture::Apply(
    ID3D11DeviceContext* pContext,
    UINT iSlot)
{
    pContext->PSSetShaderResources(iSlot, 1, &m_pSRV);
    return true;
}


CATexture::CATexture()
{
    Draw_Flag = true;
    m_Index_Draw_Flag = true;
    m_Draw_Count = 0;
    m_Start_Vertex_Location = 0;
    m_Start_Index_Location = 0;
}


CATexture::~CATexture()
{
    if (m_pSRV)
    {
        m_pSRV->Release();
        m_pSRV = nullptr;
    }
}

void CATexture::Set_Draw_OPT(int draw_count, int vertex_location, int index_location)
{
    m_Draw_Count = draw_count;
    m_Start_Vertex_Location = vertex_location;
    m_Start_Index_Location = index_location;
}

bool CATexture::Draw(ID3D11DeviceContext* pContext)
{
        if (m_Index_Draw_Flag)
        {
            pContext->DrawIndexed(m_Draw_Count, m_Start_Vertex_Location, m_Start_Index_Location);
        }
        else
        {
            pContext->Draw(m_Draw_Count, m_Start_Vertex_Location);
        }
#ifdef _DEBUG
        if (m_Draw_Count == 0)
        {
            OutputDebugString(L"m_Draw_Count ==0; No_Draw_Device");
        }
#endif


    return true;
}

bool CATexture::Load(ID3D11Device* pDevice,
    std::wstring filename)
{
    HRESULT hr;
    if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(
        pDevice,
        filename.c_str(),
        NULL,
        NULL,
        &m_pSRV,
        NULL)))
    {
        return false;
    }
    return true;
}