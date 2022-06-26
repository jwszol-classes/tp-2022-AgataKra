// draw.cpp : Defines the entry point for the application.
// 

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <string>

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
const int Traveller_Speed = 5;
const int Elevator_Speed = 5;
const int Elevator_Door_Speed = 5;
const int Spot_Width = 20;
const int E_spot[8] = {320, 340, 360, 380, 400, 420, 440, 460};
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
const int ZERO = 10;
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
	int Elevator_Spot = ZERO;
};

struct Elevator {
	std::vector<Person>passengers;
	Directions direction = NONE;
	Directions previous_direction = UP;
	int weight_limit = 600;
	int current_weight = 0;
	DoorState door = CLOSED;
	Position elevator_position = FLOOR1;
	int position_y = Floor_1;
	bool Spots[8] = {false, false , false , false , false , false , false , false};
	int Door_Height = 100;
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
RECT StaticDrawArea = { 50, 0, 750, 1500 };

/*Im might try to fix bitmaps but this is hell
Bitmap* person_dest1 = new Bitmap(20, 50, PixelFormat32bppARGB);
Bitmap* person_dest2 = new Bitmap(20, 50, PixelFormat32bppARGB);
Bitmap* person_dest3 = new Bitmap(20, 50, PixelFormat32bppARGB);
Bitmap* person_dest4 = new Bitmap(20, 50, PixelFormat32bppARGB);
Bitmap* person_dest5 = new Bitmap(20, 50, PixelFormat32bppARGB);
*/
// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);
/*
void InitializeSilhouettes(HWND hWnd, Bitmap* one, Bitmap* two, Bitmap* three, Bitmap* four, Bitmap* five) {
	HDC hdcbuf = CreateCompatibleDC(NULL);
	PAINTSTRUCT ps;
	hdcbuf = BeginPaint(hWnd, &ps);

	Pen Static_Pen(Color(255, 0, 0, 255), 2);
	Graphics* imageGraphics1 = Graphics::FromImage(one);
	imageGraphics1->DrawEllipse(&Static_Pen, 0, 0, 20, 20);
	imageGraphics1->DrawRectangle(&Static_Pen, 0, 20, 20, 30);
	imageGraphics1->DrawLine(&Static_Pen, 5, 25, 5, 45);
	delete imageGraphics1;

	Graphics* imageGraphics2 = Graphics::FromImage(two);
	imageGraphics2->DrawEllipse(&Static_Pen, 0, 0, 20, 20);
	imageGraphics2->DrawRectangle(&Static_Pen, 0, 20, 20, 30);
	imageGraphics2->DrawLine(&Static_Pen, 5, 25, 15, 25);
	imageGraphics2->DrawLine(&Static_Pen, 15, 25, 15, 35);
	imageGraphics2->DrawLine(&Static_Pen, 15, 35, 5, 35);
	imageGraphics2->DrawLine(&Static_Pen, 5, 35, 5, 45);
	imageGraphics2->DrawLine(&Static_Pen, 5, 45, 15, 45);
	delete imageGraphics2;

	Graphics* imageGraphics3 = Graphics::FromImage(three);
	imageGraphics3->DrawEllipse(&Static_Pen, 0, 0, 20, 20);
	imageGraphics3->DrawRectangle(&Static_Pen, 0, 20, 20, 30);
	imageGraphics3->DrawLine(&Static_Pen, 5, 25, 15, 25);
	imageGraphics3->DrawLine(&Static_Pen, 15, 25, 15, 45);
	imageGraphics3->DrawLine(&Static_Pen, 5, 35, 15, 35);
	imageGraphics3->DrawLine(&Static_Pen, 5, 45, 15, 45);
	delete imageGraphics3;

	Graphics* imageGraphics4 = Graphics::FromImage(four);
	imageGraphics4->DrawEllipse(&Static_Pen, 0, 0, 20, 20);
	imageGraphics4->DrawRectangle(&Static_Pen, 0, 20, 20, 30);
	imageGraphics4->DrawLine(&Static_Pen, 5, 25, 5, 35);
	imageGraphics4->DrawLine(&Static_Pen, 5, 35, 15, 35);
	imageGraphics4->DrawLine(&Static_Pen, 15, 25, 15, 45);
	delete imageGraphics4;

	Graphics* imageGraphics5 = Graphics::FromImage(five);
	imageGraphics5->DrawEllipse(&Static_Pen, 0, 0, 20, 20);
	imageGraphics5->DrawRectangle(&Static_Pen, 0, 20, 20, 30);
	imageGraphics5->DrawLine(&Static_Pen, 5, 25, 15, 25);
	imageGraphics5->DrawLine(&Static_Pen, 5, 25, 5, 35);
	imageGraphics5->DrawLine(&Static_Pen, 5, 35, 15, 35);
	imageGraphics5->DrawLine(&Static_Pen, 15, 35, 15, 45);
	imageGraphics5->DrawLine(&Static_Pen, 5, 45, 15, 45);
	delete imageGraphics5;


	EndPaint(hWnd, &ps);
}
*/

bool passengers_waiting() {
	if (floor1_people.size() != 0 || floor2_people.size() != 0 || floor3_people.size() != 0 || floor4_people.size() != 0 || floor5_people.size() != 0)
		return true;
	else return false;
}

bool passengers_to_enter() {	//in this function you check if on the current floor anyone needs to enter (returns true in this case)		FUCKED
	if ((elevator.current_weight + 70) < elevator.weight_limit) {
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
	}
	return false;
}

bool passengers_in_elevator() {				//this one checks if people arrived at their spot in the elevator
	switch (elevator.elevator_position)
	{
	case FLOOR5:
		for (int j = 0; j < floor5_people.size(); j++) {
			if (floor5_people[j].Elevator_Spot == ZERO)
				continue;
			int k = floor5_people[j].Elevator_Spot;
			if (floor5_people[j].position_x != E_spot[k])
				return false;
		}
		break;
	case FLOOR4:
		for (int j = 0; j < floor4_people.size(); j++) {
			if (floor4_people[j].Elevator_Spot == ZERO)
				continue;
			int k = floor4_people[j].Elevator_Spot;
			if (floor4_people[j].position_x != E_spot[k])
				return false;
		}
		break;
	case FLOOR3:
		for (int j = 0; j < floor3_people.size(); j++) {
			if (floor3_people[j].Elevator_Spot == ZERO)
				continue;
			int k = floor3_people[j].Elevator_Spot;
			if (floor3_people[j].position_x != E_spot[k])
				return false;
		}
		break;
	case FLOOR2:
		for (int j = 0; j < floor2_people.size(); j++) {
			if (floor2_people[j].Elevator_Spot == ZERO)
				continue;
			int k = floor2_people[j].Elevator_Spot;
			if (floor2_people[j].position_x != E_spot[k])
				return false;
		}
		break;
	case FLOOR1:
		for (int j = 0; j < floor1_people.size(); j++) {
			if (floor1_people[j].Elevator_Spot == ZERO)
				continue;
			int k = floor1_people[j].Elevator_Spot;
			if (floor1_people[j].position_x != E_spot[k])
				return false;
		}
		break;
	}
	return true;
}

bool passengers_at_destination() {			//this one checks if people arrived at their destination (end exited the window)
	for (int j = 0; j < elevator.passengers.size(); j++) {
		if (elevator.passengers[j].destination == elevator.elevator_position) {
			if (elevator.passengers[j].position_x > R_Platform_R || elevator.passengers[j].position_x < L_Platform_L - 20)
				return true;
		}

	}
	return false;
}

void elevator_control(HDC hdc) {
	if (passengers_to_depart()) {

		if (elevator.door == CLOSED)
			elevator.door = OPENING;
		if (elevator.door == OPENING) {
			if (elevator.Door_Height <= 0) {
				elevator.door = OPEN;
				return;
			}
			else {
				elevator.Door_Height -= Elevator_Door_Speed;
				return;
			}
		}

		for (int i = 0; i < elevator.passengers.size();) {
			if (elevator.passengers[i].destination == elevator.elevator_position) {
				if (elevator.elevator_position == FLOOR5 || elevator.elevator_position == FLOOR3 || elevator.elevator_position == FLOOR1)
					elevator.passengers[i].position_x += Traveller_Speed;

				if (elevator.elevator_position == FLOOR4 || elevator.elevator_position == FLOOR2)
					elevator.passengers[i].position_x -= Traveller_Speed;

				if (!passengers_at_destination())							//Until the passanger leaves the floor nothing will continue
					return;
				int j = elevator.passengers[i].Elevator_Spot;
				elevator.Spots[j] = false;
				elevator.passengers.erase(elevator.passengers.begin() + i);
				elevator.current_weight -= 70;
				return;
			}
			else
				i++;
		}
	}
	if (passengers_to_enter()) {

		if (elevator.door == CLOSED)
			elevator.door = OPENING;
		if (elevator.door == OPENING) {
			if (elevator.Door_Height <= 0) {
				elevator.door = OPEN;
				return;
			}
			else {
				elevator.Door_Height -= Elevator_Door_Speed;
				return;
			}
		}

		switch (elevator.elevator_position) {
		case FLOOR5:
			for (int i = 0; i < floor5_people.size(); i++) {
				if (floor5_people[i].Elevator_Spot == ZERO) {
					for (int j = 0; j < 8; j++) {
						if (elevator.Spots[j] == false) {
							elevator.Spots[j] = true;
							floor5_people[i].Elevator_Spot = j;
							return;									//If something's wrong with elevator spots check here
						}
					}
				}
				if (!passengers_in_elevator()) {
					floor5_people[i].position_x -= Traveller_Speed;
					int k = floor5_people[i].Elevator_Spot;
					if (floor5_people[i].position_x <= (E_spot[k]))
						floor5_people[i].position_x = E_spot[k];
					return;
				}
				else {
					elevator.passengers.push_back(floor5_people[i]);
					elevator.current_weight += 70;
					floor5_people.erase(floor5_people.begin() + i);
					return;
				}
			}
			break;
		case FLOOR4:
			for (int i = 0; i < floor4_people.size(); i++) {
				if (floor4_people[i].destination_direction == elevator.direction || elevator.direction == NONE) {
					if (floor4_people[i].Elevator_Spot == ZERO) {
						for (int j = 0; j < 8; j++) {
							if (elevator.Spots[j] == false) {
								elevator.Spots[j] = true;
								floor4_people[i].Elevator_Spot = j;
								return;									//If something's wrong with elevator spots check here
							}
						}
					}
					if (!passengers_in_elevator()) {
						floor4_people[i].position_x += Traveller_Speed;
						int k = floor4_people[i].Elevator_Spot;
						if (floor4_people[i].position_x >= (E_spot[k]))
							floor4_people[i].position_x = E_spot[k];
						return;
					}
					else {
						elevator.passengers.push_back(floor4_people[i]);
						elevator.current_weight += 70;
						floor4_people.erase(floor4_people.begin() + i);
						return;
					}
				}

			}
			break;
		case FLOOR3:
			for (int i = 0; i < floor3_people.size(); i++) {
				if (floor3_people[i].destination_direction == elevator.direction || elevator.direction == NONE) {
					if (floor3_people[i].Elevator_Spot == ZERO) {
						for (int j = 0; j < 8; j++) {
							if (elevator.Spots[j] == false) {
								elevator.Spots[j] = true;
								floor3_people[i].Elevator_Spot = j;
								return;									//If something's wrong with elevator spots check here
							}
						}
					}
					if (!passengers_in_elevator()) {
						floor3_people[i].position_x -= Traveller_Speed;
						int k = floor3_people[i].Elevator_Spot;
						if (floor3_people[i].position_x <= (E_spot[k]))
							floor3_people[i].position_x = E_spot[k];
						return;
					}
					else {
						elevator.passengers.push_back(floor3_people[i]);
						elevator.current_weight += 70;
						floor3_people.erase(floor3_people.begin() + i);
						return;
					}
				}
				
			}
			break;
		case FLOOR2:
			for (int i = 0; i < floor2_people.size(); i++) {
				if (floor2_people[i].destination_direction == elevator.direction || elevator.direction == NONE) {
					if (floor2_people[i].Elevator_Spot == ZERO) {
						for (int j = 0; j < 8; j++) {
							if (elevator.Spots[j] == false) {
								elevator.Spots[j] = true;
								floor2_people[i].Elevator_Spot = j;
								return;									//If something's wrong with elevator spots check here
							}
						}
					}
					if (!passengers_in_elevator()) {
						floor2_people[i].position_x += Traveller_Speed;
						int k = floor2_people[i].Elevator_Spot;
						if (floor2_people[i].position_x >= (E_spot[k]))
							floor2_people[i].position_x = E_spot[k];
						return;
					}
					else {
						elevator.passengers.push_back(floor2_people[i]);
						elevator.current_weight += 70;
						floor2_people.erase(floor2_people.begin() + i);
						return;
					}
				}

			}
			break;
		case FLOOR1:
			for (int i = 0; i < floor1_people.size(); i++) {
				if (floor1_people[i].Elevator_Spot == ZERO) {
					for (int j = 0; j < 8; j++) {
						if (elevator.Spots[j] == false) {
							elevator.Spots[j] = true;
							floor1_people[i].Elevator_Spot = j;
							return;									//If something's wrong with elevator spots check here
						}
					}
				}
				if (!passengers_in_elevator()) {
					floor1_people[i].position_x -= Traveller_Speed;
					int k = floor1_people[i].Elevator_Spot;
					if (floor1_people[i].position_x <= (E_spot[k]))
						floor1_people[i].position_x = E_spot[k];
					return;
				}
				else {
					elevator.passengers.push_back(floor1_people[i]);
					elevator.current_weight += 70;
					floor1_people.erase(floor1_people.begin() + i);
					return;
				}
			}
			break;
		}
	}

	if (elevator.door == OPEN)
		elevator.door = CLOSING;
	if (elevator.door == CLOSING) {
		if (elevator.Door_Height <= 0) {
			elevator.door = CLOSED;
			return;
		}
		else {
			elevator.Door_Height += Elevator_Door_Speed;
			return;
		}
	}

	if (elevator.passengers.size() != 0) {
		elevator.direction = elevator.passengers[0].destination_direction;
	}
	else if (passengers_waiting()) {
		switch (elevator.elevator_position) {
		case FLOOR5:
			if (floor5_people.size() != 0)
				return;
			elevator.direction = DOWN;
			break;
		case FLOOR4:
			if (floor4_people.size() != 0)
				return;
			if (floor5_people.size() != 0)
				elevator.direction = UP;
			else
				elevator.direction = DOWN;
			break;
		case FLOOR3:
			if (floor3_people.size() != 0)
				return;
			if (floor5_people.size() != 0 || floor4_people.size() != 0)
				elevator.direction = UP;
			else
				elevator.direction = DOWN;
			break;
		case FLOOR2:
			if (floor2_people.size() != 0)
				return;
			if (floor1_people.size() != 0)
				elevator.direction = DOWN;
			else
				elevator.direction = UP;
			break;
		case FLOOR1:
			if (floor1_people.size() != 0)
				return;
			elevator.direction = UP;
			break;
		default:
			break;
		}
	}
	else
		elevator.direction = NONE;

	if (elevator.direction == UP) {				//move elevator down
		elevator.elevator_position = TRANSIT;
		elevator.position_y -= Elevator_Speed;
		for (int i = 0; i < elevator.passengers.size(); i++)
			elevator.passengers[i].position_y = elevator.position_y;  
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_5 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_5 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR5);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_4 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_4 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR4);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_3 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_3 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR3);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_2 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_2 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR2);
		}

	}
	if (elevator.direction == DOWN) {		//move elevator up
		elevator.elevator_position = TRANSIT;
		elevator.position_y += Elevator_Speed;
		for (int i = 0; i < elevator.passengers.size(); i++)
			elevator.passengers[i].position_y = elevator.position_y;
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_4 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_4 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR4);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_3 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_3 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR3);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_2 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_2 + (Elevator_Speed)) {
			(elevator.elevator_position = FLOOR2);
		}
		if (elevator.position_y - (Elevator_Speed - 1) >= Floor_1 - (Elevator_Speed) && elevator.position_y + (Elevator_Speed - 1) <= Floor_1 + (Elevator_Speed))
			(elevator.elevator_position = FLOOR1);
	}

}



