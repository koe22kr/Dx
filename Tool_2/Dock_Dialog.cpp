// Dock_Dialog.cpp: 구현 파일
//

#include "stdafx.h"
#include "Tool_2.h"
#include "Dock_Dialog.h"
#include "afxdialogex.h"


// Dock_Dialog 대화 상자

IMPLEMENT_DYNAMIC(Dock_Dialog, CDialogEx)

Dock_Dialog::Dock_Dialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Dock_Dialog, pParent)
{

}

Dock_Dialog::~Dock_Dialog()
{
}

void Dock_Dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Dock_Dialog, CDialogEx)
END_MESSAGE_MAP()


// Dock_Dialog 메시지 처리기
