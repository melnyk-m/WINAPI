// small game.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <windows.h>; 
#include <ctime>
#include <cmath>


struct Cell {
	int x, y;

	struct rgb {
		int r, g, b, z;
	}
	mainColor,
		borderColor,
		circleColor,
		textColor,
		circleSize,
		starSize,
		starColor,
		circleBorderColor;

};

HWND hWnd;
HDC hdc;
HPALETTE hPal;
BOOL bForceBkgd;
COLORREF color;
HBRUSH brush;




const int rectSize = 90;
const int circleSize = 40;
const int starSize = 40;

int y = 0, x = 0, yCoord, xCoord;
char buf[50];

bool flag = 0;
Cell cells[7][7];
HINSTANCE hInst; //Дескриптор програми
LPCTSTR szWindowClass = "QWERTY";
LPCTSTR szTitle = "  ";
// Попередній опис функцій
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


bool isInCircle(int x, int y, int x0, int y0, int R) {

	if (pow((x - x0), 2) + pow((y - y0), 2) <= pow(R, 2)) {
		return true;
	}
	return false;

}

bool isInStar(int x, int y, int x0, int y0, int R) {

	if (pow((x - x0), 2) + pow((y - y0), 2) <= pow(R, 2)) {
		return true;
	}
	return false;

}


