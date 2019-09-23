// AAA_Export.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//
#include "stdafx.h"
#define AAA_CLASS_ID Class_ID(0x35814db8, 0x363c672c)

class myexport : public SceneExport
{
public:
    myexport();
    ~myexport();
    virtual int				ExtCount();
    virtual const MCHAR *	Ext(int n);
    virtual const MCHAR *	LongDesc();
    virtual const MCHAR *	ShortDesc();
    virtual const MCHAR *	AuthorName();
    virtual const MCHAR *	CopyrightMessage();
    virtual const MCHAR *	OtherMessage1();
    virtual const MCHAR *	OtherMessage2();
    virtual unsigned int	Version();
    virtual void			ShowAbout(HWND hWnd);
    virtual int				DoExport(const MCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);
    virtual BOOL			SupportsOptions(int ext, DWORD options) { UNUSED_PARAM(ext); UNUSED_PARAM(options); return FALSE; }


};

myexport::myexport()
{
}

myexport::~myexport()
{
}

class myexportdesc : public ClassDesc2
{
public:
    myexportdesc();
    ~myexportdesc();

    virtual int IsPublic() { return TRUE; }
    virtual void* Create(BOOL /*loading = FALSE*/) { return new myexport(); }
    virtual const TCHAR *	ClassName() { return _T("kgcaExporter100"); }
    virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
    virtual Class_ID ClassID() { return AAA_CLASS_ID; }
    virtual const TCHAR* Category() { return _T("kgcaExporter"); }
    virtual const TCHAR* InternalName() { return _T("tbsExportClassDesc"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle




};

myexportdesc::myexportdesc()
{
}

myexportdesc::~myexportdesc()
{
}



ClassDesc2* GetExportDesc() {
    static myexportdesc tbsExportDesc;
    return &tbsExportDesc;
}

int myexport::ExtCount()
{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
    return 1;
}

const TCHAR *myexport::Ext(int /*i*/)
{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
    return _T("AAAA");
}

const TCHAR *myexport::LongDesc()
{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
    return _T("KGCA Expoter 2.0");
}

const TCHAR *myexport::ShortDesc()
{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
    return _T("KGCAExpoter");
}

const TCHAR *myexport::AuthorName()
{
#pragma message(TODO("Return ASCII Author name"))
    return _T("PROKVIP");
}

const TCHAR *myexport::CopyrightMessage()
{
#pragma message(TODO("Return ASCII Copyright message"))
    return _T("");
}

const TCHAR *myexport::OtherMessage1()
{
    //TODO: Return Other message #1 if any
    return _T("");
}

const TCHAR *myexport::OtherMessage2()
{
    //TODO: Return other message #2 in any
    return _T("");
}

unsigned int myexport::Version()
{
#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
    return 100;
}

void myexport::ShowAbout(HWND /*hWnd*/)
{
    // Optional
}


int	myexport::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i,
    BOOL suppressPrompts, DWORD options)
{
    return FALSE;
}
