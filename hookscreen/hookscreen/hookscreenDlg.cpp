
// hookscreenDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "hookscreen.h"
#include "hookscreenDlg.h"
#include "afxdialogex.h"

#include "ShieldScreen.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#pragma comment(lib, "ShieldScreen.lib")

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// ChookscreenDlg 对话框

void get_FileSuffix(std::string path, std::string& suffix)
{
	for (int i = path.size() - 1; i > 0; i--)
	{
		if (path[i] == '.')
		{
			suffix = path.substr(i + 1);
			return;
		}
	}
	suffix = path;
}


BOOL ProcessClipboardPic()
{
	/*
	TCHAR lpszFileName[MAX_PATH];
	std::string strFilePath;
	BOOL result = FALSE;
	if (!IsClipboardFormatAvailable(CF_HDROP))
	{
		return FALSE;
	}
	if (OpenClipboard(NULL))//打开剪贴板  
	{
		HGLOBAL  nHandle = (HGLOBAL)GetClipboardData(CF_HDROP);
		if (nHandle)
		{
			HDROP hDrop = (HDROP)::GlobalLock(nHandle);
			::GlobalUnlock(nHandle);
			if (hDrop)
			{
				UINT fileCount = DragQueryFile(hDrop, 0xFFFFFFFF, 0, 0);
				UINT filenameLength;
				for (UINT i = 0; i < fileCount; ++i)
				{
					filenameLength = DragQueryFile(hDrop, i, 0, 0);
					DragQueryFile(hDrop, i, lpszFileName, filenameLength + 1);
					if (lpszFileName == NULL)
						continue;

					//如果是文件夹，则跳过
					if (IsDirectory(lpszFileName))
					{
						continue;
					}
					//该函数获取文件后缀名
					std::string strexr;
					get_FileSuffix(lpszFileName, strexr);
					CString strFileExtension(get_FileSuffix(lpszFileName, ).c_str());
					strFileExtension.MakeLower();

					//如果是图片格式，则对图片格式做处理
					if (strFileExtension == _T("jpg") ||
						strFileExtension == _T("jpeg") ||
						strFileExtension == _T("png") ||
						strFileExtension == _T("bmp") ||
						strFileExtension == _T("gif"))
					{
						//进行图片格式处理，可以全部改成自己想要的格式也可以不改
						EmptyClipboard();
					}
				}

			}
			//DragFinish(hDrop);        //TODO：不释放这个内存，在这里是释放会导致粘贴板访问会出错，下次就无法正常打开粘贴板了


		}
		if (_T("") != strFilePath)
		{
			Gdiplus::Bitmap* gdibmp = Gdiplus::Bitmap::FromFile(strFilePath.c_str());
			if (gdibmp)
			{
				HBITMAP hbitmap;
				gdibmp->GetHBITMAP(0, &hbitmap);

				EmptyClipboard();
				DIBSECTION ds;
				if (GetObject(hbitmap, sizeof(DIBSECTION), &ds))
				{
					HDC hdc = GetDC();
					//create compatible bitmap (get DDB from DIB)
					HBITMAP hbitmap_ddb = CreateDIBitmap(hdc, &ds.dsBmih, CBM_INIT,
						ds.dsBm.bmBits, (BITMAPINFO*)&ds.dsBmih, DIB_RGB_COLORS);
					ReleaseDC(hdc);
					SetClipboardData(CF_BITMAP, hbitmap_ddb);
					SetClipboardData(CF_OWNERDISPLAY, NULL);
					SetClipboardData(CF_TEXT, NULL);
					DeleteObject(hbitmap_ddb);
					result = TRUE;
				}

				//cleanup:
				DeleteObject(hbitmap);
				delete gdibmp;

			}
		}
		CloseClipboard();
	}

	return result;
	*/
	return TRUE;
}

void ChookscreenDlg::BlackScreen()
{
	HWND hwnd = this->m_hWnd;
	if (hwnd != NULL)
	{
		BOOL temp = FALSE;
		if (m_bStart == 1)
		{
			// 打开
			temp = SetWindowDisplayAffinity(hwnd, WDA_MONITOR);
			m_bStart = 0;
		}
		else if(m_bStart == 0)
		{
			temp = SetWindowDisplayAffinity(hwnd, WDA_NONE);
			m_bStart = 1;
		}

		if (!temp) {
			char szError[256];
			DWORD dwError = GetLastError();
			FormatMessage(
				FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				dwError,
				0,
				(LPWSTR)szError,
				sizeof(szError),
				NULL);
			//AfxMessageBox(szError);
			::MessageBox(0, (LPCTSTR)szError, NULL, NULL);
		}
	}
}


void ChookscreenDlg::ThreadSleep()
{
	while (1)
	{
		Sleep(1000);

		if (m_bStart == 1)
		{
			if (::OpenClipboard(NULL) && ::IsClipboardFormatAvailable(CF_HDROP))
			{
				HDROP hDrop = (HDROP)::GetClipboardData(CF_HDROP);
				if (hDrop != NULL)
				{
					EmptyClipboard();
				}
			}
		}
	}

	m_bStart = 0;
}

ChookscreenDlg::ChookscreenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOOKSCREEN_DIALOG, pParent), threadSleep(&ChookscreenDlg::ThreadSleep, this)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void ChookscreenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(ChookscreenDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &ChookscreenDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ChookscreenDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// ChookscreenDlg 消息处理程序

BOOL ChookscreenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void ChookscreenDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void ChookscreenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR ChookscreenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void ChookscreenDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//InstallLaunchEv();
	m_bStart = 1;
	BlackScreen();

	
	//CDialogEx::OnOK();
}


void ChookscreenDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//UnInstallLaunchEv();
	m_bStart = 0;
	BlackScreen();

	//CDialogEx::OnCancel();
}
