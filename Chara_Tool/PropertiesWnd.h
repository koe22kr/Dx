﻿
#pragma once


class CPropertiesToolBar : public CMFCToolBar
{
public:
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPropertiesWnd : public CDockablePane
{
// 생성입니다.
public:
	CPropertiesWnd() noexcept;

	void AdjustLayout();
    //커스텀
    CMFCPropertyGridProperty* m_pBlend_Root;
    CMFCPropertyGridProperty* m_pBlend_Enable;
    CMFCPropertyGridProperty* m_pSrcBlend;
    CMFCPropertyGridProperty* m_pDestBlend;
    CMFCPropertyGridProperty* m_pBlendOp;
    CMFCPropertyGridProperty* m_pSrcBlendAlpha;
    CMFCPropertyGridProperty* m_pDestBlendAlpha;
    CMFCPropertyGridProperty* m_pBlendOpAlpha;
    CMFCPropertyGridProperty* m_pRenderTargetWriteMask;

    CMFCPropertyGridProperty* m_pRasterizer_Root;
    CMFCPropertyGridProperty* m_pFillMode;
    CMFCPropertyGridProperty* m_pCullMode;

    CMFCPropertyGridProperty* m_pSampler_Root;
    CMFCPropertyGridProperty* m_pFilter;
    CMFCPropertyGridProperty* m_pAddressU;
    CMFCPropertyGridProperty* m_pAddressV;
    CMFCPropertyGridProperty* m_pAddressW;

    CMFCPropertyGridProperty* m_pDepthStencil_Root;
    CMFCPropertyGridProperty* m_pDepth_Enable;
    CMFCPropertyGridProperty* m_pDepthWriteMask;
    CMFCPropertyGridProperty* m_pDepthFunc;
   // void Custom_Update_Property(CMFCPropertyGridProperty* target);
    void Update_Property_List();
// 특성입니다.
public:
	void SetVSDotNetLook(BOOL bSet)
	{
		m_wndPropList.SetVSDotNetLook(bSet);
		m_wndPropList.SetGroupNameFullWidth(bSet);
	}
   // 사용위해 공개시킴
    CMFCPropertyGridCtrl m_wndPropList;
protected:
	CFont m_fntPropList;
	CComboBox m_wndObjectCombo;
	CPropertiesToolBar m_wndToolBar;

// 구현입니다.
public:
	virtual ~CPropertiesWnd();

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnExpandAllProperties();
	afx_msg void OnUpdateExpandAllProperties(CCmdUI* pCmdUI);
	afx_msg void OnSortProperties();
	afx_msg void OnUpdateSortProperties(CCmdUI* pCmdUI);
	afx_msg void OnProperties1();
	afx_msg void OnUpdateProperties1(CCmdUI* pCmdUI);
	afx_msg void OnProperties2();
	afx_msg void OnUpdateProperties2(CCmdUI* pCmdUI);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnSettingChange(UINT uFlags, LPCTSTR lpszSection);

    afx_msg LRESULT OnPropertyChanged(WPARAM w, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

	void InitPropList();
	void SetPropListFont();

	int m_nComboHeight;
};

