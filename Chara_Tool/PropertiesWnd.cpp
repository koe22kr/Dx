
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "Chara_Tool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
///////////////////////

//enum Group
//{
//    AlphaBlend,
//
//};
enum MY_Blend_Prop_ID
{
    ID_BLEND_BLEND_ENABLE = 100,
    ID_BLEND_SRC_BLEND,
    ID_BLEND_DEST_BLEND,
    ID_BLEND_BLEND_OP,
    ID_BLEND_SRC_BLEND_ALPHA,
    ID_BLEND_DEST_BLEND_ALPHA,
    ID_BLEND_BLEND_OP_ALPHA,
    ID_BLEND_RT_WRITE_MASK,

};
enum MY_Sampler_Prop_ID
{
    ID_SAMPLER_FILTER = 200,
    ID_SAMPLER_ADDRESS_U,
    ID_SAMPLER_ADDRESS_V,
    ID_SAMPLER_ADDRESS_W,

};
enum MY_Rasterizer_Prop_ID
{
    ID_RASTERIZER_FILL_MODE = 300,
    ID_RASTERIZER_CULL_MODE,
};
enum MY_Depth_Stencil_Prop_ID
{
    ID_DEPTH_STENCIL_DEPTH_ENABLE = 400,
    ID_DEPTH_STENCIL_DEPTH_WRITE_MASK,
    ID_DEPTH_STENCIL_DEPTH_FUNC,
    
};

const int MY_D3D11_BLEND_NUM[] =
{
    1,2,3,4,5,6,7,8,9,10,11,14,15,16,17,18,19
};

const TCHAR* MY_D3D11_BLEND_STRING[] =
{
    _T("D3D11_BLEND_ZERO"),
    _T("D3D11_BLEND_ONE"),
    _T("D3D11_BLEND_SRC_COLOR"),
    _T("D3D11_BLEND_INV_SRC_COLOR"),
    _T("D3D11_BLEND_SRC_ALPHA"),
    _T("D3D11_BLEND_INV_SRC_ALPHA"),
    _T("D3D11_BLEND_DEST_ALPHA"),
    _T("D3D11_BLEND_INV_DEST_ALPHA"),
    _T("D3D11_BLEND_DEST_COLOR"),
    _T("D3D11_BLEND_INV_DEST_COLOR"),
    _T("D3D11_BLEND_SRC_ALPHA_SAT"),
    _T("D3D11_BLEND_BLEND_FACTOR"),
    _T("D3D11_BLEND_INV_BLEND_FACTOR"),
    _T("D3D11_BLEND_SRC1_COLOR"),
    _T("D3D11_BLEND_INV_SRC1_COLOR"),
    _T("D3D11_BLEND_SRC1_ALPHA"),
    _T("D3D11_BLEND_INV_SRC1_ALPHA"),
};

const int MY_D3D11_BLEND_OP_NUM[] =
{
    1,2,3,4,5
};
const TCHAR* MY_D3D11_BLEND_OP_STRING[] =
{
     _T("D3D11_BLEND_OP_ADD"),
     _T("D3D11_BLEND_OP_SUBTRACT"),
     _T("D3D11_BLEND_OP_REV_SUBTRACT"),
     _T("D3D11_BLEND_OP_MIN"),
     _T("D3D11_BLEND_OP_MAX")
};

const UINT8 MY_D3D11_COLOR_WRITE_ENABLE_NUM[] =
{
    1,
    2,
    4,
    8,
    15,
};

const TCHAR* MY_D3D11_COLOR_WRITE_ENABLE_STRING[] = 
{
    _T("D3D11_COLOR_WRITE_ENABLE_RED"),
    _T("D3D11_COLOR_WRITE_ENABLE_GREEN"),
    _T("D3D11_COLOR_WRITE_ENABLE_BLUE"),
    _T("D3D11_COLOR_WRITE_ENABLE_ALPHA"),
    _T("D3D11_COLOR_WRITE_ENABLE_ALL"),
};


const int MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[] =
{
    1,
    2,
    3,
    4,
    5
};

const TCHAR* MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[] =
{
    _T("D3D11_TEXTURE_ADDRESS_WRAP"),
    _T("D3D11_TEXTURE_ADDRESS_MIRROR"),
    _T("D3D11_TEXTURE_ADDRESS_CLAMP"),
    _T("D3D11_TEXTURE_ADDRESS_BORDER"),
    _T("D3D11_TEXTURE_ADDRESS_MIRROR_ONCE"),
};

const int MY_D3D11_SAMPLER_FILTER_NUM[] =
{
     0,    0x1,    0x4,    0x5,    0x10,    0x11,    0x14,    0x15,    0x55,    0x80,//10
    0x81,    0x84,    0x85,    0x90,    0x91,    0x94,    0x95,    0xd5,  //8
    /*0x100,    0x101,    0x104,    0x105,    0x110,    0x111,    0x114,    0x115,    0x155,    0x180,    0x181,
    0x184,    0x185,    0x190,    0x191,    0x194,    0x195,    0x1d5*/
};

