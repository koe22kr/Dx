#include "Sample.h"


bool Sample::Create_Vertex_Buffer_F3(FLOAT3* float_2d, int obj_num, ID3D11Buffer*& pVertex_buffer)
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

    BD.ByteWidth = sizeof(FLOAT3)*obj_num;
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;   ///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));

    SD.pSysMem = float_2d;
    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, &SD, &pVertex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"Device", MB_OK);
        return false;
    }

    return true;
}


bool Sample::Create_Index_Buffer(DWORD* Idata, int m_Index_Num, ID3D11Buffer*& pIndex_buffer)
{
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DEFAULT;
    BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
    BD.ByteWidth = sizeof(DWORD)*m_Index_Num;
    BD.CPUAccessFlags = 0;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = Idata;

    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, &SD, &pIndex_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device", MB_OK);
        return false;
    }
    return true;
}

bool Sample::Create_Const_Buffer(ID3D11Buffer*& pConst_buffer)
{
    Const_Data cb;
    D3D11_BUFFER_DESC BD;
    ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
    BD.Usage = D3D11_USAGE_DYNAMIC;
    BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    BD.ByteWidth = sizeof(Const_Data);
    BD.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    BD.MiscFlags = 0;
    BD.StructureByteStride = 0;///

    D3D11_SUBRESOURCE_DATA SD;
    ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
    SD.pSysMem = (void*)&cb;

    if (FAILED(hr = m_pDevice->CreateBuffer(&BD, NULL, &pConst_buffer)))
    {
        MessageBox(g_hWnd, L"Create_Index_Buffer", L"Device", MB_OK);
        return false;
    }
    return true;
}