void repaintWindow(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps, RECT* Static_Area)
{
	elevator_control(hdc);
	Bitmap* bmp = new Bitmap(1500, 1500, PixelFormat32bppARGB);

	hdc = BeginPaint(hWnd, &ps);

	Graphics graphics(hdc);
	
	Graphics* imageGraphics = Graphics::FromImage(bmp);
	Pen Static_Pen(Color(255, 0, 0, 255), 3);

	Pen Pen1(Color(255, 255, 0, 255), 3);				//RGB
	Pen Pen2(Color(255, 0, 255, 255), 3);
	Pen Pen3(Color(255, 255, 255, 0), 3);
	Pen Pen4(Color(255, 255, 0, 0), 3);
	Pen Pen5(Color(255, 0, 255, 0), 3);
	
	SolidBrush S_Pen1(Color(255, 255, 0, 255));				//RGB
	SolidBrush S_Pen2(Color(255, 0, 255, 255));
	SolidBrush S_Pen3(Color(255, 255, 255, 0));
	SolidBrush S_Pen4(Color(255, 255, 0, 0));
	SolidBrush S_Pen5(Color(255, 0, 255, 0));
	
	//draw everything to image graphics
	imageGraphics->DrawLine(&Static_Pen, L_Platform_R, E_Endings / 2, R_Platform_L, E_Endings / 2);
	imageGraphics->DrawLine(&Static_Pen, L_Platform_R, E_Endings / 2 - 1, L_Platform_R, Floor_4 - Elevator_Height);
	imageGraphics->DrawLine(&Static_Pen, R_Platform_L, E_Endings / 2 - 1, R_Platform_L, E_Endings);
	imageGraphics->DrawLine(&Static_Pen, L_Platform_R, Floor_4, L_Platform_R, Floor_2 - Elevator_Height);
	imageGraphics->DrawLine(&Static_Pen, L_Platform_R, Floor_2, L_Platform_R, Floor_2 + Elevator_Height + E_Endings);
	imageGraphics->DrawLine(&Static_Pen, R_Platform_L, Floor_5, R_Platform_L, Floor_3 - Elevator_Height);
	imageGraphics->DrawLine(&Static_Pen, R_Platform_L, Floor_3, R_Platform_L, Floor_1 - Elevator_Height);
	imageGraphics->DrawLine(&Static_Pen, R_Platform_L, Floor_1,  R_Platform_L, Floor_1 + E_Endings);
	imageGraphics->DrawLine(&Static_Pen, L_Platform_R, Floor_1 + E_Endings - 2, R_Platform_L, Floor_1 + E_Endings - 2);

	imageGraphics->DrawLine(&Pen1, R_Platform_L, Floor_1, R_Platform_R, Floor_1);
	imageGraphics->DrawLine(&Pen2, L_Platform_L, Floor_2, L_Platform_R, Floor_2);
	imageGraphics->DrawLine(&Pen3, R_Platform_L, Floor_3, R_Platform_R, Floor_3);
	imageGraphics->DrawLine(&Pen4, L_Platform_L, Floor_4, L_Platform_R, Floor_4);
	imageGraphics->DrawLine(&Pen5, R_Platform_L, Floor_5, R_Platform_R, Floor_5);
	//here is the door functions
	
	if (elevator.door == CLOSED)
		imageGraphics->DrawRectangle(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_R - Elevator_L, Elevator_Height);

	else if (elevator.door == OPEN) {
		if (elevator.elevator_position == FLOOR1 || elevator.elevator_position == FLOOR3 || elevator.elevator_position == FLOOR5) {
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_L, elevator.position_y);
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y - Elevator_Height);
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y, Elevator_R, elevator.position_y);
		}
		else if (elevator.elevator_position == FLOOR2 || elevator.elevator_position == FLOOR4) {
			imageGraphics->DrawLine(&Static_Pen, Elevator_R, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y);
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y - Elevator_Height);
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y, Elevator_R, elevator.position_y);
		}
	}

	else if (elevator.door == OPENING || elevator.door == CLOSING) {
		if (elevator.elevator_position == FLOOR1 || elevator.elevator_position == FLOOR3 || elevator.elevator_position == FLOOR5) {
			imageGraphics->DrawLine(&Static_Pen, Elevator_R, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y - Elevator_Height + elevator.Door_Height);
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_L, elevator.position_y); //left
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y - Elevator_Height); //top
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y, Elevator_R, elevator.position_y);  //bottom
		}
		else if (elevator.elevator_position == FLOOR2 || elevator.elevator_position == FLOOR4) {
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_L, elevator.position_y - Elevator_Height + elevator.Door_Height);
			imageGraphics->DrawLine(&Static_Pen, Elevator_R, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y); //right
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y - Elevator_Height, Elevator_R, elevator.position_y - Elevator_Height); //top
			imageGraphics->DrawLine(&Static_Pen, Elevator_L, elevator.position_y, Elevator_R, elevator.position_y);  //bottom
		}
	}
	
	//elevator.position_y -= 2;	//this is just for testing 

	
	for (int i = 0; i < floor1_people.size(); i++) {
		if (floor1_people[i].destination == FLOOR2)
			imageGraphics->FillRectangle(&S_Pen2, floor1_people[i].position_x, floor1_people[i].position_y - 50, 18, 50);
		else if (floor1_people[i].destination == FLOOR3)
			imageGraphics->FillRectangle(&S_Pen3, floor1_people[i].position_x, floor1_people[i].position_y - 50, 18, 50);
		else if (floor1_people[i].destination == FLOOR4)
			imageGraphics->FillRectangle(&S_Pen4, floor1_people[i].position_x, floor1_people[i].position_y - 50, 18, 50);
		else if (floor1_people[i].destination == FLOOR5)
			imageGraphics->FillRectangle(&S_Pen5, floor1_people[i].position_x, floor1_people[i].position_y - 50, 18, 50);
	}
	for (int i = 0; i < floor2_people.size(); i++) {
		if (floor2_people[i].destination == FLOOR1)
			imageGraphics->FillRectangle(&S_Pen1, floor2_people[i].position_x, floor2_people[i].position_y - 50, 18, 50);
		else if (floor2_people[i].destination == FLOOR3)
			imageGraphics->FillRectangle(&S_Pen3, floor2_people[i].position_x, floor2_people[i].position_y - 50, 18, 50);
		else if (floor2_people[i].destination == FLOOR4)
			imageGraphics->FillRectangle(&S_Pen4, floor2_people[i].position_x, floor2_people[i].position_y - 50, 18, 50);
		else if (floor2_people[i].destination == FLOOR5)
			imageGraphics->FillRectangle(&S_Pen5, floor2_people[i].position_x, floor2_people[i].position_y - 50, 18, 50);
	}
	for (int i = 0; i < floor3_people.size(); i++) {
		if (floor3_people[i].destination == FLOOR1)
			imageGraphics->FillRectangle(&S_Pen1, floor3_people[i].position_x, floor3_people[i].position_y - 50, 18, 50);
		else if (floor3_people[i].destination == FLOOR2)
			imageGraphics->FillRectangle(&S_Pen2, floor3_people[i].position_x, floor3_people[i].position_y - 50, 18, 50);
		else if (floor3_people[i].destination == FLOOR4)
			imageGraphics->FillRectangle(&S_Pen4, floor3_people[i].position_x, floor3_people[i].position_y - 50, 18, 50);
		else if (floor3_people[i].destination == FLOOR5)
			imageGraphics->FillRectangle(&S_Pen5, floor3_people[i].position_x, floor3_people[i].position_y - 50, 18, 50);
	}
	for (int i = 0; i < floor4_people.size(); i++) {
		if (floor4_people[i].destination == FLOOR1)
			imageGraphics->FillRectangle(&S_Pen1, floor4_people[i].position_x, floor4_people[i].position_y - 50, 18, 50);
		else if (floor4_people[i].destination == FLOOR2)
			imageGraphics->FillRectangle(&S_Pen2, floor4_people[i].position_x, floor4_people[i].position_y - 50, 18, 50);
		else if (floor4_people[i].destination == FLOOR3)
			imageGraphics->FillRectangle(&S_Pen3, floor4_people[i].position_x, floor4_people[i].position_y - 50, 18, 50);
		else if (floor4_people[i].destination == FLOOR5)
			imageGraphics->FillRectangle(&S_Pen5, floor4_people[i].position_x, floor4_people[i].position_y - 50, 18, 50);
	}
	for (int i = 0; i < floor5_people.size(); i++) {
		if (floor5_people[i].destination == FLOOR1)
			imageGraphics->FillRectangle(&S_Pen1, floor5_people[i].position_x, floor5_people[i].position_y - 50, 18, 50);
		else if (floor5_people[i].destination == FLOOR2)
			imageGraphics->FillRectangle(&S_Pen2, floor5_people[i].position_x, floor5_people[i].position_y - 50, 18, 50);
		else if (floor5_people[i].destination == FLOOR3)
			imageGraphics->FillRectangle(&S_Pen3, floor5_people[i].position_x, floor5_people[i].position_y - 50, 18, 50);
		else if (floor5_people[i].destination == FLOOR4)
			imageGraphics->FillRectangle(&S_Pen4, floor5_people[i].position_x, floor5_people[i].position_y - 50, 18, 50);
	}
	for (int i = 0; i < elevator.passengers.size(); i++) {
		if (elevator.passengers[i].destination == FLOOR1)
			imageGraphics->FillRectangle(&S_Pen1, elevator.passengers[i].position_x, elevator.passengers[i].position_y - 50, 18, 50);
		else if (elevator.passengers[i].destination == FLOOR2)
			imageGraphics->FillRectangle(&S_Pen2, elevator.passengers[i].position_x, elevator.passengers[i].position_y - 50, 18, 50);
		else if (elevator.passengers[i].destination == FLOOR3)
			imageGraphics->FillRectangle(&S_Pen3, elevator.passengers[i].position_x, elevator.passengers[i].position_y - 50, 18, 50);
		else if (elevator.passengers[i].destination == FLOOR4)
			imageGraphics->FillRectangle(&S_Pen4, elevator.passengers[i].position_x, elevator.passengers[i].position_y - 50, 18, 50);
		else if (elevator.passengers[i].destination == FLOOR5)
			imageGraphics->FillRectangle(&S_Pen5, elevator.passengers[i].position_x, elevator.passengers[i].position_y - 50, 18, 50);
	}
	
	FontFamily   fontFamily(L"Arial");
	Font         font(&fontFamily, 12, FontStyleRegular, UnitPoint);
	PointF      pointF(20, 20);
	PointF      pointG(150, 20);
	SolidBrush  solidBrush(Color(255, 0, 0, 255));

	int weight = 70 * elevator.passengers.size();
	wchar_t current_weight[10];
	swprintf_s(current_weight, L"%d", weight);

	imageGraphics->DrawString(L"Waga w windzie: ", -1, &font, pointF, &solidBrush);
	imageGraphics->DrawString(current_weight, -1, &font, pointG, &solidBrush);
	
	graphics.DrawImage(bmp, 0, 0);

	//this method also slow
	//TextureBrush* myBrush = new TextureBrush(bmp);
	//graphics.FillRectangle(myBrush, 0, 0, 1500, 1500);

	EndPaint(hWnd, &ps);

	delete imageGraphics;
	delete bmp;
}