const TCHAR* MY_D3D11_SAMPLER_FILTER_STRING[] =
{
    _T("D3D11_FILTER_MIN_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MIN_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_ANISOTROPIC"),
    _T("D3D11_FILTER_COMPARISON_MIN_MAG_MIP_POINT"),//10
    _T("D3D11_FILTER_COMPARISON_MIN_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_COMPARISON_MIN_POINT_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_COMPARISON_MIN_POINT_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_MIP_POINT"),
    _T("D3D11_FILTER_COMPARISON_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_COMPARISON_MIN_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_COMPARISON_MIN_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_COMPARISON_ANISOTROPIC"),//18
   /* _T("D3D11_FILTER_MINIMUM_MIN_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MINIMUM_MIN_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MINIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MINIMUM_MIN_POINT_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MINIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MINIMUM_MIN_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MINIMUM_MIN_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_MINIMUM_ANISOTROPIC"),
    _T("D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MAXIMUM_MIN_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MAXIMUM_MIN_POINT_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_MIP_POINT"),
    _T("D3D11_FILTER_MAXIMUM_MIN_LINEAR_MAG_POINT_MIP_LINEAR"),
    _T("D3D11_FILTER_MAXIMUM_MIN_MAG_LINEAR_MIP_POINT"),
    _T("D3D11_FILTER_MAXIMUM_MIN_MAG_MIP_LINEAR"),
    _T("D3D11_FILTER_MAXIMUM_ANISOTROPIC"),*/
};

const int MY_D3D11_RASTERIZER_FILL_MODE_NUM[] =
{
    2,
    3
};
const TCHAR* MY_D3D11_RASTERIZER_FILL_MODE_STRING[] =
{
    _T("D3D11_FILL_WIREFRAME"),
    _T("D3D11_FILL_SOLID"),
};

const int MY_D3D11_RASTERIZER_CULL_MODE_NUM[] =
{
    1,
    2,
    3
};
const TCHAR* MY_D3D11_RASTERIZER_CULL_MODE_STRING[] =
{
    _T("D3D11_CULL_NONE"),
    _T("D3D11_CULL_FRONT"),
    _T("D3D11_CULL_BACK"),
};

const int MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[] =
{
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8
};
const TCHAR* MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[] =
{
    _T("D3D11_COMPARISON_NEVER"),
    _T("D3D11_COMPARISON_LESS"),
    _T("D3D11_COMPARISON_EQUAL"),
    _T("D3D11_COMPARISON_LESS_EQUAL"),
    _T("D3D11_COMPARISON_GREATER"),
    _T("D3D11_COMPARISON_NOT_EQUAL"),
    _T("D3D11_COMPARISON_GREATER_EQUAL"),
    _T("D3D11_COMPARISON_ALWAYS"),
};

const int MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[] =
{
    0,
    1
};
const TCHAR* MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[] =
{
    _T("D3D11_DEPTH_WRITE_MASK_ZERO"),
    _T("D3D11_DEPTH_WRITE_MASK_ALL"),
};


/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd() noexcept
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()


    ON_REGISTERED_MESSAGE(AFX_WM_PROPERTY_CHANGED,OnPropertyChanged)
END_MESSAGE_MAP()

