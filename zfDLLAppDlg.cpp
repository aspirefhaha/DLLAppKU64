// zfDLLAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "zfDLLApp.h"
#include "zfDLLAppDlg.h"
#include "masKUApi.h"
#include "mmsystem.h"
#include "maskuapi_ex.h"

#pragma comment(lib,"winmm.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//extern int main_test();

HANDLE zfHandle=INVALID_HANDLE_VALUE;

CString ISOPath; 

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#define WM_UPOS	WM_USER+100

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZfDLLAppDlg dialog

CZfDLLAppDlg::CZfDLLAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZfDLLAppDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZfDLLAppDlg)
	m_pid = 0;
	m_vid = 0;
	m_radio = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bIsTestQuit = FALSE;
	
	hTestThread = INVALID_HANDLE_VALUE;
	hWriteThread = INVALID_HANDLE_VALUE;
}

void CZfDLLAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZfDLLAppDlg)
	//DDX_Text(pDX, IDC_DISK_PID, m_pid);
	//DDX_Text(pDX, IDC_DISK_VID, m_vid);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CZfDLLAppDlg, CDialog)
	//{{AFX_MSG_MAP(CZfDLLAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OpenUSB, OnOpenUSB)
	ON_BN_CLICKED(IDC_CloseUSB, OnCloseUSB)
	ON_BN_CLICKED(IDC_GetCDDVD, OnGetCDDVD)
	ON_BN_CLICKED(IDC_GetDiskInfoAll, OnGetDiskInfoAll)
	ON_BN_CLICKED(IDC_SetDiskInfoAll, OnSetDiskInfoAll)
	ON_BN_CLICKED(IDC_WriteHide, OnWriteHide)
	ON_BN_CLICKED(IDC_ReadHide, OnReadHide)
	ON_BN_CLICKED(IDC_UpdateISO, OnUpdateISO)
	ON_BN_CLICKED(IDC_Clear, OnClear)
	ON_BN_CLICKED(IDC_ISO_ROUTE, OnIsoRoute)
	ON_BN_CLICKED(IDC_WriteHide2, OnWriteHide2)
	ON_BN_CLICKED(IDC_ReadHide2, OnReadHide2)
	ON_BN_CLICKED(IDC_GetTime, OnGetTime)
	ON_BN_CLICKED(IDC_SetTime, OnSetTime)
	ON_BN_CLICKED(IDC_Pwd_Verify, OnPwdVerify)
	ON_BN_CLICKED(IDC_Pwd_Change, OnPwdChange)
	ON_BN_CLICKED(IDC_Pwd_Err, OnPwdErr)
	ON_BN_CLICKED(IDC_Pwd_Change2, OnPwdChange2)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_WriteHide3, OnWriteHide3)
	ON_BN_CLICKED(IDC_Pwd_Change4, OnPwdChange4)
	ON_BN_CLICKED(IDCANCEL2, OnCancel2)
	ON_BN_CLICKED(IDC_GetTime2, OnGetTime2)
	ON_BN_CLICKED(IDC_WriteHide4, OnWriteHide4)
	ON_BN_CLICKED(IDC_WriteHide5, OnWriteHide5)
	ON_BN_CLICKED(IDC_WriteHide6, OnWriteHide6)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_WriteHide7, &CZfDLLAppDlg::OnBnClickedWritehide7)
	ON_BN_CLICKED(IDC_ReadHide3, &CZfDLLAppDlg::OnBnClickedReadhide3)
	ON_BN_CLICKED(IDC_GetCDDVD2, &CZfDLLAppDlg::OnBnClickedGetcddvd2)
	ON_BN_CLICKED(IDC_BUTTON3, &CZfDLLAppDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_CD_CAPACITY, &CZfDLLAppDlg::OnEnChangeCdCapacity)
	ON_EN_CHANGE(IDC_U_CAPACITY, &CZfDLLAppDlg::OnEnChangeUCapacity)
	ON_EN_CHANGE(IDC_S_CAPACITY, &CZfDLLAppDlg::OnEnChangeSCapacity)
	ON_EN_CHANGE(IDC_H_CAPACITY, &CZfDLLAppDlg::OnEnChangeHCapacity)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_COL_FP, &CZfDLLAppDlg::OnBnClickedColFp)
	ON_BN_CLICKED(IDC_UP_IMG, &CZfDLLAppDlg::OnBnClickedUpImg)
	ON_BN_CLICKED(IDC_BUTTON6, &CZfDLLAppDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_CIPID, &CZfDLLAppDlg::OnBnClickedCipid)
	ON_BN_CLICKED(IDC_BUTTON4, &CZfDLLAppDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CZfDLLAppDlg::OnBnClickedButton5)
	ON_MESSAGE(WM_UPOS, &CZfDLLAppDlg::OnUPos)
	ON_BN_CLICKED(IDC_BUTTON7, &CZfDLLAppDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CZfDLLAppDlg::OnBnClickedButton8)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZfDLLAppDlg message handlers

LRESULT CZfDLLAppDlg::OnUPos(WPARAM wparam, LPARAM)
{
	((CProgressCtrl *)GetDlgItem(IDC_PROGRESS1))->SetPos(wparam);
	return 0;
}

BOOL CZfDLLAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	GetDlgItem(IDC_EDIT_CYCLE)->SetWindowText("1");
	GetDlgItem(IDC_PSEC)->SetWindowText("1");

	((CButton*)GetDlgItem(IDC_RADIOR00))->SetCheck(TRUE);

	CFileFind finder;   //查找是否存在ini文件，若不存在，则生成一个新的默认设置的ini文件，这样就保证了我们更改后的设置每次都可用
	BOOL ifFind = finder.FindFile("./config.ini");
	if (!ifFind)
	{
		MessageBox("未找到配置文件！", "警告", MB_OK);
		OnOK();
		//OnDestory();
		PostNcDestroy();
		return FALSE;
	}
	int fp_st = GetPrivateProfileInt("FUNCTION", "fingerprint", 1, "./config.ini");

	if (0 == fp_st)
	{
		GetDlgItem(IDC_COL_FP)->EnableWindow(FALSE);
		GetDlgItem(IDC_UP_IMG)->EnableWindow(FALSE);
	}
	
	//初始化分区密码
	char* pDevSec = "12345678";
	CString DevSec = (CString)pDevSec;
	GetDlgItem(IDC_SEC_OLD)->SetWindowText(DevSec);

	//初始化分区号
	char* pDevSec2 = "0";
	CString DevSec2 = (CString)pDevSec2;
	GetDlgItem(IDC_SEC_OLD2)->SetWindowText(DevSec2);

	//初始化CD区大小(MB)
	char* pDevT = "30";
	CString DevT = (CString)pDevT;
	GetDlgItem(IDC_CD_CAPACITY)->SetWindowText(DevT);
	
	//初始化安全区大小(MB)
	char* pDevS = "0";
	CString DevS = (CString)pDevS;
	GetDlgItem(IDC_S_CAPACITY)->SetWindowText(DevS);

	//初始化隐藏区大小(MB)
	char* pDevH = "0";
	CString DevH = (CString)pDevH;
	GetDlgItem(IDC_H_CAPACITY)->SetWindowText(DevH);

	//初始化普通U盘区大小(MB)
	char* pDevU = "300";
	CString DevU = (CString)pDevU;
	GetDlgItem(IDC_U_CAPACITY)->SetWindowText(DevU);

	//序列号
	char* pDevUSN = "2014071100000001";
	CString DevUSN = (CString)pDevUSN;
	GetDlgItem(IDC_SN)->SetWindowText(DevUSN);
	CEdit*pEdt = (CEdit*)GetDlgItem(IDC_SN);
	pEdt->SetLimitText(16);                              //限制编辑框输入长度为8字节

	pEdt = (CEdit*)GetDlgItem(IDC_EDIT_QUANTITY);
	pEdt->SetLimitText(8);
	//错误阀值默认为10次
	char* pErrNum = "10";
	CString ErrNum = (CString)pErrNum;
	GetDlgItem(IDC_SEC_OLD5)->SetWindowText(ErrNum);

	//VID,PID
