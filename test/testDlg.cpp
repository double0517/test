
// testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "afxdialogex.h"
#import "C://Program Files//Common Files//System//ado//msado15.dll" no_namespace rename("EOF","adoEOF")rename("BOF","adoBOF")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CtestDlg �Ի���




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_list);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CtestDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_ADD, &CtestDlg::OnBnClickedAdd)
END_MESSAGE_MAP()


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_list.ModifyStyle(0, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0, _T("ѧ��"), LVCFMT_CENTER, 200);
	m_list.InsertColumn(1, _T("�γ̺�"), LVCFMT_CENTER, 150);
	m_list.InsertColumn(2, _T("ѧ��"), LVCFMT_CENTER,200);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CtestDlg::OnBnClickedConnect()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	::CoInitialize(NULL);   //��ʼ��OLE/COM�⻷�� 
	HRESULT hr = NULL;
	try
	{
		hr = m_pConnection.CreateInstance(_uuidof(Connection));//�������Ӷ���ʵ��
		if (SUCCEEDED(hr))
		{
			m_pConnection->ConnectionString =("Provider = SQLOLEDB.1; Persist Security Info =True; User ID = sa; Password=123456; Initial Catalog = school; Data Source = 192.168.10.111");
			hr = m_pConnection->Open("", "", "", adConnectUnspecified);//�����ݿ�
			AfxMessageBox(_T("���ӳɹ�"));
			if (FAILED(hr))
			{
				AfxMessageBox(_T("Open Failed!"));	
			}
		}
		else
		{
			AfxMessageBox(_T("Create instance of connection failed!"));
		}
	}
	catch (_com_error e)
	{
		CString temp;
	    temp.Format(_T("���ݿ����Ӵ���\r\n������ϢΪ��%s"), e.ErrorMessage());
		AfxMessageBox(temp);
	}
}


void CtestDlg::OnBnClickedAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	try
	{
		m_pRecordset.CreateInstance("ADODB.Recordset");
	    m_pRecordset->Open("select sno, cno, grade from sc",
		_variant_t((IDispatch*)m_pConnection, true), adOpenStatic, adLockOptimistic, adCmdText);
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
	_variant_t sno, cno, grade;
	try
	{
		int num = m_list.GetItemCount();
		while (!m_pRecordset->adoEOF)
		{
			CString sno= (_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("sno"))->Value);
			CString cno = (_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("cno"))->Value);
			CString grade = (_bstr_t)(m_pRecordset->Fields->GetItem(_variant_t("grade"))->Value);

			m_list.InsertItem(num, sno);
			m_list.SetItemText(num, 1, cno);
			m_list.SetItemText(num , 2, grade);

			num++;
			m_pRecordset->MoveNext();
		}
	}
	catch (_com_error &e)
	{
		AfxMessageBox(e.Description());
	}
}

