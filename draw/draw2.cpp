// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
const int Platform_Length = 250;
const int Platform_Height = 3;
const int Shaft_Length = 200;
const int Elevator_Height = 100;
const int Elevator_Length = 180;
const int Number_Of_Floors = 5;
const int E_Endings = 50;
//creating my base structures here:

enum Directions {UP, DOWN, NONE};				//NONE is for when it doesnt have passengers and waits for new ones
enum DoorState {OPEN, OPENING, CLOSING, CLOSED};					
enum Position {FLOOR0, FLOOR1, FLOOR2, FLOOR3, FLOOR4, ELEVATOR, TRANSIT};	//ELEVATOR is just for people

struct Person {
	Position person_position;
	Position destination;
	Directions destination_direction;
	int person_weight = 70;
};

struct Elevator {
	std::vector<Person>passengers;
	Directions direction = UP;
	int weight_limit = 600;
	int current_weight = 0;
	DoorState door = CLOSED;
	Position elevator_position = FLOOR0;
};

int test = 0;

std::vector<Person>floor0_people;
std::vector<Person>floor1_people;
std::vector<Person>floor2_people;
std::vector<Person>floor3_people;
std::vector<Person>floor4_people;

INT value;

// buttons
HWND hwndButton;

// sent data
int col = 0;
//std::vector<Point> data;
RECT drawArea1 = { 0, 0, 300, 300 };
RECT drawArea2 = { 50, 400, 1500, 1500};
RECT Elevator_Shaft = { 0, 0, 800, 800 };				//elevator animation area

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);


void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	Pen pen2(Color(255, 25*col, 0, 255));

	for (int i = 0; i <= Number_Of_Floors; i++) {

		if (i % 2 == 0) //Left Side of the elevator
			if (i == 0) {
				for (int j = 1; j < Platform_Height + 1; j++) {
					graphics.DrawLine(&pen, Platform_Length + E_Endings - 2 + j, E_Endings / 2, Platform_Length + E_Endings - 2 + j, Elevator_Height + E_Endings);
					graphics.DrawLine(&pen, Platform_Length + Shaft_Length + E_Endings - 1 + j, (E_Endings / 2), Platform_Length + Shaft_Length + E_Endings - 1 + j, E_Endings);
					graphics.DrawLine(&pen, Platform_Length + E_Endings, (E_Endings / 2) - 1 + j, Platform_Length + Shaft_Length + E_Endings, (E_Endings / 2) - 1 + j);
				}
			}
			else {
				for (int j = 1; j < Platform_Height + 1; j++) {
					graphics.DrawLine(&pen, E_Endings, (i * Elevator_Height + E_Endings) - 1 + j, Platform_Length + E_Endings, (i * Elevator_Height + E_Endings) - 1 + j);
					graphics.DrawLine(&pen, Platform_Length + E_Endings - 2 + j, (i * Elevator_Height + E_Endings), Platform_Length + E_Endings - 2 + j, ((i + 1) * Elevator_Height + E_Endings));
				}
			}
		else
			if (i == 5)
				for (int j = 1; j < Platform_Height + 1; j++) {
					graphics.DrawLine(&pen, Platform_Length + Shaft_Length + E_Endings, (i * Elevator_Height + E_Endings) + j, (2 * Platform_Length) + Shaft_Length + E_Endings, (i * Elevator_Height + E_Endings) + j);
					graphics.DrawLine(&pen, Platform_Length + E_Endings - 2 + j, i * Elevator_Height + E_Endings, Platform_Length + E_Endings - 2 + j, i * Elevator_Height + 2 * E_Endings);
					graphics.DrawLine(&pen, Platform_Length + Shaft_Length + E_Endings - 1 + j, (i * Elevator_Height + E_Endings) + j, Platform_Length + Shaft_Length + E_Endings - 1 + j, (i * Elevator_Height + 2 * E_Endings) + j);
					graphics.DrawLine(&pen, Platform_Length + E_Endings, (i * Elevator_Height + 2 * E_Endings) - 1 + j, Platform_Length + Shaft_Length + E_Endings, (i * Elevator_Height + 2 * E_Endings) - 1 + j);
				}
			else
				for (int j = 1; j < Platform_Height + 1; j++) {
				graphics.DrawLine(&pen, Platform_Length + Shaft_Length + E_Endings, (i * Elevator_Height + E_Endings) + j, (2 * Platform_Length) + Shaft_Length + E_Endings, (i * Elevator_Height + E_Endings) + j);
				graphics.DrawLine(&pen, Platform_Length + Shaft_Length + E_Endings + 2 - j, (i * Elevator_Height + E_Endings) + 1, Platform_Length + Shaft_Length + E_Endings + 2 - j, ((i + 1) * Elevator_Height + E_Endings));
				}

	}
	/*for (int i = 1; i < 50; i++)
		graphics.DrawLine(&pen2, 0, 0, 50, test);
	test += 10;
	graphics.DrawRectangle(&pen, 50 + value, 400, 10, 20); */
}

//for now repaintwindow just has a test animation TO DO:
void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	/*if (drawArea == NULL)
		InvalidateRect(hWnd, NULL, TRUE); // repaint all
	else*/
		InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

int OnCreate(HWND window)
{
	//inputData();
	return 0;
}


// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle          
	
	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("Draw"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 60,                                  // the left and top co-ordinates
		80, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("DrawAll"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		800, 0,                                  // the left and top co-ordinates
		80, 50,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON2,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	// create button and store the handle                                                       

	/*hwndButton = CreateWindow(TEXT("button"), TEXT("Timer ON"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 155, 100, 30, hWnd, (HMENU)ID_RBUTTON1, GetModuleHandle(NULL), NULL);

	hwndButton = CreateWindow(TEXT("button"), TEXT("Timer OFF"),
		WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON,
		300, 200, 100, 30, hWnd, (HMENU)ID_RBUTTON2, GetModuleHandle(NULL), NULL);*/

	OnCreate(hWnd);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, TMR_1, 25, 0);									//timer for animation is set up here, 25ms per frame
		break;
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1 :
			col++;
			if (col > 10)
				col = 0;
			repaintWindow(hWnd, hdc, ps, &drawArea1);
			break;
		case ID_BUTTON2 :
			repaintWindow(hWnd, hdc, ps, NULL);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code here (not depend on timer, buttons)
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:					//change the timer redrawing
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			repaintWindow(hWnd, hdc, ps, &Elevator_Shaft);
			break;
		}

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