bool Sample::Load_VS_And_Set_Input_Layout(ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout,const char* VS_name, const D3D11_INPUT_ELEMENT_DESC Lay_Out)
{
    ID3D10Blob* pVS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"VS.vsh", NULL, NULL, VS_name, "vs_5_0",
        NULL, NULL, NULL, &pVS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
    }

    if (FAILED(hr = m_pDevice->CreateVertexShader(
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
        MessageBox(g_hWnd, L"Create_Vertex_Shader", L"Device", MB_OK);
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
    

    if (FAILED(hr = m_pDevice->CreateInputLayout(
        /* [__in_ecount(NumElements)  const D3D11_INPUT_ELEMENT_DESC *pInputElementDescs,] */
        &Lay_Out,
        /* [ __in_range(0, D3D11_IA_VERTEX_INPUT_STRUCTURE_ELEMENT_COUNT)  UINT NumElements] */
        1,
        /* [__in  const void *pShaderBytecodeWithInputSignature] */
        pVS->GetBufferPointer(),
        /* [__in  SIZE_T BytecodeLength] */
        pVS->GetBufferSize(),
        /* [__out_opt  ID3D11InputLayout **ppInputLayout] */
        &pInput_Layout
    )))
    {
        MessageBox(g_hWnd, L"Create_Input_Layout", L"Device", MB_OK);
        return false;
    }
    ////
    if (pVS != nullptr)pVS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}
bool Sample::Load_PS(ID3D11PixelShader*& pPixel_Shader, const char* PS_name)
{
    ID3D10Blob* pPS;
    ID3D10Blob* pEM;

    if (FAILED(hr = D3DX11CompileFromFile(L"PS.psh", NULL, NULL, PS_name, "ps_5_0",
        NULL, NULL, NULL, &pPS, &pEM, NULL)))
    {
        MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"Device", MB_OK);
        return false;
    }

    if (FAILED(hr = m_pDevice->CreatePixelShader(
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
        MessageBox(g_hWnd, L"Create_Pixel_Shader", L"Device", MB_OK);
        return false;
    }
    if (pPS != nullptr)pPS->Release();
    if (pEM != nullptr)pEM->Release();
    return true;
}

void Sample::Load_Texture_2D_From_File(const TCHAR* texture_full_path, int width, int height,UINT key)
{

    m_pBack_Buffer->GetDesc(&m_Back_Buffer_Desc);
    // 백버퍼에 복사하기 위한 원본 텍스쳐의 변환을 지정한다. 
    // CopyResource()함수를 사용할 경우이기 때문에 반드시 백 버퍼의 가로 및 세로 크기보다 크거나 같아야 한다.
    D3DX11_IMAGE_LOAD_INFO Load_Info;
    ZeroMemory(&Load_Info, sizeof(D3DX11_IMAGE_LOAD_INFO));
    Load_Info.Width = m_Back_Buffer_Desc.Width;
    Load_Info.Height = m_Back_Buffer_Desc.Height;
    Load_Info.Depth = D3DX11_DEFAULT;
    Load_Info.FirstMipLevel = 0;
    Load_Info.MipLevels = 1;	// 반드시 1 이여야 한다.
    Load_Info.Usage = D3D11_USAGE_DEFAULT;//D3D11_USAGE_STAGING;    
    Load_Info.CpuAccessFlags = 0;//D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    Load_Info.BindFlags = 0;
    Load_Info.MiscFlags = 0;
    Load_Info.Format = m_Back_Buffer_Desc.Format;
    Load_Info.Filter = D3DX11_FILTER_LINEAR;
    Load_Info.MipFilter = D3DX11_FILTER_NONE;

//    D3DX11CreateTextureFromFileW(
//        ID3D11Device*               pDevice,
//        LPCWSTR                     pSrcFile,
//        D3DX11_IMAGE_LOAD_INFO      *pLoadInfo,
//        ID3DX11ThreadPump*          pPump,
//        ID3D11Resource**            ppTexture,
//        HRESULT*                    pHResult);
    ID3D11Resource* pResource = NULL;
    
    ID3D11Texture2D* pTexture_2D = NULL;
    if (FAILED(hr = D3DX11CreateTextureFromFile(m_pDevice,texture_full_path,&Load_Info,NULL,&pResource,NULL)))
    {
            MessageBox(g_hWnd, L"Load_Texture_2D_From_File", L"Device", MB_OK);
            return;
    }
    
    pResource->QueryInterface(__uuidof(ID3D11Texture2D), (void**)pTexture_2D);
    m_Texture_Map.insert(make_pair(key,pTexture_2D));
    D3D11_TEXTURE2D_DESC test;
    pTexture_2D->GetDesc(&test);
    return;
}

bool Sample::Create_Vertex_And_Index(FLOAT3* vertex_array, int vertex_size, DWORD* index_array, int index_size, bool index_drawing)
{

    Create_Vertex_Buffer_F3(vertex_array, vertex_size, m_pVertex_Buffer);
    Create_Index_Buffer(index_array, index_size, m_pIndex_Buffer);


    if (index_drawing)
    {
        m_Index_Draw_Flag = true;
        m_Draw_Count = index_size;
    }
    else
    {
        m_Draw_Count = vertex_size;
    }

    return true;
}

bool Sample::Test()
{
/////Create_Vertex_And_Index/////////
   
    ///////////// 설정해야함.

    FLOAT3 TAG[] = {
{1.0f, 1.0f, 0.6f} ,
{1.0f, -1.0f, 0.6f},
{0.0f, 0.0f, 0.6f },
{1.0f, -1.0f, 0.6f},
{1.0f, 1.0f, 0.6f} ,
{-1.0f ,-1.0f,0.6f},
    };

    DWORD Idata[] = { 0,1,2,2,1,3 };

    
    
    Create_Vertex_And_Index(TAG, ARRAYSIZE(TAG), Idata, ARRAYSIZE(Idata),true);
    ////////// 
    Load_PS(m_pPixel_Shader, "PS");

    const D3D11_INPUT_ELEMENT_DESC Lay_Out = { "POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT ,0,0,D3D11_INPUT_PER_VERTEX_DATA ,0 };
    Load_VS_And_Set_Input_Layout(m_pVertex_Shader, m_pInput_Layout, "VS", Lay_Out);

    Set_Draw_Flag(true);

    Set_Start_Location(6, 0, 0);
    //로케이션 세팅을 한다면!

    return true;
}

void Sample::Set_Start_Location(int draw_count, int vertex_location, int index_location)
{ 
    m_Draw_Count = draw_count;
    m_Start_Vertex_Location = vertex_location;
    m_Start_Index_Location = index_location;
}

bool Sample::Init()
{


    m_pDevice = m_Device.m_pDevice;
    m_pImmediate_Device_Context = m_Device.m_pImmediate_Device_Context;
    m_pFactory = m_Device.m_pFactory;


    Create_Const_Buffer(m_pConst_Buffer);


    //////////////////////
    Test();



    return true;
}


void Sample::Set_Const_Buffer(float color_x, float color_y, float color_z, float color_w, float x, float y, float z, float w)
{
    m_Const_Data.Color = { color_x, color_y, color_z, color_w };
    m_Const_Data.x = x;
    m_Const_Data.y = y;
    m_Const_Data.z = z;
    m_Const_Data.w = w;
}

void Sample::Set_Const_Buffer(Const_Data& data)
{
    ZeroMemory(&m_Const_Data, sizeof(Const_Data));
    m_Const_Data = data;
}

void Sample::Set_Const_Buffer(const Const_Data& data)
{
    ZeroMemory(&m_Const_Data, sizeof(Const_Data));
    m_Const_Data = data;
}



void Sample::Test_Frame()
{
    //Sample용 테스트 상수버퍼 타임값.
    float fbtime = cosf(g_fGameTimer)*0.5f + 0.5f;
    Set_Const_Buffer(cosf(g_fGameTimer), sinf(g_fGameTimer), tanf(g_fGameTimer), 1.0f, fbtime);

   /* m_Const_Data.Color = D3DXVECTOR4(cosf(g_fGameTimer), sinf(g_fGameTimer), tanf(g_fGameTimer), 1.0f);
    m_Const_Data.x = fbtime;*/
    //Unmap
}

bool Sample::Frame()
{
    //m_Device.m_pDevice->CreateRasterizerState();
    
    
    Test_Frame();
    
   
    D3D11_MAPPED_SUBRESOURCE MappedResourse;
    //Map  
    m_pImmediate_Device_Context->Map(m_pConst_Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);
    Const_Data* pConstData = (Const_Data*)MappedResourse.pData;
    memcpy(pConstData, &m_Const_Data, sizeof(Const_Data));
    m_pImmediate_Device_Context->Unmap(m_pConst_Buffer, 0);


    return true;
}
bool Sample::Render()
{
    UINT strid = sizeof(FLOAT3);
    UINT offset = 0;

    m_pImmediate_Device_Context->IASetInputLayout(m_pInput_Layout);
    //Num_of_buffers, start_slot 버텍스,상수 버퍼별로 준비해야. offset도 생각해봐야겟
    m_pImmediate_Device_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


    if (m_pVertex_Buffer != NULL)
    {
        m_pImmediate_Device_Context->IASetVertexBuffers(0, 1, &m_pVertex_Buffer, &strid, &offset);

    }
    if (m_pIndex_Buffer != NULL)
    {
        m_pImmediate_Device_Context->IASetIndexBuffer(m_pIndex_Buffer, DXGI_FORMAT_R32_UINT, 0);
    }
    if (m_pConst_Buffer != NULL)
    {
        m_pImmediate_Device_Context->VSSetConstantBuffers(0, 1, &m_pConst_Buffer);
    }
    if (m_pVertex_Shader != NULL)
    {
        m_pImmediate_Device_Context->VSSetShader(m_pVertex_Shader, NULL, 0);
    }
    m_pImmediate_Device_Context->HSSetShader(NULL, NULL, 0);
    m_pImmediate_Device_Context->DSSetShader(NULL, NULL, 0);
    m_pImmediate_Device_Context->GSSetShader(NULL, NULL, 0);

    if (m_pVertex_Shader != NULL)
    {
        m_pImmediate_Device_Context->PSSetShader(m_pPixel_Shader, NULL, 0);
    }
    if (Draw_Flag)
    {
        Draw();
    }
    return true;
}

bool Sample::Draw()
{
    if (m_Index_Draw_Flag)
    {
        m_pImmediate_Device_Context->DrawIndexed(m_Draw_Count, m_Start_Index_Location, m_Start_Vertex_Location);
    }
    else
    {
        m_pImmediate_Device_Context->Draw(m_Draw_Count, m_Start_Vertex_Location);
    }
#ifdef _DEBUG
    if (m_Draw_Count == 0)
    {
        OutputDebugString(L"m_Draw_Count ==0; No_Draw_Device");
    }
#endif
    return true;
}
void Sample::Set_Box(int left, int top, int right, int bottom, int front, int back, int box_index)
{

}
void Sample::Custom_Draw(int posx, int posy, int texture_key,int box_index)
{
    // 원본 텍스처(m_pTextureKoala)의 전체 선택 및 일부 영역 선택
    //D3D11_BOX sourceRegion;
    //sourceRegion.left = left;					// 텍스처의 시작 위치 X
    //sourceRegion.right = right; // 텍스처의 끝   위치 X
    //sourceRegion.top = top;					// 텍스처의 시작 위치 Y
    //sourceRegion.bottom = bottom;// 텍스처의 끝   위치 Y
    //sourceRegion.front = front;
    //sourceRegion.back = back;
    // 원본 텍스처(m_pTextureKoala)의 전체 및 일부 영역을 백 버퍼의 0,0 위치에 복사함.
    // (주의)텍스처 영역이 백버퍼의 영역을 벗어나면 출력창에 경고 메세지가 발생함.
    
    m_pImmediate_Device_Context->CopySubresourceRegion(m_pBack_Buffer, 0, posx, posy, 0, m_Texture_Map[texture_key], 0, &m_Box_Vector[box_index]);

}

bool Sample::Release()
{
    if (m_pInput_Layout)m_pInput_Layout->Release();

    if (m_pVertex_Buffer)m_pVertex_Buffer->Release();
    if (m_pIndex_Buffer)m_pIndex_Buffer->Release();
    if (m_pConst_Buffer)m_pConst_Buffer->Release();

    if (m_pVertex_Shader)m_pVertex_Shader->Release();
    if (m_pPixel_Shader)m_pPixel_Shader->Release();

    m_pVertex_Buffer = NULL;
    m_pIndex_Buffer = NULL;
    m_pConst_Buffer = NULL;

    m_pInput_Layout = NULL;

    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;

    return true;
}


Sample::Sample()
{

    m_pInput_Layout = NULL;

    m_pVertex_Buffer = NULL;
    m_pIndex_Buffer = NULL;
    m_pConst_Buffer = NULL;

    m_pVertex_Shader = NULL;
    m_pPixel_Shader = NULL;
    m_pBack_Buffer = m_Device.m_pBack_Buffer;
    m_Back_Buffer_Desc = m_Device.m_Back_Buffer_Desc;

    bool m_Index_Draw_Flag = 0;
    int m_Start_Vertex_Location = 0;
    int m_Draw_Count = 0;
    int m_Start_Index_Location = 0;
}

Sample::~Sample()
{

}

WINRUN_DEFAULT