//  	m_vid = 0x6673;	//老U盘
// 	m_pid = 0x1234;
// 	m_vid = 0x465A;	//税控盘
// 	m_pid = 0x4454;
	m_vid = 0x465A;	//Key+U
	m_pid = 0x2480;

	char tmp_buf[20];
	sprintf(tmp_buf, "%04x", m_vid);
	SetDlgItemText(IDC_DISK_VID, (LPCTSTR)tmp_buf);
	sprintf(tmp_buf, "%04x", m_pid);
	SetDlgItemText(IDC_DISK_PID, (LPCTSTR)tmp_buf);



	UpdateData(FALSE);


	CString DevStr = "disk_keyU";	//产品信息
	GetDlgItem(IDC_EDIT5)->SetWindowText(DevStr);



	GetDlgItem(IDC_CD_CAPACITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_U_CAPACITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_S_CAPACITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_H_CAPACITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_QUANTITY)->EnableWindow(FALSE);
	GetDlgItem(IDC_SN)->EnableWindow(FALSE);
	GetDlgItem(IDC_SetDiskInfoAll)->EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CZfDLLAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CZfDLLAppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CZfDLLAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CZfDLLAppDlg::PrintOut(const char *format, ...)
{
	CString str;
	UINT i;
	
	const int buffersize = 2048;
	va_list argptr;
	char buffer[buffersize];
	
	// print to buffer
	va_start(argptr,format);
	_vsnprintf(buffer,buffersize-1,format,argptr);
	buffer[buffersize-1] = 0;
	
	// send buffer to output window (synchronous behavior)
	//先获取原来显示的文本
	GetDlgItemText(IDC_EDIT_OUTPUTWIN,str);
	//将新的信息追加在最后
	str+=buffer;
	//需要换行
	//str+="\r\n";	
	//设置新的文本
	SetDlgItemText(IDC_EDIT_OUTPUTWIN,str);
	//滚动条自动滚动到最后一行
	i=((CEdit*)GetDlgItem(IDC_EDIT_OUTPUTWIN))->GetLineCount();
	((CEdit*)GetDlgItem(IDC_EDIT_OUTPUTWIN))->LineScroll(i,0);
	
	va_end(argptr);	
}
//产生唯一序列号,成功返回TRUE;devSN存序列号
BOOL CZfDLLAppDlg::ZFUSetSN(unsigned char *devSN)
{
	unsigned char devNum = 0;
	DWORD snTemp;
	char sn[17];
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	
	CString strRootPath="c:\\";		//带根目录标记的磁盘符号
	char chVolName[20];				//卷标的缓冲区
	DWORD dwLength=20;				//卷标缓冲区的大小
	DWORD dwVolSerialNum=0;			//磁盘序列号
	DWORD dwMaxLength=255;			//最大文件名的长度 
	char chFileSysName[20];			//文件系统名称缓冲区 
	DWORD dwFileSysLength=20;		//文件系统名称缓冲区大小
	GetVolumeInformation(strRootPath,chVolName,dwLength,&dwVolSerialNum,&dwMaxLength,0,chFileSysName,dwFileSysLength);//获取卷标信息
	
	devNum = 0;
	
	snTemp = dwVolSerialNum%100;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wYear%100;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wMonth;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wDay;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wHour;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wMinute;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wSecond;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	snTemp = st.wMilliseconds%100;
	sn[devNum++] = (char)(snTemp/10 + 0x30);
	snTemp %= 10;
	sn[devNum++] = (char)(snTemp/1 + 0x30);
	
	sn[devNum++] = '\0';
	memcpy(devSN,sn,16);
	
	return TRUE;
}



void CZfDLLAppDlg::OnOpenUSB() 
{
	// TODO: Add your control notification handler code here
//	unsigned int tim;
//	unsigned int res;
	CString DiskStr;
	unsigned char buf[256];
	GetDlgItemText(IDC_DISK_SYMBOL,DiskStr);				//得到输入盘符
	
	if(((DiskStr>'A') && (DiskStr < 'Z')) || ((DiskStr>'a') && (DiskStr < 'z')))
	{
		//PrintOut("\r\n输入的盘符正确 !\r\n");
	}
	else
	{
		PrintOut("\r\n输入的盘符错误 ！\r\n");
		return;
	}

	zfHandle = masKU_Open(DiskStr[0]);					//打开光盘盘符
	
	if(zfHandle == INVALID_HANDLE_VALUE)
		PrintOut("\r\n设备打开失败 !\r\n");
	else
		PrintOut("\r\n设备打开成功 !\r\n");
//	masKU_check_emmc(zfHandle,&tim,&res);
//	USB_Inquiry(zfHandle,buf);
}

void CZfDLLAppDlg::OnCloseUSB() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	if(zfHandle != INVALID_HANDLE_VALUE)
		result = masKU_Close(zfHandle);		//打开指定盘符
	
	if (result) {
		zfHandle = INVALID_HANDLE_VALUE;
		PrintOut("\r\n设备关闭成功 !\r\n");
	}
	else {

		PrintOut("\r\n设备关闭失败 !\r\n");
	}
}


void CZfDLLAppDlg::OnGetCDDVD() 
{
	// TODO: Add your control notification handler code here
	unsigned int i,j;
	unsigned char diskTmp;
	unsigned char diskDriver[26*7];
	unsigned char wLen = 0;
	unsigned short usbVID = 0;//0x6673;
	unsigned short usbPID = 0;//0x1234;
	
	//得到vid,pid
	UpdateData(TRUE);
	usbVID = m_vid;
	usbPID = m_pid;

	wLen = masKU_Scan(diskDriver,usbVID,usbPID);
	
	if(wLen)
	{
		PrintOut("查找到%2d个设备 \r\n",wLen);
		
		for(i=0;i<wLen;i++)
		{
			diskTmp = i+1;
			PrintOut("第%2d个设备有%2d个分区，各分区对应盘符依次如下：\r\n",diskTmp,diskDriver[i*7]);
			
			for(j=0;j<diskDriver[i*7];j++)
			{
				if(diskDriver[i*7+1+j*2] == 'T')
					PrintOut("   光盘区对应盘符为:%2c \r\n",diskDriver[i*7+1+j*2+1]);
				else if(diskDriver[i*7+1+j*2] == 'U')
					PrintOut("   U 盘区对应盘符为:%2c \r\n",diskDriver[i*7+1+j*2+1]);
				else if(diskDriver[i*7+1+j*2] == 'S')
					PrintOut("   安全区对应盘符为:%2c \r\n",diskDriver[i*7+1+j*2+1]);
			}
		}
		
		PrintOut("\r\n");
		
		zfHandle = masKU_Open(diskDriver[2]);	//打开头一个设备
		if(zfHandle == INVALID_HANDLE_VALUE)
			PrintOut("打开第1个设备第1个分区%2c失败! \r\n",diskDriver[2]);
		else
			PrintOut("打开第1个设备第1个分区%2c成功! \r\n",diskDriver[2]);
		
		//第一个分区
		char* pDevSN = (char*)&diskDriver[2];
		CString DevStr = (CString)pDevSN[0];
		GetDlgItem(IDC_DISK_SYMBOL)->SetWindowText(DevStr);
	}
	else
		PrintOut("查找设备失败! \r\n");
}


