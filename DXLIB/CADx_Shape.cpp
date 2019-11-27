#include "CADx_Shape.h"
namespace DX
{
    using namespace DirectX;
    CADx_Shape::CADx_Shape()
    {
    }


    CADx_Shape::~CADx_Shape()
    {
    }
    HRESULT  CADx_Shape_Line::CreateVertexData_coord(float x, float y, float z)
    {
        m_Vertex_List.resize(6);
        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].c = { 1.0f,0.0f,0.0f,1.0f };
        m_Vertex_List[0].p = { 1000.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].c = { 1.0f,0.0f,0.0f,1.0f };

        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].c = { 0.0f,1.0f,0.0f,1.0f };
        m_Vertex_List[0].p = { 0.0f + x,1000.0f + y,0.0f + z };
        m_Vertex_List[0].c = { 0.0f,1.0f,0.0f,1.0f };

        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].c = { 0.0f,0.0f,1.0f,1.0f };
        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,1000.0f + z };
        m_Vertex_List[0].c = { 0.0f,0.0f,1.0f,1.0f };
        return S_OK;
    }

    HRESULT CADx_Shape_Line::CreateVertexData()
    {
        m_LineVertexList.resize(2);
        m_LineVertexList[0].p = XMFLOAT3(0.0f, 0.0f, 0.0f);
        m_LineVertexList[0].c = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
        m_LineVertexList[1].p = XMFLOAT3(1.0f, 0.0f, 0.0f);
        m_LineVertexList[1].c = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);

        m_helper.m_iVertexSize = sizeof(PC_VERTEX);
        m_helper.m_iNumVertex = (UINT)m_LineVertexList.size();
        return true;
    }

    bool CADx_Shape_Line::Draw_Line(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor)
    {
        PC_VERTEX vertices[2];
        vertices[0].p = *(XMFLOAT3 *)&vStart;
        vertices[0].c = *(XMFLOAT4 *)&vColor;
        vertices[1].p = *(XMFLOAT3 *)& vEnd;
        vertices[1].c = *(XMFLOAT4 *)& vColor;
        // µ¿Àû ¸®¼Ò½º °»½Å ¹æ¹ý 1 : D3D11_USAGE_DEFAULT »ç¿ë
        pContext->UpdateSubresource(m_helper.m_pVertexBuffer.Get(), 0, NULL, &vertices, 0, 0);
        return Render(pContext);
    }


    HRESULT				CADx_Shape_Line::SetInputLayout()
    {
        HRESULT hr = S_OK;
      //  ID3D10Blob* pEM = nullptr;

        D3D11_INPUT_ELEMENT_DESC layout[] =
        {
            { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
            { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        };
        UINT numElements = sizeof(layout) / sizeof(layout[0]);
        m_helper.m_pInputLayout.Attach(CreateInputLayout(CADevice::m_pDevice, m_helper.m_pVSBlob->GetBufferSize(),
            m_helper.m_pVSBlob->GetBufferPointer(), layout, numElements));

    //    if (pEM)pEM->Release();
        return hr;
    }
    HRESULT				CADx_Shape_Line::CreateVertexBuffer()
    {
        if (m_helper.m_iNumVertex <= 0) return S_OK;
        m_helper.m_pVertexBuffer.Attach(DX::CreateVertexBuffer(CADevice::m_pDevice,
            &m_LineVertexList.at(0),
            m_helper.m_iNumVertex,
            m_helper.m_iVertexSize));
        return S_OK;
    }
    
    HRESULT CADx_Shape_Line::CreateIndexData()
    {
        m_Index_List.resize(2);
        m_Index_List[0] = 0;
        m_Index_List[1] = 1;

        m_helper.m_iNumIndex = (UINT)m_Index_List.size();
        return true;
    }
    HRESULT CADx_Shape_Line::CreateIndexData_coord()
    {
        m_Index_List.resize(6);
        m_Index_List = { 0,1,2,3,4,5 };
        return S_OK;
    }
    bool CADx_Shape_Line::Create_Debug_Coordinate(float x, float y, float z)
    {
        m_Vertex_List.resize(6);
        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 1.0f,0.0f,0.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };
        m_Vertex_List[0].p = { 1000.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 1.0f,0.0f,0.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };

        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 0.0f,1.0f,0.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };
        m_Vertex_List[0].p = { 0.0f + x,1000.0f + y,0.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 0.0f,1.0f,0.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };

        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,0.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 0.0f,0.0f,1.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };
        m_Vertex_List[0].p = { 0.0f + x,0.0f + y,1000.0f + z };
        m_Vertex_List[0].n = { 0.0f,0.0f,0.0f };
        m_Vertex_List[0].c = { 0.0f,0.0f,1.0f,1.0f };
        m_Vertex_List[0].t = { 0.0f,0.0f };

        m_Index_List.resize(6);
        m_Index_List = { 0,1,2,3,4,5 };

        //m_HDX.Create_Vertex_And_Index_Buffer_Self(&m_Vertex_List, &m_Index_List);
        return true;
    }
    bool CADx_Shape_Line::PostRender(ID3D11DeviceContext* pContext)
    {
        pContext->IASetPrimitiveTopology(
            D3D10_PRIMITIVE_TOPOLOGY_LINELIST);

        m_helper.PostRender(pContext,
            m_helper.m_iNumIndex);

      /*  pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        m_HDX.Render(pContext);*/

        return true;
    }
    CADx_Shape_Line::CADx_Shape_Line()
    {

    }
    CADx_Shape_Line::~CADx_Shape_Line()
    {

    }
    HRESULT CADx_Shape_Box::CreateVertexData()
    {
        m_Vertex_List.resize(24);

        m_Vertex_List[0] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[1] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[2] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[3] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));
        // µÞ¸é
        m_Vertex_List[4] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[5] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[6] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[7] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿À¸¥ÂÊ
        m_Vertex_List[8] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[9] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[10] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[11] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿ÞÂÊ
        m_Vertex_List[12] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[13] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[14] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[15] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // À­¸é
        m_Vertex_List[16] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[17] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[18] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[19] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¾Æ·§¸é
        m_Vertex_List[20] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[21] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[22] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[23] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));


        return S_OK;
    }
    HRESULT CADx_Shape_Box::CreateIndexData()
    {

        m_Index_List.resize(36);
        int iIndex = 0;
        m_Index_List[iIndex++] = 0; 	m_Index_List[iIndex++] = 1; 	 m_Index_List[iIndex++] = 2;
        m_Index_List[iIndex++] = 0; 	m_Index_List[iIndex++] = 2; 	 m_Index_List[iIndex++] = 3;
        m_Index_List[iIndex++] = 4; 	m_Index_List[iIndex++] = 5; 	 m_Index_List[iIndex++] = 6;
        m_Index_List[iIndex++] = 4; 	m_Index_List[iIndex++] = 6; 	 m_Index_List[iIndex++] = 7;
        m_Index_List[iIndex++] = 8; 	m_Index_List[iIndex++] = 9; 	 m_Index_List[iIndex++] = 10;
        m_Index_List[iIndex++] = 8;	    m_Index_List[iIndex++] = 10;     m_Index_List[iIndex++] = 11;
        m_Index_List[iIndex++] = 12;    m_Index_List[iIndex++] = 13;     m_Index_List[iIndex++] = 14;
        m_Index_List[iIndex++] = 12;	m_Index_List[iIndex++] = 14;     m_Index_List[iIndex++] = 15;
        m_Index_List[iIndex++] = 16;    m_Index_List[iIndex++] = 17;     m_Index_List[iIndex++] = 18;
        m_Index_List[iIndex++] = 16;	m_Index_List[iIndex++] = 18;     m_Index_List[iIndex++] = 19;
        m_Index_List[iIndex++] = 20;    m_Index_List[iIndex++] = 21;     m_Index_List[iIndex++] = 22;
        m_Index_List[iIndex++] = 20;	m_Index_List[iIndex++] = 22;     m_Index_List[iIndex++] = 23;
        return S_OK;
    }
    bool CADx_Shape_Box::Create_Vertex_Index_Const_Data()
    {
        // »ó´Ü
    // 5    6
    // 1    2
    // ÇÏ´Ü
    // 4    7
    // 0    3  
    // ¾Õ¸é
        m_Vertex_List.resize(24);
        
        m_Vertex_List[0] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[1] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[2] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[3] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));
        // µÞ¸é
        m_Vertex_List[4] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[5] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[6] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[7] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿À¸¥ÂÊ
        m_Vertex_List[8] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[9] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[10] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[11] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿ÞÂÊ
        m_Vertex_List[12] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[13] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[14] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[15] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // À­¸é
        m_Vertex_List[16] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[17] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[18] = PNCT_VERTEX2(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[19] = PNCT_VERTEX2(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¾Æ·§¸é
        m_Vertex_List[20] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[21] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[22] = PNCT_VERTEX2(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[23] = PNCT_VERTEX2(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));



        m_Index_List.resize(36);
        int iIndex = 0;
        m_Index_List[iIndex++] = 0; 	m_Index_List[iIndex++] = 1; 	 m_Index_List[iIndex++] = 2; 
        m_Index_List[iIndex++] = 0; 	m_Index_List[iIndex++] = 2; 	 m_Index_List[iIndex++] = 3;
        m_Index_List[iIndex++] = 4; 	m_Index_List[iIndex++] = 5; 	 m_Index_List[iIndex++] = 6; 
        m_Index_List[iIndex++] = 4; 	m_Index_List[iIndex++] = 6; 	 m_Index_List[iIndex++] = 7;
        m_Index_List[iIndex++] = 8; 	m_Index_List[iIndex++] = 9; 	 m_Index_List[iIndex++] = 10;
        m_Index_List[iIndex++] = 8;	    m_Index_List[iIndex++] = 10;     m_Index_List[iIndex++] = 11;
        m_Index_List[iIndex++] = 12;    m_Index_List[iIndex++] = 13;     m_Index_List[iIndex++] = 14; 
        m_Index_List[iIndex++] = 12;	m_Index_List[iIndex++] = 14;     m_Index_List[iIndex++] = 15;
        m_Index_List[iIndex++] = 16;    m_Index_List[iIndex++] = 17;     m_Index_List[iIndex++] = 18; 
        m_Index_List[iIndex++] = 16;	m_Index_List[iIndex++] = 18;     m_Index_List[iIndex++] = 19;
        m_Index_List[iIndex++] = 20;    m_Index_List[iIndex++] = 21;     m_Index_List[iIndex++] = 22; 
        m_Index_List[iIndex++] = 20;	m_Index_List[iIndex++] = 22;     m_Index_List[iIndex++] = 23;
        return true;

    }


    CADx_Shape_Box::CADx_Shape_Box()
    {
    }

    CADx_Shape_Box::~CADx_Shape_Box()
    {
    }


    HRESULT Sky::LoadTextures(
        ID3D11Device* pd3dDevice)
    {
        HRESULT hr = S_OK;
        const TCHAR* g_szSkyTextures[] =
        {
            L"../../_data/sky/C_F.png",
            L"../../_data/sky/C_B.png",
            L"../../_data/sky/C_R.bmp",
            L"../../_data/sky/C_L.bmp",
            L"../../_data/sky/C_U.bmp",
            L"../../_data/sky/C_D.bmp"
        };
        for (int iSub = 0; iSub < 6; iSub++)
        {
            int iIndex = I_TextureMgr.Load(pd3dDevice, g_szSkyTextures[iSub]);
            if (iIndex >= 0)
            {
                //m_pTexSRV[iSub].Swap(I_TextureMgr.GetPtr(iIndex)->m_pSRV.Get());
                m_pTexSRV[iSub] = I_TextureMgr.GetPtr(iIndex)->m_pSRV;
            }
        }
        return hr;
    }
    bool  Sky::PostRender(ID3D11DeviceContext* pContext)
    {
        //DX::Set_SState(pContext, DX::CADx_State::m_pSSWrap_Point);
        
        pContext->PSSetShaderResources(2, 6, m_pTexSRV[0].GetAddressOf());
        pContext->DrawIndexed(36, 0, 0);
        //DX::Set_SState(pContext, DX::CADx_State::m_pSSWrap_Linear);
        return true;
    }


    //void Sky::Sky_Init(ID3D11Device* pdevice)
    //{
    //    Create(pdevice,L"Sky",L"")

    //}
    Sky::Sky()
    {
    }

    Sky::~Sky()
    {
    }
}