//void CPropertiesWnd::Custom_Update_Property(CMFCPropertyGridProperty* target)
//{
//    //인덱스 미사용중
//    switch ((int)target->GetData())
//    {
//        case ID_BLEND_BLEND_ENABLE:
//        {
//            bool bEnable = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[0];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendEnable = bEnable;
//
//            target->SetValue((_variant_t)bEnable);
//
//           // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//        }break;
//        case ID_BLEND_SRC_BLEND:
//        {
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[1];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//        }break;
//        case ID_BLEND_DEST_BLEND:
//        {
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[2];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//
//        }break;
//        case ID_BLEND_BLEND_OP:
//        {
//
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[3];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_OP_NUM) / sizeof(MY_D3D11_BLEND_OP_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_OP_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_OP_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//        }break;
//        case   ID_BLEND_SRC_BLEND_ALPHA:
//        {
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[4];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//
//        }break;
//        case   ID_BLEND_DEST_BLEND_ALPHA:
//        {
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[5];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//        }break;
//        case   ID_BLEND_BLEND_OP_ALPHA:
//        {
//            int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[6];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_BLEND_OP_NUM) / sizeof(MY_D3D11_BLEND_OP_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_BLEND_OP_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_BLEND_OP_STRING[i]);
//
//                   // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//
//        }break;
//        case   ID_BLEND_RT_WRITE_MASK:
//        {
//            UINT8 iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[7];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = (D3D11_COLOR_WRITE_ENABLE)iSelBlend;
//
//            int iNumBlend = sizeof(MY_D3D11_COLOR_WRITE_ENABLE_NUM) / sizeof(MY_D3D11_COLOR_WRITE_ENABLE_NUM[0]);
//            for (int i = 0; i < iNumBlend; i++)
//            {
//                if (iSelBlend == MY_D3D11_COLOR_WRITE_ENABLE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_COLOR_WRITE_ENABLE_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
//                    break;
//                }
//            }
//
//        }break;
//        //Sampler//
//        case ID_SAMPLER_FILTER:
//        {
//            int iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[0];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.Filter = (D3D11_FILTER)iSelSampler;
//
//            int iNumSampler = sizeof(MY_D3D11_SAMPLER_FILTER_NUM) / sizeof(MY_D3D11_SAMPLER_FILTER_NUM[0]);
//            for (int i = 0; i < iNumSampler; i++)
//            {
//                if (iSelSampler == MY_D3D11_SAMPLER_FILTER_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_SAMPLER_FILTER_STRING[i]);
//
//                    //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
//                    break;
//                }
//            }
//
//        }break;
//        case ID_SAMPLER_ADDRESS_U:
//        {
//            int iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[1];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
//
//            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
//            for (int i = 0; i < iNumSampler; i++)
//            {
//                if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
//
//                   // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
//                    break;
//                }
//
//            }
//        }break;
//        case ID_SAMPLER_ADDRESS_V:
//        {
//            int iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[2];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
//
//            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
//            for (int i = 0; i < iNumSampler; i++)
//            {
//                if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
//
//                   // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
//                    break;
//                }
//
//            }
//
//
//        }break;
//        case ID_SAMPLER_ADDRESS_W:
//        {
//            int iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[3];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
//
//            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
//            for (int i = 0; i < iNumSampler; i++)
//            {
//                if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
//
//                  //  TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
//                    break;
//                }
//
//            }
//        }break;
//        //
//            //Rasterizer//
//        case ID_RASTERIZER_FILL_MODE:
//        {
//
//            int iSelRaster = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[0];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.FillMode = (D3D11_FILL_MODE)iSelRaster;
//
//            int iNumRaster = sizeof(MY_D3D11_RASTERIZER_FILL_MODE_NUM) / sizeof(MY_D3D11_RASTERIZER_FILL_MODE_NUM[0]);
//            for (int i = 0; i < iNumRaster; i++)
//            {
//                if (iSelRaster == MY_D3D11_RASTERIZER_FILL_MODE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_RASTERIZER_FILL_MODE_STRING[i]);
//
//                  //  TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
//                    break;
//                }
//
//            }
//        }break;
//        case ID_RASTERIZER_CULL_MODE:
//        {
//            int iSelRaster = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[1];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.CullMode = (D3D11_CULL_MODE)iSelRaster;
//
//            int iNumRaster = sizeof(MY_D3D11_RASTERIZER_CULL_MODE_NUM) / sizeof(MY_D3D11_RASTERIZER_CULL_MODE_NUM[0]);
//            for (int i = 0; i < iNumRaster; i++)
//            {
//                if (iSelRaster == MY_D3D11_RASTERIZER_CULL_MODE_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_RASTERIZER_CULL_MODE_STRING[i]);
//
//                 //   TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
//                    break;
//                }
//            }
//        }break;
//        //DepthStencil//
//        case ID_DEPTH_STENCIL_DEPTH_ENABLE:
//        {
//            bool bEnable = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[0];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthEnable = bEnable;
//
//            target->SetValue((_variant_t)bEnable);
//
//           // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
//
//        }break;
//        case ID_DEPTH_STENCIL_DEPTH_WRITE_MASK:
//        {
//            int iSelDepth = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[1];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)iSelDepth;
//
//            int iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM) / sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[0]);
//            for (int i = 0; i < iNumDepth; i++)
//            {
//                if (iSelDepth == MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[i]);
//
//               //     TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
//                    break;
//                }
//            }
//        }break;
//        case ID_DEPTH_STENCIL_DEPTH_FUNC:
//        {
//            int iSelDepth = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[2];
//            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthFunc = (D3D11_COMPARISON_FUNC)iSelDepth;
//
//            int iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM) / sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[0]);
//            for (int i = 0; i < iNumDepth; i++)
//            {
//                if (iSelDepth == MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[i])
//                {
//                    target->SetValue(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[i]);
//
//                 //   TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
//                    break;
//                }
//            }
//
//        }break;
//
//    }
//}
void CPropertiesWnd::Update_Property_List()
{
    //인덱스 미사용중
    
    if (TOOL.m_iSel_Obj >= TOOL.m_Render_List.size()|| TOOL.m_iSel_Obj<0)
    {
        return;
    }

        bool bEnable = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[0];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendEnable = bEnable;

        m_pBlend_Enable->SetValue((_variant_t)bEnable);

        // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
   
        int iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[1];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)iSelBlend;

        int iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_NUM[i])
            {
                m_pSrcBlend->SetValue(MY_D3D11_BLEND_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }
    
         iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[2];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)iSelBlend;

         iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_NUM[i])
            {
                m_pDestBlend->SetValue(MY_D3D11_BLEND_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }


         iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[3];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)iSelBlend;

         iNumBlend = sizeof(MY_D3D11_BLEND_OP_NUM) / sizeof(MY_D3D11_BLEND_OP_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_OP_NUM[i])
            {
                m_pBlendOp->SetValue(MY_D3D11_BLEND_OP_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }
 
         iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[4];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)iSelBlend;

         iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_NUM[i])
            {
                m_pSrcBlendAlpha->SetValue(MY_D3D11_BLEND_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }

   
         iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[5];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)iSelBlend;

         iNumBlend = sizeof(MY_D3D11_BLEND_NUM) / sizeof(MY_D3D11_BLEND_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_NUM[i])
            {
                m_pDestBlendAlpha->SetValue(MY_D3D11_BLEND_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }

         iSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[6];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)iSelBlend;

         iNumBlend = sizeof(MY_D3D11_BLEND_OP_NUM) / sizeof(MY_D3D11_BLEND_OP_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (iSelBlend == MY_D3D11_BLEND_OP_NUM[i])
            {
                m_pBlendOpAlpha->SetValue(MY_D3D11_BLEND_OP_STRING[i]);

                // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }

        UINT8 nSelBlend = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[7];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = (D3D11_COLOR_WRITE_ENABLE)nSelBlend;

         iNumBlend = sizeof(MY_D3D11_COLOR_WRITE_ENABLE_NUM) / sizeof(MY_D3D11_COLOR_WRITE_ENABLE_NUM[0]);
        for (int i = 0; i < iNumBlend; i++)
        {
            if (nSelBlend == MY_D3D11_COLOR_WRITE_ENABLE_NUM[i])
            {
                m_pRenderTargetWriteMask->SetValue(MY_D3D11_COLOR_WRITE_ENABLE_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                break;
            }
        }

    //Sampler//
   
        int iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[0];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.Filter = (D3D11_FILTER)iSelSampler;

        int iNumSampler = sizeof(MY_D3D11_SAMPLER_FILTER_NUM) / sizeof(MY_D3D11_SAMPLER_FILTER_NUM[0]);
        for (int i = 0; i < iNumSampler; i++)
        {
            if (iSelSampler == MY_D3D11_SAMPLER_FILTER_NUM[i])
            {
                m_pFilter->SetValue(MY_D3D11_SAMPLER_FILTER_STRING[i]);

                //TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                break;
            }
        }
   
         iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[1];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;

         iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
        for (int i = 0; i < iNumSampler; i++)
        {
            if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
            {
                m_pAddressU->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);

                // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                break;
            }

        }

         iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[2];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;

         iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
        for (int i = 0; i < iNumSampler; i++)
        {
            if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
            {
                m_pAddressV->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);

                // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                break;
            }

        }


         iSelSampler = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[3];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;

         iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[0]);
        for (int i = 0; i < iNumSampler; i++)
        {
            if (iSelSampler == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i])
            {
                m_pAddressW->SetValue(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);

                //  TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                break;
            }

        }

        int iSelRaster = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[0];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.FillMode = (D3D11_FILL_MODE)iSelRaster;

        int iNumRaster = sizeof(MY_D3D11_RASTERIZER_FILL_MODE_NUM) / sizeof(MY_D3D11_RASTERIZER_FILL_MODE_NUM[0]);
        for (int i = 0; i < iNumRaster; i++)
        {
            if (iSelRaster == MY_D3D11_RASTERIZER_FILL_MODE_NUM[i])
            {
                m_pFillMode->SetValue(MY_D3D11_RASTERIZER_FILL_MODE_STRING[i]);

                //  TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
                break;
            }

        }
   
         iSelRaster = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[1];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.CullMode = (D3D11_CULL_MODE)iSelRaster;

         iNumRaster = sizeof(MY_D3D11_RASTERIZER_CULL_MODE_NUM) / sizeof(MY_D3D11_RASTERIZER_CULL_MODE_NUM[0]);
        for (int i = 0; i < iNumRaster; i++)
        {
            if (iSelRaster == MY_D3D11_RASTERIZER_CULL_MODE_NUM[i])
            {
                m_pCullMode->SetValue(MY_D3D11_RASTERIZER_CULL_MODE_STRING[i]);

                //   TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
                break;
            }
        }
 
    //DepthStencil//
   
        bEnable = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[0];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthEnable = bEnable;

        m_pDepth_Enable->SetValue((_variant_t)bEnable);

        // TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);


   
        int iSelDepth = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[1];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)iSelDepth;

        int iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM) / sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[0]);
        for (int i = 0; i < iNumDepth; i++)
        {
            if (iSelDepth == MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[i])
            {
                m_pDepthWriteMask->SetValue(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[i]);

                //     TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
                break;
            }
        }

         iSelDepth = TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[2];
        TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthFunc = (D3D11_COMPARISON_FUNC)iSelDepth;

         iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM) / sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[0]);
        for (int i = 0; i < iNumDepth; i++)
        {
            if (iSelDepth == MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[i])
            {
                m_pDepthFunc->SetValue(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[i]);

                //   TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
                break;
            }
        }
       
        
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
        
       
}