void CZfDLLAppDlg::OnGetDiskInfoAll() 
{
	// TODO: Add your control notification handler code here
	bool result;
	unsigned char binVer[100]={'0'};
//	unsigned long binLen;
	unsigned char zfUsbSN[17];

	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	result = masKU_GetDiskInfo(zfHandle,&zfUsb);

	memcpy(zfUsbSN,zfUsb.SN,16);
	zfUsbSN[16] = '\0';
	if(result)
	{
		PrintOut("\r\n获取设备信息成功 !\r\n");
		PrintOut("VID：%04x \r\n",zfUsb.VID);
		PrintOut("PID：%04x \r\n",zfUsb.PID);
		PrintOut("设备序列号：%16s \r\n",zfUsbSN);
		PrintOut("设备属性：%08x \r\n",zfUsb.diskQuantity);
		PrintOut("CD区大小：%d MB \r\n",zfUsb.tDiskCapacity);
		PrintOut("安全区大小：%d MB \r\n",zfUsb.sDiskCapacity);
		PrintOut("隐藏区大小：%d MB \r\n",zfUsb.hDiskCapacity);
		PrintOut("U盘区大小：%d MB \r\n",zfUsb.uDiskCapacity);
		PrintOut("扇区大小： %d 字节\r\n",zfUsb.unit);
		PrintOut("固件版本号： %x \r\n",zfUsb.usbVersion);
		PrintOut("设备总容量：%d MB \r\n",zfUsb.AllDiskCapacity);
		PrintOut("厂商信息：%-8.8s \r\n",zfUsb.ManufacturerInfo);
		PrintOut("产品信息：%-16.16s \r\n",zfUsb.ProductInfo);
		PrintOut("厂商字符串：%-8.8s \r\n",zfUsb.ManufacturerStr);
		PrintOut("产品字符串：%-16.16s \r\n",zfUsb.ProductStr);
	}
	else{
		PrintOut("\r\n获取设备信息失败! \r\n");
		return;
	}

	GetDlgItem(IDC_CD_CAPACITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_U_CAPACITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_S_CAPACITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_H_CAPACITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_QUANTITY)->EnableWindow(TRUE);
	GetDlgItem(IDC_SN)->EnableWindow(TRUE);
	GetDlgItem(IDC_SetDiskInfoAll)->EnableWindow(TRUE);
	



	SetDlgItemText(IDC_SN,(LPCTSTR)zfUsbSN);
	SetDlgItemInt(IDC_CD_CAPACITY, zfUsb.tDiskCapacity);
	SetDlgItemInt(IDC_U_CAPACITY, zfUsb.uDiskCapacity);
	SetDlgItemInt(IDC_S_CAPACITY, zfUsb.sDiskCapacity);
	SetDlgItemInt(IDC_H_CAPACITY, zfUsb.hDiskCapacity); 
	sprintf((char *)zfUsbSN, "%08x", zfUsb.diskQuantity);
	SetDlgItemText(IDC_EDIT_QUANTITY, (LPCTSTR)zfUsbSN);

	sprintf((char *)zfUsbSN, "%04x", zfUsb.VID);
	SetDlgItemText(IDC_DISK_VID, (LPCTSTR)zfUsbSN);
	sprintf((char *)zfUsbSN, "%04x", zfUsb.PID);
	SetDlgItemText(IDC_DISK_PID, (LPCTSTR)zfUsbSN);


	memcpy(binVer, zfUsb.ManufacturerStr, 8);
	binVer[8] = 0;
	SetDlgItemText(IDC_EDIT6, (LPCTSTR)binVer);

	memcpy(binVer, zfUsb.ProductStr, 16);
	binVer[16] = 0;
	SetDlgItemText(IDC_EDIT7, (LPCTSTR)binVer);

	memcpy(binVer, zfUsb.ManufacturerInfo, 8);
	binVer[8] = 0;
	SetDlgItemText(IDC_DISK_SYMBOL2, (LPCTSTR)binVer);

	memcpy(binVer, zfUsb.ProductInfo, 16);
	binVer[16] = 0;
	SetDlgItemText(IDC_EDIT5, (LPCTSTR)binVer);



}

void CZfDLLAppDlg::OnSetDiskInfoAll() 
{
	// TODO: Add your control notification handler code here
	bool result;
	int ret;
	UINT32 u32_tmp = 0;
	CString str_tmp;
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}
	//////////////////////////VID////////////////////////////////////////
	GetDlgItemText(IDC_DISK_VID, str_tmp);
	ret = sscanf(str_tmp.GetBuffer(str_tmp.GetLength()), "%04x", &u32_tmp);
	if (1 != ret)
	{
		PrintOut("VID错误\r\n");
		return;
	}
	zfUsb.VID = u32_tmp;
	str_tmp.ReleaseBuffer();
	//---------------------------------------------------------------------

	/////////////////////////PID//////////////////////////////////////////
	GetDlgItemText(IDC_DISK_PID, str_tmp);
	ret = sscanf(str_tmp.GetBuffer(str_tmp.GetLength()), "%04x", &u32_tmp);
	if (1 != ret)
	{
		PrintOut("PID错误\r\n");
		return;
	}
	zfUsb.PID = u32_tmp;
	str_tmp.ReleaseBuffer();
	//---------------------------------------------------------------------

	//////////////////////////////////////厂商描述符///////////////////////
	GetDlgItemText(IDC_EDIT6, str_tmp);
	if (str_tmp.GetLength() > 8)
	{
		PrintOut("厂商描述符太长\r\n");
		return;
	}
	memcpy(zfUsb.ManufacturerStr, str_tmp.GetBuffer(str_tmp.GetLength()), str_tmp.GetLength());
	str_tmp.ReleaseBuffer();
	//---------------------------------------------------------------------

	////////////////////////////////////产品描述符/////////////////////////
	GetDlgItemText(IDC_EDIT7, str_tmp);
	if (str_tmp.GetLength() > 16)
	{
		PrintOut("产品描述符太长\r\n");
		return;
	}
	memcpy(zfUsb.ProductStr, str_tmp.GetBuffer(str_tmp.GetLength()), str_tmp.GetLength());
	str_tmp.ReleaseBuffer();
	//------------------------------------------------------------------------

	////////////////////////////////////厂商信息/////////////////////////
	GetDlgItemText(IDC_DISK_SYMBOL2, str_tmp);
	if (str_tmp.GetLength() > 8)
	{
		PrintOut("厂商信息太长\r\n");
		return;
	}
	memcpy(zfUsb.ManufacturerInfo, str_tmp.GetBuffer(str_tmp.GetLength()), str_tmp.GetLength());
	str_tmp.ReleaseBuffer();
	//------------------------------------------------------------------------


	////////////////////////////////////产品信息/////////////////////////
	GetDlgItemText(IDC_EDIT5, str_tmp);
	if (str_tmp.GetLength() > 16)
	{
		PrintOut("产品信息太长\r\n");
		return;
	}
	memcpy(zfUsb.ProductInfo, str_tmp.GetBuffer(str_tmp.GetLength()), str_tmp.GetLength());
	str_tmp.ReleaseBuffer();
	//------------------------------------------------------------------------


	////////////////////////////设备序列号///////////////////////////////////////////
	GetDlgItemText(IDC_SN, str_tmp);
	if (str_tmp.GetLength() > 16)
	{
		PrintOut("序列号长度不对\r\n");
		return;
	}
	memset(zfUsb.SN, 0, 16);
	memcpy(zfUsb.SN, str_tmp.GetBuffer(str_tmp.GetLength()), str_tmp.GetLength());
	str_tmp.ReleaseBuffer();
	//--------------------------------------------------------------------------------




	//////////////////////////////////分区容量////////////////////////////////////////////
/*	if (0 != GetDlgItemInt(IDC_STATIC_REM))
	{
		PrintOut("各分区容量配置不对，剩余容易必须为0\r\n");
		return;
	}*/
	zfUsb.tDiskCapacity = GetDlgItemInt(IDC_CD_CAPACITY);
	zfUsb.hDiskCapacity = GetDlgItemInt(IDC_H_CAPACITY);
	zfUsb.sDiskCapacity = GetDlgItemInt(IDC_S_CAPACITY);
	zfUsb.uDiskCapacity = GetDlgItemInt(IDC_U_CAPACITY);

	//------------------------------------------------------------------------------------

	GetDlgItemText(IDC_EDIT_QUANTITY, str_tmp);
	ret = sscanf(str_tmp.GetBuffer(str_tmp.GetLength()), "%08x",&u32_tmp);
	if (1 != ret)
	{
		PrintOut("QUTI错误\r\n");
		return;
	}
	zfUsb.diskQuantity = u32_tmp;
	str_tmp.ReleaseBuffer();


	result = masKU_SetDiskInfo(zfHandle,zfUsb);
	
	if(result)
		PrintOut("设备信息集合设置成功 !\r\n");
	else
		PrintOut("设备信息集合设置失败 !\r\n");
}


#define  LEN_ONETIME	65536

unsigned char buff1_r[4096*16*2];
unsigned char buff1_w[4096*16*2];


void CZfDLLAppDlg::OnWriteHide() 
{
	// TODO: Add your control notification handler code here
	unsigned int time_ms1,time_ms;
	unsigned int i;
	unsigned int result = 0;				//错误计数	
	unsigned int SecAddr = 0;				//写的起始地址
	unsigned int SecCnt = 10;				//写的数据大小，单位MB

	unsigned int sectorSize = 512;	//设备扇区大小
	MASKU_INFO zfUsb;
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	masKU_GetDiskInfo(zfHandle,&zfUsb);
	sectorSize = zfUsb.unit;

	SecCnt = SecCnt*1024*1024/sectorSize;	//算出扇区个数
	
	for(i=0;i<LEN_ONETIME;i++)
	{
		buff1_w[i] = i;
	}
	
	time_ms1 = timeGetTime();
	
	for(i = 0; i<SecCnt; i+=(LEN_ONETIME/sectorSize))
	{
		if(0 == masKU_WriteHideDisk(zfHandle, i, LEN_ONETIME/sectorSize, buff1_w,0))
		{
			PrintOut("\r\n写隐藏区 %d 扇区失败 \r\n",i);
			return;
		}
	}
	
	SecCnt = SecCnt*sectorSize/1024/1024;
	time_ms = timeGetTime() - time_ms1;
	PrintOut("\r\n写隐藏区 %d MB 用时 %d ms \r\n",SecCnt,time_ms);
	
	PrintOut("\r\n写隐藏区成功!  速度 %d MB/S \r\n", 1000 / time_ms*SecCnt);
}

