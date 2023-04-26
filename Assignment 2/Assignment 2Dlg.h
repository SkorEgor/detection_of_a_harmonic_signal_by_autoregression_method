
// Assignment 2Dlg.h: файл заголовка
//
#include "Drawer.h"
#pragma once


// Диалоговое окно CAssignment2Dlg
class CAssignment2Dlg : public CDialogEx
{
// Создание
public:
	CAssignment2Dlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ASSIGNMENT2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	Drawer drv;
	Drawer drv2;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStnClickedStatic1();
	afx_msg void OnBnClickedButton1();
	double input_f1;
	double input_f2;
	double input_f3;
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit4();
	afx_msg void OnEnChangeEdit5();
	int input_n0;
	int input_n1;
	int input_N;
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeEdit7();
	double input_fd;
	afx_msg void OnStnClickedStatic2();
	afx_msg void OnEnChangeEdit8();
	afx_msg void OnEnChangeEdit9();
	// Пороговое значение
	double t;
	// граница окна
	int T;
	int out_n0;
	int out_n1;
	afx_msg void OnStnClickedStatic3();
	afx_msg void OnStnClickedStatic4();
	int out_del_n0;
	int out_del_n1;
	afx_msg void OnStnClickedStatic5();
	afx_msg void OnStnClickedStatic6();
};
