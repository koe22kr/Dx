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

    class Map :public CADx_Shape
    {
    public:
        ///
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
        void	GenVertexNormal();
        void    InitFaceNormals();
        void	CalcFaceNormals();
        void	CalsVertexNormals();
        DirectX::XMVECTOR	ComputeFaceNormal(DWORD i0, DWORD i1, DWORD i2);

        virtual float   GetHeightMap(UINT index)
        {
            return 0.0f;
        };
        virtual  DirectX::XMFLOAT3  GetNormalMap(UINT index)
        {
            return DirectX::XMFLOAT3(0, 0, 0);
        };
        virtual DirectX::XMFLOAT4   GetColorMap(UINT index)
        {
            return DirectX::XMFLOAT4(1, 1, 1, 1);
        };
        virtual HRESULT CreateVertexData();
        virtual HRESULT CreateIndexData();
        virtual bool    Load(ID3D11Device* pd3dDevice, MapDesc& md);
    public:
        bool	Render(ID3D11DeviceContext*	pContext);
    public:
        ///

    public:
        Map();
        virtual ~Map();
    };



    class HeightMap : public Map
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
        bool CreateHeightMap(
            ID3D11Device* pd3dDevice,
            ID3D11DeviceContext*	pContext,
            const TCHAR* pMapFile);
    public:
        HeightMap() {};
        virtual ~HeightMap() {};
    };


}