void CZfDLLAppDlg::OnReadHide()
{
	// TODO: Add your control notification handler code here
	unsigned int time_ms1, time_ms;
	unsigned int i;
	unsigned int result = 0;				//错误计数	
	unsigned int SecAddr = 0;				//读的起始地址
	unsigned int SecCnt = 10;				//数据大小，单位MB
	unsigned int sectorSize = 512;	//设备扇区大小
	MASKU_INFO zfUsb;

	masKU_GetDiskInfo(zfHandle, &zfUsb);
	sectorSize = zfUsb.unit;

	if (zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}
	SecCnt = SecCnt * 1024 * 1024 / sectorSize;	//算出扇区个数
	for (i = 0; i < 65536; i++)
		buff1_w[i] = i;

	time_ms1 = timeGetTime();
	for (i = SecAddr; i < (SecAddr + SecCnt); i += (LEN_ONETIME / sectorSize))
	{
		memset(buff1_r, 0x00, LEN_ONETIME);
		if (0 == masKU_ReadHideDisk(zfHandle, i, LEN_ONETIME / sectorSize, buff1_r, 0))
		{
			PrintOut("读隐藏区 %d 扇区失败 退出\r\n", i);
			return;
		}

		if (memcmp(buff1_w, buff1_r, LEN_ONETIME))
		{
			PrintOut("隐藏区第 %d 扇区数据错误  退出\r\n", i);
			return;
		}
	}
	SecCnt = SecCnt*sectorSize / 1024 / 1024;
	time_ms = timeGetTime() - time_ms1;
	PrintOut("读隐藏区 %d MB 用时 %d ms \r\n", SecCnt, time_ms);
	PrintOut("操作完成! 速度 %d MB/S \r\n",1000/time_ms*SecCnt);
}
void CZfDLLAppDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CZfDLLAppDlg::OnClear() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText(IDC_EDIT_OUTPUTWIN,"");
	//masku_ex_test();
}


void CZfDLLAppDlg::OnIsoRoute() 
{
	// TODO: Add your control notification handler code here
	
}

void CZfDLLAppDlg::OnWriteHide2()
{
	// TODO: Add your control notification handler code here
	MASKU_INFO zfUsb;

	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}
	
	if(0 == masKU_GetDiskInfo(zfHandle,&zfUsb))	//读参数不正确
		return;
	
	zfUsb.diskQuantity &= 0xf7ffffff;	//设置为只读属性
	//zfUsb.diskQuantity |= 0x10000000;	//设置为不可读属性

	if(TRUE == masKU_SetDiskInfo(zfHandle,zfUsb))
		PrintOut("\r\nU盘区只读属性设置成功!\r\n");
	else
		PrintOut("\r\nU盘区只读属性设置失败 !\r\n");
	
	masKU_Close(zfHandle);
}

void CZfDLLAppDlg::OnReadHide2() 
{
	// TODO: Add your control notification handler code here
	MASKU_INFO zfUsb;

	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}
	
	if(0 == masKU_GetDiskInfo(zfHandle,&zfUsb))	//读参数不正确
		return;
	
	zfUsb.diskQuantity |= 0x08000800;	//设置为读写属性
	//zfUsb.diskQuantity &= 0xefffffff;	//设置为读写属性

	if(TRUE == masKU_SetDiskInfo(zfHandle,zfUsb))
		PrintOut("\r\nU盘区读写属性设置成功!\r\n");
	else
		PrintOut("\r\nU盘区读写属性设置失败 !\r\n");

	masKU_Close(zfHandle);
}

void CZfDLLAppDlg::OnGetTime() 
{
	// TODO: Add your control notification handler code here
	bool result;
	MASKU_TIMER USBTime;
	
	result = masKU_Time(zfHandle,1,&USBTime);
	
	if(result)
	{
		PrintOut("\r\nkey盘当前时间：%4d年%2d月%2d日%2d时%2d分%2d秒,星期%d",USBTime.year,USBTime.month,USBTime.day,USBTime.hour,USBTime.minute,USBTime.seconds,USBTime.weekday);
/*
		PrintOut("\r\nkey盘时间获取成功 ！");
		PrintOut("\r\n年：%d",USBTime.year);
		PrintOut("\r\n月：%d",USBTime.month);
		PrintOut("\r\n日：%d",USBTime.day);
		PrintOut("\r\n时：%d",USBTime.hour);
		PrintOut("\r\n分：%d",USBTime.minute);
		PrintOut("\r\n秒：%d",USBTime.seconds);
		PrintOut("\r\n星期：%d\r\n",USBTime.weekday);*/
	}
	else
	{
		PrintOut("\r\nkey盘时间获取失败 ！\r\n");
	}
}

void CZfDLLAppDlg::OnSetTime() 
{
	// TODO: Add your control notification handler code here
	bool result;
	MASKU_TIMER USBTime;
	SYSTEMTIME st;
	CString strDate,strTime;
	GetLocalTime(&st);
	
	USBTime.year = st.wYear;
	USBTime.month = st.wMonth;
	USBTime.day = st.wDay;
	USBTime.hour = st.wHour;
	USBTime.minute = st.wMinute;
	USBTime.seconds = st.wSecond;
	USBTime.weekday = st.wDayOfWeek;
	
	result = masKU_Time(zfHandle,2,&USBTime);
	
	if(result)
	{
		PrintOut("\r\nkey盘时间设置成功 ！\r\n");
	}
	else
	{
		PrintOut("\r\nkey盘时间设置失败 ！\r\n");
	}
}

void CZfDLLAppDlg::OnPwdVerify() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	unsigned char subArea;		//00H：普通用户，01H：隐藏区，02H：安全区，03H：管理员
	
	//得到分区号
	CEdit*   edit1=(CEdit*)GetDlgItem(IDC_SEC_OLD2); 
	CString   OldSec1; 
	edit1-> GetWindowText(OldSec1); 
	subArea = OldSec1[0]-0x30;
	
	//得到原密码
	CEdit*   edit=(CEdit*)GetDlgItem(IDC_SEC_OLD); 
	CString   OldSec; 
	edit-> GetWindowText(OldSec); 
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	//result = masKU_Password_Verify(zfHandle,"Bs#$@__s@f^t",subArea,0);
	result = masKU_Password_Verify(zfHandle,OldSec,subArea,0);
	if(result == 0)
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码校验失败 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码校验失败 !\r\n");
		if(subArea == 2)
			PrintOut("\r\n安全区 密码校验失败 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码校验失败 !\r\n");
	}		
	else
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码校验成功 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码校验成功 !\r\n");
		if(subArea == 2)
			PrintOut("\r\n安全区 密码校验成功 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码校验成功 !\r\n");
	}

}

void CZfDLLAppDlg::OnPwdChange()
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	unsigned char subArea;		//00H：普通用户，01H：隐藏区，02H：安全区，03H：管理员
	
	//得到分区号
	CEdit*   edit1=(CEdit*)GetDlgItem(IDC_SEC_OLD2); 
	CString   OldSec1; 
	edit1-> GetWindowText(OldSec1); 
	subArea = OldSec1[0]-0x30;
	
	//得到原密码
	CEdit*   edit=(CEdit*)GetDlgItem(IDC_SEC_OLD); 
	CString   OldSec; 
	edit-> GetWindowText(OldSec); 

	//得到新密码
	CEdit*   edit2=(CEdit*)GetDlgItem(IDC_SEC_OLD3); 
	CString   NewSec; 
	edit2-> GetWindowText(NewSec); 
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	result = masKU_Password_Change(zfHandle,NewSec,subArea,0);
	
	if(result == 0)
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码修改失败 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码修改失败 !\r\n");
		if(subArea == 2)
			PrintOut("\r\n安全区 密码修改失败 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码修改失败 !\r\n");
	}		
	else
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码修改成功 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码修改成功 !\r\n");
		if(subArea == 2)
			PrintOut("\r\n安全区 密码修改成功 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码修改成功 !\r\n");
	}
}