LRESULT CPropertiesWnd::OnPropertyChanged(WPARAM w, LPARAM lParam)
    {
        CMFCPropertyGridProperty* pProp =
            (CMFCPropertyGridProperty*)lParam;
       // if (TOOL.m_iSel_Obj > TOOL.m_Render_List.size()|| TOOL.m_Render_List.size()==0)
       // {
       //     return 0;
       // }
        switch ((int)pProp->GetData())
        {
            //Blend//

        case ID_BLEND_BLEND_ENABLE:
        {
            bool bEnable = pProp->GetValue().boolVal == VARIANT_TRUE;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendEnable = bEnable;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[0] = bEnable;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
        }break;
        case ID_BLEND_SRC_BLEND:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_STRING) /
                sizeof(MY_D3D11_BLEND_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlend = (D3D11_BLEND)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[1] = iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }
        }break;
        case ID_BLEND_DEST_BLEND:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_STRING) /
                sizeof(MY_D3D11_BLEND_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlend = (D3D11_BLEND)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[2] = iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }

        }break;
        case ID_BLEND_BLEND_OP:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_OP_STRING) /
                sizeof(MY_D3D11_BLEND_OP_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_OP_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_OP_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOp = (D3D11_BLEND_OP)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[3] = iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }

        }break;
        case   ID_BLEND_SRC_BLEND_ALPHA:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_STRING) /
                sizeof(MY_D3D11_BLEND_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].SrcBlendAlpha = (D3D11_BLEND)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[4] = iSelBlend;

                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }
        }break;
        case   ID_BLEND_DEST_BLEND_ALPHA:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_STRING) /
                sizeof(MY_D3D11_BLEND_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].DestBlendAlpha = (D3D11_BLEND)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[5] = iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }
        }break;
        case   ID_BLEND_BLEND_OP_ALPHA:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelBlend = -1;
            int iNumBlend = sizeof(MY_D3D11_BLEND_OP_STRING) /
                sizeof(MY_D3D11_BLEND_OP_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_BLEND_OP_STRING[i])
                {
                    iSelBlend = MY_D3D11_BLEND_OP_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].BlendOpAlpha = (D3D11_BLEND_OP)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[6] = iSelBlend;

                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }

        }break;
        case   ID_BLEND_RT_WRITE_MASK:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            UINT8 iSelBlend = 0;
            int iNumBlend = sizeof(MY_D3D11_COLOR_WRITE_ENABLE_STRING) /
                sizeof(MY_D3D11_COLOR_WRITE_ENABLE_STRING[0]);
            for (int i = 0; i < iNumBlend; i++)
            {
                if (data == MY_D3D11_COLOR_WRITE_ENABLE_STRING[i])
                {
                    iSelBlend = MY_D3D11_COLOR_WRITE_ENABLE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc.RenderTarget[0].RenderTargetWriteMask = (UINT8)iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.blend[7] = iSelBlend;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetBlendState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_BlendDesc);
                    break;
                }
            }

        }break;
        //Sampler//

        case ID_SAMPLER_FILTER:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelSampler = 0;
            int iNumSampler = sizeof(MY_D3D11_SAMPLER_FILTER_STRING) /
                sizeof(MY_D3D11_SAMPLER_FILTER_STRING[0]);
            for (int i = 0; i < iNumSampler; i++)
            {
                if (data == MY_D3D11_SAMPLER_FILTER_STRING[i])
                {
                    iSelSampler = MY_D3D11_SAMPLER_FILTER_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.Filter = (D3D11_FILTER)iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[0] = iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                    break;
                }
            }
        }break;
        case ID_SAMPLER_ADDRESS_U:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelSampler = 0;
            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING) /
                sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[0]);
            for (int i = 0; i < iNumSampler; i++)
            {
                if (data == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i])
                {
                    iSelSampler = MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressU = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[1] = iSelSampler;

                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                    break;
                }
            }
        }break;
        case ID_SAMPLER_ADDRESS_V:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelSampler = 0;
            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING) /
                sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[0]);
            for (int i = 0; i < iNumSampler; i++)
            {
                if (data == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i])
                {
                    iSelSampler = MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressV = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[2] = iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                    break;
                }
            }
        }break;
        case ID_SAMPLER_ADDRESS_W:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelSampler = 0;
            int iNumSampler = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING) /
                sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[0]);
            for (int i = 0; i < iNumSampler; i++)
            {
                if (data == MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i])
                {
                    iSelSampler = MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc.AddressW = (D3D11_TEXTURE_ADDRESS_MODE)iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.sampler[3] = iSelSampler;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetSamplerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_SamplerDesc);
                    break;
                }
            }
        }break;

        //Rasterizer//
        case ID_RASTERIZER_FILL_MODE:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelRaster = 0;
            int iNumRaster = sizeof(MY_D3D11_RASTERIZER_FILL_MODE_STRING) /
                sizeof(MY_D3D11_RASTERIZER_FILL_MODE_STRING[0]);
            for (int i = 0; i < iNumRaster; i++)
            {
                if (data == MY_D3D11_RASTERIZER_FILL_MODE_STRING[i])
                {
                    iSelRaster = MY_D3D11_RASTERIZER_FILL_MODE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.FillMode = (D3D11_FILL_MODE)iSelRaster;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[0] = iSelRaster;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
                    break;
                }
            }
        }break;
        case ID_RASTERIZER_CULL_MODE:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelRaster = 0;
            int iNumRaster = sizeof(MY_D3D11_RASTERIZER_CULL_MODE_STRING) /
                sizeof(MY_D3D11_RASTERIZER_CULL_MODE_STRING[0]);
            for (int i = 0; i < iNumRaster; i++)
            {
                if (data == MY_D3D11_RASTERIZER_CULL_MODE_STRING[i])
                {
                    iSelRaster = MY_D3D11_RASTERIZER_CULL_MODE_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc.CullMode = (D3D11_CULL_MODE)iSelRaster;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.rasterizer[1] = iSelRaster;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetRasterizerState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_RasterizerDesc);
                    break;
                }
            }
        }break;

        //DepthStencil//
        case ID_DEPTH_STENCIL_DEPTH_ENABLE:
        {
            bool bEnable = pProp->GetValue().boolVal == VARIANT_TRUE;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthEnable = bEnable;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[0] = bEnable;
            TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
        }break;
        case ID_DEPTH_STENCIL_DEPTH_WRITE_MASK:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelDepth = 0;
            int iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING) /
                sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[0]);
            for (int i = 0; i < iNumDepth; i++)
            {
                if (data == MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[i])
                {
                    iSelDepth = MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthWriteMask = (D3D11_DEPTH_WRITE_MASK)iSelDepth;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[1] = iSelDepth;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
                    break;
                }
            }
        }break;
        case ID_DEPTH_STENCIL_DEPTH_FUNC:
        {
            CString data = (LPCTSTR)(_bstr_t)pProp->GetValue();
            int iSelDepth = 0;
            int iNumDepth = sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING) /
                sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[0]);
            for (int i = 0; i < iNumDepth; i++)
            {
                if (data == MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[i])
                {
                    iSelDepth = MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_NUM[i];
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc.DepthFunc = (D3D11_COMPARISON_FUNC)iSelDepth;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_data.m_State.depthstencil[2] = iSelDepth;
                    TOOL.m_Render_List[TOOL.m_iSel_Obj]->SetDepthStencilState(&TOOL.m_Render_List[TOOL.m_iSel_Obj]->m_DepthStencilDesc);
                    break;
                }
            }
        }break;

        
    }

    return 0;

}



