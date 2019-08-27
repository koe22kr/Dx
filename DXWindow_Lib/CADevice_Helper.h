#pragma once
#include "CATexture.h"


class CADevice_Helper
{

    HRESULT hr;
    map<std::wstring, CATexture*>* m_pTexture_Map;//
  /*
   // IDXGIFactory*            m_pFactory; //현재 필요없음 190827khg
    //ID3D11Device*            m_pDevice;
    //ID3D11DeviceContext*     m_pImmediate_Device_Context;
 미사용
    ID3D11InputLayout* m_pInput_Layout;

    ID3D11Buffer* m_pVertex_Buffer;
    ID3D11Buffer* m_pIndex_Buffer;
    ID3D11Buffer* m_pConst_Buffer;

    ID3D11VertexShader* m_pVertex_Shader;
    ID3D11PixelShader* m_pPixel_Shader;

    ID3D11ShaderResourceView* m_pSRV;*/

private:
    bool Create_Vertex_Buffer(void* data, int num,int size, ID3D11Buffer*& pVertex_buffer, ID3D11Device* pDevice=CADevice::m_pDevice);
    bool Create_Index_Buffer(void* Idata, int index_num, int index_size, ID3D11Buffer*& pIndex_buffer, ID3D11Device* pDevice = CADevice::m_pDevice);
public:
    bool Create_Const_Buffer(ID3D11Buffer*& pConst_buffer, void* Const_data, int num, int size, ID3D11Device* pDevice = CADevice::m_pDevice);

    bool Create_Vertex_And_Index_Buffer(void* vertex_array, int vertex_num, int vertex_size, ID3D11Buffer*& pVertex_Buffer, void* index_array, int index_num, int index_size, ID3D11Buffer*& pIndex_Buffer);
   
    bool Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice = CADevice::m_pDevice);
    bool Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name, ID3D11Device* pDevice = CADevice::m_pDevice);


   /* void Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height, ID3D11Device* pDevice = CADevice::m_pDevice);
    bool Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path, ID3D11ShaderResourceView*& pSRV, ID3D11Device* pDevice = CADevice::m_pDevice);*/
    
    bool Create_Shader_Resource_View_From_File(const TCHAR* texture_full_path, CATexture* ca_texture, ID3D11Device* pDevice);
    void Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV, int start_slot, ID3D11DeviceContext* pContext=CADevice::m_pImmediate_Device_Context);
    
    void Set_Const_Buffer(ID3D11Buffer* pConst_buffer, void* const_data,UINT size, ID3D11DeviceContext* pContext= CADevice::m_pImmediate_Device_Context);
  
    void Set_Pipe_Line(ID3D11DeviceContext* pContext= CADevice::m_pImmediate_Device_Context,ID3D11InputLayout* pInput_Layout=NULL,ID3D11Buffer* pVertex_buffer = NULL,UINT VB_size=0, ID3D11Buffer* pIndex_Buffer = NULL, ID3D11Buffer* pConst_Buffer = NULL, ID3D11VertexShader* pVertex_Shader = NULL, ID3D11HullShader* pHull_Shader = NULL, ID3D11DomainShader* pDomain_Shader = NULL, ID3D11GeometryShader* pGeometry_Shader = NULL, ID3D11PixelShader* pPixel_Shader = NULL);
    
    

public:
    CADevice_Helper();
   // CADevice_Helper(map<wstring, ID3D11Texture2D*>* pTexture_Map=&CADevice::m_Texture_Map/*,IDXGIFactory* pfactory,*/ ,
   //     ID3D11Device* pdevice = CADevice::m_pDevice, 
   //     ID3D11DeviceContext* pimmediate_device_context = CADevice::m_pImmediate_Device_Context);
    virtual ~CADevice_Helper();
   /* bool Init();
    bool Frame();
    bool Render();
    bool Release();*/
    bool Draw(ID3D11DeviceContext* pContext);
};