void CZfDLLAppDlg::OnPwdChange2() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	unsigned char subArea;		//00H：普通用户，01H：隐藏区1，02H：隐藏区2，03H：管理员

	//得到分区号
	CEdit*   edit1=(CEdit*)GetDlgItem(IDC_SEC_OLD2); 
	CString   OldSec1; 
	edit1-> GetWindowText(OldSec1); 
	subArea = OldSec1[0]-0x30;
	
	//得到新密码
	CEdit*   edit2=(CEdit*)GetDlgItem(IDC_SEC_OLD3); 
	CString   NewSec; 
	edit2-> GetWindowText(NewSec); 

	//得到管理员密码
	CEdit*   edit3=(CEdit*)GetDlgItem(IDC_SEC_OLD4); 
	CString   ManagerSec; 
	edit3-> GetWindowText(ManagerSec); 
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	result = masKU_Password_Verify(zfHandle,ManagerSec,3,0);	//校验管理员密码
	
	if(result == 0)
	{
		PrintOut("\r\n管理员 密码校验失败 !\r\n");
		return;
	}

	result = masKU_Password_Change(zfHandle,NewSec,subArea,0xf4);
	
	if(result == 0)
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码修改失败 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码修改失败 !\r\n");
		if (subArea == 2)
			PrintOut("\r\n安全区 密码修改失败 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码修改失败 !\r\n");
	}		
	else
	{
		if(subArea == 0)
			PrintOut("\r\n普通用户 密码修改成功 !\r\n");
		if(subArea == 1)
			PrintOut("\r\n隐藏区 密码修改成功 !\r\n");
		if (subArea == 2)
			PrintOut("\r\n安全区 密码修改成功 !\r\n");
		if(subArea == 3)
			PrintOut("\r\n管理员 密码修改成功 !\r\n");
	}
}

void CZfDLLAppDlg::OnPwdErr() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	unsigned char subArea = GetDlgItemInt(IDC_SEC_OLD2);			//00H：普通用户，01H：隐藏区，02H：安全区，03H：管理员
	unsigned char errFlg;// = ((CButton*)GetDlgItem(IDC_RADIO1))->GetCheck();	//=1读取：=2设置
	int temp = GetDlgItemInt(IDC_SEC_OLD5);
	if ((temp < 0) || (temp > 255)) {
		PrintOut("输入数据错误\r\n");
		return;
	}
	unsigned char errSetVal = temp&0xff;			//读取或设置的错误阀值，取值范围1~255
	unsigned char errReturnVal = 0;	//返回的当前错误计数值
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	UpdateData(TRUE);
	errFlg=m_radio;
	if(0==m_radio)
		errFlg=2;
	else if(2==m_radio)
		errFlg=3;
	UpdateData(FALSE);

	//errFlg= 4;	//更新设备密钥
	result = masKU_Password_Err(zfHandle,subArea,errFlg,&errSetVal,&errReturnVal);
	
	if(2 == errFlg)				//设置阀值
	{
		if(result)
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,错误阀值设置成功,为: %d次 \r\n",errSetVal);
			if(subArea == 1)
				PrintOut("\r\n隐藏区,错误阀值设置成功,为: %d次 \r\n",errSetVal);
			if(subArea == 2)
				PrintOut("\r\n安全区,错误阀值设置成功,为: %d次 \r\n",errSetVal);
			if(subArea == 3)
				PrintOut("\r\n管理员,错误阀值设置成功,为: %d次 \r\n",errSetVal);
		}
		else
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,错误阀值设置失败 \r\n");
			if(subArea == 1)
				PrintOut("\r\n隐藏区,错误阀值设置失败 \r\n");
			if(subArea == 2)
				PrintOut("\r\n安全区,错误阀值设置失败 \r\n");
			if(subArea == 3)
				PrintOut("\r\n管理员,错误阀值设置失败 \r\n");
		}
	}
	else if(1 == errFlg)						//读取阀值
	{
		if(result)
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,口令错误阀值为: %d,当前错误次数为: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 1)
				PrintOut("\r\n隐藏区,口令错误阀值为: %d,当前错误次数为: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 2)
				PrintOut("\r\n安全区,口令错误阀值为: %d,当前错误次数为: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 3)
				PrintOut("\r\n管理员,口令错误阀值为: %d,当前错误次数为: %d \r\n",errSetVal,errReturnVal);
		}
		else
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,错误阀值读取失败 \r\n");
			if(subArea == 1)
				PrintOut("\r\n隐藏区,错误阀值读取失败 \r\n");
			if(subArea == 2)
				PrintOut("\r\n安全区,错误阀值读取失败 \r\n");
			if(subArea == 3)
				PrintOut("\r\n管理员,错误阀值读取失败 \r\n");
		}
	}
	else if(3 == errFlg)						//读取pin状态
	{
		if(result)
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,口令错误阀值为: %d,当前pin状态: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 1)
				PrintOut("\r\n隐藏区,口令错误阀值为: %d,当前pin状态为: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 2)
				PrintOut("\r\n安全区,口令错误阀值为: %d,当前pin状态为: %d \r\n",errSetVal,errReturnVal);
			if(subArea == 3)
				PrintOut("\r\n管理员,口令错误阀值为: %d,当前pin状态为: %d \r\n",errSetVal,errReturnVal);
		}
		else
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,pin状态读取失败 \r\n");
			if(subArea == 1)
				PrintOut("\r\n隐藏区,pin状态读取失败 \r\n");
			if(subArea == 2)
				PrintOut("\r\n安全区,pin状态读取失败 \r\n");
			if(subArea == 3)
				PrintOut("\r\n管理员,pin状态读取失败 \r\n");
		}
	}
	else if(4 == errFlg)						//更新设备对称密钥
	{
		if(result)
		{
			if(subArea == 0)
				PrintOut("\r\n普通用户,密钥更新成功 \r\n");
			else if(subArea == 3)
				PrintOut("\r\n管理员用户,密钥更新成功 \r\n");
			else
				PrintOut("\r\n密钥更新失败 \r\n");
		}
		else
		{
			PrintOut("\r\n密钥更新失败 \r\n");
		}
	}
}


void CZfDLLAppDlg::OnButton2() 
{
	// TODO: Add your control notification handler code here
	ISOPath = "";
	
	CFileDialog dlg(TRUE);         //TRUE为OPEN对话框，FALSE为SAVE AS对话框 
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	if(dlg.DoModal() == IDOK)
	{
		ISOPath = dlg.GetPathName(); 
		SetDlgItemText(IDC_EDIT2,ISOPath);
		PrintOut("\r\nISO文件打开成功! \r\n");
	}
	else
	{
		PrintOut("\r\nISO文件打开失败! \r\n");
	}
}

void CZfDLLAppDlg::OnUpdateISO() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	UINT8 resp[512];
	ULONG resp_len = 512;
	UINT8 cmd[256];
	const char *fileAddr = ISOPath;

	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}
	
	PrintOut("\r\nISO 开始下载，请稍侯 !\r\n");
	
	result = masKU_UpdateISO(zfHandle,fileAddr);
	
	if(result)
		PrintOut("\r\nISO 下载成功 !\r\n");
	else
		PrintOut("\r\nISO 下载失败 !\r\n");

	memcpy(cmd, "\x80\xff\x00\x00\x01\x00\x40", 7);
	if (masKU_APDU(zfHandle, 0, cmd, 7, resp, &resp_len))
	{
		PrintOut("\r\n媒体刷新失败\r\n");
	}
	if (!memcmp(resp, "\x90\x00", 2))
	{
		PrintOut("\r\n媒体刷新完成 !\r\n");
	}
	else
	{
		PrintOut("\r\n媒体刷新失败111\r\n");
	}
}

void CZfDLLAppDlg::OnWriteHide3() 
{
	// TODO: Add your control notification handler code here
	MASKU_INFO zfUsb;

	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	if(FALSE == masKU_GetDiskInfo(zfHandle,&zfUsb))	//读参数不正确
	{
		PrintOut("\r\n获取分区属性失败!\r\n");
		return;
	}
	
	if(zfUsb.diskQuantity & 0x08000000)
		PrintOut("\r\nU盘区当前属性为：读写!\r\n");
	else
		PrintOut("\r\nU盘区当前属性为：只读!\r\n");
}

