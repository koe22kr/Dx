#include "CAShape.h"
namespace DX
{
    using namespace DirectX;
    CAShape::CAShape()
    {
    }


    CAShape::~CAShape()
    {
    }

    bool CAShape_Line::Create_Debug_Coordinate(float x, float y, float z)
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

        m_HDX.Create_Vertex_And_Index_Buffer_Self(&m_Vertex_List, &m_Index_List);
        return true;
    }
    bool CAShape_Line::PostRender(ID3D11DeviceContext* pContext)
    {
        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        m_HDX.PostRender(pContext);

        return true;
    }
    CAShape_Line::CAShape_Line()
    {

    }
    CAShape_Line::~CAShape_Line()
    {

    }

    bool CAShape_Box::Create_Vertex_Index_Const_Data()
    {
        // »ó´Ü
    // 5    6
    // 1    2
    // ÇÏ´Ü
    // 4    7
    // 0    3  
    // ¾Õ¸é
        m_Vertex_List.resize(24);
        
        m_Vertex_List[0] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[1] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[2] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[3] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, 0.0f, -1.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));
        // µÞ¸é
        m_Vertex_List[4] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[5] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[6] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[7] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿À¸¥ÂÊ
        m_Vertex_List[8] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[9] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[10] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[11] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¿ÞÂÊ
        m_Vertex_List[12] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[13] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[14] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[15] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // À­¸é
        m_Vertex_List[16] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[17] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[18] = PNCT_VERTEX(XMFLOAT3(1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[19] = PNCT_VERTEX(XMFLOAT3(-1.0f, 1.0f, -1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT4(1.0f, 0.5f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));

        // ¾Æ·§¸é
        m_Vertex_List[20] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f));
        m_Vertex_List[21] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, -1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f));
        m_Vertex_List[22] = PNCT_VERTEX(XMFLOAT3(1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f));
        m_Vertex_List[23] = PNCT_VERTEX(XMFLOAT3(-1.0f, -1.0f, 1.0f), XMFLOAT3(0.0f, -1.0f, 0.0f), XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f));



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


    CAShape_Box::CAShape_Box()
    {
    }

    CAShape_Box::~CAShape_Box()
    {
    }
}

