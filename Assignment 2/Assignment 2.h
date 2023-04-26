
// Assignment 2.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CAssignment2App:
// Сведения о реализации этого класса: Assignment 2.cpp
//

class CAssignment2App : public CWinApp
{
public:
	CAssignment2App();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CAssignment2App theApp;
