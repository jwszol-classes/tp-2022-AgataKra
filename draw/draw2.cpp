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
const int Platform_Height = 3;
const int Elevator_L = 310;
const int Elevator_R = 490;
const int Elevator_Height = 100;
const int E_spot_0 = 320;						// x value of a spot for a person in an elevator
const int E_spot_1 = 340;
const int E_spot_2 = 360;
const int E_spot_3 = 380;
const int E_spot_4 = 400;
const int E_spot_5 = 420;
const int E_spot_6 = 440;
const int E_spot_7 = 460;
const int Number_Of_Floors = 5;
const int E_Endings = 50;
const int Button = 25;
const int Floor_5 = 150;
const int Floor_4 = 250;
const int Floor_3 = 350;
const int Floor_2 = 450;
const int Floor_1 = 550;
const int L_Platform_L = 50;					//Left platform left end
const int L_Platform_R = 300;
const int R_Platform_L = 500;
const int R_Platform_R = 750;
//creating my base structures here:

enum Directions { UP, DOWN, NONE };				//NONE is for when it doesnt have passengers and waits for new ones
enum DoorState { OPEN, OPENING, CLOSING, CLOSED };
enum Position { FLOOR1, FLOOR2, FLOOR3, FLOOR4, FLOOR5, ELEVATOR, TRANSIT };	//ELEVATOR is just for people

struct Person {
	Position person_position;
	Position destination;
	Directions destination_direction;
	int person_weight = 70;
	int position_x;
	int position_y;
	int Elevator_Spot;
};

struct Elevator {
	std::vector<Person>passengers;
	Directions direction = NONE;
	int weight_limit = 600;
	int current_weight = 0;
	DoorState door = CLOSED;
	Position elevator_position = FLOOR1;
	int position_y = 0;
};

Elevator elevator;

int test = 0;

std::vector<Person>floor1_people;
std::vector<Person>floor2_people;
std::vector<Person>floor3_people;
std::vector<Person>floor4_people;
std::vector<Person>floor5_people;

INT value;

// buttons
HWND hwndButton;

//Fit the elevator in the Elevator_Shaft, we'd have to employ some additional drawing areas to have the "shell" walls also open
//it's an option but for now I'd say is not essential

RECT Elevator_Shaft = { L_Platform_R, E_Endings, R_Platform_L, 5 * Elevator_Height + 2 * E_Endings };				//elevator animation area
RECT StaticDrawArea = { 0, 0, 1500, 1500};

//input the areas per floor here:
RECT Floor1 = {};
RECT Floor2 = {};
RECT Floor3 = {};
RECT Floor4 = {};
RECT Floor5 = {};

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);

bool passengers_to_enter() {							//in this function you check if on the current floor anyone needs to enter (returns true in this case)
	switch (elevator.elevator_position)
	{
	case FLOOR1:
		if (floor1_people.size() != 0)
			return true;
		break;
	case FLOOR2:
		if (floor2_people.size() != 0)
			return true;
		break;
	case FLOOR3:
		if (floor3_people.size() != 0)
			return true;
		break;
	case FLOOR4:
		if (floor4_people.size() != 0)
			return true;
		break;
	case FLOOR5:
		if (floor5_people.size() != 0)
			return true;
		break;
	default:
		break;
	}
	return false;
}

bool passengers_to_depart() {							//in this function you check if on the current floor anyone needs to depart (returns true in this case)
	switch (elevator.elevator_position)
	{
	case FLOOR1:
		for (int k = 0; k < elevator.passengers.size(); k++) {
			if (elevator.passengers[k].destination == FLOOR1)
				return true;
		}
		break;
	case FLOOR2:
		for (int k = 0; k < elevator.passengers.size(); k++) {
			if (elevator.passengers[k].destination == FLOOR2)
				return true;
		}
		break;
	case FLOOR3:
		for (int k = 0; k < elevator.passengers.size(); k++) {
			if (elevator.passengers[k].destination == FLOOR3)
				return true;
		}
		break;
	case FLOOR4:
		for (int k = 0; k < elevator.passengers.size(); k++) {
			if (elevator.passengers[k].destination == FLOOR4)
				return true;
		}
		break;
	case FLOOR5:
		for (int k = 0; k < elevator.passengers.size(); k++) {
			if (elevator.passengers[k].destination == FLOOR5)
				return true;
		}
		break;
	default:
		break;
	}
	return false;
}