/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 메시지 처리기

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == nullptr || (AfxGetMainWnd() != nullptr && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(nullptr, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(nullptr, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 콤보 상자를 만듭니다.
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("속성 콤보 상자를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	m_wndObjectCombo.AddString(_T("응용 프로그램"));
	m_wndObjectCombo.AddString(_T("속성 창"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("속성 표를 만들지 못했습니다. \n");
		return -1;      // 만들지 못했습니다.
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 잠금 */);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 모든 명령은 부모 프레임이 아닌 이 컨트롤을 통해 라우팅됩니다.
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnProperties2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO: 여기에 명령 업데이트 UI 처리기 코드를 추가합니다.
}

void CPropertiesWnd::InitPropList()
{
   

	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
    
#pragma region Blend_State


    //D3D11_BLEND_DESC;
   //D3D11_RENDER_TARGET_BLEND_DESC;
   //BOOL BlendEnable;
   //D3D11_BLEND SrcBlend;
   //D3D11_BLEND DestBlend;
   //D3D11_BLEND_OP BlendOp;
   //D3D11_BLEND SrcBlendAlpha;
   //D3D11_BLEND DestBlendAlpha;
   //D3D11_BLEND_OP BlendOpAlpha;
   //UINT8 RenderTargetWriteMask;

    int iNumBlend = sizeof(MY_D3D11_BLEND_STRING) / sizeof(MY_D3D11_BLEND_STRING[0]);
    int iNumBlendOp= sizeof(MY_D3D11_BLEND_OP_STRING) / sizeof(MY_D3D11_BLEND_OP_STRING[0]);

    m_pBlend_Root = new CMFCPropertyGridProperty(_T("Blend_State"));

    //BlendEnable
    m_pBlend_Enable = new CMFCPropertyGridProperty(_T("Enable"), (_variant_t)true, _T("알파블랜딩 ON/OFF"), ID_BLEND_BLEND_ENABLE);
    m_pBlend_Root->AddSubItem(m_pBlend_Enable);
    //SrcBlend
    m_pSrcBlend = new CMFCPropertyGridProperty(_T("Src_Blend"), _T("D3D11_BLEND_SRC_ALPHA"), _T("Alpha_Blend_Src_Option"), ID_BLEND_SRC_BLEND);
    for (int i = 0; i < iNumBlend; i++)
    {
        m_pSrcBlend->AddOption(MY_D3D11_BLEND_STRING[i]);
    }
    m_pSrcBlend->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pSrcBlend);
    
    //DestBlend
    m_pDestBlend = new CMFCPropertyGridProperty(_T("Dest_Blend"), _T("D3D11_BLEND_INV_SRC_ALPHA"), _T("Alpha_Blend_Dest_Option"), ID_BLEND_DEST_BLEND);
    for (int i = 0; i < iNumBlend; i++)
    {
        m_pDestBlend->AddOption(MY_D3D11_BLEND_STRING[i]);
    }
    m_pDestBlend->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pDestBlend);

    //BlendOp
    m_pBlendOp = new CMFCPropertyGridProperty(_T("Blend_Op"), _T("D3D11_BLEND_OP_ADD"), _T("Alpha_Blend_Op_Option"), ID_BLEND_BLEND_OP);
    for (int i = 0; i < iNumBlendOp; i++)
    {
        m_pBlendOp->AddOption(MY_D3D11_BLEND_OP_STRING[i]);
    }
    m_pBlendOp->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pBlendOp);

    //SrcBlendAlpha;
    m_pSrcBlendAlpha = new CMFCPropertyGridProperty(_T("Src_Blend_Alpha"), _T("D3D11_BLEND_ONE"), _T("Alpha_Blend_Src_Alpha_Option"), ID_BLEND_SRC_BLEND_ALPHA);
    for (int i = 0; i < iNumBlend; i++)
    {
        m_pSrcBlendAlpha->AddOption(MY_D3D11_BLEND_STRING[i]);
    }
    m_pSrcBlendAlpha->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pSrcBlendAlpha);

    //DestBlendAlpha;
    m_pDestBlendAlpha = new CMFCPropertyGridProperty(_T("Dest_Blend_Alpha"), _T("D3D11_BLEND_ZERO"), _T("Alpha_Blend_Dest_Alpha_Option"), ID_BLEND_DEST_BLEND_ALPHA);
    for (int i = 0; i < iNumBlend; i++)
    {
        m_pDestBlendAlpha->AddOption(MY_D3D11_BLEND_STRING[i]);
    }
    m_pDestBlendAlpha->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pDestBlendAlpha);

    //BlendOpAlpha
    m_pBlendOpAlpha = new CMFCPropertyGridProperty(_T("Blend_Op_Alpha"), _T("D3D11_BLEND_OP_ADD"), _T("Alpha_Blend_Op_Alpha_Option"), ID_BLEND_BLEND_OP_ALPHA);
    for (int i = 0; i < iNumBlendOp; i++)
    {
        m_pBlendOpAlpha->AddOption(MY_D3D11_BLEND_OP_STRING[i]);
    }
    m_pBlendOpAlpha->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pBlendOpAlpha);

    //RenderTargetWriteMask
    m_pRenderTargetWriteMask = new CMFCPropertyGridProperty(_T("RT_Write_Mask"), _T("D3D11_COLOR_WRITE_ENABLE_ALL"), _T("Alpha_Blend_Render_Target_Write_Mask_Option"), ID_BLEND_RT_WRITE_MASK);
    int iNumRTWM = sizeof(MY_D3D11_COLOR_WRITE_ENABLE_STRING) / sizeof(MY_D3D11_COLOR_WRITE_ENABLE_STRING[0]);
    for (int i = 0; i < iNumRTWM; i++)
    {
        m_pRenderTargetWriteMask->AddOption(MY_D3D11_COLOR_WRITE_ENABLE_STRING[i]);
    }
    m_pRenderTargetWriteMask->AllowEdit(FALSE);
    m_pBlend_Root->AddSubItem(m_pRenderTargetWriteMask);

    //ADD PROPERTY
    m_wndPropList.AddProperty(m_pBlend_Root);

