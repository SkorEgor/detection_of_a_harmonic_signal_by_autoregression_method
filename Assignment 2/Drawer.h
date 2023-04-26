#pragma once

#include <afxwin.h>
#include <vector>
#define pi 3.1415926535897932384626433832795

using namespace std;

class Drawer
{
	// Прямоугольник области рисования.
	CRect frame;
	// Указатель на объект окна, области рисования.
	CWnd* wnd;
	// Контекст рисования, привязанный к области рисования.
	CDC* dc;
	// Контекст рисования, привязанный к памяти.
	CDC memDC;
	// Память для контекста рисования memDC.
	CBitmap bmp;
	// Флаг для отслеживания состояния инициализации класса.
	bool init;
public:
	// Проинициализировать объект класса на основе HWND.
	void Create(HWND hWnd)
	{
		// Получаем указатель на окно.
		wnd = CWnd::FromHandle(hWnd);
		// Получаем прямоугольник окна.
		wnd->GetClientRect(frame);
		// Получаем контекст для рисования в этом окне.
		dc = wnd->GetDC();

		// Создаем буфер-контекст.
		memDC.CreateCompatibleDC(dc);
		// Создаем растр для контекста рисования.
		bmp.CreateCompatibleBitmap(dc, frame.Width(), frame.Height());
		// Выбираем растр для использования буфер-контекстом.
		memDC.SelectObject(&bmp);
		init = true;
	}