bool passengers_in_elevator() {															//this one checks if people arrived at their spot in the elevator
	
	return false;
}

bool passengers_at_destination() {														//this one checks if people arrived at their destination (end exited the window)
	return false;
}

void MyOnPaint(HDC hdc)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));	
	Pen pen2(Color(255, 20, 0, 255));
	graphics.DrawLine(&pen, 0, 10, 100, 200);

	if (elevator.door == CLOSED && elevator.elevator_position == TRANSIT) {		//move up or down between floors
	}
	
	else if (elevator.door == CLOSED && elevator.direction == NONE) {			//dont move if no direction
	}

	else if (elevator.door == CLOSED && (passengers_to_depart() || passengers_to_enter())) {	//are the doors supposed to open? (to let people out or in) if so open doors 
	}

	else if (elevator.door == OPEN && passengers_to_depart()) {		//let people out
	}

	else if (elevator.door == OPEN && passengers_to_enter() && !passengers_to_depart()) {	//is anyone going into the elevator? (let people in)
	}

	else if (elevator.door == OPEN && !passengers_to_enter() && !passengers_to_depart()) {	//is everyone in/out as needed? if so close doors
	}

	else if (elevator.door == CLOSED && !passengers_to_enter() && !passengers_to_depart()) {	//if elevator on floor with doors closed, move elevator in the needed direction
		if (elevator.direction == UP) {}
		else if (elevator.direction == DOWN) {}
	}
}

//for now repaintwindow just has a test animation TO DO:
void repaintWindow(HWND hWnd, HDC &hdc, PAINTSTRUCT &ps, RECT *drawArea)
{
	InvalidateRect(hWnd, drawArea, TRUE); //repaint drawArea
	hdc = BeginPaint(hWnd, &ps);
	MyOnPaint(hdc);
	EndPaint(hWnd, &ps);
}

