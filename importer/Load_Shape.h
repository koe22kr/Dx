#pragma once
#include "CADx_Shape.h"
#include <iostream>
#include <fstream>
#include "CADx_Model2.h"
#include <vector>
#include <string>

class Load_Shape : public DX::CADx_Shape_Box
{
public:
    std::vector<DX::PNCT_VERTEX2>* m_pnct_List;
    std::map<UINT, wstring> m_filename_map;

    //m_Index_List;
    void Load(const char* maxconvertfile);

public:
    ////////////////
    HRESULT CreateVertexData();
    HRESULT CreateIndexData();

    Load_Shape();
    virtual ~Load_Shape();
};