void CZfDLLAppDlg::OnPwdChange4() 
{
	// TODO: Add your control notification handler code here
	bool result = 0;
	
	if(zfHandle == INVALID_HANDLE_VALUE)
	{
		PrintOut("请先打开设备！\r\n");
		return;
	}

	result = masKU_LogoutSecurityDisk(zfHandle);
	
	if(result)
	{
		PrintOut("\r\n设备登出成功 !\r\n");
	}
	else
		PrintOut("\r\n设备登出失败 !\r\n");

	//masKU_Close(zfHandle);
}

void CZfDLLAppDlg::OnCancel2() 
{
	// TODO: Add your control notification handler code here
	if(masKU_Destroy(zfHandle,0,0))
	{
		PrintOut("\r\n恢复出厂成功 !\r\n");
	}
	else
		PrintOut("\r\n恢复出厂失败 !\r\n");

	masKU_Close(zfHandle);
}

void CZfDLLAppDlg::OnGetTime2() 
{
	// TODO: Add your control notification handler code here
	bool result;
	MASKU_TIMER USBTime;
	
	result = masKU_Time(zfHandle,3,&USBTime);
	
	if(result)
	{
		PrintOut("\r\n初始化成功!当前时间：%4d年%2d月%2d日%2d时%2d分%2d秒,星期%d",USBTime.year,USBTime.month,USBTime.day,USBTime.hour,USBTime.minute,USBTime.seconds,USBTime.weekday);
	}
	else
	{
		PrintOut("\r\n初始化失败 !\r\n");
	}
}

void CZfDLLAppDlg::OnWriteHide4() 
{
	// TODO: Add your control notification handler code here
	unsigned char cmdBuf[8192+16];
	unsigned char recvBuf[8192+16];
	unsigned long recvLen=8192;
	unsigned int i;
	
	memcpy(cmdBuf,"\xef\x01\xff\xff\xff\xff\x01\x00\x03\x01\x00\x05",12);	//录入图像
	//memcpy(cmdBuf,"\xef\x01\xff\xff\xff\xff\x01\x00\x03\x0f\x00\x13",12);	//读系统基本参数
	
	if(0 == masKU_APDU(zfHandle,1,cmdBuf,12,recvBuf,&recvLen))
	{
		PrintOut("接收数据长度%4d：\r\n",recvLen);
		for(i=0;i<recvLen;i++)
		{
			PrintOut("%02x ",recvBuf[i]);
			if(((i+1)%16) == 0)	PrintOut("\r\n");
		}
		PrintOut("\r\n");
	}
}

void CZfDLLAppDlg::OnWriteHide5() 
{
	// TODO: Add your control notification handler code here
	unsigned char cmdBuf[8192+16];
	unsigned char recvBuf[8192+16];
	unsigned long recvLen=8192;
	unsigned int i;
	unsigned char imageBuf[72*1024]={'\0'};	//图像缓存区
	unsigned int imageP=0;
	unsigned int imageCnt=0;

	memcpy(cmdBuf,"\xef\x01\xff\xff\xff\xff\x01\x00\x03\x0a\x00\x0e",12);	//上传图像
	
	if(0 == masKU_APDU(zfHandle,1,cmdBuf,12,recvBuf,&recvLen))
	{
		PrintOut("应答数据长度%4d：\r\n",recvLen);
		for(i=0;i<recvLen;i++)
		{
			PrintOut("%02x ",recvBuf[i]);
			if(((i+1)%16) == 0)	PrintOut("\r\n");
		}
		PrintOut("\r\n");

		if(recvBuf[9]!=0)	//表示接着发送后续数据包
		{
			PrintOut("上传图像命令应答成功，但无后续数据包\r\n");
			return;
		}
		else
			PrintOut("上传图像命令应答成功，开始接收后续数据包\r\n");
	}
	else
	{
		PrintOut("上传图像命令应答失败\r\n");
		return;
	}

_PRINT_INFO:
	recvLen=8192;
	if(0 == masKU_APDU(zfHandle,1,NULL,0,recvBuf,&recvLen))
	{
		memcpy(&imageBuf[imageP],recvBuf,recvLen);
		imageP+=recvLen;
		imageCnt++;
		
		if(recvBuf[6]==0x02)	//表示有后续数据包要接收
		{
			goto _PRINT_INFO;
		}
		else if(recvBuf[6]==0x08)	//表示数据包接收完成
		{
			PrintOut("图像数据获取成功，共接收 %4d 包\r\n",imageCnt);
			return;
		}
	}
	else
		PrintOut("图像数据获取失败\r\n");
}

void CZfDLLAppDlg::OnWriteHide6() 
{
	// TODO: Add your control notification handler code here
	if(masKU_SoftRestart(zfHandle))
	{
		PrintOut("\r\n软复位成功 !\r\n");
	}
	else
		PrintOut("\r\n软复位失败 !\r\n");

	masKU_Close(zfHandle);
}



#define  REVERSE_FLAG			1										// 数据反转标志,=1反转


//以字节为单位，在字(4B)内 大小端转换
void reverse_data1(void *data_buf, unsigned int char_len)
{
	unsigned char temp;
	unsigned char	*ptr;
	unsigned int i;

	ptr = (unsigned char *)data_buf;

	for(i=0; i<char_len; i=i+4)
	{
		temp = *(ptr+i);
		*(ptr+i) = *(ptr+3+i);
		*(ptr+3+i) = temp;

		temp = *(ptr+1+i);
		*(ptr+1+i) = *(ptr+2+i);
		*(ptr+2+i) = temp;		
	}
}
//
void reverse_word(unsigned int *src_data, unsigned int data_len)
{
	unsigned int i,tmp = 0;

	data_len --;
	for(i=0; i<=data_len; i++,data_len--)
	{
		tmp = src_data[i];
		src_data[i] = src_data[data_len];
		src_data[data_len] = tmp;
	}
}

#define  SR_LEN						(1024*32)						//流加解密单次最大数据包，字节
void CZfDLLAppDlg::OnBnClickedWritehide7()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned long testCnt=SR_LEN;	//控制多少MB，转换为字节
	unsigned char sBuf[SR_LEN];
	unsigned char rBuf[SR_LEN];
	unsigned long resLen=SR_LEN;
	unsigned char edKey[16]={0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10};	//密钥
	unsigned char sm4Plain[SR_LEN]={"1234567812345678"};	//sm4原始明文数据
	UINT32 i;

	if (INVALID_HANDLE_VALUE == zfHandle)
	{
		PrintOut("未打开设备\r\n");
		return;
	}


	//********************* sm4 ecb模式加密测试 *********************
	PrintOut("sm4密钥：\r\n");
	for(i=0;i<16;i++)	//只打印16B
	{
		PrintOut("%x",edKey[i]);
	}
	PrintOut("\r\nsm4明文：\r\n");
	for(i=0;i<16;i++)	//只打印16B
	{
		PrintOut("%x",sm4Plain[i]);
	}
	PrintOut("\r\n");
	secu_crypto_cfg(zfHandle, SM4, edKey, 16);
	//secu_crypto_enc(zfHandle);
	masKU_EncDec(zfHandle,0,ENC,0,NULL,0,NULL, sm4Plain,16, rBuf,&resLen);
	
	PrintOut("开始加密...\r\n");
	PrintOut("\r\nsm4密文：\r\n");
	for (i = 0; i < resLen; i++)	//只打印16B
	{
		PrintOut("%x", rBuf[i]);
	}
	PrintOut("\r\n");
	secu_crypto_dec(zfHandle);
	masKU_EncDec(zfHandle, 0, DEC, 0, NULL, 0, NULL, rBuf, resLen, sBuf, &testCnt);
	
	PrintOut("开始解密...\r\n");
	PrintOut("sm4明文：\r\n");
	for (i = 0; i < 16; i++)	//只打印16B
	{
		PrintOut("%x", sBuf[i]);
	}
	PrintOut("\r\n");
	
}

void CZfDLLAppDlg::OnBnClickedReadhide3()
{
	// TODO: 在此添加控件通知处理程序代码
	//main_test();
}

