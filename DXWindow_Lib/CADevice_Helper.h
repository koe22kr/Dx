#pragma once
#include "CATexture.h"
namespace DX
{
    
    

    struct VS_CB
    {
        DirectX::XMMATRIX matWorld;
        DirectX::XMMATRIX matView;
        DirectX::XMMATRIX matProj;
        DirectX::XMFLOAT4 color;
        DirectX::XMFLOAT4 etc;
    };

    class CADevice_Helper
    {
    public:
        HRESULT hr;
        Microsoft::WRL::ComPtr< ID3D11InputLayout> m_cInput_Layout;
        Microsoft::WRL::ComPtr< ID3D11Buffer> m_cVertex_Buffer;
        Microsoft::WRL::ComPtr< ID3D11Buffer> m_cIndex_Buffer;
        Microsoft::WRL::ComPtr< ID3D11Buffer> m_cConst_Buffer;
        Microsoft::WRL::ComPtr< ID3D11VertexShader> m_cVertex_Shader;
        Microsoft::WRL::ComPtr< ID3D11PixelShader> m_cPixel_Shader;
        CATexture m_CATexture;

        UINT m_nShader_Flag2;
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
        bool Create_Vertex_Buffer(void* data, int num, int size, ID3D11Buffer* pVertex_buffer, ID3D11Device* pDevice = CADevice::m_pDevice);
        bool Create_Vertex_Buffer_Self(std::vector<PNCT_VERTEX>* m_Vertex_List, ID3D11Device* pDevice = CADevice::m_pDevice);


        bool Create_Index_Buffer(void* Idata, int index_num, int index_size, ID3D11Buffer*& pIndex_buffer, ID3D11Device* pDevice = CADevice::m_pDevice);
        bool Create_Index_Buffer_Self(std::vector<DWORD>* m_Index_List, ID3D11Device* pDevice = CADevice::m_pDevice);
    public:
        bool Create_Vertex_And_Index_Buffer(void* vertex_array, int vertex_num, int vertex_size, ID3D11Buffer*& pVertex_Buffer, void* index_array, int index_num, int index_size, ID3D11Buffer*& pIndex_Buffer);
        bool Create_Vertex_And_Index_Buffer_Self(std::vector<PNCT_VERTEX>* m_Vertex_List, std::vector<DWORD>* m_Index_List, ID3D11Device* pDevice = CADevice::m_pDevice);

        bool Create_Const_Buffer(ID3D11Buffer*& pConst_buffer, void* Const_data = nullptr, int num = 0, int size = 0, ID3D11Device* pDevice = CADevice::m_pDevice);
        bool Create_Const_Buffer_Self(void* Const_data = nullptr, int num = 0, int size = 0, ID3D11Device* pDevice = CADevice::m_pDevice);

        bool Load_VS_And_Set_Input_Layout(const WCHAR* VS_compiler, ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice = CADevice::m_pDevice);
        bool Load_VS_And_Set_Input_Layout_Self(const WCHAR* VS_compiler, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice= CADevice::m_pDevice);

        bool Load_PS(const WCHAR* PS_compiler, ID3D11PixelShader*& pPixel_Shader, const char* PS_name, ID3D11Device* pDevice = CADevice::m_pDevice);
        bool Load_PS_Self(const WCHAR* PS_compiler, const char* PS_name, ID3D11Device* pDevice = CADevice::m_pDevice);

        /* void Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height, ID3D11Device* pDevice = CADevice::m_pDevice);
         bool Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path, ID3D11ShaderResourceView*& pSRV, ID3D11Device* pDevice = CADevice::m_pDevice);*/

        int Load_Shader_Resource_View_From_File(const TCHAR* texture_full_path, CATexture* ca_texture, UINT KEY, ID3D11Device* pDevice);
        int Load_Shader_Resource_View_From_File_Self(const TCHAR* texture_full_path, UINT KEY, ID3D11Device* pDevice= CADevice::m_pDevice);

        void Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV, UINT start_slot, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);
        void Set_SRV_To_PS_Self(UINT start_slot, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);

        void Set_Const_Buffer(ID3D11Buffer* pConst_buffer, void* const_data, UINT size, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);
        void Set_Const_Buffer_Self(void* const_data, UINT size, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);

        void Set_Pipe_Line(ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context, ID3D11InputLayout* pInput_Layout = NULL, ID3D11Buffer* pVertex_buffer = NULL, UINT VB_size = 0, ID3D11Buffer* pIndex_Buffer = NULL, ID3D11Buffer* pConst_Buffer = NULL, ID3D11VertexShader* pVertex_Shader = NULL, ID3D11HullShader* pHull_Shader = NULL, ID3D11DomainShader* pDomain_Shader = NULL, ID3D11GeometryShader* pGeometry_Shader = NULL, ID3D11PixelShader* pPixel_Shader = NULL);
        void Set_Pipe_Line_Self(ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context, UINT VB_size = 48);


    public:
        CADevice_Helper();
        // CADevice_Helper(map<wstring, ID3D11Texture2D*>* pTexture_Map=&CADevice::m_Texture_Map/*,IDXGIFactory* pfactory,*/ ,
        //     ID3D11Device* pdevice = CADevice::m_pDevice, 
        //     ID3D11DeviceContext* pimmediate_device_context = CADevice::m_pImmediate_Device_Context);
        virtual ~CADevice_Helper();
        // bool Init();
        // bool Frame();
        bool Render(ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context, UINT draw_count = 0);
        bool Render(UINT draw_count, UINT vertex_location = 0, UINT index_location = 0, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);

        bool PreRender(ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context, UINT V_Bsize = sizeof(PNCT_VERTEX), UINT SRV_start_slot = 1);
        bool PostRender(ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);
        bool PostRender_And_Set_Draw_OPT(UINT draw_count, UINT vertex_location = 0, UINT index_location = 0, ID3D11DeviceContext* pContext = CADevice::m_pImmediate_Device_Context);
        // bool Release();
         //bool Draw(ID3D11DeviceContext* pContext);
    };

}