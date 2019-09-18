#include "Map.h"

namespace DX
{
    ///

    bool    Map::Load(ID3D11Device* pd3dDevice,
        MapDesc& md)
    {
        MapDesc  m_MapDesc = md;
        m_iNumRows = md.iNumRows;
        m_iNumCols = md.iNumCols;
        m_iNumCellRows = m_iNumRows - 1;
        m_iNumCellCols = m_iNumCols - 1;
        m_iNumVertices = m_iNumRows * m_iNumCols;
        m_iNumFace = m_iNumCellRows * m_iNumCellCols * 2;
        m_fCellDistance = md.fCellDistance;

       if(!Create(pd3dDevice,
           m_MapDesc.szShaderFile.c_str(),
           m_MapDesc.szTextureFile.c_str()))
        {
            return false;
        }
        return true;
    }
    bool	Map::Render(ID3D11DeviceContext*	pContext)
    {
        return CADx_Model2::Render(pContext);
    }


    HRESULT Map::CreateVertexData()
    {
        using namespace DX;

        // 0(-1,1)   1(0,1)    2(1,1) 
        // 3(-1,0)   4(0,0)    5(1,0) 
        // 6(-1,-1)  7(0,-1)   8(1,-1) 
        float fHalfCols = (m_iNumCols - 1) / 2.0f;
        float fHalfRows = (m_iNumRows - 1) / 2.0f;
        float ftxOffsetU = 1.0f / (m_iNumCols - 1);
        float ftxOffsetV = 1.0f / (m_iNumRows - 1);

        m_Vertex_List.resize(m_iNumVertices);
        for (int iRow = 0; iRow < m_iNumRows; iRow++)
        {
            for (int iCol = 0; iCol < m_iNumCols; iCol++)
            {
                int iVertexIndex = iRow * m_iNumCols + iCol;
                m_Vertex_List[iVertexIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
                m_Vertex_List[iVertexIndex].p.z = -((iRow - fHalfRows)*m_fCellDistance);
                m_Vertex_List[iVertexIndex].t.x = iCol * ftxOffsetU;
                m_Vertex_List[iVertexIndex].t.y = iRow * ftxOffsetV;

                m_Vertex_List[iVertexIndex].p.y = GetHeightMap(iVertexIndex);
                m_Vertex_List[iVertexIndex].n = GetNormalMap(iVertexIndex);
                m_Vertex_List[iVertexIndex].c = GetColorMap(iVertexIndex);


            }
        }
        return S_OK;
    }
    HRESULT Map::CreateIndexData()
    {
        m_Index_List.resize(m_iNumFace * 3);
        // 0(0)   1(1)    2(1,1) 
        // 3(2)   4(3)    5(1,0) 
        // 6()  7()   8(1,-1) 
        int iIndex = 0;
        for (int iRow = 0; iRow < m_iNumCellRows; iRow++)
        {
            for (int iCol = 0; iCol < m_iNumCellCols; iCol++)
            {
                int iNextRow = iRow + 1;
                int iNextCol = iCol + 1;
                m_Index_List[iIndex + 0] = iRow * m_iNumCols + iCol;
                m_Index_List[iIndex + 1] = iRow * m_iNumCols + iNextCol;
                m_Index_List[iIndex + 2] = iNextRow * m_iNumCols + iCol;

                DWORD i0 = m_Index_List[iIndex + 0];
                DWORD i1 = m_Index_List[iIndex + 1];
                DWORD i2 = m_Index_List[iIndex + 2];

                DirectX::XMVECTOR vNormal = ComputeFaceNormal(i0, i1, i2);

                DirectX::XMVECTOR temp;

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i2].n, temp);

                m_Index_List[iIndex + 3] = m_Index_List[iIndex + 2];
                m_Index_List[iIndex + 4] = m_Index_List[iIndex + 1];
                m_Index_List[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;

                i0 = m_Index_List[iIndex + 3];
                i1 = m_Index_List[iIndex + 4];
                i2 = m_Index_List[iIndex + 5];
                vNormal = ComputeFaceNormal(i0, i1, i2);
     

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List[i2].n, temp);
              
                iIndex += 6;
            }
        }
        GenVertexNormal();
        return S_OK;
    }
    void Map::InitFaceNormals()
    {
        m_FaceNormals.resize(m_iNumFace);
        for (int iFace = 0; iFace < m_iNumFace; iFace++)
        {
            m_FaceNormals[iFace] = DirectX::XMVectorSet(0, 1, 0, 1);
        }
    }

    DirectX::XMVECTOR Map::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
    {
        DirectX::XMVECTOR vNormal;
        DirectX::XMVECTOR v0, v1, v2;
        v0 = DirectX::XMVectorSet(m_Vertex_List[i0].p.x, m_Vertex_List[i0].p.y, m_Vertex_List[i0].p.z, 0);
        v1 = DirectX::XMVectorSet(m_Vertex_List[i1].p.x, m_Vertex_List[i1].p.y, m_Vertex_List[i1].p.z, 0);
        v2 = DirectX::XMVectorSet(m_Vertex_List[i2].p.x, m_Vertex_List[i2].p.y, m_Vertex_List[i2].p.z, 0);

        DirectX::XMVECTOR vEdge0;
        vEdge0 = DirectX::XMVectorSubtract(v1, v0);
     
        DirectX::XMVECTOR vEdge1;
        vEdge1 = DirectX::XMVectorSubtract(v2, v0);

  

        vNormal = DirectX::XMVector3Cross(vEdge0, vEdge1);
        vNormal = DirectX::XMVector3Normalize(vNormal);
        return vNormal;
    }
    void Map::CalcFaceNormals()
    {
        m_FaceNormals.resize(m_iNumFace);
        int iFace = 0;
        for (int iIndex = 0; iIndex < m_iNumFace * 3; iIndex += 3)
        {
            DWORD i0 = m_Index_List[iIndex + 0];
            DWORD i1 = m_Index_List[iIndex + 1];
            DWORD i2 = m_Index_List[iIndex + 2];

            m_FaceNormals[iFace] = ComputeFaceNormal(i0, i1, i2);
            iFace++;
        }
    }
    void Map::CalsVertexNormals()
    {
        /*for (int iVer = 0; iVer < m_iNumVertices; iVer++)
        {
            m_Vertex_List[iVer].n = ;
        }*/
    }
    void Map::GenVertexNormal()
    {
        InitFaceNormals();
        CalcFaceNormals();
        CalsVertexNormals();
    }

    Map::Map()
    {
    }


    Map::~Map()
    {
    }



    bool HeightMap::CreateHeightMap(
        ID3D11Device* pd3dDevice,
        ID3D11DeviceContext*	pContext,
        const TCHAR* pMapFile)
    {
        
        D3DX11_IMAGE_LOAD_INFO imageload;
        ZeroMemory(&imageload, sizeof(imageload));
        imageload.MipLevels = 1;
        imageload.Usage = D3D11_USAGE_STAGING;
        imageload.CpuAccessFlags =
            D3D11_CPU_ACCESS_READ |
            D3D11_CPU_ACCESS_WRITE;
        imageload.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

        ID3D11Resource* pTexture;
        D3DX11CreateTextureFromFile(
            pd3dDevice,
            pMapFile, &imageload, NULL, &pTexture, NULL);

        ID3D11Texture2D* pTex2D = (ID3D11Texture2D*)pTexture;



        D3D11_TEXTURE2D_DESC td;
        pTex2D->GetDesc(&td);

        m_fHeightList.resize(td.Width*td.Height);

        D3D11_MAPPED_SUBRESOURCE mapsub;
        if (SUCCEEDED(pContext->Map(
            pTex2D, D3D11CalcSubresource(0, 0, 1),
            D3D11_MAP_READ, 0, &mapsub)))
        {
            UCHAR* pTexels = (UCHAR*)mapsub.pData;
            for (UINT row = 0; row < td.Height; row++)
            {
                UINT rowStart = row * mapsub.RowPitch;
                for (UINT col = 0; col < td.Width; col++)
                {
                    UINT uRed = pTexels[rowStart + col * 4];
                    m_fHeightList[row*td.Width + col] = uRed;
                }
            }
            pContext->Unmap(pTex2D,
                D3D11CalcSubresource(0, 0, 1));
        }
        m_iNumRows = td.Height;
        m_iNumCols = td.Width;

        pTexture->Release();
        return true;
    }

}