// main program
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	srand(time(NULL));

	MSG msg;
	// window class register
	MyRegisterClass(hInstance);
	// creating a program window
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}
	// messages processing cycle
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
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = (WNDPROC)WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(NULL, IDI_SHIELD);
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW + 3);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = NULL;
	return RegisterClassEx(&wcex);
}
// FUNCTION: InitInstance (HANDLE, int)

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance;
	hWnd = CreateWindow(szWindowClass, // window class name
		szTitle, // program name
		WS_OVERLAPPED | WS_SYSMENU,
		400, // position on x
		0, // position on y
		718,
		790,
		NULL,
		NULL,
		hInstance,
		NULL);
	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	return TRUE;
}
// FUNCTION: WndProc (HWND, unsigned, WORD, LONG)
void DrawRectangle(HWND hWnd)
{
	HBRUSH hBrush;
	HDC hdc;
	RECT rect;

	SetRect(&rect, cells[1][6].x * rectSize, cells[1][6].y * rectSize + circleSize, (cells[1][6].x + 1) * rectSize, (cells[1][6].y + 1) * rectSize + circleSize);
	hBrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));
	hdc = GetDC(hWnd);
	FillRect(hdc, &rect, hBrush);
	ReleaseDC(hWnd, hdc);
	DeleteObject(hBrush);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	PAINTSTRUCT ps;

	RECT rt;
	HPEN pen;

	static unsigned short index = 0, index1 = 0, strSize = 257;
	static char* str = new char[strSize];
	static unsigned short const strSize1 = 6;
	int g = 0;
	srand(time(NULL));

	switch (message)
	{
	case WM_CREATE: //the message will appear when creating a window
		static char arr[strSize1];


		for (int i = 0; i < strSize1;)
		{
			char ch = rand() % 127;
			if (isalnum(ch))
			{
				arr[i] = ch;
				++i;
			}
		}

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				//serial numberoftheelement
				cells[i][j].x = j;
				cells[i][j].y = i;

				cells[i][j].mainColor.r = 0;
				cells[i][j].mainColor.g = 0;
				cells[i][j].mainColor.b = 0;

				//setting the grid color
				//cells[i][j].borderColor.r = 40;
				//cells[i][j].borderColor.g = 40;
				//cells[i][j].borderColor.b = 40;

				//setting the colorofthe circle
				if (i < 1 && j < 6) {
					cells[i][j].circleColor.r = rand() % 256;
					cells[i][j].circleColor.g = rand() % 256;
					cells[i][j].circleColor.b = rand() % 256;
				}
				else {
					cells[i][j].circleColor.r = 0;
					cells[i][j].circleColor.g = 0;
					cells[i][j].circleColor.b = 0;
				}
				//setting textcolor
				if (i < 1 && j < 6) {
					cells[i][j].textColor.r = rand() % 256;
					cells[i][j].textColor.g = rand() % 256;
					cells[i][j].textColor.b = rand() % 256;
					//setting circleSize

				}
				else {
					cells[i][j].textColor.r = 0;
					cells[i][j].textColor.g = 0;
					cells[i][j].textColor.b = 0;
				}
				cells[i][j].circleSize.z = 1 + rand() % (30 - 1);
				cells[i][j].starColor.r = 0;
				cells[i][j].starColor.g = 0;
				cells[i][j].starColor.b = 0;

			}
		}
		break;

	case WM_PAINT: //redraw the widow
		hdc = BeginPaint(hWnd, &ps); //start graphical output
		GetClientRect(hWnd, &rt);
		SetBkMode(hdc, TRANSPARENT);
		SetPolyFillMode(hdc, WINDING);




		//cycle of creating a grid with circles
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < 7; j++)
			{
				//Setting a custom pen and fill for the grid
				pen = CreatePen(PS_SOLID, 5, RGB(cells[i][j].borderColor.r, cells[i][j].borderColor.g, cells[i][j].borderColor.b));
				brush = CreateSolidBrush(RGB(cells[i][j].mainColor.r, cells[i][j].mainColor.g, cells[i][j].mainColor.b));
				SelectObject(hdc, brush);
				SelectObject(hdc, pen);

				//Meshing
				Rectangle(hdc, cells[i][j].x * rectSize, cells[i][j].y * rectSize + circleSize, (cells[i][j].x + 1) * rectSize, (cells[i][j].y + 1) * rectSize + circleSize);


				//Remove Penand Mesh Fill
				DeleteObject(pen);
				DeleteObject(brush);

				//Setting a custom pen and fill for circles

				if (i < 7 && j < 6) {
					//int z = 1 + rand() % (30 - 1);
					//int z = 10;
					pen = CreatePen(PS_SOLID, 5, RGB(cells[i][j].circleBorderColor.r, cells[i][j].circleBorderColor.g, cells[i][j].circleBorderColor.b));
					brush = CreateSolidBrush(RGB(cells[i][j].circleColor.r, cells[i][j].circleColor.g, cells[i][j].circleColor.b));
					SelectObject(hdc, brush);
					SelectObject(hdc, pen);

					//Making circles
					Ellipse(hdc, cells[i][j].x * rectSize + cells[i][j].circleSize.z, cells[i][j].y * rectSize + cells[i][j].circleSize.z + circleSize, (cells[i][j].x + 1) * rectSize - cells[i][j].circleSize.z, (cells[i][j].y + 1) * rectSize - cells[i][j].circleSize.z + circleSize);

					//Remove pen and circle fill
					DeleteObject(pen);
					DeleteObject(brush);



					// text output
					SetTextColor(hdc, RGB(cells[i][j].textColor.r, cells[i][j].textColor.g, cells[i][j].textColor.b));
					// text output
					if (i < 1 && j < 6) {

						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[j], 1);
					}
					else if (i == 4 && j < 6) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[0], 1);
					}
					else if (i < 4 && j < 2 && i>0) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[1], 1);
					}
					else if (i > 4 && j < 6 && j>2) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[2], 1);
					}
					else if (i < 4 && j < 6 && i>0 && j>3) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[3], 1);
					}
					else if (i < 4 && j < 4 && i>0 && j>1) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[4], 1);
					}
					else if (i > 4 && j < 3) {
						TextOutA(hdc, cells[i][j].x * rectSize + 40, cells[i][j].y * rectSize + circleSize + 39, &arr[4], 1);
					}


				}

				if (i > 0 && j > 5) {
					//int z = 1 + rand() % (30 - 1);

					pen = CreatePen(PS_SOLID, 5, RGB(cells[i][j].starColor.r, cells[i][j].starColor.g, cells[i][j].starColor.b));
					brush = CreateSolidBrush(RGB(cells[i][j].starColor.r, cells[i][j].starColor.g, cells[i][j].starColor.b));
					SelectObject(hdc, brush);


					//Making circles

					POINT poly[11];

					poly[0].x = cells[i][6].x * rectSize + 60;
					poly[0].y = cells[i][6].y * rectSize + circleSize + 28;
					poly[1].x = cells[i][6].x * rectSize + 45;
					poly[1].y = cells[i][6].y * rectSize + circleSize + 32;
					poly[2].x = cells[i][6].x * rectSize + 35;
					poly[2].y = cells[i][6].y * rectSize + circleSize + 20;
					poly[3].x = cells[i][6].x * rectSize + 35;
					poly[3].y = cells[i][6].y * rectSize + circleSize + 35;
					poly[4].x = cells[i][6].x * rectSize + 20;
					poly[4].y = cells[i][6].y * rectSize + circleSize + 40;
					poly[5].x = cells[i][6].x * rectSize + 35;
					poly[5].y = cells[i][6].y * rectSize + circleSize + 45;

					poly[6].x = cells[i][6].x * rectSize + 35;
					poly[6].y = cells[i][6].y * rectSize + circleSize + 60;
					poly[7].x = cells[i][6].x * rectSize + 45;
					poly[7].y = cells[i][6].y * rectSize + circleSize + 48;
					poly[8].x = cells[i][6].x * rectSize + 60;
					poly[8].y = cells[i][6].y * rectSize + circleSize + 52;
					poly[9].x = cells[i][6].x * rectSize + 51;
					poly[9].y = cells[i][6].y * rectSize + circleSize + 40;
					poly[10].x = cells[i][6].x * rectSize + 60;
					poly[10].y = cells[i][6].y * rectSize + circleSize + 28;
					Polygon(hdc, poly, 11);


					//Remove pen and circle fill
					DeleteObject(pen);
					DeleteObject(brush);
					// text output
					SetTextColor(hdc, RGB(cells[i][j].textColor.r, cells[i][j].textColor.g, cells[i][j].textColor.b));
					TextOutA(hdc, cells[i][j].x * rectSize + 14, cells[i][j].y * rectSize + circleSize + 35, &arr[g], 1);

					g++;

				}
				//Displaying text on the screen



			}
		}




		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:

		y = HIWORD(lParam);
		x = LOWORD(lParam);
		rt.top = 7;
		rt.left = 0;
		rt.right = 7 * rectSize;
		rt.bottom = circleSize;


		break;

	case WM_LBUTTONDOWN:

		yCoord = y;
		xCoord = x;

		yCoord -= circleSize;
		yCoord /= rectSize;
		xCoord /= rectSize;



		//Checking if coordinates are included in circle coordinates
		if (xCoord < 6 && yCoord < 7 && isInCircle(x, y - circleSize, xCoord * rectSize + rectSize / 2, yCoord * rectSize + rectSize / 2, (rectSize - 20) / 2)) {


			if (yCoord == 0) {
				cells[xCoord + 1][yCoord + 6].starColor.r = cells[yCoord][xCoord].circleColor.r;
				cells[xCoord + 1][yCoord + 6].starColor.g = cells[yCoord][xCoord].circleColor.g;
				cells[xCoord + 1][yCoord + 6].starColor.b = cells[yCoord][xCoord].circleColor.b;

				cells[xCoord + 1][yCoord + 6].textColor.r = cells[yCoord][xCoord].circleColor.r;
				cells[xCoord + 1][yCoord + 6].textColor.g = cells[yCoord][xCoord].circleColor.g;
				cells[xCoord + 1][yCoord + 6].textColor.b = cells[yCoord][xCoord].circleColor.b;
			}
			else {

				if (yCoord == 4 && xCoord < 6) {
					cells[1][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[1][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[1][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[1][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[1][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[1][6].textColor.b = cells[yCoord][xCoord].circleColor.b;

				}
				else if (yCoord < 4 && xCoord < 2 && yCoord>0) {
					cells[2][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[2][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[2][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[2][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[2][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[2][6].textColor.b = cells[yCoord][xCoord].circleColor.b;

				}
				else if (yCoord > 4 && xCoord < 6 && xCoord>2) {
					cells[3][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[3][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[3][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[3][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[3][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[3][6].textColor.b = cells[yCoord][xCoord].circleColor.b;
				}
				else if (yCoord < 4 && xCoord < 6 && yCoord>0 && xCoord>3) {
					cells[4][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[4][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[4][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[4][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[4][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[4][6].textColor.b = cells[yCoord][xCoord].circleColor.b;

				}
				else if (yCoord < 4 && xCoord < 4 && yCoord>0 && xCoord>1) {
					cells[5][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[5][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[5][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[5][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[5][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[5][6].textColor.b = cells[yCoord][xCoord].circleColor.b;
				}
				else if (yCoord > 4 && xCoord < 3) {
					cells[6][6].starColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[6][6].starColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[6][6].starColor.b = cells[yCoord][xCoord].circleColor.b;

					cells[6][6].textColor.r = cells[yCoord][xCoord].circleColor.r;
					cells[6][6].textColor.g = cells[yCoord][xCoord].circleColor.g;
					cells[6][6].textColor.b = cells[yCoord][xCoord].circleColor.b;

				}
			}


			cells[yCoord][xCoord].circleColor.r = 0;
			cells[yCoord][xCoord].circleColor.g = 0;
			cells[yCoord][xCoord].circleColor.b = 0;
			cells[yCoord][xCoord].circleSize.z = 1 + rand() % (30 - 1);

			cells[yCoord][xCoord].textColor.r = 0;
			cells[yCoord][xCoord].textColor.g = 0;
			cells[yCoord][xCoord].textColor.b = 0;


			//InvalidateRect(hWnd, NULL, TRUE);
			//brush = CreateSolidBrush(RGB(5,5,5));
			SetRectEmpty(&rt);
			InvalidateRect(hWnd, NULL, TRUE);


			//DeleteObject(brush);
			DrawRectangle(hWnd);
			GetPixel(hdc, x, y);

			flag = 1;
		}
		else if (xCoord > 5 && yCoord < 7 && isInCircle(x, y - circleSize, xCoord * rectSize + rectSize / 2, yCoord * rectSize + rectSize / 2, (rectSize - 20) / 2)) {



			if (yCoord == 1) {
				int z = 0 + rand() % (6 - 0);//множитель
				cells[4][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[4][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[4][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[4][z].textColor.r = rand() % 256;
				cells[4][z].textColor.g = rand() % 256;
				cells[4][z].textColor.b = rand() % 256;


			}
			else if (yCoord == 2) {
				int z = 0 + rand() % (2 - 0);//множитель
				int f = 1 + rand() % (4 - 1);
				cells[f][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[f][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[f][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[f][z].textColor.r = rand() % 256;
				cells[f][z].textColor.g = rand() % 256;
				cells[f][z].textColor.b = rand() % 256;
			}
			else if (yCoord == 3) {
				int z = 3 + rand() % (6 - 3);//множитель
				int f = 5 + rand() % (7 - 5);
				cells[f][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[f][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[f][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[f][z].textColor.r = rand() % 256;
				cells[f][z].textColor.g = rand() % 256;
				cells[f][z].textColor.b = rand() % 256;


			}
			else if (yCoord == 4) {

				int z = 4 + rand() % (6 - 4);//множитель
				int f = 1 + rand() % (4 - 1);
				cells[f][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[f][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[f][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[f][z].textColor.r = rand() % 256;
				cells[f][z].textColor.g = rand() % 256;
				cells[f][z].textColor.b = rand() % 256;
			}
			else if (yCoord == 5) {
				int z = 2 + rand() % (4 - 2);//множитель
				int f = 1 + rand() % (4 - 1);
				cells[f][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[f][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[f][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[f][z].textColor.r = rand() % 256;
				cells[f][z].textColor.g = rand() % 256;
				cells[f][z].textColor.b = rand() % 256;

			}
			else if (yCoord == 6) {
				int z = 0 + rand() % (3 - 0);//множитель
				int f = 5 + rand() % (7 - 5);
				cells[f][z].circleColor.r = cells[yCoord][xCoord].starColor.r;
				cells[f][z].circleColor.g = cells[yCoord][xCoord].starColor.g;
				cells[f][z].circleColor.b = cells[yCoord][xCoord].starColor.b;

				cells[f][z].textColor.r = rand() % 256;
				cells[f][z].textColor.g = rand() % 256;
				cells[f][z].textColor.b = rand() % 256;

			}


			cells[yCoord][xCoord].starColor.r = 0;
			cells[yCoord][xCoord].starColor.g = 0;
			cells[yCoord][xCoord].starColor.b = 0;
			//cells[yCoord][xCoord].circleSize.z = 1 + rand() % (30 - 1);

			cells[yCoord][xCoord].textColor.r = 0;
			cells[yCoord][xCoord].textColor.g = 0;
			cells[yCoord][xCoord].textColor.b = 0;


			//InvalidateRect(hWnd, NULL, TRUE);
			//brush = CreateSolidBrush(RGB(5,5,5));
			SetRectEmpty(&rt);
			InvalidateRect(hWnd, NULL, TRUE);


			//DeleteObject(brush);
			DrawRectangle(hWnd);
			GetPixel(hdc, x, y);

			flag = 1;
		}

		break;


	case WM_DESTROY: 				//completion of work
		PostQuitMessage(0);
		break;
	default:
		//Processing messages that are not processed by the user
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
