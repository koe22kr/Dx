#include "CADevice_Helper.h"

bool CADevice_Helper::Create_Vertex_Buffer(void* data, int num, int size, ID3D11Buffer*& pVertex_buffer,ID3D11Device* pDevice)
{

    //D3D11_BUFFER_DESC;
    //UINT ByteWidth;
    //D3D11_USAGE Usage;
    //UINT BindFlags;
    //UINT CPUAccessFlags;
    //UINT MiscFlags;
    //UINT StructureByteStride;
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));

    BD.ByteWidth = size *num;
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;   ///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    
    SD.pSysMem = data;
    if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &pVertex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"CADevice_Helper", MB_OK);
        return false;
    }

    return true;
}



bool CADevice_Helper::Create_Index_Buffer(void* Idata,int index_num, int index_size, ID3D11Buffer*& pIndex_buffer, ID3D11Device* pDevice)
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BD.ByteWidth = index_size *index_num;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = Idata;

    if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &pIndex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
        return false;
    }
    return true;
}

bool CADevice_Helper::Create_Vertex_And_Index_Buffer(void* vertex_array,int vertex_num, int vertex_size, ID3D11Buffer*& pVertex_Buffer, void* index_array, int index_num,int index_size, ID3D11Buffer*& pIndex_Buffer)
{

    Create_Vertex_Buffer(vertex_array, vertex_num, vertex_size, pVertex_Buffer);
    Create_Index_Buffer(index_array, index_num, index_size, pIndex_Buffer);



    return true;
}


bool CADevice_Helper::Create_Const_Buffer(ID3D11Buffer*& pConst_buffer,void* Const_data,int num,int size, ID3D11Device* pDevice)
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DYNAMIC;
    BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BD.ByteWidth = num * size;
    BD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///
    if (Const_data != nullptr)
    {
        D3D11_SUBRESOURCE_DATA SD;
        ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
        SD.pSysMem = Const_data;

        if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &pConst_buffer)))
        {
            MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
            return false;
        }
    }
    else
    {
        if (FAILED(hr = pDevice->CreateBuffer(&BD, NULL, &pConst_buffer)))
        {
            MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
            return false;
        }
    }
    return true;
}


bool CADevice_Helper::Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice)
{
    ID3D10Blob* pVS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"VS.vsh", NULL, NULL, VS_name, "vs_5_0",
        NULL, NULL, NULL, &pVS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"CADevice_Helper", MB_OK);
        return false;
    }

    if (FAILED(hr = pDevice->CreateVertexShader(
        /* [ __in  const void *pShaderBytecode] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pVS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
        &pVertex_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"CADevice_Helper", MB_OK);
        return false;
    }
    ////////////////
     //   LPCSTR SemanticName;
     //   UINT SemanticIndex;
     //   DXGI_FORMAT Format;
     //   UINT InputSlot;
     //   UINT AlignedByteOffset;
     //   D3D11_INPUT_CLASSIFICATION InputSlotClass;
     //   UINT InstanceDataStepRate;


    if (FAILED(hr = pDevice->CreateInputLayout(
        /* [__in_ecount(NumElements)  const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,] */
        Lay_Out,
        /* [ __in_range(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements] */
        element_count,
        /* [__in  const void *pShaderBytecodeWithInputSignature] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength] */
        pVS->GetBufferSize(),
        /* [__out_opt  ID3D11InputLayout **ppInputLayout] */
        &pInput_Layout
    )))
    {
        MessageBox(g_hWnd, L"Create_Input_Layout", L"CADevice_Helper", MB_OK);
        return false;
    }
    ////
    if (pVS != nullptr)pVS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}


bool CADevice_Helper::Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name, ID3D11Device* pDevice)
{
    ID3D10Blob* pPS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"PS.psh", NULL, NULL, PS_name, "ps_5_0",
        NULL, NULL, NULL, &pPS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"CADevice_Helper", MB_OK);
        return false;
    }

    if (FAILED(hr = pDevice->CreatePixelShader(
        /* [ __in  const void *pShaderBytecode] */
        pPS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength,] */
        pPS->GetBufferSize(),
        /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
        NULL,
        /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
        &pPixel_Shader
    )))
    {
        MessageBox(g_hWnd, L"Create_Pixel_Shader", L"CADevice_Helper", MB_OK);
        return false;
    }
    if (pPS != nullptr)pPS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}

