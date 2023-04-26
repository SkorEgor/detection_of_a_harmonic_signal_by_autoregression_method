
// Assignment 2Dlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "Assignment 2.h"
#include "Assignment 2Dlg.h"
#include "afxdialogex.h"
#include "Drawer.h"
#include <vector>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
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


// Диалоговое окно CAssignment2Dlg



CAssignment2Dlg::CAssignment2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ASSIGNMENT2_DIALOG, pParent)
	, input_f1(2)
	, input_f2(10)
	, input_f3(5)
	, input_n0(350)
	, input_n1(700)
	, input_N(1000)
	, input_fd(200)
	, t(0.03)
	, T(20)
	, out_n0(0)
	, out_n1(0)
	, out_del_n0(0)
	, out_del_n1(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAssignment2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, input_f1);
	DDX_Text(pDX, IDC_EDIT2, input_f2);
	DDX_Text(pDX, IDC_EDIT3, input_f3);
	DDX_Text(pDX, IDC_EDIT4, input_n0);
	DDX_Text(pDX, IDC_EDIT5, input_n1);
	DDX_Text(pDX, IDC_EDIT6, input_N);
	DDX_Text(pDX, IDC_EDIT7, input_fd);
	DDX_Text(pDX, IDC_EDIT8, t);
	DDX_Text(pDX, IDC_EDIT9, T);
	DDX_Text(pDX, IDC_STATIC3, out_n0);
	DDX_Text(pDX, IDC_STATIC4, out_n1);
	DDX_Text(pDX, IDC_STATIC5, out_del_n0);
	DDX_Text(pDX, IDC_STATIC6, out_del_n1);
}

