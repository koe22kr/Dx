#pragma once

#include "CADx_Shape.h"

#pragma once
namespace DX
{

    struct MapDesc
    {
        int iNumCols;
        int iNumRows;
        float fCellDistance;
        T_STR szTextureFile;
        T_STR szShaderFile;
    };

    class CADx_Map :public CADx_Shape
    {
    public:
        ///
        virtual bool Init(const TCHAR* shaderfile, const TCHAR* texturefile);
        vector<DirectX::XMFLOAT3> m_vTangent_List;
        //vector<float> m_fColor_List;
        int m_iNumRows;
        int m_iNumCols;
        int m_iNumCellRows;
        int m_iNumCellCols;
        int m_iNumVertices;
        int m_iNumFace;
        float m_fCellDistance;
    public:
        vector<DirectX::XMVECTOR>   m_FaceNormals;
    public:
        virtual  void	GenVertexNormal();
        virtual  void    InitFaceNormals();
        virtual  void	CalcFaceNormals();
        virtual  void	CalsVertexNormals();
        virtual  void CalsTangentNormals();
        virtual DirectX::XMVECTOR	ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);

        virtual float   GetHeightMap(UINT index)
        {
            return 0.0f;
        };
        virtual  DirectX::XMFLOAT3  GetNormalMap(UINT index)
        {
            if (m_vTangent_List.size() != 0)
            {
                return m_vTangent_List[index];
            }
            return DirectX::XMFLOAT3(0, 0, 0);
        }


        virtual DirectX::XMFLOAT4   GetColorMap(UINT index)
        {
            return DirectX::XMFLOAT4(1, 1, 1, 1);
        };
        virtual HRESULT CreateVertexData();
        virtual HRESULT CreateIndexData();
        virtual bool    Load(ID3D11Device* pd3dDevice, MapDesc& md);
        virtual HRESULT SetInputLayout() override;
        virtual HRESULT CreateVertexBuffer() override;
    public:
        bool	Render(ID3D11DeviceContext*	pContext, D3DXMATRIX* pWorld,
            D3DXMATRIX* pView,
            D3DXMATRIX* pProj);
    public:
        ///

    public:
        CADx_Map();
        virtual ~CADx_Map();
    };



    class CADx_HeightMap : public CADx_Map
    {
    public:
        vector<float>  m_fHeightList;
    public:
        virtual float   GetHeightMap(UINT index)
        {
            return m_fHeightList[index] / 5.0f;
        };
        /*virtual  Vector3  GetNormalMap(UINT index)
        {
            return Vector3(0,1,0);
        };
        virtual Vector4   GetColorMap(UINT index)
        {
            return Vector4(1, 1, 1,1);
        };*/
        virtual bool Init(const TCHAR* shaderfile, const TCHAR* texturefile, const TCHAR* heightmapfile);

        virtual HRESULT CreateVertexData();
        virtual HRESULT CreateVertexBuffer();
        virtual HRESULT CreateIndexData();
        virtual DirectX::XMVECTOR ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);
        virtual void CalsTangentNormals() {};


        virtual bool CreateHeightMap(
            ID3D11Device* pd3dDevice,
            ID3D11DeviceContext*	pContext,
            const TCHAR* pMapFile);
    public:
        CADx_HeightMap() {};
        virtual ~CADx_HeightMap() {};
    };

    class NormalMap : public CADx_Map
    {
    public:
        HRESULT CreateIndexData();
        HRESULT SetInputLayout();

        virtual  bool CreateNormalMap(ID3D11Device* pd3dDevice, ID3D11DeviceContext* pContext, const TCHAR* pMapFile);
        virtual DirectX::XMFLOAT3 Get_Tangent(DWORD i0, DWORD i1, DWORD i2);
        virtual void CalsTangentNormals();

        NormalMap();
        ~NormalMap();

    private:

    };

}