void CZfDLLAppDlg::OnBnClickedGetcddvd2()
{
	unsigned int i;
	unsigned char deviceCnt=0;
	char* path[16] = {'\0'};
	unsigned short usbVID = 0;//0x6673;
	unsigned short usbPID = 0;//0x1234;
	CString str_tmp = "";
	CString DiskStr1 = "udisk_keyu";
	GetDlgItemText(IDC_EDIT5,DiskStr1);				//得到输入盘符
	if(strlen(DiskStr1) > 16)
	{
		PrintOut("产品信息 长度最大16字节，请重新输入! \r\n");
		return;
	}
	//DiskStr1.erase(DiskStr1.find_last_not_of(" ") + 1);
	DiskStr1.Replace(" ", "");
	DiskStr1 = "u" + DiskStr1;

	//得到vid,pid
	UpdateData(TRUE);
	GetDlgItemText(IDC_DISK_VID, str_tmp);
	sscanf(str_tmp.GetBuffer(str_tmp.GetLength()), "%04x", &m_vid);
	str_tmp.ReleaseBuffer();
	GetDlgItemText(IDC_DISK_PID, str_tmp);
	sscanf(str_tmp.GetBuffer(str_tmp.GetLength()), "%04x", &m_pid);
	str_tmp.ReleaseBuffer();
	usbVID = m_vid;
	usbPID = m_pid;

	for (int i=0; i<16; i++)  
	{  
		path[i] = (char*)malloc(512);  
	}
	
	DWORD timsStart,timeEnd,timeVal;
	timsStart = timeGetTime();

	deviceCnt = masKU_Scan_GUID(path ,usbVID ,usbPID, (LPSTR)(LPCTSTR)DiskStr1);
	//deviceCnt = masKU_Scan_GUID(path ,0xe83d ,0x0f73, "Sz1204          ");
	timeEnd = timeGetTime();
	timeVal = timeEnd - timsStart;
	
	if(deviceCnt)
	{
		PrintOut("查找到%2d个设备,地址如下：\r\n",deviceCnt);

		for(i=0;i<deviceCnt;i++)
		{
			PrintOut("%s \r\n",path[i]);
		}
		PrintOut("\r\n");

		zfHandle = masKU_Open_GUID(path[0]);	//打开头一个设备
		if(zfHandle == INVALID_HANDLE_VALUE)
			PrintOut("打开第1个设备失败! \r\n");
		else
			PrintOut("打开第1个设备成功! \r\n");
	}
	else
		PrintOut("查找设备失败! \r\n");

	for (i=0; i<16; i++)  
	{  
		free(path[i]);  
	}
}


void CZfDLLAppDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	unsigned char cmdBuf[4096];
	unsigned char recvBuf[4096];
	unsigned long recvLen = 4096;
	memcpy(cmdBuf, "\x80\xff\x00\x00\x01\x00\x0d",7);	//录入图像
	masKU_APDU(zfHandle, 0, cmdBuf, 7, recvBuf, &recvLen);

}


void CZfDLLAppDlg::OnEnChangeCdCapacity()
{
	INT rem_cap;
	rem_cap = zfUsb.AllDiskCapacity - GetDlgItemInt(IDC_CD_CAPACITY) - GetDlgItemInt(IDC_U_CAPACITY) - GetDlgItemInt(IDC_S_CAPACITY) - GetDlgItemInt(IDC_H_CAPACITY);
	SetDlgItemInt(IDC_STATIC_REM, rem_cap);
}


void CZfDLLAppDlg::OnEnChangeUCapacity()
{
	INT rem_cap;
	rem_cap = zfUsb.AllDiskCapacity - GetDlgItemInt(IDC_CD_CAPACITY) - GetDlgItemInt(IDC_U_CAPACITY) - GetDlgItemInt(IDC_S_CAPACITY) - GetDlgItemInt(IDC_H_CAPACITY);
	SetDlgItemInt(IDC_STATIC_REM, rem_cap);
}


void CZfDLLAppDlg::OnEnChangeSCapacity()
{
	INT rem_cap;
	rem_cap = zfUsb.AllDiskCapacity - GetDlgItemInt(IDC_CD_CAPACITY) - GetDlgItemInt(IDC_U_CAPACITY) - GetDlgItemInt(IDC_S_CAPACITY) - GetDlgItemInt(IDC_H_CAPACITY);
	SetDlgItemInt(IDC_STATIC_REM, rem_cap);
}


void CZfDLLAppDlg::OnEnChangeHCapacity()
{
	INT rem_cap;
	rem_cap = zfUsb.AllDiskCapacity - GetDlgItemInt(IDC_CD_CAPACITY) - GetDlgItemInt(IDC_U_CAPACITY) - GetDlgItemInt(IDC_S_CAPACITY) - GetDlgItemInt(IDC_H_CAPACITY);
	SetDlgItemInt(IDC_STATIC_REM, rem_cap);
}


void CZfDLLAppDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnClose();
	CDialog::OnCancel();
	//CDialog::OnDestory();
	//CDialog::PostNcDestroy();
}


void CZfDLLAppDlg::OnBnClickedColFp()
{
	// TODO: 在此添加控件通知处理程序代码


	fp_toy_occ(zfHandle, 1);
	while (1) {
		//PrintOut("请按下手指\r\n");
		if (fp_toy_get_img(zfHandle)) {
			break;
		}
		Sleep(100);
	}
	fp_toy_occ(zfHandle, 0);
	PrintOut("采集指纹完成\r\n");
}


void CZfDLLAppDlg::OnBnClickedUpImg()
{
	// TODO: 在此添加控件通知处理程序代码
	uint8 buf[20480];
	int32 len;
	int32 i;

	fp_toy_occ(zfHandle, 1);
	len = fp_up_img(zfHandle, buf);
	fp_toy_occ(zfHandle, 0);

	for (i = 0; i < len; i++)
	{
		PrintOut("%02x", buf[i]);
	}
	PrintOut("采集数据上传完成\r\n");
}


void CZfDLLAppDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	uint8 buf[1024];
	uint8 buf1[1024];
	uint32 i;
	for (i = 0; i < 1024; i++)
	{
		buf[i] = i % 1024;
	}

	masKU_WriteAppNor(zfHandle,0,1024,buf,0);
	PrintOut("写数据成功\r\n");

	masKU_ReadAppNor(zfHandle, 0, 1024, buf1, 0);
	PrintOut("读数据成功\r\n");

	if (memcmp(buf, buf1, 1024))
	{
		PrintOut("数据对比失败\r\n");
		return;
	}
	PrintOut("数据对比成功\r\n");
}


void CZfDLLAppDlg::OnBnClickedCipid()
{
	// TODO: 在此添加控件通知处理程序代码
	uint32 i;
	uint8 buf[1024];
	uint32 len;
	len = secu_get_chipid(zfHandle, buf);
	PrintOut("芯片ID获取成功\r\n");
	for(i = 0; i < len; i++)
	{
		PrintOut("%02x", buf[i]);
	}
}


DWORD WINAPI TestWThread(void *arg) {
	CZfDLLAppDlg * pParentDlg = (CZfDLLAppDlg*)arg;
	unsigned int time_ms1, time_ms;
	unsigned int i;
	unsigned int result = 0;				//错误计数	
	unsigned int SecAddr = 0;				//读的起始地址
	unsigned int SecCnt = 10;				//数据大小，单位MB
	unsigned int sectorSize = 512;	//设备扇区大小
	unsigned int SecPerR = 0;
	int CycleCount = 0;
	CString secr;
	MASKU_INFO zfUsb;

	pParentDlg->GetDlgItem(IDC_PSEC)->GetWindowTextA(secr);
	if (secr.IsEmpty()) {
		SecPerR = 1;
	}
	else {
		SecPerR = atoi(secr.GetBuffer());
	}

	pParentDlg->GetDlgItem(IDC_EDIT_CYCLE)->GetWindowTextA(secr);
	if (secr.IsEmpty()) {
		CycleCount = 1;
	}
	else {
		CycleCount = atoi(secr.GetBuffer());
	}


	masKU_GetDiskInfo(zfHandle, &zfUsb);
	sectorSize = zfUsb.unit;

	if (zfHandle == INVALID_HANDLE_VALUE)
	{
		pParentDlg->PrintOut("请先打开设备！\r\n");
		pParentDlg->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		pParentDlg->GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		return 0;
	}
	pParentDlg->PrintOut("隐藏区大小 %d MB\r\n", zfUsb.hDiskCapacity);
	pParentDlg->PrintOut("本次测试每次读写%d个扇区\r\n", SecPerR);

	BYTE *pbuf = (BYTE *)malloc(SecPerR * sectorSize);

	if (((CButton *)(pParentDlg->GetDlgItem(IDC_RADIOR00)))->GetCheck()) {
		memset(pbuf, 0, SecPerR*sectorSize);
	}
	else {
		memset(pbuf, 0xff, SecPerR*sectorSize);
	}
	long long wantwritesize = zfUsb.hDiskCapacity;
	wantwritesize *= 1024 * 1024;


	while (!pParentDlg->m_bIsWriteQuit && CycleCount>0) {
		pParentDlg->PrintOut("第%d次写测试\r\n", CycleCount);
		time_ms1 = timeGetTime();
		long long writesize = 0;
		unsigned int writelua = 0;
		while (!pParentDlg->m_bIsWriteQuit && wantwritesize > (writesize + SecPerR * sectorSize)) {
			if (0 == masKU_WriteHideDisk(zfHandle, writelua, SecPerR, pbuf, 0))
			{
				pParentDlg->PrintOut("写隐藏区 %d 扇区失败 退出\r\n", writelua);
				pParentDlg->m_bIsWriteQuit = TRUE;

			}
			
			//pParentDlg->PrintOut(".");
			WPARAM wparam = writesize * 100 / wantwritesize;
			pParentDlg->PostMessageA(WM_UPOS, wparam, 0);
			writesize += SecPerR * sectorSize;
			writelua += SecPerR;
		}
		time_ms = timeGetTime() - time_ms1;
		if (time_ms == 0)time_ms = 1;
		pParentDlg->PrintOut("写隐藏区 %lld MB  用时 %d ms \r\n", writesize / 1024 / 1024, time_ms);
		pParentDlg->PrintOut("操作完成! 速度 %d MB/S \r\n", writesize * 1000 / time_ms / 1024 / 1024);


		CycleCount--;
	}
	if (pbuf != NULL) {
		free(pbuf);
		pbuf = NULL;
	}
	
	pParentDlg->OnBnClickedButton8();
	pParentDlg->PrintOut("写测试结束\r\n");
	return 0;
}