void StaticPaint(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* drawArea)
{
	InvalidateRect(hWnd, drawArea, TRUE);
	hdc = BeginPaint(hWnd, &ps);

	Graphics graphics(hdc);
	Pen Static_Pen(Color(255, 0, 0, 255), Platform_Height);
	Pen pen2(Color(255, 25, 0, 255));

	for (int i = 0; i <= Number_Of_Floors; i++) {

		if (i % 2 == 0) //Left Side of the elevator
			if (i == 0) {			//upper end and floor
				graphics.DrawLine(&Static_Pen, L_Platform_R - 2 , E_Endings / 2, L_Platform_R - 2 , Floor_5);
				graphics.DrawLine(&Static_Pen, R_Platform_L - 2 , (E_Endings / 2), R_Platform_L - 2 , E_Endings);
				graphics.DrawLine(&Static_Pen, L_Platform_R - Platform_Height, (E_Endings / 2) - 1 , R_Platform_L, (E_Endings / 2) - 1);
			}
			else {
				graphics.DrawLine(&Static_Pen, L_Platform_L, ((i - 1) * Elevator_Height + Floor_5) - 1, L_Platform_R, ((i - 1) * Elevator_Height + Floor_5) - 1);
				graphics.DrawLine(&Static_Pen, L_Platform_R - 2, ((i - 1) * Elevator_Height + Floor_5), L_Platform_R - 2, i * Elevator_Height + Floor_5);
			}
		else
			if (i == 5) {
				graphics.DrawLine(&Static_Pen, R_Platform_L, ((i - 1) * Elevator_Height + Floor_5) - 1, R_Platform_R, ((i - 1) * Elevator_Height + Floor_5) - 1);
				graphics.DrawLine(&Static_Pen, L_Platform_R - 2, i * Elevator_Height + E_Endings, L_Platform_R - 2, i * Elevator_Height + 2 * E_Endings);
				graphics.DrawLine(&Static_Pen, R_Platform_L + 1, (i * Elevator_Height + E_Endings), R_Platform_L + 1, (i * Elevator_Height + 2 * E_Endings));
				graphics.DrawLine(&Static_Pen, L_Platform_R - Platform_Height, (i * Elevator_Height + 2 * E_Endings) + 1, R_Platform_L + Platform_Height, (i * Elevator_Height + 2 * E_Endings) + 1);
			}
			else {
				graphics.DrawLine(&Static_Pen, R_Platform_L + 1, (i * Elevator_Height + E_Endings), R_Platform_R, (i * Elevator_Height + E_Endings));
				graphics.DrawLine(&Static_Pen, R_Platform_L + 2, (i * Elevator_Height + E_Endings) + 1, R_Platform_L + 2 , ((i + 1) * Elevator_Height + E_Endings));
			}

	}
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

	//floor 4 buttons

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_4 - 2 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON4_1,
		hInstance,
		NULL);
	
	hwndButton = CreateWindow(TEXT("button"),        // The class name required is button
		TEXT("2"),									 // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,		 // the styles
		Button, Floor_4 - 3 * Button,				 // the left and top co-ordinates
		Button, Button,                              // width and height
		hWnd,									     // parent window handle
		(HMENU)ID_BUTTON4_2,					     // the ID of your button
		hInstance,								     // the instance of your application
		NULL);									     // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_4 - 4 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON4_3,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_4 - 6 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON4_5,
		hInstance,
		NULL);

	//floor 5 buttons

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_5 - 2 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON5_1,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"), 
		TEXT("2"),	
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_5 - 3 * Button,
		Button, Button, 
		hWnd,
		(HMENU)ID_BUTTON5_2,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_5 - 4 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON5_3,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_5 - 5 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON5_4,
		hInstance,
		NULL);

	//floor 2 buttons

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_2 - 2 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON2_1,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_2 - 4 * Button,
		Button, Button, 
		hWnd,
		(HMENU)ID_BUTTON2_3,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_2 - 5 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON2_4,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		Button, Floor_2 - 6 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON2_5,
		hInstance,
		NULL);

	//floor 3 buttons

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_3 - 2 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON3_1,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_3 - 3 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON3_2,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_3 - 5 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON3_4,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_3 - 6 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON3_5,
		hInstance,
		NULL);

	//floor 1 buttons

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_1 - 3 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON1_2,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_1 - 4 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON1_3,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("4"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_1 - 5 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON1_4,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("5"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		R_Platform_R, Floor_1 - 6 * Button,
		Button, Button,
		hWnd,
		(HMENU)ID_BUTTON1_5,
		hInstance,
		NULL);

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
	Person traveller;

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
		case ID_BUTTON1_2 :
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR2;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_3 :
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR3;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_4:
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_5:
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;

		case ID_BUTTON2_1:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON2_3:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR3;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON2_4:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON2_5:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;

		case ID_BUTTON3_1:
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON3_2:
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON3_4:
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON3_5:;
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;

		case ID_BUTTON4_1:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON4_2:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON4_3:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR3;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON4_5:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			floor1_people.push_back(traveller);
			break;

		case ID_BUTTON5_1:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON5_2:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON5_3:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR3;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON5_4:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR4;
			traveller.destination_direction = DOWN;
			floor1_people.push_back(traveller);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		// TODO: Add any drawing code here (not depend on timer, buttons)

		StaticPaint(hWnd, hdc, ps, &StaticDrawArea);

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