BEGIN_MESSAGE_MAP(CAssignment2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_STN_CLICKED(IDC_STATIC1, &CAssignment2Dlg::OnStnClickedStatic1)
	ON_BN_CLICKED(IDC_BUTTON1, &CAssignment2Dlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CAssignment2Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CAssignment2Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CAssignment2Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CAssignment2Dlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CAssignment2Dlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CAssignment2Dlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CAssignment2Dlg::OnEnChangeEdit7)
	ON_STN_CLICKED(IDC_STATIC2, &CAssignment2Dlg::OnStnClickedStatic2)
	ON_EN_CHANGE(IDC_EDIT8, &CAssignment2Dlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CAssignment2Dlg::OnEnChangeEdit9)
	ON_STN_CLICKED(IDC_STATIC3, &CAssignment2Dlg::OnStnClickedStatic3)
	ON_STN_CLICKED(IDC_STATIC4, &CAssignment2Dlg::OnStnClickedStatic4)
	ON_STN_CLICKED(IDC_STATIC5, &CAssignment2Dlg::OnStnClickedStatic5)
	ON_STN_CLICKED(IDC_STATIC6, &CAssignment2Dlg::OnStnClickedStatic6)
END_MESSAGE_MAP()


// Обработчики сообщений CAssignment2Dlg

BOOL CAssignment2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
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

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	drv.Create(GetDlgItem(IDC_STATIC1)->GetSafeHwnd());
	drv2.Create(GetDlgItem(IDC_STATIC2)->GetSafeHwnd());
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CAssignment2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CAssignment2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CAssignment2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAssignment2Dlg::OnStnClickedStatic1()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void CAssignment2Dlg::OnBnClickedButton1()
{
	//Задание первое - отрисовать соединенные между собой  синусоиды
	double initial_phase = 0;									//Значение начальной фазы
	vector<double>  list_t;										
	vector<double>  list_x;

	for (int n = 0; n <= input_n0; n++)	{						//График 1 сигнала, от начала до n0
		list_t.push_back(n /input_fd);
		list_x.push_back(sin(2 * pi * input_f1 * list_t[n] + initial_phase));
	}
	initial_phase = 2 * pi * input_f1 * ((input_n0) / input_fd);	//Высчитываем фазу, в n0
	for (int n = input_n0+1; n <= input_n1; n++)	{				//График 2 сигнала
		list_t.push_back(n / input_fd);
		list_x.push_back(sin(2 * pi * input_f2 * ((n - input_n0) / input_fd) + initial_phase));
	}
	initial_phase = 2 * pi * input_f2 * ((input_n1 - input_n0) / input_fd) + initial_phase;
	for (int n = input_n1+1; n < input_N; n++)	{				//График 3 сигнала
		list_t.push_back(n / input_fd);
		list_x.push_back(sin(2 * pi * input_f3 * ((n - input_n1) / input_fd) + initial_phase));
	}

	drv.Draw(	list_x, -1.25, 1.25,
				list_t, 0, input_N/ input_fd,
				true,
				input_n0, input_n1);
	

	vector<double>  list_deviation_t;
	vector<double>  list_deviation_x;
	double max_x=0;
	for (int n = 2; n < input_N-2; n++) {
		list_deviation_t.push_back(n / input_fd);
		list_deviation_x.push_back(abs(list_x[n] - (list_x[n - 1] * (2 * cos(2 * pi * input_f2*(1 / input_fd))) - list_x[n - 2])));
		if (max_x < list_deviation_x[n - 2]) max_x = list_deviation_x[n - 2];
	}
	
	//Фильтр 
	//Для T = 2, функция окна:
	//     -2 -1 0 1 2
	vector<double>  average_error_x;
	vector<double>  average_error_y;
	int average_error_t0 = T+2;
	int number_samples = T * 2 + 1; //Окно состоит из T отсчетов влево и вправо (*2); еще +1 на нулевой отсчет
	bool no_start = true;
	for (int n = average_error_t0; n < input_N - average_error_t0; n++) {
		average_error_x.push_back(n / input_fd);

		//Суммирование значений в окне
		double average_error_sum = 0;
		for (int i = -T; i <= T; i++) {
			average_error_sum += list_deviation_x[n + i-2];
		}

		//Среднее значение в окне
		average_error_y.push_back(average_error_sum / number_samples);

		//Поиск начала и конца
		if (average_error_y[n - average_error_t0] < t && no_start) {
			out_n0 = n;
			no_start = false;
		}
		if (average_error_y[n - average_error_t0] < t) out_n1 = n;
	}
	

	//Создадим вектор порогового значения фильтрации
	vector<double>  list_threshold_value;
	for (int n = 0; n < input_N ; n++) list_threshold_value.push_back(t);

	//Передаем аргументы для отрисовывания 2 графика
	drv2.Draw(	list_deviation_x, 0, max_x,					//ось ординат (вертикаль) 
				list_deviation_t, 0, input_N / input_fd,	//ось абсцисс (горизонт)
				true,	input_n0-2, input_n1-2,				//окрашивать интервалы
				true,	list_threshold_value,				//вектор коорд по ординате ПОРОГОВОЕ ЗНАЧЕНИЕ
				average_error_x, average_error_y
			  );

	out_del_n0 = abs(input_n0 - out_n0);
	out_del_n1 = abs(input_n1 - out_n1);

	UpdateData(FALSE);

}

//Ввод частот сигналов
void CAssignment2Dlg::OnEnChangeEdit1() { UpdateData(TRUE); }
void CAssignment2Dlg::OnEnChangeEdit2() { UpdateData(TRUE); }
void CAssignment2Dlg::OnEnChangeEdit3() { UpdateData(TRUE); }

//Ввод границ сигналов
void CAssignment2Dlg::OnEnChangeEdit4() { UpdateData(TRUE); }
void CAssignment2Dlg::OnEnChangeEdit5() { UpdateData(TRUE); }

//Ввод параметров построения
void CAssignment2Dlg::OnEnChangeEdit6() { UpdateData(TRUE); }
void CAssignment2Dlg::OnEnChangeEdit7() { UpdateData(TRUE); }

//Ввод параметров фильтрации
void CAssignment2Dlg::OnEnChangeEdit8() { UpdateData(TRUE); }
void CAssignment2Dlg::OnEnChangeEdit9() { UpdateData(TRUE); }


void CAssignment2Dlg::OnStnClickedStatic2()
{
	// TODO: добавьте свой код обработчика уведомлений
}




void CAssignment2Dlg::OnStnClickedStatic3(){}
void CAssignment2Dlg::OnStnClickedStatic4(){}
void CAssignment2Dlg::OnStnClickedStatic5(){}
void CAssignment2Dlg::OnStnClickedStatic6(){}