DWORD WINAPI TestThread(void *arg) {
	CZfDLLAppDlg * pParentDlg = (CZfDLLAppDlg*)arg;
	unsigned int time_ms1, time_ms;
	unsigned int i;
	unsigned int result = 0;				//错误计数	
	unsigned int SecAddr = 0;				//读的起始地址
	unsigned int SecCnt = 10;				//数据大小，单位MB
	unsigned int sectorSize = 512;	//设备扇区大小
	unsigned int SecPerR = 0;
	int CycleCount = 0;
	CString secr;
	MASKU_INFO zfUsb;

	pParentDlg->GetDlgItem(IDC_PSEC)->GetWindowTextA(secr);
	if (secr.IsEmpty()) {
		SecPerR = 1;
	}
	else {
		SecPerR = atoi(secr.GetBuffer());
	}

	pParentDlg->GetDlgItem(IDC_EDIT_CYCLE)->GetWindowTextA(secr);
	if (secr.IsEmpty()) {
		CycleCount = 1;
	}
	else {
		CycleCount = atoi(secr.GetBuffer());
	}
	

	masKU_GetDiskInfo(zfHandle, &zfUsb);
	sectorSize = zfUsb.unit;

	if (zfHandle == INVALID_HANDLE_VALUE)
	{
		pParentDlg->PrintOut("请先打开设备！\r\n");
		pParentDlg->GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		pParentDlg->GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);
		return 0;
	}
	pParentDlg->PrintOut("隐藏区大小 %d MB\r\n", zfUsb.hDiskCapacity);
	pParentDlg->PrintOut("本次测试每次读写%d个扇区\r\n", SecPerR);
	
	BYTE *pbuf = (BYTE *)malloc(SecPerR * sectorSize);
	BYTE * pcmpbuf = (BYTE *)malloc(SecPerR * sectorSize);

	if (((CButton *)(pParentDlg->GetDlgItem(IDC_RADIOR00)))->GetCheck()) {
		memset(pcmpbuf, 0, SecPerR*sectorSize);
	}
	else {
		memset(pcmpbuf, 0xff, SecPerR*sectorSize);
	}
	long long wantreadsize = zfUsb.hDiskCapacity;
	wantreadsize *= 1024 * 1024;

	
	while (!pParentDlg->m_bIsTestQuit && CycleCount>0) {
		pParentDlg->PrintOut("第%d次测试\r\n", CycleCount);
		time_ms1 = timeGetTime();
		long long readsize = 0;
		unsigned int readlua = 0;
		while (!pParentDlg->m_bIsTestQuit && wantreadsize > (readsize + SecPerR * sectorSize)) {
			if (0 == masKU_ReadHideDisk(zfHandle, readlua, SecPerR, pbuf, 0))
			{
				pParentDlg->PrintOut("读隐藏区 %d 扇区失败 退出\r\n", readlua);
				pParentDlg->m_bIsTestQuit = TRUE;
				
			}
			if (memcmp(pbuf, pcmpbuf, SecPerR * sectorSize) != 0) {
				pParentDlg->PrintOut("隐藏区 %d 扇区开始的数据错误失败 退出\r\n", readlua);
				pParentDlg->m_bIsTestQuit = TRUE;
			}
			//pParentDlg->PrintOut(".");
			WPARAM wparam = readsize * 100 / wantreadsize;
			pParentDlg->PostMessageA(WM_UPOS, wparam, 0);
			readsize += SecPerR * sectorSize;
			readlua += SecPerR;
		}
		time_ms = timeGetTime() - time_ms1;
		if (time_ms == 0)time_ms = 1;
		pParentDlg->PrintOut("读隐藏区 %lld MB  用时 %d ms \r\n", readsize/1024/1024, time_ms);
		pParentDlg->PrintOut("操作完成! 速度 %d MB/S \r\n", readsize * 1000 / time_ms / 1024 / 1024);


		CycleCount--;
	}
	if (pbuf != NULL) {
		free(pbuf);
		pbuf = NULL;
	}
	if (pcmpbuf != NULL) {
		free(pcmpbuf);
		pcmpbuf = NULL;
	}
	pParentDlg->OnBnClickedButton5();
	pParentDlg->PrintOut("读测试结束\r\n");
	return 0;
}



void CZfDLLAppDlg::OnBnClickedButton4()
{
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	//GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	if (hTestThread != INVALID_HANDLE_VALUE) {
		//PrintOut("上一次测试没有关闭，结束中\r\n");
		m_bIsTestQuit = TRUE;
		WaitForSingleObject(hTestThread, INFINITE);
		CloseHandle(hTestThread);
		hTestThread = INVALID_HANDLE_VALUE;
		//PrintOut("请重新点击开始按钮!!\r\n");
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
		return;
	}
	
	m_bIsTestQuit = FALSE;
	hTestThread = CreateThread(NULL, 0, TestThread, this, 0, NULL);
	if (hTestThread != INVALID_HANDLE_VALUE) {
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON5)->EnableWindow(TRUE);
	}
}


void CZfDLLAppDlg::OnBnClickedButton5()
{
	GetDlgItem(IDC_BUTTON5)->EnableWindow(FALSE);

	if (hTestThread != INVALID_HANDLE_VALUE) {
		m_bIsTestQuit = TRUE;
		WaitForSingleObject(hTestThread, 2000);
		CloseHandle(hTestThread);
		hTestThread = INVALID_HANDLE_VALUE;
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	}
	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
}


void CZfDLLAppDlg::OnBnClickedButton7()
{
	GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);

	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	if (hWriteThread != INVALID_HANDLE_VALUE) {
		//PrintOut("上一次测试没有关闭，结束中\r\n");
		m_bIsWriteQuit = TRUE;
		WaitForSingleObject(hWriteThread, INFINITE);
		CloseHandle(hWriteThread);
		hWriteThread = INVALID_HANDLE_VALUE;
		//PrintOut("请重新点击开始按钮!!\r\n");
		GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);

		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
		return;
	}

	m_bIsWriteQuit = FALSE;
	hWriteThread = CreateThread(NULL, 0, TestWThread, this, 0, NULL);
	if (hWriteThread != INVALID_HANDLE_VALUE) {
		GetDlgItem(IDC_BUTTON7)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON8)->EnableWindow(TRUE);
	}
}


void CZfDLLAppDlg::OnBnClickedButton8()
{
	GetDlgItem(IDC_BUTTON8)->EnableWindow(FALSE);
	if (hWriteThread != INVALID_HANDLE_VALUE) {
		m_bIsWriteQuit = TRUE;
		WaitForSingleObject(hWriteThread, 2000);
		CloseHandle(hWriteThread);
		hWriteThread = INVALID_HANDLE_VALUE;
		GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
	}
	GetDlgItem(IDC_BUTTON7)->EnableWindow(TRUE);

	GetDlgItem(IDC_BUTTON4)->EnableWindow(TRUE);
}