#pragma endregion

#pragma region Rasterizer_State

    //D3D11_FILL_MODE FillMode;//
    //D3D11_CULL_MODE CullMode;//
    //아래는 기본값
    //BOOL FrontCounterClockwise;
    //INT DepthBias;
    //FLOAT DepthBiasClamp;
    //FLOAT SlopeScaledDepthBias;
    //BOOL DepthClipEnable;  //TRUE
    //BOOL ScissorEnable;
    //BOOL MultisampleEnable;//TRUE
    //BOOL AntialiasedLineEnable; //TRUE

    int iNumFill = sizeof(MY_D3D11_RASTERIZER_FILL_MODE_STRING) / sizeof(MY_D3D11_RASTERIZER_FILL_MODE_STRING[0]);
    int iNumCull = sizeof(MY_D3D11_RASTERIZER_CULL_MODE_STRING) / sizeof(MY_D3D11_RASTERIZER_CULL_MODE_STRING[0]);
    m_pRasterizer_Root = new CMFCPropertyGridProperty(_T("Rasterizer_State"));

    //FillMode
    m_pFillMode = new CMFCPropertyGridProperty(_T("Fill_Mode"), _T("D3D11_FILL_SOLID"), _T("Rasterizer_Fill_Mode_Option"), ID_RASTERIZER_FILL_MODE);
    for (int i = 0; i < iNumFill; i++)
    {
        m_pFillMode->AddOption(MY_D3D11_RASTERIZER_FILL_MODE_STRING[i]);
    }
    m_pFillMode->AllowEdit(FALSE);
    m_pRasterizer_Root->AddSubItem(m_pFillMode);
    //CullMode
    m_pCullMode = new CMFCPropertyGridProperty(_T("Cull_Mode"), _T("D3D11_CULL_NONE"), _T("Rasterizer_Cull_Mode_Option"), ID_RASTERIZER_CULL_MODE);
    for (int i = 0; i < iNumCull; i++)
    {
        m_pCullMode->AddOption(MY_D3D11_RASTERIZER_CULL_MODE_STRING[i]);
    }
    m_pCullMode->AllowEdit(FALSE);
    m_pRasterizer_Root->AddSubItem(m_pCullMode);
    // //ADD PROPERTY
    m_wndPropList.AddProperty(m_pRasterizer_Root);