//
//void CADevice_Helper::Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height,UINT KEY, ID3D11Device* pDevice)
//{
//
//    D3DX11_IMAGE_LOAD_INFO Load_Info;
//    ZeroMemory(&Load_Info, sizeof(D3DX11_IMAGE_LOAD_INFO));
//    Load_Info.Width = width;
//    Load_Info.Height = height;
//    Load_Info.Depth = D3DX11_DEFAULT;
//    Load_Info.FirstMipLevel = 0;
//    Load_Info.MipLevels = 1;	// 반드시 1 이여야 한다.
//    Load_Info.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_STAGING;    
//    Load_Info.CpuAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
//    Load_Info.BindFlags = D3D11_BIND_SHADER_RESOURCE;
//    Load_Info.MiscFlags = 0;
//    Load_Info.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    Load_Info.Filter = D3DX11_FILTER_LINEAR;
//    Load_Info.MipFilter = D3DX11_FILTER_NONE;
//
//    //    D3DX11CreateTextureFromFileW(
//    //        ID3D11Device*               pDevice,
//    //        LPCWSTR                     pSrcFile,
//    //        D3DX11_IMAGE_LOAD_INFO      *pLoadInfo,
//    //        ID3DX11ThreadPump*          pPump,
//    //        ID3D11Resource**            ppTexture,
//    //        HRESULT*                    pHResult);
//    ID3D11Resource* pResource = NULL;
//
//    ID3D11Texture2D* pTexture_2D = NULL;
//    if (FAILED(hr = D3DX11CreateTextureFromFile(pDevice, texture_full_path, &Load_Info, NULL, &pResource, NULL)))
//    {
//        MessageBox(g_hWnd, L"Load_Texture_2D_From_File", L"CADevice_Helper", MB_OK);
//        return;
//    }
//
//    hr = pResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)&pTexture_2D);
//    EM(hr, QueryInterface, Load_Texture_2D_From_File);
//    m_pTexture_Map->insert(make_pair(KEY, pTexture_2D));
//    return;
//}
//
//bool CADevice_Helper::Create_Shader_Resource_View_From_Resource(const TCHAR* texture_full_path, ID3D11ShaderResourceView*& pSRV, ID3D11Device* pDevice)
//{
//    D3D11_SHADER_RESOURCE_VIEW_DESC SRV_Desc;
//    ZeroMemory(&SRV_Desc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
//    SRV_Desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
//    SRV_Desc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
//    SRV_Desc.Texture2D.MipLevels = 1;
//    SRV_Desc.Texture2D.MostDetailedMip = 0;
//
//    auto iter = m_pTexture_Map->find(texture_full_path);
//    if (iter == m_pTexture_Map->end())
//    {
//        MessageBox(g_hWnd, L"CreateShaderResourceView", L"CADevice_Helper", MB_OK);
//        return false;
//    }
//    else
//    {
//
//        hr = pDevice->CreateShaderResourceView(iter->second, &SRV_Desc, &pSRV);
//        EM(hr, CreateShaderResourceView, Create_Shader_Resource_View_From_Resource);
//        if (pSRV == NULL)
//        {
//            MessageBox(g_hWnd, L"CreateShaderResourceView", L"CADevice_Helper", MB_OK);
//            return false;
//        }
//        return true;
//    }
//}

bool CADevice_Helper::Create_Shader_Resource_View_From_File(const TCHAR* texture_full_path, CATexture* ca_texture, ID3D11Device* pDevice)
{
    auto iter = (m_pTexture_Map->find(texture_full_path));
    if (iter == m_pTexture_Map->end())//없으면 파일추출
    {
        if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pDevice, texture_full_path, NULL, NULL, &ca_texture->m_pSRV, NULL)))
        {
            EM(hr, Create_Shader_Resource_View_From_File, CADevice_Helper);
            return false;

        }
        if (ca_texture != NULL)
        {
            m_pTexture_Map->insert(make_pair(texture_full_path, ca_texture));
        }
       
        return true;
    }//있으면 있는 리소스 리턴?
   
    
}

