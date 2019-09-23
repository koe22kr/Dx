#include "CADx_Map.h"
#include "TCamera.h"
namespace DX
{

    bool CADx_Map::Init(const TCHAR* shaderfile, const TCHAR* texturefile)
    {
        MapDesc md;
        if (m_iNumCols == 0 || m_iNumRows == 0)
        {
            m_iNumCols = 100;
            m_iNumRows = 100;
        }
        md.iNumCols = m_iNumCols;
        md.iNumRows = m_iNumRows;
        md.fCellDistance = 1;
        md.szShaderFile = shaderfile;
        md.szTextureFile = texturefile;
        if (!Load(CADevice::m_pDevice, md))
        {
            return false;
        }
        return true;
    }
    ///

    bool    CADx_Map::Load(ID3D11Device* pd3dDevice,
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

        if (!Create(pd3dDevice,
            m_MapDesc.szShaderFile.c_str(),
            m_MapDesc.szTextureFile.c_str()))
        {
            return false;
        }
        return true;
    }
    bool	CADx_Map::Render(ID3D11DeviceContext*	pContext, D3DXMATRIX* pWorld,
        D3DXMATRIX* pView,
        D3DXMATRIX* pProj)
    {
        SetMatrix(
            pWorld,
            pView,
            pProj);
        return CADx_Model2::Render(pContext);
    }

    HRESULT CADx_Map::SetInputLayout()
    {
        HRESULT hr = S_OK;
        //input layout
        //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0}

        };
        int iNumElement = sizeof(layout) / sizeof(layout[0]);
        m_helper.m_pInputLayout.Attach(
            DX::CreateInputLayout(m_pDevice,
                m_helper.m_pVSBlob->GetBufferSize(),
                m_helper.m_pVSBlob->GetBufferPointer(),
                layout, iNumElement));

