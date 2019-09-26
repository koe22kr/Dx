// khg_Export.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//
#include "stdafx.h"
#define khgExport_CLASS_ID Class_ID(0x390f1b7a, 0x56d52e5b)
#include "khgWriter.h"


class khg_Export : public SceneExport 
{
public:
    khgWriter m_khgWriter;
    khg_Export();
    ~khg_Export();
    int				ExtCount();					// Number of extensions supported
    const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
    const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
    const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
    const TCHAR *	AuthorName();				// ASCII Author name
    const TCHAR *	CopyrightMessage();			// ASCII Copyright message
    const TCHAR *	OtherMessage1();			// Other message #1
    const TCHAR *	OtherMessage2();			// Other message #2
    unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
    void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
    BOOL SupportsOptions(int ext, DWORD options);
    int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);
};
khg_Export::khg_Export()
{

}

khg_Export::~khg_Export()
{

}


class khgExportClassDesc : public ClassDesc2
{
public:
    virtual int IsPublic() { return TRUE; }
    virtual void* Create(BOOL /*loading = FALSE*/) { return new khg_Export(); }
    virtual const TCHAR *	ClassName() { return _T("khg_Export100"); }
    virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
    virtual Class_ID ClassID() { return khgExport_CLASS_ID; }
    virtual const TCHAR* Category() { return _T("khg_Export"); }
    virtual const TCHAR* InternalName() { return _T("khgExportClassDesc"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle

};


ClassDesc2* GetExportDesc() {
    static khgExportClassDesc tbsExportDesc;
    return &tbsExportDesc;
}


//--- tbsExport2016 -------------------------------------------------------


int khg_Export::ExtCount()
{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
    return 1;
}

const TCHAR *khg_Export::Ext(int /*i*/)
{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
    return _T("MD");
}

const TCHAR *khg_Export::LongDesc()
{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
    return _T("khg Expoter 100");
}

const TCHAR *khg_Export::ShortDesc()
{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
    return _T("khgExpoter");
}

const TCHAR *khg_Export::AuthorName()
{
#pragma message(TODO("Return ASCII Author name"))
    return _T("Author");
}

const TCHAR *khg_Export::CopyrightMessage()
{
#pragma message(TODO("Return ASCII Copyright message"))
    return _T("");
}

const TCHAR *khg_Export::OtherMessage1()
{
    //TODO: Return Other message #1 if any
    return _T("");
}

const TCHAR *khg_Export::OtherMessage2()
{
    //TODO: Return other message #2 in any
    return _T("");
}

unsigned int khg_Export::Version()
{
#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
    return 100;
}

void khg_Export::ShowAbout(HWND /*hWnd*/)
{
    // Optional
}

BOOL khg_Export::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
#pragma message(TODO("Decide which options to support.  Simply return true for each option supported by each Extension the exporter supports."))
    return TRUE;
}


int	khg_Export::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i,  //인터페이스 뭐든 다 건드릴 수 있다.
    BOOL suppressPrompts, DWORD options)
{
    m_khgWriter.Set(name, i);
    m_khgWriter.Export();
    return true;
}



