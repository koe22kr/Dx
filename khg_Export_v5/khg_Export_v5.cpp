// khg_Export_v5.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//
//

#include "stdafx.h"
#define KHG_UTIL_CLASS_ID Class_ID(0x532703b3, 0x7d57553d)
#include "resource.h"
#include "khg_Skin_Exp.h"
#include "khg_Matrix_Exp.h"

extern HINSTANCE hInstance;


INT_PTR CALLBACK DlgProc(HWND hWnd,
    UINT msg, WPARAM wParam, LPARAM lParam);

class khg_Util : public UtilityObj
{
public:
    HWND m_hPanel;
    Interface* m_Objip;
    Interface* m_Skinip;
public:
    virtual void BeginEditParams(Interface *ip, IUtil *iu)
    {
        m_Objip = ip;
        m_hPanel = ip->AddRollupPage(hInstance,
            MAKEINTRESOURCE(IDD_DIALOG1),
            DlgProc,
            _T("khg_Exp"), 0);
    }
    virtual void EndEditParams(Interface *ip, IUtil *iu)
    {
        ip->DeleteRollupPage(m_hPanel);
    }
    virtual void DeleteThis()
    {
    }

    virtual void SelectionSetChanged(Interface *ip, IUtil *iu) 
    {
        m_Skinip = ip;


    }
    static khg_Util* Get()
    {
        static khg_Util theExp;
        return &theExp;
    }
    khg_Util() 
    {
        m_hPanel = NULL;
    };
    ~khg_Util() {};
};


class khgExportClassDesc : public ClassDesc2
{
public:
    virtual int IsPublic() { return TRUE; }
    virtual void* Create(BOOL /*loading = FALSE*/) { return khg_Util::Get(); }
    virtual const TCHAR *	ClassName() { return _T("khg_Util100"); }
    virtual SClass_ID SuperClassID() { return UTILITY_CLASS_ID; }
    virtual Class_ID ClassID() { return KHG_UTIL_CLASS_ID; }
    virtual const TCHAR* Category() { return _T("khg_Util"); }
    virtual const TCHAR* InternalName() { return _T("khg_Util_ClassDesc"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle

};


ClassDesc2* GetExportDesc() {
    static khgExportClassDesc khgExportDesc;
    return &khgExportDesc;
}

INT_PTR CALLBACK DlgProc(HWND hWnd,
    UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        break;
    case WM_DESTROY:
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case ID_khg_ObjExp:
        {
#pragma message (TODO("OBJ_EXP"))
            khg_Obj_Exp::Get()->Set(khg_Obj_Exp::Get()->SaveFileDlg(L"obx",L"khg_Obj"),khg_Util::Get()->m_Objip);
            khg_Obj_Exp::Get()->Export();
           


        }break;
        case ID_khg_SkinExp:
        {
#pragma message (TODO("SKIN_EXP"))
            khg_Skin_Exp::Get()->Set(khg_Skin_Exp::Get()->SaveFileDlg(L"skx", L"khg_Skin"), khg_Util::Get()->m_Skinip);
            khg_Skin_Exp::Get()->Export();
          

        }break;
        case ID_khg_MatrixExp:
        {
#pragma message (TODO("MATRIX_EXP"))
            khg_Matrix_Exp::Get()->Set(khg_Matrix_Exp::Get()->SaveFileDlg(L"mtx",L"khg_Matrix"), khg_Util::Get()->m_Objip);
            khg_Matrix_Exp::Get()->Export();
           

        }break;
        }
    }
    case WM_LBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MOUSEMOVE:
        GetCOREInterface()->RollupMouseMessage(
            hWnd, msg, wParam, lParam);
        break;
    default:
        return 0;
    }
    return 1;
}