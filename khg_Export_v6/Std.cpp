#include "stdafx.h"
#include "Std.h"



std::wstring Exprot_Obj::m_filename;
Interval Exprot_Obj::m_Interval;
Interface* Exprot_Obj::m_pMax=nullptr;   //max �������̽�. dx�� ����̽� �̻��� ���;
INode* Exprot_Obj::m_pRootNode=nullptr; //Ʈ���ε� �׷��� ���� �̶� ����ȴ���.
Scene Exprot_Obj::m_Scene;
std::vector<INode*> Exprot_Obj::m_ObjList;
std::vector<Mtl*>    Exprot_Obj::m_MaterialList;//���͸��� ����Ʈ..?
std::vector<MtlInfo> Exprot_Obj::m_MtlInfoList; //Mtl* ���� ������
std::vector<tempMesh> Exprot_Obj::m_tempMesh_List;
