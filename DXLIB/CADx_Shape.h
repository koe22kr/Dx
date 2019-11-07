#pragma once
#include "CADx_Model.h"
#include "CADx_Model2.h"
#include "CADx_State.h"
namespace DX
{
    class CADx_Shape :public CADx_Model2
    {
    public:
        virtual HRESULT CreateVertexData() { return S_OK; };
        virtual HRESULT CreateIndexData() { return S_OK; };
        virtual bool Create_Vertex_Index_Const_Data() { return true; };

    public:
        CADx_Shape();
        ~CADx_Shape();
    };

    class CADx_Shape_Line : public CADx_Model2
    {
    public:
        vector<PC_VERTEX>	m_LineVertexList;

        HRESULT				SetInputLayout();
        HRESULT				CreateVertexBuffer();


        bool Draw_Line(ID3D11DeviceContext* pContext, D3DXVECTOR3 vStart, D3DXVECTOR3 vEnd, D3DXVECTOR4 vColor);
        HRESULT CreateVertexData();
        virtual HRESULT CreateVertexData_coord(float x = 0, float y = 0, float z = 0);
        virtual HRESULT CreateIndexData();
        virtual HRESULT CreateIndexData_coord();
        bool Create_Debug_Coordinate(float x = 0, float y = 0, float z = 0);
        virtual bool PostRender(ID3D11DeviceContext* pContext);

    public:
        CADx_Shape_Line();
        ~CADx_Shape_Line();
    };

    class CADx_Shape_Box : public CADx_Model2
    {
    public:
        virtual HRESULT CreateVertexData();
        virtual HRESULT CreateIndexData();
        virtual bool Create_Vertex_Index_Const_Data();
    public:
        CADx_Shape_Box();
        ~CADx_Shape_Box();

    private:

    };
    
    class Sky :public CADx_Shape_Box
    {
    public:
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_pTexSRV[6];
    public:
        bool  PostRender(ID3D11DeviceContext* pContext) override;
        HRESULT LoadTextures(
            ID3D11Device* pd3dDevice);
        //void Sky_Init();
    public:
        Sky();
        ~Sky();

    private:

    };

 
   

}
