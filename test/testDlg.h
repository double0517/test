
// testDlg.h : ͷ�ļ�
//
#include "afxcmn.h"
#import "C://Program Files//Common Files//System//ado//msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")
#pragma once


// CtestDlg �Ի���
class CtestDlg : public CDialogEx
{
// ����
public:
	CtestDlg(CWnd* pParent = NULL);	// ��׼���캯��

	_ConnectionPtr m_pConnection; // ���ݿ�
    _RecordsetPtr m_pRecordset; // ����
    _CommandPtr m_pCommand; // ��¼

// �Ի�������
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedAdd();
	CListCtrl m_list;
};