#pragma endregion

#pragma region Sampler_State

    //D3D11_FILTER Filter;//
    //D3D11_TEXTURE_ADDRESS_MODE AddressU;//
    //D3D11_TEXTURE_ADDRESS_MODE AddressV;//
    //D3D11_TEXTURE_ADDRESS_MODE AddressW;//
    //아래는 기본값
   // D3D11_COMPARISON_FUNC ComparisonFunc; //0
   // FLOAT BorderColor[4];// zeromem ->  0,0,0,0;
   // FLOAT MipLODBias;//0 고정
   //UINT MaxAnisotropy;// 16고정
   // FLOAT MinLOD;//FLT_MIN고정
   // FLOAT MaxLOD;//FLT_MAX 고정

    int iNumTexAddMod = sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING) / sizeof(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[0]);
    int iNumFilter = sizeof(MY_D3D11_SAMPLER_FILTER_STRING) / sizeof(MY_D3D11_SAMPLER_FILTER_STRING[0]);

    m_pSampler_Root = new CMFCPropertyGridProperty(_T("Sampler_State"));

    //Filter
    m_pFilter = new CMFCPropertyGridProperty(_T("Filter"), _T("D3D11_FILTER_MIN_MAG_MIP_LINEAR"), _T("Sampler_Filter_Option"), ID_SAMPLER_FILTER);
    for (int i = 0; i < iNumFilter; i++)
    {
        m_pFilter->AddOption(MY_D3D11_SAMPLER_FILTER_STRING[i]);
    }
    m_pFilter->AllowEdit(FALSE);
    m_pSampler_Root->AddSubItem(m_pFilter);

    //AddressU
    m_pAddressU = new CMFCPropertyGridProperty(_T("AddressU"), _T("D3D11_TEXTURE_ADDRESS_WRAP"), _T("Sampler_AddressU_Option"), ID_SAMPLER_ADDRESS_U);
    for (int i = 0; i < iNumTexAddMod; i++)
    {
        m_pAddressU->AddOption(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
    }
    m_pAddressU->AllowEdit(FALSE);
    m_pSampler_Root->AddSubItem(m_pAddressU);

    //AddressV
    m_pAddressV = new CMFCPropertyGridProperty(_T("AddressV"), _T("D3D11_TEXTURE_ADDRESS_WRAP"), _T("Sampler_AddressV_Option"), ID_SAMPLER_ADDRESS_V);
    for (int i = 0; i < iNumTexAddMod; i++)
    {
        m_pAddressV->AddOption(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
    }
    m_pAddressV->AllowEdit(FALSE);
    m_pSampler_Root->AddSubItem(m_pAddressV);

    //AddressW
    m_pAddressW = new CMFCPropertyGridProperty(_T("AddressW"), _T("D3D11_TEXTURE_ADDRESS_WRAP"), _T("Sampler_AddressW_Option"), ID_SAMPLER_ADDRESS_W);
    for (int i = 0; i < iNumTexAddMod; i++)
    {
        m_pAddressW->AddOption(MY_D3D11_SAMPLER_TEXTURE_ADDRESS_MODE_STRING[i]);
    }
    m_pAddressW->AllowEdit(FALSE);
    m_pSampler_Root->AddSubItem(m_pAddressW);

    //ADD PROPERTY
    m_wndPropList.AddProperty(m_pSampler_Root);
#pragma endregion

#pragma region DepthStencil_State

    //BOOL DepthEnable; //TRUE
    //D3D11_DEPTH_WRITE_MASK DepthWriteMask;
    //D3D11_COMPARISON_FUNC DepthFunc;

    //0초기화 
    //BOOL StencilEnable;
    //UINT8 StencilReadMask;
    //UINT8 StencilWriteMask;
    //D3D11_DEPTH_STENCILOP_DESC FrontFace;
    //D3D11_DEPTH_STENCILOP_DESC BackFace;



    int iNumComparisonFunc = sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING) / sizeof(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[0]);
    int iNumWriteMask = sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING) / sizeof(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[0]);

    m_pDepthStencil_Root = new CMFCPropertyGridProperty(_T("Depth_Stencil_State"));

    //DepthEnable
    m_pDepth_Enable = new CMFCPropertyGridProperty(_T("Depth_Enable"), (_variant_t)true, _T("Depth_Stencil_Depth_Enable/Disable_Option"), ID_DEPTH_STENCIL_DEPTH_ENABLE);
    m_pDepthStencil_Root->AddSubItem(m_pDepth_Enable);

    //DepthWriteMask
    m_pDepthWriteMask = new CMFCPropertyGridProperty(_T("Depth_Write_Mask"), _T("D3D11_DEPTH_WRITE_MASK_ALL"), _T("Depth_Stencil_Depth_Write_Mask_Option"), ID_DEPTH_STENCIL_DEPTH_WRITE_MASK);
    for (int i = 0; i < iNumWriteMask; i++)
    {
        m_pDepthWriteMask->AddOption(MY_D3D11_DEPTH_STENCIL_DEPTH_WRITE_MASK_STRING[i]);
    }
    m_pDepthWriteMask->AllowEdit(FALSE);
    m_pDepthStencil_Root->AddSubItem(m_pDepthWriteMask);

    // DepthFunc
    m_pDepthFunc = new CMFCPropertyGridProperty(_T("Depth_Func"), _T("D3D11_COMPARISON_LESS_EQUAL"), _T("Depth_Stencil_Depth_Func_Option"), ID_DEPTH_STENCIL_DEPTH_FUNC);
    for (int i = 0; i < iNumComparisonFunc; i++)
    {
        m_pDepthFunc->AddOption(MY_D3D11_DEPTH_STENCIL_COMPARISON_FUNC_STRING[i]);
    }
    m_pDepthFunc->AllowEdit(FALSE);
    m_pDepthStencil_Root->AddSubItem(m_pDepthFunc);

    //ADD PROPERTY
    m_wndPropList.AddProperty(m_pDepthStencil_Root);
    
