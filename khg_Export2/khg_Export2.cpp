// khg_Export2.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//
//dle익스포터   dlu유틸리티
#include "stdafx.h"
#define khgExport_CLASS_ID Class_ID(0x487d061e, 0x42d7658)
class khgExport : public SceneExport
{
public:
    khgExport();
    ~khgExport();
   int				ExtCount();
   const TCHAR *	Ext(int n);	        	// Extension #n (i.e. "3DS")
   const TCHAR *	LongDesc();		        // Long ASCII description (i.e. "Autodesk 3D Studio File")
   const TCHAR *	ShortDesc();			// Short ASCII description (i.e. "3D Studio")
   const TCHAR *	AuthorName();			// ASCII Author name
   const TCHAR *	CopyrightMessage();		// ASCII Copyright message
   const TCHAR *	OtherMessage1();	    // Other message #1
   const TCHAR *	OtherMessage2();    	// Other message #2
   unsigned int	Version();		    	// Version number * 100 (i.e. v3.01 = 301)
   void			ShowAbout(HWND hWnd);	// Show DLL's "About..." box
    BOOL SupportsOptions(int ext, DWORD options);
    virtual int				DoExport(const MCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);	// Export file
};

khgExport::khgExport()
{

}
khgExport::~khgExport()
{

}
class khgExport_Class_Desc : public ClassDesc2
{
public:
    virtual int IsPublic() { return TRUE; };
    //virtual void* Create(BOOL/*loading = FALSE*/)
    //{
    //    return new khgExport();
    //}
    virtual void* Create(BOOL /*loading = FALSE*/) { return new khgExport(); }
    virtual const TCHAR *	ClassName() { return _T("khgExporter100"); }
    virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }  //고정
    virtual Class_ID ClassID() { return khgExport_CLASS_ID; }  //발급할 id 유틸로 만들어야함
    virtual const TCHAR* Category() { return _T("khgExporter"); }
    virtual const TCHAR* InternalName() { return _T("khgExportClassDesc"); }	// returns fixed parsable name (scripter-visible name)
    virtual HINSTANCE HInstance() { return hInstance; }					// returns owning module handle

};
ClassDesc2* GetExportDesc()
{
    static khgExport_Class_Desc khgexportdesc;
    return &khgexportdesc;
}





int				khgExport::ExtCount()//ext == 확장자
{
    return true;
}
const MCHAR *	khgExport::Ext(int n) //출력파일 확장자
{
    return _T("KHG");
}
const MCHAR *	khgExport::LongDesc()
{
    return _T("KHG exporter_T36");
}
const MCHAR *	khgExport::ShortDesc()
{
    return _T("KHG exporter");
}
const MCHAR *	khgExport::AuthorName()
{
    return _T("KHG");
}
const MCHAR *	khgExport::CopyrightMessage()
{
    return _T("");
}
const MCHAR *	khgExport::OtherMessage1()
{
    return _T("");
}
const MCHAR *	khgExport::OtherMessage2()
{
    return _T("");
}
unsigned int	khgExport::Version()
{
    return 100;
}
void			khgExport::ShowAbout(HWND hWnd)
{

}

BOOL khgExport::SupportsOptions(int /*ext*/, DWORD /*options*/)
{
    return TRUE;
}
int			khgExport::DoExport(const MCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)
{
    return TRUE;
}