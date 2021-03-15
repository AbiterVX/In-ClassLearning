
// 计算器Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "计算器.h"
#include "计算器Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#include"中缀转后缀并计算.h"
using namespace std;

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


// C计算器Dlg 对话框



C计算器Dlg::C计算器Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
	, ReallResult(0),CurrentSymbol1(" ")
	, ResultFormular(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C计算器Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, Result);
	DDX_Text(pDX, IDC_EDIT2, ResultFormular);
}

BEGIN_MESSAGE_MAP(C计算器Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C计算器Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &C计算器Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &C计算器Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &C计算器Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &C计算器Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &C计算器Dlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &C计算器Dlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &C计算器Dlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &C计算器Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &C计算器Dlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON18, &C计算器Dlg::OnBnClickedButton18)
	ON_BN_CLICKED(IDC_BUTTONPLUS, &C计算器Dlg::OnBnClickedButtonplus)
	ON_BN_CLICKED(IDC_BUTTONminus, &C计算器Dlg::OnBnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONmultipled, &C计算器Dlg::OnBnClickedButtonmultipled)
	ON_BN_CLICKED(IDC_BUTTONdivided, &C计算器Dlg::OnBnClickedButtondivided)
	ON_BN_CLICKED(IDC_BUTTONequal, &C计算器Dlg::OnBnClickedButtonequal)
	ON_BN_CLICKED(IDC_BUTTON15, &C计算器Dlg::OnBnClickedButton15)
	ON_BN_CLICKED(IDC_BUTTON16, &C计算器Dlg::OnBnClickedButton16)
	ON_BN_CLICKED(IDC_BUTTONwithdraw, &C计算器Dlg::OnBnClickedButtonwithdraw)
	ON_BN_CLICKED(IDC_BUTTONdelete, &C计算器Dlg::OnBnClickedButtondelete)
	ON_BN_CLICKED(IDC_BUTTONsin, &C计算器Dlg::OnBnClickedButtonsin)
	ON_BN_CLICKED(IDC_BUTTONcos, &C计算器Dlg::OnBnClickedButtoncos)
	ON_BN_CLICKED(IDC_BUTTON10, &C计算器Dlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON11, &C计算器Dlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON12, &C计算器Dlg::OnBnClickedButton12)
END_MESSAGE_MAP()


// C计算器Dlg 消息处理程序

BOOL C计算器Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C计算器Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void C计算器Dlg::OnPaint()
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
HCURSOR C计算器Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}




 /*------------------------------数字与小数点------------------------------------------------*/