	// Нарисовать график по переданным данным.
	void Draw	(
				vector<double>& data, double min_data, double max_data,
				vector<double>& keys, double min_keys, double max_keys,
				bool backlight = false,
				int n0=0, int n1=0,
				bool border = false,
				vector<double> & porog = vector<double>(),
				vector<double> & error_x = vector<double>(), vector<double> & error_y = vector<double>()
				)
	{
		if (!init) return;

		CPen subgrid_pen(PS_DOT, 1, RGB(200, 200, 200));
		CPen grid_pen(PS_SOLID, 1, RGB(0, 0, 0));
		CPen data_pen_red(PS_SOLID, 2, RGB(255, 0, 0));		
		CPen data_pen_green(PS_SOLID, 2, RGB(32, 232, 14));
		CPen data_pen_blue(PS_SOLID, 2, RGB(0, 0, 255));
		CPen data_pen_yellow(PS_SOLID, 2, RGB(128, 128, 0));
		CFont font;
		font.CreateFontW(18, 0, 0, 0,
			FW_DONTCARE,
			FALSE,				// Курсив
			FALSE,				// Подчеркнутый
			FALSE,				// Перечеркнутый
			DEFAULT_CHARSET,	// Набор символов
			OUT_OUTLINE_PRECIS,	// Точность соответствия.	
			CLIP_DEFAULT_PRECIS,//  
			CLEARTYPE_QUALITY,	// Качество
			VARIABLE_PITCH,		//
			TEXT("Times New Roman")		//
		);

		int padding = 20;
		int left_keys_padding = 20;
		int bottom_keys_padding = 10;

		int actual_width = frame.Width() - 2 * padding - left_keys_padding;
		int actual_height = frame.Height() - 2 * padding - bottom_keys_padding;

		int actual_top = padding;
		int actual_bottom = actual_top + actual_height;
		int actual_left = padding + left_keys_padding;
		int actual_right = actual_left + actual_width;

		// Белый фон.
		memDC.FillSolidRect(frame, RGB(255, 255, 255));

		// Рисуем сетку и подсетку.
		unsigned int grid_size = 10;

		memDC.SelectObject(&subgrid_pen);

		for (double i = 0.5; i < grid_size; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		memDC.SelectObject(&grid_pen);

		for (double i = 0.0; i < grid_size + 1; i += 1.0)
		{
			memDC.MoveTo(actual_left + i * actual_width / grid_size, actual_top);
			memDC.LineTo(actual_left + i * actual_width / grid_size, actual_bottom);
			memDC.MoveTo(actual_left, actual_top + i * actual_height / grid_size);
			memDC.LineTo(actual_right, actual_top + i * actual_height / grid_size);
		}

		// Рисуем график.
		if (data.empty()) return;

		if (keys.size() != data.size())
		{
			keys.resize(data.size());
			for (int i = 0; i < keys.size(); i++)
			{
				keys[i] = i;
			}
		}

		memDC.SelectObject(&data_pen_red);

		double data_y_max(max_data), data_y_min(min_data);
		double data_x_max(max_keys), data_x_min(min_keys);

		//Отрисовка графика и графика порога:
		vector<double> y = convert_range(data, actual_top, actual_bottom, data_y_max, data_y_min);
		vector<double> x = convert_range(keys, actual_right, actual_left, data_x_max, data_x_min);

		if (backlight) {
			//Отрисовка графика
			memDC.SelectObject(&data_pen_yellow);
			memDC.MoveTo(x[0], y[0]);
			for (unsigned int i = 0; i <= n0; i++)
			{
				memDC.LineTo(x[i], y[i]);
			}
			memDC.SelectObject(&data_pen_green);
			for (unsigned int i = n0 + 1; i <= n1; i++)
			{
				memDC.LineTo(x[i], y[i]);
			}
			memDC.SelectObject(&data_pen_yellow);
			for (unsigned int i = n1 + 1; i < y.size(); i++)
			{
				memDC.LineTo(x[i], y[i]);
			}
		}
		else {
			memDC.SelectObject(&data_pen_yellow);
			memDC.MoveTo(x[0], y[0]);
			for (unsigned int i = 0; i < y.size(); i++)
			{
				memDC.LineTo(x[i], y[i]);
			}
		}
		memDC.SelectObject(&font);
		memDC.SetTextColor(RGB(0, 0, 0));
		
		
		if (border) {
			//отрисовка порога
			vector<double> t = convert_range(porog, actual_top, actual_bottom, data_y_max, data_y_min);

			memDC.SelectObject(&data_pen_blue);
			memDC.MoveTo(x[0], t[0]);

			for (unsigned int i = 0; i < y.size(); i++)
			{
				memDC.LineTo(x[i], t[i]);
			}
			memDC.SelectObject(&font);
			memDC.SetTextColor(RGB(0, 0, 0));


			//отрисовка графика ошибки
			vector<double> er_y = convert_range(error_y, actual_top, actual_bottom, data_y_max, data_y_min);
			vector<double> er_x = convert_range(error_x, actual_right, actual_left, data_x_max, data_x_min);
			memDC.SelectObject(&data_pen_red);
			memDC.MoveTo(er_x[0], er_y[0]);
			for (unsigned int i = 0; i < er_y.size(); i++)
			{
				memDC.LineTo(er_x[i], er_y[i]);
			}
			memDC.SelectObject(&font);
			memDC.SetTextColor(RGB(0, 0, 0));
		}
		
		for (int i = 0; i < grid_size / 2 + 1; i++)
		{
			CString str;
			str.Format(L"%.1f", data_x_min + i * (data_x_max - data_x_min) / (grid_size / 2));
			memDC.TextOutW(actual_left + (double)i * actual_width / (grid_size / 2) - bottom_keys_padding, actual_bottom + bottom_keys_padding / 2, str);

			str.Format(L"%.2f", data_y_min + i * (data_y_max - data_y_min) / (grid_size / 2));
			memDC.TextOutW(actual_left - 1.7 * left_keys_padding, actual_bottom - (double)i * actual_height / (grid_size / 2) - bottom_keys_padding, str);
		}
		//Добавим название осей
		CString str = _T("t");
		memDC.TextOutW(actual_right+5, actual_bottom-10 , str);

		dc->BitBlt(0, 0, frame.Width(), frame.Height(), &memDC, 0, 0, SRCCOPY);
	}

	vector<double> convert_range(vector <double>& data, double outmax, double outmin, double inmax, double inmin)
	{
		vector<double> output = data;
		double k = (outmax - outmin) / (inmax - inmin);
		for (auto& item : output)
		{
			item = (item - inmin) * k + outmin;
		}

		return output;
	}
};