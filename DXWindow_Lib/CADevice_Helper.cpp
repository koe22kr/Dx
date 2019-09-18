#include "CADevice_Helper.h"
#include "CADx_State.h"
namespace DX
{

    bool CADevice_Helper::Create_Vertex_Buffer(void* data, int num, int size, ID3D11Buffer*& pVertex_buffer, ID3D11Device* pDevice)
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

        BD.ByteWidth = size * num;
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
    //ID3D11Buffer* temp_buffer;
    //v.Attach
    bool CADevice_Helper::Create_Vertex_Buffer_Self(std::vector<PNCT_VERTEX>* m_Vertex_List, ID3D11Device* pDevice)
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

        BD.ByteWidth = m_Vertex_List->size() * sizeof(PNCT_VERTEX);
        BD.Usage = D3D11_USAGE_DEFAULT;
        BD.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        BD.CPUAccessFlags = 0;
       /* BD.MiscFlags = 0;
        BD.StructureByteStride = 0;   /*///

        D3D11_SUBRESOURCE_DATA SD;
        ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));

        ID3D11Buffer* temp_buffer;
        SD.pSysMem = &m_Vertex_List->at(0);
        if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &temp_buffer)))
        {
            MessageBox(g_hWnd, L"Create_Vertex_Buffer_Fail", L"CADevice_Helper", MB_OK);
            return false;
        }
        m_cVertex_Buffer.Attach(temp_buffer);
        return true;
    }

    bool CADevice_Helper::Create_Index_Buffer(void* Idata, int index_num, int index_size, ID3D11Buffer*& pIndex_buffer, ID3D11Device* pDevice)
    {
        D3D11_BUFFER_DESC BD;
        ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
        BD.Usage = D3D11_USAGE_DEFAULT;
        BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
        BD.ByteWidth = index_size * index_num;
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

    bool CADevice_Helper::Create_Index_Buffer_Self(std::vector<DWORD>* m_Index_List, ID3D11Device* pDevice)
    {

        D3D11_BUFFER_DESC BD;
        ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
        BD.Usage = D3D11_USAGE_DEFAULT;
        BD.BindFlags = D3D11_BIND_INDEX_BUFFER;
        BD.ByteWidth = m_Index_List->size() * sizeof(DWORD);
        BD.CPUAccessFlags = 0;
        BD.MiscFlags = 0;
        BD.StructureByteStride = 0;///

        ID3D11Buffer* temp_buffer;

        D3D11_SUBRESOURCE_DATA SD;
        ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
        SD.pSysMem = &m_Index_List->at(0);

        if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &temp_buffer)))
        {
            MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
            return false;
        }
        m_cIndex_Buffer.Attach(temp_buffer);
        return true;
    }


    bool CADevice_Helper::Create_Vertex_And_Index_Buffer(void* vertex_array, int vertex_num, int vertex_size, ID3D11Buffer*& pVertex_Buffer, void* index_array, int index_num, int index_size, ID3D11Buffer*& pIndex_Buffer)
    {
        Create_Vertex_Buffer(vertex_array, vertex_num, vertex_size, pVertex_Buffer);
        Create_Index_Buffer(index_array, index_num, index_size, pIndex_Buffer);
        return true;
    }
    bool CADevice_Helper::Create_Vertex_And_Index_Buffer_Self(std::vector<PNCT_VERTEX>* m_Vertex_List, std::vector<DWORD>* m_Index_List, ID3D11Device* pDevice)
    {
        Create_Vertex_Buffer_Self(m_Vertex_List, pDevice);
        Create_Index_Buffer_Self(m_Index_List, pDevice);
        return true;
    }

    bool CADevice_Helper::Create_Const_Buffer(ID3D11Buffer*& pConst_buffer, void* Const_data, int num, int size, ID3D11Device* pDevice)
    {
        D3D11_BUFFER_DESC BD;
        ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
        BD.Usage = D3D11_USAGE_DEFAULT;
        BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        BD.ByteWidth = num * size;
        BD.CPUAccessFlags = 0;
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

    bool CADevice_Helper::Create_Const_Buffer_Self(void* Const_data, int num, int size, ID3D11Device* pDevice)
    {
        D3D11_BUFFER_DESC BD;
        ZeroMemory(&BD, sizeof(D3D11_BUFFER_DESC));
        BD.Usage = D3D11_USAGE_DEFAULT;
        BD.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        BD.ByteWidth = num * size;
        BD.CPUAccessFlags = 0;
        BD.MiscFlags = 0;
        BD.StructureByteStride = 0;///
        
        ID3D11Buffer* temp_buffer;

        if (Const_data != nullptr)
        {
            D3D11_SUBRESOURCE_DATA SD;
            ZeroMemory(&SD, sizeof(D3D11_SUBRESOURCE_DATA));
            SD.pSysMem = Const_data;

            if (FAILED(hr = pDevice->CreateBuffer(&BD, &SD, &temp_buffer)))
            {
                MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
                return false;
            }
        }
        else
        {
            if (FAILED(hr = pDevice->CreateBuffer(&BD, NULL, &temp_buffer)))
            {
                MessageBox(g_hWnd, L"Create_Index_Buffer", L"CADevice_Helper", MB_OK);
                return false;
            }
        }
        m_cConst_Buffer.Attach(temp_buffer);
        return true;
    }

    bool CADevice_Helper::Load_VS_And_Set_Input_Layout(const WCHAR* VS_compiler, ID3D11VertexShader*& pVertex_Shader, ID3D11InputLayout*& pInput_Layout, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice)
    {
        ID3D10Blob* pVS;
        ID3D10Blob* pEM;

        if (FAILED(hr = D3DX11CompileFromFile(VS_compiler, NULL, NULL, VS_name, "vs_5_0",
            NULL, m_nShader_Flag2, NULL, &pVS, &pEM, NULL)))
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

    bool CADevice_Helper::Load_VS_And_Set_Input_Layout_Self(const WCHAR* VS_compiler, const char* VS_name, const D3D11_INPUT_ELEMENT_DESC* Lay_Out, UINT element_count, ID3D11Device* pDevice)
    {
        ID3D10Blob* pVS;
        ID3D10Blob* pEM;

        if (FAILED(hr = D3DX11CompileFromFile(VS_compiler, NULL, NULL, VS_name, "vs_5_0",
            NULL, NULL, NULL, &pVS, &pEM, NULL)))
        {
            MessageBoxA(g_hWnd, (char*)pEM->GetBufferPointer(), "CADevice_Helper", MB_OK);
            return false;
        }
        ID3D11VertexShader* temp_vs;
        if (FAILED(hr = pDevice->CreateVertexShader(
            /* [ __in  const void *pShaderBytecode] */
            pVS->GetBufferPointer(),
            /* [__in  SIZE_T BytecodeLength,] */
            pVS->GetBufferSize(),
            /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
            NULL,
            /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
            &temp_vs
        )))
        {
            MessageBox(g_hWnd, L"Create_Vertex_Shader", L"CADevice_Helper", MB_OK);
            return false;
        }
        m_cVertex_Shader.Attach(temp_vs);
        ////////////////
         //   LPCSTR SemanticName;
         //   UINT SemanticIndex;
         //   DXGI_FORMAT Format;
         //   UINT InputSlot;
         //   UINT AlignedByteOffset;
         //   D3D11_INPUT_CLASSIFICATION InputSlotClass;
         //   UINT InstanceDataStepRate;

        ID3D11InputLayout* temp_il;
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
            &temp_il
        )))
        {
            MessageBox(g_hWnd, L"Create_Input_Layout", L"CADevice_Helper", MB_OK);
            return false;
        }
        m_cInput_Layout.Attach(temp_il);
        ////
        if (pVS != nullptr)pVS->Release();
        if (pEM != nullptr)pEM->Release();
        return true;
    }

    bool CADevice_Helper::Load_PS(const WCHAR* PS_compiler, ID3D11PixelShader*& pPixel_Shader, const char* PS_name, ID3D11Device* pDevice)
    {
        ID3D10Blob* pPS;
        ID3D10Blob* pEM;

        if (FAILED(hr = D3DX11CompileFromFile(PS_compiler, NULL, NULL, PS_name, "ps_5_0",
            NULL, m_nShader_Flag2, NULL, &pPS, &pEM, NULL)))
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

    bool CADevice_Helper::Load_PS_Self(const WCHAR* PS_compiler, const char* PS_name, ID3D11Device* pDevice)
    {
        ID3D10Blob* pPS;
        ID3D10Blob* pEM;


        
        if (FAILED(hr = D3DX11CompileFromFile(PS_compiler, NULL, NULL, PS_name, "ps_5_0",
            NULL, NULL, NULL, &pPS, &pEM, NULL)))
        {
            MessageBox(g_hWnd, L"D3DX11Compile_From_File_Fail", L"CADevice_Helper", MB_OK);
            return false;
        }

        ID3D11PixelShader* temp_ps;
        if (FAILED(hr = pDevice->CreatePixelShader(
            /* [ __in  const void *pShaderBytecode] */
            pPS->GetBufferPointer(),
            /* [__in  SIZE_T BytecodeLength,] */
            pPS->GetBufferSize(),
            /* [__in_opt  ID3D11ClassLinkage *pClassLinkage,] */
            NULL,
            /* [ __out_opt  ID3D11VertexShader **ppVertexShader] */
            &temp_ps
        )))
        {
            MessageBox(g_hWnd, L"Create_Pixel_Shader", L"CADevice_Helper", MB_OK);
            return false;
        }
        m_cPixel_Shader.Attach(temp_ps);
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
    //    CADevice::m_Texture_Map.insert(make_pair(KEY, pTexture_2D));
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
    //    auto iter = CADevice::m_Texture_Map.find(texture_full_path);
    //    if (iter == CADevice::m_Texture_Map.end())
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

    int CADevice_Helper::Load_Shader_Resource_View_From_File(const TCHAR* texture_full_path, CATexture* ca_texture, UINT KEY, ID3D11Device* pDevice)
    {
        //auto iter = (CADevice::m_Texture_Map.find(texture_full_path));
        if (CADevice::m_Texture_Map.size() != 0)
        {
            for (auto target : (CADevice::m_Texture_Map))
            {
                if (texture_full_path == target.second->m_File_Full_Path)
                {
                    ca_texture = target.second;
                    return KEY;
                }
            }
        }

        if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pDevice, texture_full_path, NULL, NULL, &ca_texture->m_pSRV, NULL)))
        {
            EM(hr, Load_Shader_Resource_View_From_File, CADevice_Helper);
            return -1;
        }
        if (ca_texture != NULL)
        {
            auto result = CADevice::m_Texture_Map.insert(make_pair(KEY, ca_texture));
            if (result.second == true)
            {
                result.first->second->m_Index = KEY;
                result.first->second->m_File_Full_Path = texture_full_path;
            }
        }

        return KEY;
    }

    int CADevice_Helper::Load_Shader_Resource_View_From_File_Self(const TCHAR* texture_full_path, UINT KEY, ID3D11Device* pDevice)
    {

        //auto iter = (CADevice::m_Texture_Map.find(texture_full_path));
        if (CADevice::m_Texture_Map.size() != 0)
        {
            for (auto target : (CADevice::m_Texture_Map))
            {
                if (texture_full_path == target.second->m_File_Full_Path)
                {
                    m_CATexture = *target.second;
                    return KEY;
                }
            }
        }

        ID3D11ShaderResourceView* temp_SRV;

        if (FAILED(hr = D3DX11CreateShaderResourceViewFromFile(pDevice, texture_full_path, NULL, NULL, &m_CATexture.m_pSRV, NULL)))
        {
            EM(hr, Load_Shader_Resource_View_From_File, CADevice_Helper);

            return -1;
        }

        
            auto result = CADevice::m_Texture_Map.insert(make_pair(KEY, &m_CATexture));
            if (result.second == true)
            {
                result.first->second->m_Index = KEY;
                result.first->second->m_File_Full_Path = texture_full_path;
            }
            return KEY;
        


    }
    void CADevice_Helper::Set_SRV_To_PS(ID3D11ShaderResourceView* pSRV, UINT start_slot, ID3D11DeviceContext* pContext)
    {
        if (pSRV != NULL)
        {
            pContext->PSSetShaderResources(start_slot, 1, &pSRV);
            
            return;
        }
        MessageBox(g_hWnd, L"Set_SRV_To_PS", L"CADevice_Helper", MB_OK);

    }
    void CADevice_Helper::Set_SRV_To_PS_Self(UINT start_slot, ID3D11DeviceContext* pContext)
    {
        if (m_CATexture.m_pSRV != NULL)
        {
            pContext->PSSetShaderResources(start_slot, 1, &m_CATexture.m_pSRV);
            return;
        }
        //MessageBox(g_hWnd, L"Set_SRV_To_PS", L"CADevice_Helper", MB_OK);

    }


    void CADevice_Helper::Set_Const_Buffer(ID3D11Buffer* pConst_buffer, void* const_data, UINT size, ID3D11DeviceContext* pContext)
    {
       // D3D11_MAPPED_SUBRESOURCE MappedResourse;
        if (pConst_buffer != NULL)
        {
            pContext->UpdateSubresource(pConst_buffer, 0, NULL, const_data, 0, 0);
        }
        //Map
        /*pContext->Map(pConst_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);

        void* data = MappedResourse.pData;
        memcpy(data, const_data, size);

        pContext->Unmap(pConst_buffer, 0);*/
    }

    void CADevice_Helper::Set_Const_Buffer_Self(void* const_data, UINT size, ID3D11DeviceContext* pContext)
    {
        //D3D11_MAPPED_SUBRESOURCE MappedResourse;
        if (const_data != nullptr)
        {
            pContext->UpdateSubresource(m_cConst_Buffer.Get(), 0, NULL, const_data, 0, 0);
        }
        ////Map  
        //pContext->Map(m_cConst_Buffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResourse);

        //void* data = MappedResourse.pData;
        //memcpy(data, const_data, size);

        //pContext->Unmap(m_cConst_Buffer.Get(), 0);
    }

    void CADevice_Helper::Set_Pipe_Line(ID3D11DeviceContext* pContext, ID3D11InputLayout* pInput_Layout, ID3D11Buffer* pVertex_buffer, UINT VB_size, ID3D11Buffer* pIndex_Buffer, ID3D11Buffer* pConst_Buffer, ID3D11VertexShader* pVertex_Shader, ID3D11HullShader* pHull_Shader, ID3D11DomainShader* pDomain_Shader, ID3D11GeometryShader* pGeometry_Shader, ID3D11PixelShader* pPixel_Shader)
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

    void CADevice_Helper::Set_Pipe_Line_Self(ID3D11DeviceContext* pContext, UINT VB_size)
    {
        if (m_cInput_Layout)
        {
            pContext->IASetInputLayout(m_cInput_Layout.Get());
        }
        //Num_of_buffers, start_slot 버텍스,상수 버퍼별로 준비해야. offset도 생각해봐야겟
        pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        if (m_cVertex_Buffer)
        {
            UINT strid = VB_size;
            UINT offset = 0;
            pContext->IASetVertexBuffers(0, 1, m_cVertex_Buffer.GetAddressOf(), &strid, &offset);

        }
        if (m_cIndex_Buffer)
        {
            pContext->IASetIndexBuffer(m_cIndex_Buffer.Get(), DXGI_FORMAT_R32_UINT, 0);
        }
        if (m_cConst_Buffer)
        {
            pContext->VSSetConstantBuffers(0, 1, m_cConst_Buffer.GetAddressOf());
        }
        if (m_cVertex_Shader)
        {
            pContext->VSSetShader(m_cVertex_Shader.Get(), NULL, 0);
        }

        if (m_cPixel_Shader)
        {
            pContext->PSSetShader(m_cPixel_Shader.Get(), NULL, 0);
        }
    }


    bool CADevice_Helper::Render(ID3D11DeviceContext* pContext,UINT draw_count)
    {
        PreRender(pContext);
        PostRender_And_Set_Draw_OPT(draw_count);
        PostRender(pContext);
        return true;
    }

    bool CADevice_Helper::Render(UINT draw_count, UINT vertex_location, UINT index_location, ID3D11DeviceContext* pContext)
    {
        PreRender(pContext);
        PostRender_And_Set_Draw_OPT(draw_count, vertex_location, index_location, pContext);
        PostRender();
        return true;
    }

    bool CADevice_Helper::PreRender(ID3D11DeviceContext* pContext, UINT VB_size, UINT SRV_start_slot)
    {
        Set_RSState(CADevice::m_pImmediate_Device_Context, DX::CADx_State::m_pRSSolid_Frame);
        Set_SState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pSSWrap_Linear);
        Set_DSState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pDSSDepth_Enable);
        Set_BState(CADevice::m_pImmediate_Device_Context, CADx_State::m_pAlpha_Blend);
        Set_SRV_To_PS_Self(SRV_start_slot, pContext);
        Set_Pipe_Line_Self(pContext, VB_size);
        return true;
    }

    bool CADevice_Helper::PostRender(ID3D11DeviceContext* pContext)
    {
        m_CATexture.Draw(pContext);
        return true;
    }

    bool CADevice_Helper::PostRender_And_Set_Draw_OPT(UINT draw_count, UINT vertex_location, UINT index_location, ID3D11DeviceContext* pContext)
    {
        m_CATexture.Set_Draw_OPT(draw_count, vertex_location, index_location);
        m_CATexture.Draw(pContext);
        return true;
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
        
            m_nShader_Flag2 = D3DCOMPILE_ENABLE_STRICTNESS;
#ifdef _DEBUG
            m_nShader_Flag2 |= D3DCOMPILE_DEBUG;
            m_nShader_Flag2 |= D3DCOMPILE_SKIP_OPTIMIZATION;
#endif // DEBUG


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


}