void C计算器Dlg::OnBnClickedButton1()
{
	CurrentSymbol1 = "1";
	if (Symbol(CurrentSymbol1))
	{
		Result += "1";
	}	
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton2()
{
	CurrentSymbol1 = "2";
	if (Symbol(CurrentSymbol1))
	{
		Result += "2";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton3()
{
	CurrentSymbol1 = "3";
	if (Symbol(CurrentSymbol1))
	{
		Result += "3";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton4()
{
	CurrentSymbol1 = "4";
	if (Symbol(CurrentSymbol1))
	{
		Result += "4";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton5()
{
	CurrentSymbol1 = "5";
	if (Symbol(CurrentSymbol1))
	{
		Result += "5";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton6()
{
	CurrentSymbol1 = "6";
	if (Symbol(CurrentSymbol1))
	{
		Result += "6";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton7()
{
	CurrentSymbol1 = "7";
	if (Symbol(CurrentSymbol1))
	{
		Result += "7";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton8()
{
	CurrentSymbol1 = "8";
	if (Symbol(CurrentSymbol1))
	{
		Result += "8";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton9()
{
	CurrentSymbol1 = "9";
	if (Symbol(CurrentSymbol1))
	{
		
		Result += "9";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton0()
{
	CurrentSymbol1 = "0";
	if (Symbol(CurrentSymbol1))
	{
		if (Result.GetLength() != 0)
		{
			CString CurrentNumber;
			CurrentNumber = Result.Right(1);

			CString zero;
			zero = "0";

			if (CurrentNumber != zero)
			{
				Result += "0";
			}
		}
		else
		{
			Result += "0";
		}

	}

	
	UpdateData(false);
}



void C计算器Dlg::OnBnClickedButton18()  //小数点
{
	CurrentSymbol1 = ".";



	if (Symbol(CurrentSymbol1))
	{
		if (CurrentPoint != CurrentSymbol1)   // 标记小数点不存在，则添加，
		{
			Result += ".";
		}
		
	}
	CurrentPoint = ".";
	UpdateData(false);
}


/*------------------------------运算符--------------------------------------------*/
void C计算器Dlg::OnBnClickedButtonplus()
{
	CurrentPoint = "";
	CurrentSymbol1 = "+";
	if (Symbol(CurrentSymbol1))
	{
		Result += "+";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButtonminus()
{	
	CurrentPoint = "";
	CurrentSymbol1 = "-";
	if (Symbol(CurrentSymbol1))
	{
		Result += "-";
	}
	
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButtonmultipled()
{
	CurrentPoint = "";
	CurrentSymbol1 = "*";
	if (Symbol(CurrentSymbol1))
	{
		Result += "*";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButtondivided()
{
	CurrentPoint = "";
	CurrentSymbol1 = "/";
	if (Symbol(CurrentSymbol1))
	{
		Result += "/";
	}	
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButtonsin() //sin
{
	CurrentPoint = "";
	CurrentSymbol1 = "sin";
	if (Symbol(CurrentSymbol1))
	{
		Result += "sin(";
		Brackets++;
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButtoncos()  //cos
{
	CurrentPoint = "";
	CurrentSymbol1 = "cos";
	if (Symbol(CurrentSymbol1))
	{
		Result += "cos(";
		Brackets++;
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton10()    //负数
{
	CurrentPoint = "";
	CurrentSymbol1 = "sin";
	if (Symbol(CurrentSymbol1))
	{
		Result += "(-";
		Brackets++;
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton11()    //pow
{
	CurrentPoint = "";
	CurrentSymbol1 = "pow";
	if (Symbol(CurrentSymbol1))
	{
		Result += "^";
	}
	UpdateData(false);
}
void C计算器Dlg::OnBnClickedButton12()     //取余
{
	CurrentPoint = "";
	CurrentSymbol1 = "%";
	if (Symbol(CurrentSymbol1))
	{
		Result += "%";
	}
	UpdateData(false);
}


///////////////////////////////////////////////////

void C计算器Dlg::OnBnClickedButton15()        //前括号
{
	CurrentPoint = "";
	CurrentSymbol1 = "(";
	if (Symbol(CurrentSymbol1))
	{
		Brackets++; 

		Result += "(";
		CurrentSymbol1 = "(";
		UpdateData(false);
	}
	
}
void C计算器Dlg::OnBnClickedButton16()       //后括号
{
	CurrentPoint = "";
	CurrentSymbol1 = ")";
	if (Symbol(CurrentSymbol1))
	{
		if (Brackets != 0)
		{
			Brackets--;

			Result += ")";
			CurrentSymbol1 = ")";
		}
	}
	
	
	UpdateData(false);
}




/*-----------------------------等于：计算------------------------------------*/
void C计算器Dlg::OnBnClickedButtonequal()
{
	UpdateData(true);
	ResultFormular = Result;         //编辑框存入公式


	CString Negative;
	Negative = "(-";
	int negative=Result.Find(Negative);

	CString zero;
	zero = "0";
	while (negative != -1)
	{
		Result.Insert(negative+1, zero);
		negative = Result.Find(Negative);
	}






	///////////////////////////////////////////////////////////////////////
	CString SIN;
	CString COS;
	CString LeftBrackets;
	CString RightBrackets;
	SIN = "sin(";
	COS = "cos(";
	LeftBrackets = "(";
	RightBrackets = ")";

	int EndPosition;
	int SinPosition=Result.Find(SIN);
	
	int Sinbrackets;
	int Cosbrackets;

	while (SinPosition != -1)
	{
		Sinbrackets = 1;
		for (int i = SinPosition + 4;; i++)
		{
			if (Result[i] == LeftBrackets)
			{
				Sinbrackets++;
			}
			else if (Result[i] == RightBrackets)
			{
				Sinbrackets--;
			}

			if (Sinbrackets == 0)
			{
				EndPosition = i;
				break;
			}
		}

		CString SinResult;
		int length= EndPosition- SinPosition - 4;
		SinResult = Result.Mid(SinPosition + 4, length);


		Calculater Sincalculater;            //计算
		CString SinFormula = SinResult + '#';    //转换格式
		double FormulaResult = 0;         //结果

		int sinlen = WideCharToMultiByte(CP_ACP, 0, SinFormula, -1, NULL, 0, NULL, NULL);   //CString转
		char *SinFormular = new char[sinlen + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, SinFormula, -1, SinFormular, sinlen, NULL, NULL);       //char*

		Sincalculater.LeadingIn(SinFormular);                                               //导入。	
		FormulaResult = Sincalculater.Transform();                                       //计算，得出结果
		FormulaResult = sin(FormulaResult*acos(-1.0) /180);

		CString SINresult;
		SINresult=Sincalculater.DoubleToCString(FormulaResult);

		CString SIN;
		SIN = "sin(";
		SinResult = SIN + SinResult+ ')';
		Result.Replace(SinResult, SINresult);

		SinPosition = Result.Find(SIN);
	}
	

	int CosPosition = Result.Find(COS);
	while (CosPosition != -1)
	{
		Cosbrackets = 1;
		for (int i = CosPosition + 4;; i++)
		{
			if (Result[i] == LeftBrackets)
			{
				Cosbrackets++;
			}
			else if (Result[i] == RightBrackets)
			{
				Cosbrackets--;
			}

			if (Cosbrackets == 0)
			{
				EndPosition = i;
				break;
			}
		}

		CString CosResult;
		CosResult = Result.Mid(CosPosition + 4, EndPosition - CosPosition -4 );


		Calculater Coscalculater;            //计算
		CString CosFormula = CosResult + '#';    //转换格式
		double FormulaResult = 0;         //结果

		int sinlen = WideCharToMultiByte(CP_ACP, 0, CosFormula, -1, NULL, 0, NULL, NULL);   //CString转
		char *CosFormular = new char[sinlen + 1];                                           //
		WideCharToMultiByte(CP_ACP, 0, CosFormula, -1, CosFormular, sinlen, NULL, NULL);       //char*

		Coscalculater.LeadingIn(CosFormular);                                               //导入。	
		FormulaResult = Coscalculater.Transform();                                       //计算，得出结果
		FormulaResult = cos(FormulaResult*acos(-1.0) / 180);

		CString COSresult;
		COSresult = Coscalculater.DoubleToCString(FormulaResult);
		CString COS;
		COS = "cos(";
		CosResult = COS + CosResult + ')';
		Result.Replace(CosResult, COSresult);

		CosPosition = Result.Find(COS);	
	}
////////////////////////////////////////////////////////////////////////////////////////////////////






	Calculater calculater;            //计算
	CString Formula= Result + '#';    //转换格式
	double FormulaResult = 0;         //结果

	int len = WideCharToMultiByte(CP_ACP, 0, Formula, -1, NULL, 0, NULL, NULL);   //CString转
	char *Formular = new char[len + 1];                                           //
	WideCharToMultiByte(CP_ACP, 0, Formula, -1, Formular, len, NULL, NULL);       //char*


	calculater.LeadingIn(Formular);                                               //导入。	
	FormulaResult = calculater.Transform();                                       //计算，得出结果
	
	Result =calculater.DoubleToCString(FormulaResult);                            //编辑框显示答案

	UpdateData(false);
}




/////////////////////////////////////////////////////////////////////////////////////////////////////
void C计算器Dlg::OnBnClickedButtonwithdraw()           //撤回一位
{
	CString point;
	CString bracketsform;
	CString bracketslatter;
	point = ".";
	bracketsform = "(";
	bracketslatter = ")";


	CString DeleteSymbol;
	DeleteSymbol=Result.Right(1);

	CString DeleteSymbolSinCos;


	DeleteSymbolSinCos = Result.Right(4);
	CString sinbracket;
	CString cosbracket;
	sinbracket = "sin(";
	cosbracket = "cos(";




	if (DeleteSymbolSinCos == sinbracket)
	{
		Result.Delete(Result.GetLength() - 4, 4);
	}

	else if (DeleteSymbolSinCos == cosbracket)
	{
		Result.Delete(Result.GetLength() - 4, 4);
	}

	else
	{
		if (DeleteSymbol == bracketslatter)
		{
			Brackets++;
		}
		else if (DeleteSymbol == bracketsform)
		{
			Brackets--;
		}
		else if (DeleteSymbol == point)
		{
			CurrentPoint = " ";
		}
		Result.Delete(Result.GetLength() - 1, 1);
	}
	
		





	UpdateData(false);
}

void C计算器Dlg::OnBnClickedButtondelete()   //清空
{
	Result = "";
	ResultFormular = "";
	Brackets = 0;
	CurrentPoint = "";
	CurrentSymbol1 = "";

	UpdateData(false);

}