void CADevice_Helper::Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV,int start_slot, ID3D11DeviceContext* pContext)
{
    if (pSRV == NULL)
    {
        MessageBox(g_hWnd, L"Set_SRV_To_PS", L"CADevice_Helper", MB_OK);
        return;
    }
    pContext->PSSetShaderResources(start_slot, 1, &pSRV);

}



void CADevice_Helper::Set_Const_Buffer(ID3D11Buffer* pConst_buffer, void* const_data, UINT size, ID3D11DeviceContext* pContext)
{
    D3D11_MAPPED_SUBRESOURCE MappedResourse;
    //Map  
    pContext->Map(pConst_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);

    void* data = MappedResourse.pData;
    memcpy(data, const_data, size);

    pContext->Unmap(pConst_buffer, 0);
}

void CADevice_Helper::Set_Pipe_Line(ID3D11DeviceContext* pContext,ID3D11InputLayout* pInput_Layout,ID3D11Buffer* pVertex_buffer,UINT VB_size , ID3D11Buffer* pIndex_Buffer , ID3D11Buffer* pConst_Buffer , ID3D11VertexShader* pVertex_Shader , ID3D11HullShader* pHull_Shader , ID3D11DomainShader* pDomain_Shader , ID3D11GeometryShader* pGeometry_Shader , ID3D11PixelShader* pPixel_Shader )
{
    if (pInput_Layout)
    {
        pContext->IASetInputLayout(pInput_Layout);
    }
    //Num_of_buffers, start_slot 버텍스,상수 버퍼별로 준비해야. offset도 생각해봐야겟
    //pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    if (pVertex_buffer)
    {
        UINT strid = VB_size;
        UINT offset = 0;
        pContext->IASetVertexBuffers(0, 1, &pVertex_buffer, &strid, &offset);

    }
    if (pIndex_Buffer)
    {
        pContext->IASetIndexBuffer(pIndex_Buffer, DXGI_FORMAT_R32_UINT, 0);
    }
    if (pConst_Buffer)
    {
        pContext->VSSetConstantBuffers(0, 1, &pConst_Buffer);
    }
    if (pVertex_Shader)
    {
        pContext->VSSetShader(pVertex_Shader, NULL, 0);
    }
    if (pHull_Shader)
    {
        pContext->HSSetShader(NULL, NULL, 0);
    }
    if (pDomain_Shader)
    {
        pContext->DSSetShader(NULL, NULL, 0);
    }
    if (pGeometry_Shader)
    {
        pContext->GSSetShader(NULL, NULL, 0);
    }
    if (pPixel_Shader)
    {
        pContext->PSSetShader(pPixel_Shader, NULL, 0);
    }
}



//
//bool CADevice_Helper::Init()
//{
//
//}
//bool CADevice_Helper::Frame()
//{
//   
//}
//bool CADevice_Helper::Render()
//{
//   
//}
//bool CADevice_Helper::Release()
//{
//   
//}
//
CADevice_Helper::CADevice_Helper()
{
    /*m_pFactory = pfactory;*/
  //  m_pDevice = CADevice::m_pDevice;
  //  m_pImmediate_Device_Context = CADevice::m_pImmediate_Device_Context;
}
//CADevice_Helper::CADevice_Helper(map<wstring, ID3D11Texture2D*>* pTexture_Map/*,IDXGIFactory* pfactory,*/,
//    ID3D11Device* pdevice,
//    ID3D11DeviceContext* pimmediate_device_context)
//{
//    /*m_pFactory = pfactory;*/
//   // m_pDevice = pdevice;
//   // m_pImmediate_Device_Context = pimmediate_device_context;
//}

CADevice_Helper::~CADevice_Helper()
{
}
