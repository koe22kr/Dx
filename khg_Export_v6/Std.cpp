#include "stdafx.h"
#include "Std.h"



std::wstring Exprot_Obj::m_filename;
Interval Exprot_Obj::m_Interval;
Interface* Exprot_Obj::m_pMax=nullptr;   //max 인터페이스. dx의 디바이스 이상의 기능;
INode* Exprot_Obj::m_pRootNode=nullptr; //트리인데 그래프 형식 이라 보면된다함.
Scene Exprot_Obj::m_Scene;
std::vector<INode*> Exprot_Obj::m_ObjList;
std::vector<Mtl*>    Exprot_Obj::m_MaterialList;//매터리얼 리스트..?
std::vector<MtlInfo> Exprot_Obj::m_MtlInfoList; //Mtl* 외의 정보들
std::vector<tempMesh> Exprot_Obj::m_tempMesh_List;
