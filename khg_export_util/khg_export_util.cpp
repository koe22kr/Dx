// khg_export_util.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"

#define khg_export_util Class_ID(0x5f2756a, 0x235d6561)

extern ClassDesc2* GetExportDesc()
{

}

class khgExportClassDesc : public ClassDesc2
{
public:
    virtual int IsPublic() { return TRUE; }
    virtual void* Create(BOOL /*loading = FALSE*/) { return new khg_Export(); }
    virtual const TCHAR *	ClassName() { return _T("khg_Export100"); }
    virtual SClass_ID SuperClassID() { return UTILITY_CLASS_ID; }
    virtual Class_ID ClassID() { return khg_export_util; }
    virtual const TCHAR* Category() { return _T("khg_Export"); }
    virtual const TCHAR* InternalName() { return _T("khgExportClassDesc"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle

};


ClassDesc2* GetExportDesc() {
    static khgExportClassDesc tbsExportDesc;
    return &tbsExportDesc;
}