#pragma endregion
   

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("모양"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("3D 모양"), (_variant_t) false, _T("창에 굵은 글꼴이 아닌 글꼴을 지정하고, 컨트롤에 3D 테두리를 지정합니다.")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("테두리"), _T("Dialog Frame"), _T("None, Thin, Resizable 또는 Dialog Frame 중 하나를 지정합니다."));
	pProp->AddOption(_T("None"));
	pProp->AddOption(_T("Thin"));
	pProp->AddOption(_T("Resizable"));
	pProp->AddOption(_T("Dialog Frame"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("캡션"), (_variant_t) _T("정보"), _T("창의 제목 표시줄에 표시되는 텍스트를 지정합니다.")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("창 크기"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("높이"), (_variant_t) 250l, _T("창의 높이를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("너비"), (_variant_t) 150l, _T("창의 너비를 지정합니다."));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("글꼴"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	_tcscpy_s(lf.lfFaceName, _T("맑은 고딕"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("글꼴"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("창의 기본 글꼴을 지정합니다.")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("시스템 글꼴을 사용합니다."), (_variant_t) true, _T("창에서 MS Shell Dlg 글꼴을 사용하도록 지정합니다.")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("기타"));
	pProp = new CMFCPropertyGridProperty(_T("(이름)"), _T("응용 프로그램"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("창 색상"), RGB(210, 192, 254), nullptr, _T("창의 기본 색상을 지정합니다."));
	pColorProp->EnableOtherButton(_T("기타..."));
	pColorProp->EnableAutomaticButton(_T("기본값"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("아이콘 파일(*.ico)|*.ico|모든 파일(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("아이콘"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("창 아이콘을 지정합니다.")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("폴더"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("계층"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("첫번째 하위 수준"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("두 번째 하위 수준"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("항목 1"), (_variant_t) _T("값 1"), _T("설명입니다.")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("항목 2"), (_variant_t) _T("값 2"), _T("설명입니다.")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("항목 3"), (_variant_t) _T("값 3"), _T("설명입니다.")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);*/
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}
