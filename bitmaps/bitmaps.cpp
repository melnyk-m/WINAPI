// bitmaps.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h> // підключення бібліотеки з функціями API
#include <ctime>
// Глобальні змінні:
HINSTANCE hInst; //Дескриптор програми
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "ПЕРША ПРОГРАМА";
// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LPCTSTR bitmapNames[3] = { "bitmap1.bmp", "bitmap2.bmp", "bitmap3.bmp" };
int selectedBitMap = 0;
HBITMAP hBitmap[3];
BITMAP bitmap[3];
int g_scrollY = 0, g_scrollX = 0;
int rightGap = 315, topGap = 85;
COLORREF selectedColor = RGB(200, 200, 200);
COLORREF acrCustClr[16] = {
	RGB(100, 200, 200),
	RGB(200, 100, 200),
	RGB(200, 200, 100),
	RGB(200, 100, 100),
	RGB(100, 200, 200),
	RGB(200, 100, 100),
	RGB(200, 200, 200),
	RGB(200, 250, 200),
	RGB(211, 200, 211),
	RGB(200, 250, 200),
	RGB(110, 200, 110),
	RGB(150, 200, 220),
	RGB(100, 100, 100),
	RGB(0, 0, 0),
	RGB(200, 0, 100),
	RGB(100, 100, 0),
};

// Основна програма
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));
	MSG msg;
	// Реєстрація класу вікна
	MyRegisterClass(hInstance);
	// Створення вікна програми
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// Цикл обробки повідомлень
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW; //стиль вікна
	wcex.lpfnWndProc = (WNDPROC)WndProc; //віконна процедура
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance; //дескриптор програми
	wcex.hIcon = LoadIcon(NULL, IDI_HAND); //визначення іконки
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW); //визначення курсору
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW - 3); //установка фону
	wcex.lpszMenuName = NULL; //визначення меню
	wcex.lpszClassName = szWindowClass; //ім’я класу
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex); //реєстрація класу вікна
}
// FUNCTION: InitInstance (HANDLE, int)
// Створює вікно програми і зберігає дескриптор програми в змінній hInst
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, // ім’я класу вікна
		szTitle, // назва програми
		WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, // стиль вікна
		100, // положення по Х
		100, // положення по Y
		700, // розмір по Х
		300, // розмір по Y
		NULL, // дескриптор батьківського вікна
		NULL, // дескриптор меню вікна
		hInstance, // дескриптор програми
		NULL); // параметри створення.
	for (int i = 0; i < 3; i++) {
		hBitmap[i] = (HBITMAP)LoadImage( // returns a HANDLE so we have to cast to HICON
			hInst,             // hInstance must be NULL when loading from a file
			bitmapNames[i],   // the icon file name
			IMAGE_BITMAP,       // specifies that the file is an icon
			0,                // width of the image (we'll specify default later on)
			0,                // height of the image
			LR_LOADFROMFILE |  // we want to load a file (as opposed to a resource)
			LR_DEFAULTSIZE |   // default metrics based on the type (IMAGE_ICON, 32x32)
			LR_CREATEDIBSECTION      // let the system release the handle when it's no longer used
		);
	}
	if (!hWnd) //Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); //Показати вікно
	UpdateWindow(hWnd); //Оновити вікно
	return TRUE;
}

void handleScrollBar(HWND hWnd, RECT rt) {
	GetClientRect(hWnd, &rt);
	SCROLLINFO si = { 0 };
	si.cbSize = sizeof(SCROLLINFO);
	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nPos = 0;
	si.nTrackPos = 0;
	BOOL checked = IsDlgButtonChecked(hWnd, 7);
	GetObject(hBitmap[selectedBitMap], sizeof(bitmap[selectedBitMap]), &bitmap[selectedBitMap]);
	if ((bitmap[selectedBitMap].bmWidth + rightGap) > (rt.right - rt.left) && checked) {
		si.nPage = rt.right - rt.left;
		si.nMax = bitmap[selectedBitMap].bmWidth + rightGap;
		SetScrollInfo(hWnd, SB_HORZ, &si, true);
	}
	else {
		g_scrollX = 0;
		ShowScrollBar(hWnd, SB_HORZ, FALSE);
	}
	if ((bitmap[selectedBitMap].bmHeight + topGap) > (rt.bottom - rt.top) && checked) {
		si.nPage = rt.bottom - rt.top;
		si.nMax = bitmap[selectedBitMap].bmHeight + topGap;
		SetScrollInfo(hWnd, SB_VERT, &si, true);
	}
	else {
		g_scrollY = 0;
		ShowScrollBar(hWnd, SB_VERT, FALSE);
	}
}

// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
// Віконна процедура. Приймає і обробляє всі повідомлення, що приходять в додаток
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	RECT rt;
	HBRUSH hbr = CreateSolidBrush(RGB(100, 150, 100));
	HDC hdcMem;
	GetClientRect(hWnd, &rt);

	switch (message)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case 4:
			selectedBitMap = 0;
			handleScrollBar(hWnd, rt);
			InvalidateRect(hWnd, &rt, TRUE);
			break;
		case 5:
			selectedBitMap = 1;
			handleScrollBar(hWnd, rt);
			InvalidateRect(hWnd, &rt, TRUE);
			break;
		case 6:
			selectedBitMap = 2;
			handleScrollBar(hWnd, rt);
			InvalidateRect(hWnd, &rt, TRUE);
			break;
		case 7: {
			BOOL checked = IsDlgButtonChecked(hWnd, 7);
			if (checked) {
				CheckDlgButton(hWnd, 7, BST_UNCHECKED);
				InvalidateRect(hWnd, &rt, TRUE);
			}
			else {
				CheckDlgButton(hWnd, 7, BST_CHECKED);
				InvalidateRect(hWnd, &rt, TRUE);
			}
			handleScrollBar(hWnd, rt);
		}
			  break;
		case 8:
			CHOOSECOLOR cc;                 // common dialog box structure 
			HBRUSH hbrush;                  // brush handle
			static DWORD rgbCurrent;        // initial color selection

			// Initialize CHOOSECOLOR 
			ZeroMemory(&cc, sizeof(cc));
			cc.lStructSize = sizeof(cc);
			cc.hwndOwner = hWnd;
			cc.lpCustColors = (LPDWORD)acrCustClr;
			cc.rgbResult = rgbCurrent;
			cc.Flags = CC_FULLOPEN | CC_RGBINIT;


			if (ChooseColor(&cc) == TRUE)
			{
				hbrush = CreateSolidBrush(cc.rgbResult);
				selectedColor = cc.rgbResult;
			}
			InvalidateRect(hWnd, &rt, TRUE);
			break;
		}
	case WM_SIZE:
		handleScrollBar(hWnd, rt);
		InvalidateRect(hWnd, &rt, TRUE);
	case WM_VSCROLL:
	{
		auto action = LOWORD(wParam);
		HWND hScroll = (HWND)lParam;
		int pos = -1;
		if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK) {
			pos = HIWORD(wParam);
		}
		else if (action == SB_LINEDOWN) {
			pos = g_scrollY + 30;
		}
		else if (action == SB_LINEUP) {
			pos = g_scrollY - 30;
		}
		if (pos == -1)
			break;
		SCROLLINFO si = { 0 };
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		si.nPos = pos;
		si.nTrackPos = 0;
		SetScrollInfo(hWnd, SB_VERT, &si, true);
		GetScrollInfo(hWnd, SB_VERT, &si);
		pos = si.nPos;
		POINT pt;
		pt.x = 0;
		pt.y = pos - g_scrollY;
		auto hdc = GetDC(hWnd);
		LPtoDP(hdc, &pt, 1);
		ReleaseDC(hWnd, hdc);
		ScrollWindow(hWnd, 0, -pt.y, NULL, NULL);
		g_scrollY = pos;
		InvalidateRect(hWnd, &rt, TRUE);
		return 0;
	}
	case WM_HSCROLL:
	{
		auto action = LOWORD(wParam);
		HWND hScroll = (HWND)lParam;
		int pos = -1;
		if (action == SB_THUMBPOSITION || action == SB_THUMBTRACK) {
			pos = HIWORD(wParam);
		}
		else if (action == SB_LINEDOWN) {
			pos = g_scrollX + 100;
		}
		else if (action == SB_LINEUP) {
			pos = g_scrollX - 100;
		}
		if (pos == -1)
			break;
		SCROLLINFO si = { 0 };
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_POS;
		si.nPos = pos;
		si.nTrackPos = 0;
		SetScrollInfo(hWnd, SB_HORZ, &si, true);
		GetScrollInfo(hWnd, SB_HORZ, &si);
		pos = si.nPos;
		POINT pt;
		pt.x = pos - g_scrollX;
		pt.y = 0;
		auto hdc = GetDC(hWnd);
		LPtoDP(hdc, &pt, 1);
		ReleaseDC(hWnd, hdc);
		ScrollWindow(hWnd, -pt.x, 0, NULL, NULL);
		g_scrollX = pos;
		InvalidateRect(hWnd, &rt, TRUE);
		return 0;
	}
	break;
	case WM_CREATE: {
		//Повідомлення приходить при створенні вікна
		CreateWindow("button", "Change to A", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			100, 50, 85, 30, hWnd, (HMENU)4, NULL, NULL);
		CreateWindow("button", "Change to D", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			300, 50, 85, 30, hWnd, (HMENU)5, NULL, NULL);
		CreateWindow("button", "Change to O", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			500, 50, 85, 30, hWnd, (HMENU)6, NULL, NULL);
		CreateWindow("button", "Show image",
			WS_VISIBLE | WS_CHILD | BS_CHECKBOX,
			290, 10, 100, 30,
			hWnd, (HMENU)7, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
		CreateWindow("button", "Change color", WS_CHILD | BS_PUSHBUTTON | WS_VISIBLE,
			500, 10, 100, 30, hWnd, (HMENU)8, NULL, NULL);
		CheckDlgButton(hWnd, 7, BST_CHECKED);
		ShowWindow(GetDlgItem(hWnd, 8), SW_HIDE);
		handleScrollBar(hWnd, rt);
		return 0;
	}
	case WM_PAINT: { //Перемалювати вікно
		SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)CreateSolidBrush(selectedColor));
		if (IsDlgButtonChecked(hWnd, 7)) {
			GetClientRect(hWnd, &rt);
			GetObject(hBitmap[selectedBitMap], sizeof(bitmap[selectedBitMap]), &bitmap[selectedBitMap]);
			ShowWindow(GetDlgItem(hWnd, 8), SW_HIDE);
			HDC hdc = BeginPaint(hWnd, &ps);
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hBitmap[selectedBitMap]);
			BitBlt(hdc, rightGap - g_scrollX, topGap - g_scrollY, bitmap[selectedBitMap].bmWidth, bitmap[selectedBitMap].bmHeight, hdcMem, 0, 0, SRCCOPY);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps); //Закінчити графічний вивід
		}
		else {
			ShowWindow(GetDlgItem(hWnd, 8), SW_SHOW);
			GetClientRect(hWnd, &rt);
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps); //Закінчити графічний вивід
		}
	}
				 break;
	case WM_DESTROY: //Завершення роботи
		PostQuitMessage(0);
		break;
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
