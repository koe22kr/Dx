#pragma once
#include "CADx_Shape.h"
#include "CACore.h"
#include "Camera.h"
#include "Map.h"
#include "CADx_Model2.h"
#include "CATexture.h"

using namespace DX;

    class Sample : public CACore
    {
    public:
        //2
        Sky m_Sky;
        DirectX::XMFLOAT3		m_vPos;
        //xModelCamera		m_backview;
        //CADx_Shape		m_Obj;
        CADx_Shape_Box			m_Box;
        HeightMap			 m_Map;
        vector<UINT>     m_Tex;
        DirectX::XMMATRIX       m_matBoxWorld;
        DirectX::XMMATRIX       m_matPlaneWorld;
    public:
        CATexture* tex;
        bool CreateResource();
        bool DeleteResource();
       // LRESULT MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
        void Msg_Proc(MSG msg) override;
        //2
        CADx_Shape_Box box;
        Camera Cam;
        Map map;
        bool Init();
        bool Frame();
        bool Render();
        bool Release();
        Sample();
        ~Sample();

    };

    WINRUN_DEFAULT