        return hr;
    }

    HRESULT CADx_Map::CreateVertexData()
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
                m_Vertex_List[iVertexIndex].c = GetColorMap(iVertexIndex);
            }
        }
        return S_OK;
    }
    HRESULT CADx_Map::CreateVertexBuffer() {
        HRESULT hr = S_OK;
        m_helper.m_iVertexSize = sizeof(PNCT_VERTEX2);
        m_helper.m_iNumVertex = m_Vertex_List.size();;
        m_helper.m_pVertexBuffer.Attach(
            DX::CreateVertexBuffer(m_pDevice,
                &m_Vertex_List.at(0), m_helper.m_iNumVertex, m_helper.m_iVertexSize)
        );
        if (m_helper.m_pVertexBuffer.Get() == nullptr)
            return false;
        return hr;
    }




    HRESULT CADx_Map::CreateIndexData()
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
                //여기까지 index;
                //아래는 노말 구하는부분.
                DWORD i0 = m_Index_List[iIndex + 0];
                DWORD i1 = m_Index_List[iIndex + 1];
                DWORD i2 = m_Index_List[iIndex + 2];

                DirectX::XMVECTOR vNormal = ComputeFaceNormal(i0, i1, i2);
                //


                //
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
                ///

                //아래서도 또 한번 해야함
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


                //
                iIndex += 6;
            }
        }
        GenVertexNormal();
        return S_OK;
    }

    void CADx_Map::InitFaceNormals()
    {
        m_FaceNormals.resize(m_iNumFace);
        for (int iFace = 0; iFace < m_iNumFace; iFace++)
        {
            m_FaceNormals[iFace] = DirectX::XMVectorSet(0, 1, 0, 1);
        }
    }

    DirectX::XMVECTOR CADx_Map::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
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

    void CADx_Map::CalcFaceNormals()
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

    void CADx_Map::CalsVertexNormals()
    {
        /*for (int iVer = 0; iVer < m_iNumVertices; iVer++)
        {
            m_Vertex_List[iVer].n = ;
        }*/
    }
    void CADx_Map::GenVertexNormal()
    {
        InitFaceNormals();
        CalcFaceNormals();
        CalsVertexNormals();
        CalsTangentNormals();
    }
    void CADx_Map::CalsTangentNormals()
    {

    }
    CADx_Map::CADx_Map()
    {
    }


    CADx_Map::~CADx_Map()
    {
    }
    bool CADx_HeightMap::Init(const TCHAR* shaderfile, const TCHAR* texturefile, const TCHAR* heightmapfile)
    {
        CreateHeightMap(CADevice::m_pDevice, CADevice::m_pImmediate_Device_Context, heightmapfile);
        MapDesc md;
        if (m_iNumCols == 0 || m_iNumRows == 0)
        {
            m_iNumCols = 100;
            m_iNumRows = 100;
        }
        md.iNumCols = m_iNumCols;
        md.iNumRows = m_iNumRows;
        md.fCellDistance = 1;
        md.szShaderFile = shaderfile;
        md.szTextureFile = texturefile;

        if (!Load(CADevice::m_pDevice, md))
        {
            return false;
        }
        return true;
    }
    HRESULT CADx_HeightMap::CreateVertexBuffer() {
        HRESULT hr = S_OK;
        m_helper.m_iVertexSize = sizeof(PNCTT_VERTEX);
        m_helper.m_iNumVertex = m_Vertex_List2.size();;
        m_helper.m_pVertexBuffer.Attach(
            DX::CreateVertexBuffer(m_pDevice,
                &m_Vertex_List2.at(0), m_helper.m_iNumVertex, m_helper.m_iVertexSize)
        );
        if (m_helper.m_pVertexBuffer.Get() == nullptr)
            return false;
        return hr;
    }

    bool CADx_HeightMap::CreateHeightMap(
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




    HRESULT CADx_HeightMap::CreateVertexData()
    {
        using namespace DX;

        // 0(-1,1)   1(0,1)    2(1,1) 
        // 3(-1,0)   4(0,0)    5(1,0) 
        // 6(-1,-1)  7(0,-1)   8(1,-1) 
        float fHalfCols = (m_iNumCols - 1) / 2.0f;
        float fHalfRows = (m_iNumRows - 1) / 2.0f;
        float ftxOffsetU = 1.0f / (m_iNumCols - 1);
        float ftxOffsetV = 1.0f / (m_iNumRows - 1);

        m_Vertex_List2.resize(m_iNumVertices);
        for (int iRow = 0; iRow < m_iNumRows; iRow++)
        {
            for (int iCol = 0; iCol < m_iNumCols; iCol++)
            {
                int iVertexIndex = iRow * m_iNumCols + iCol;
                m_Vertex_List2[iVertexIndex].p.x = (iCol - fHalfCols)*m_fCellDistance;
                m_Vertex_List2[iVertexIndex].p.z = -((iRow - fHalfRows)*m_fCellDistance);
                m_Vertex_List2[iVertexIndex].t.x = iCol * ftxOffsetU;
                m_Vertex_List2[iVertexIndex].t.y = iRow * ftxOffsetV;

                m_Vertex_List2[iVertexIndex].p.y = GetHeightMap(iVertexIndex);
                //m_Vertex_List2[iVertexIndex].n = // CreateIndexData 에서 입력
                m_Vertex_List2[iVertexIndex].c = GetColorMap(iVertexIndex);
                //  m_Vertex_List2[iVertexIndex].tangent = Get_Tangent(iVertexIndex);  //CreateIndexData 에서 입력
                  //
            }
        }
        return S_OK;
    }


    DirectX::XMVECTOR CADx_HeightMap::ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2)
    {
        DirectX::XMVECTOR vNormal;
        DirectX::XMVECTOR v0, v1, v2;
        v0 = DirectX::XMVectorSet(m_Vertex_List2[i0].p.x, m_Vertex_List2[i0].p.y, m_Vertex_List2[i0].p.z, 0);
        v1 = DirectX::XMVectorSet(m_Vertex_List2[i1].p.x, m_Vertex_List2[i1].p.y, m_Vertex_List2[i1].p.z, 0);
        v2 = DirectX::XMVectorSet(m_Vertex_List2[i2].p.x, m_Vertex_List2[i2].p.y, m_Vertex_List2[i2].p.z, 0);

        DirectX::XMVECTOR vEdge0;
        vEdge0 = DirectX::XMVectorSubtract(v1, v0);

        DirectX::XMVECTOR vEdge1;
        vEdge1 = DirectX::XMVectorSubtract(v2, v0);


        vNormal = DirectX::XMVector3Cross(vEdge0, vEdge1);
        vNormal = DirectX::XMVector3Normalize(vNormal);
        return vNormal;
    }

    HRESULT CADx_HeightMap::CreateIndexData()
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
                //여기까지 index;
                //아래는 노말 구하는부분.
                DWORD i0 = m_Index_List[iIndex + 0];
                DWORD i1 = m_Index_List[iIndex + 1];
                DWORD i2 = m_Index_List[iIndex + 2];

                DirectX::XMVECTOR vNormal = ComputeFaceNormal(i0, i1, i2);
                //

                //
                DirectX::XMVECTOR temp;

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i2].n, temp);

                m_Index_List[iIndex + 3] = m_Index_List[iIndex + 2];
                m_Index_List[iIndex + 4] = m_Index_List[iIndex + 1];
                m_Index_List[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;
                ///

                //아래서도 또 한번 해야함
                i0 = m_Index_List[iIndex + 3];
                i1 = m_Index_List[iIndex + 4];
                i2 = m_Index_List[iIndex + 5];
                vNormal = ComputeFaceNormal(i0, i1, i2);


                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i2].n, temp);


                //
                iIndex += 6;
            }
        }
        GenVertexNormal();
        return S_OK;
    }




    bool NormalMap::CreateNormalMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext*pContext, const TCHAR* pMapFile)
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

        m_vTangent_List.resize(td.Width*td.Height);

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
                    memcpy(&m_vTangent_List[row*td.Width + col], &uRed, sizeof(UINT));
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
    DirectX::XMFLOAT3 NormalMap::Get_Tangent(DWORD i0, DWORD i1, DWORD i2)
    {
        DirectX::XMVECTOR vNormal;
        DirectX::XMVECTOR v0, v1, v2;
        v0 = DirectX::XMVectorSet(m_Vertex_List2[i0].p.x, m_Vertex_List2[i0].p.y, m_Vertex_List2[i0].p.z, 0);
        v1 = DirectX::XMVectorSet(m_Vertex_List2[i1].p.x, m_Vertex_List2[i1].p.y, m_Vertex_List2[i1].p.z, 0);
        v2 = DirectX::XMVectorSet(m_Vertex_List2[i2].p.x, m_Vertex_List2[i2].p.y, m_Vertex_List2[i2].p.z, 0);

        DirectX::XMVECTOR vEdge0;
        vEdge0 = DirectX::XMVectorSubtract(v1, v0);

        DirectX::XMVECTOR vEdge1;
        vEdge1 = DirectX::XMVectorSubtract(v2, v0);

        //일단 여기에 T백터 구하는 걸 얹기

        float fEdge0u = m_Vertex_List2[i1].t.x - m_Vertex_List2[i0].t.x;
        float fEdge0v = m_Vertex_List2[i1].t.y - m_Vertex_List2[i0].t.y;
        float fEdge1u = m_Vertex_List2[i2].t.x - m_Vertex_List2[i0].t.x;
        float fEdge1v = m_Vertex_List2[i2].t.y - m_Vertex_List2[i0].t.y;
        float fDenominater = fEdge0u * fEdge1v - fEdge0v * fEdge1u;
        float fScale1 = 1.0f / fDenominater;

        DirectX::XMFLOAT3 f3Edge0;
        DirectX::XMStoreFloat3(&f3Edge0, vEdge0);
        DirectX::XMFLOAT3 f3Edge1;
        DirectX::XMStoreFloat3(&f3Edge1, vEdge1);
        DirectX::XMFLOAT3 Tan(fScale1*(fEdge1v*f3Edge0.x - fEdge0v * f3Edge1.x),
            fScale1*(fEdge1v*f3Edge0.y - fEdge0v * f3Edge1.y),
            fScale1*(fEdge1v*f3Edge0.z - fEdge0v * f3Edge1.z));

        DirectX::XMVECTOR temp = DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&Tan));
        DirectX::XMStoreFloat3(&Tan, temp);
        return Tan;
    }

    void NormalMap::CalsTangentNormals()
    {
        m_vTangent_List.resize(m_iNumFace);
        int iFace = 0;
        for (int iIndex = 0; iIndex < m_iNumFace * 3; iIndex += 3)
        {
            DWORD i0 = m_Index_List[iIndex + 0];
            DWORD i1 = m_Index_List[iIndex + 1];
            DWORD i2 = m_Index_List[iIndex + 2];

            m_vTangent_List[iFace] = Get_Tangent(i0, i1, i2);
            iFace++;
        }
    }

    HRESULT NormalMap::CreateIndexData()
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
                //여기까지 index;
                //아래는 노말 구하는부분.
                DWORD i0 = m_Index_List[iIndex + 0];
                DWORD i1 = m_Index_List[iIndex + 1];
                DWORD i2 = m_Index_List[iIndex + 2];

                DirectX::XMVECTOR vNormal = ComputeFaceNormal(i0, i1, i2);
                //
                m_Vertex_List2[i0].tangent = Get_Tangent(i0, i1, i2);
                m_Vertex_List2[i1].tangent = Get_Tangent(i0, i1, i2);
                m_Vertex_List2[i2].tangent = Get_Tangent(i0, i1, i2);

                //
                DirectX::XMVECTOR temp;

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i2].n, temp);

                m_Index_List[iIndex + 3] = m_Index_List[iIndex + 2];
                m_Index_List[iIndex + 4] = m_Index_List[iIndex + 1];
                m_Index_List[iIndex + 5] = iNextRow * m_iNumCols + iNextCol;
                ///
                m_Vertex_List2[i0].tangent = Get_Tangent(i0, i1, i2);
                m_Vertex_List2[i1].tangent = Get_Tangent(i0, i1, i2);
                m_Vertex_List2[i2].tangent = Get_Tangent(i0, i1, i2);
                //아래서도 또 한번 해야함
                i0 = m_Index_List[iIndex + 3];
                i1 = m_Index_List[iIndex + 4];
                i2 = m_Index_List[iIndex + 5];
                vNormal = ComputeFaceNormal(i0, i1, i2);


                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i0].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i0].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i1].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i1].n, temp);

                temp = DirectX::XMLoadFloat3(&m_Vertex_List2[i2].n);
                temp = DirectX::XMVectorAdd(temp, vNormal);
                temp = DirectX::XMVector3Normalize(temp);
                DirectX::XMStoreFloat3(&m_Vertex_List2[i2].n, temp);


                //
                iIndex += 6;
            }
        }
        GenVertexNormal();
        return S_OK;
    }
    HRESULT NormalMap::SetInputLayout() {
        HRESULT hr = S_OK;
        //input layout
        //정점버퍼의 데이터를 정점 쉐이더의 인자값으로 설정
        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TANGENT", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"NORMALMAP",0,DXGI_FORMAT_R32G32B32_FLOAT, 0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0}

        };
        int iNumElement = sizeof(layout) / sizeof(layout[0]);
        m_helper.m_pInputLayout.Attach(
            DX::CreateInputLayout(m_pDevice,
                m_helper.m_pVSBlob->GetBufferSize(),
                m_helper.m_pVSBlob->GetBufferPointer(),
                layout, iNumElement));

        return hr;
    }
    NormalMap::NormalMap()
    {
    }

    NormalMap ::~NormalMap()
    {
    }
}