int OnCreate(HWND window)
{
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

	//InitializeSilhouettes(hWnd, person_dest1, person_dest2, person_dest3, person_dest4, person_dest5);

	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, TMR_1, 50, 0);									//timer for animation is set up here, 50ms per frame
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

		case ID_BUTTON1_2:								//floor1
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR2;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_1;
			traveller.position_x = R_Platform_R - 20;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_3:
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR3;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_1;
			traveller.position_x = R_Platform_R - 20;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_4:
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_1;
			traveller.position_x = R_Platform_R - 20;
			floor1_people.push_back(traveller);
			break;
		case ID_BUTTON1_5:
			traveller.person_position = FLOOR1;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_1;
			traveller.position_x = R_Platform_R - 20;
			floor1_people.push_back(traveller);
			break;

		case ID_BUTTON2_1:								//floor2
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_2;
			traveller.position_x = L_Platform_L;
			floor2_people.push_back(traveller);
			break;
		case ID_BUTTON2_3:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR3;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_2;
			traveller.position_x = L_Platform_L;
			floor2_people.push_back(traveller);
			break;
		case ID_BUTTON2_4:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_2;
			traveller.position_x = L_Platform_L;
			floor2_people.push_back(traveller);
			break;
		case ID_BUTTON2_5:
			traveller.person_position = FLOOR2;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_2;
			traveller.position_x = L_Platform_L;
			floor2_people.push_back(traveller);
			break;

		case ID_BUTTON3_1:								//floor3
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_3;
			traveller.position_x = R_Platform_R - 20;
			floor3_people.push_back(traveller);
			break;
		case ID_BUTTON3_2:
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_3;
			traveller.position_x = R_Platform_R - 20;
			floor3_people.push_back(traveller);
			break;
		case ID_BUTTON3_4:
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR4;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_3;
			traveller.position_x = R_Platform_R - 20;
			floor3_people.push_back(traveller);
			break;
		case ID_BUTTON3_5:;
			traveller.person_position = FLOOR3;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_3;
			traveller.position_x = R_Platform_R - 20;
			floor3_people.push_back(traveller);
			break;

		case ID_BUTTON4_1:								//floor4
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_4;
			traveller.position_x = L_Platform_L;
			floor4_people.push_back(traveller);
			break;
		case ID_BUTTON4_2:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_4;
			traveller.position_x = L_Platform_L;
			floor4_people.push_back(traveller);
			break;
		case ID_BUTTON4_3:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR3;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_4;
			traveller.position_x = L_Platform_L;
			floor4_people.push_back(traveller);
			break;
		case ID_BUTTON4_5:
			traveller.person_position = FLOOR4;
			traveller.destination = FLOOR5;
			traveller.destination_direction = UP;
			traveller.position_y = Floor_4;
			traveller.position_x = L_Platform_L;
			floor4_people.push_back(traveller);
			break;

		case ID_BUTTON5_1:								//floor5
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR1;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_5;
			traveller.position_x = R_Platform_R - 20;
			floor5_people.push_back(traveller);
			break;
		case ID_BUTTON5_2:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR2;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_5;
			traveller.position_x = R_Platform_R - 20;
			floor5_people.push_back(traveller);
			break;
		case ID_BUTTON5_3:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR3;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_5;
			traveller.position_x = R_Platform_R - 20;
			floor5_people.push_back(traveller);
			break;
		case ID_BUTTON5_4:
			traveller.person_position = FLOOR5;
			traveller.destination = FLOOR4;
			traveller.destination_direction = DOWN;
			traveller.position_y = Floor_5;
			traveller.position_x = R_Platform_R - 20;
			floor5_people.push_back(traveller);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;

	case WM_PAINT:
		// TODO: Add any drawing code here (not depend on timer, buttons)

		//StaticPaint(hWnd, hdc, ps, &StaticDrawArea);
		repaintWindow(hWnd, hdc, ps, &StaticDrawArea);
		break;
	case WM_DESTROY:
		//delete person_dest1;
		//delete person_dest2;
		//delete person_dest3;
		//delete person_dest4;
		//delete person_dest5;
		PostQuitMessage(0);
		break;

	case WM_TIMER:					//change the timer redrawing
		switch (wParam)
		{
		case TMR_1:
			//force window to repaint
			InvalidateRect(hWnd, &StaticDrawArea, TRUE);
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
