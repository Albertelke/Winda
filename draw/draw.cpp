// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"
#include<vector>
#include <cmath>

#define MAX_LOADSTRING 100
#define TMR_1 1

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The tit le bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
HWND hwndButton;


class people
{
public:
	people(int d,int sp, PointF pos,int ww_l);
	int destination;
	PointF position;
	PointF size;
	//int direction;
	int speed;
	int w_l;
	bool is_in;
};

class elevator
{
	friend class winda;
public:
	elevator();
	PointF position;
	PointF size;
	int slots[8];
	std::vector <int> callings;
	void moving();
	bool is_going_up;
	void load();
	int w_l = 0;
	int is_free_slot();

};
elevator winda;

class engine
{
	friend class elevator;
public:
	engine();
	std::vector <people> passengers;
	void add_passenger(int w_l, int dest);
	void walk();
	bool slots[5][12];
	bool is_free_slot(int w_l);
	int  next_free_slot(int w_l, size_t t);

};

engine main_engine;



people::people(int d, int sp, PointF pos,int ww_l)
{
	destination = d;
	size = PointF(19.0f,60.0f);
	position = pos;
	speed = sp*5;
	w_l = ww_l;
	is_in = 0;
}






elevator::elevator()
{
	position = PointF(300.0f, 665.0f);
	size = PointF(200.0f, 95.0f);
	for (int i = 0; i < 8; i++)
		slots[i] = 0;
	bool is_going_up = 1;


}

int elevator::is_free_slot()
{
	for (int i = 0; i < 8; i++)
		if (slots[i] == 0) return i;
	return -1;
}
void elevator::moving()
{


}
void elevator::load()
{
	for (size_t t = 0; t < main_engine.passengers.size(); t++)
		if (is_free_slot() != -1)
		{

			if (main_engine.passengers[t].w_l == w_l && int((main_engine.passengers[t].position.X - 6) / 25) == 11)

			{
				main_engine.passengers[t].position.X += (is_free_slot() + 1) * 25;
				slots[is_free_slot()] = 1;
				main_engine.passengers[t].is_in = 1;
				for (int i = 0; i < 12; i++)
					main_engine.slots[w_l][i] = 0;
			}
		}
}






engine::engine()
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 12; j++)
			slots[i][j] = 0;
}


int engine::next_free_slot(int w_l,size_t t)
{
	int h;
	if (w_l % 2 == 0)
	{
		h = int((passengers[t].position.X - 6) / 25);
		if (slots[w_l][h] == 0)
			for (int i = 11; i >= 0; i--)
			{
				if (slots[w_l][i] == 0)
					return i;
			}
	}
	else h = int((passengers[t].position.X - 500) / 25);
	if(slots[w_l][h]==0)
	for (int i = 0; i < 12; i++)
	{
		if (slots[w_l][i] == 0)
			return i;
	}
	return -1;
}

void engine::walk()
{
	for (size_t i = 0; i < passengers.size(); i++)
	{
		if (passengers[i].is_in == 1)
		{
			passengers[i].position.Y = winda.position.Y+25;
			continue;
		}
		int p=next_free_slot(passengers[i].w_l,i);
		if (p != -1)
		{
			if (passengers[i].w_l % 2 == 0)
			{
				if (abs(passengers[i].position.X - (6 + 25 * p)) <= 5)
				{
					passengers[i].position.X = (6 + 25 * p);
					slots[passengers[i].w_l][p] = 1;
				}

				else
					passengers[i].position.X += passengers[i].speed;
			}
			if (passengers[i].w_l % 2 == 1)
			{
				if (abs(passengers[i].position.X - (500+(p)*25)) <= 5)
				{
					passengers[i].position.X = (500+(p)*25);
					slots[passengers[i].w_l][p] = 1;
				}

				else
					passengers[i].position.X += passengers[i].speed;
			}
			
		}
		
	}
}

bool engine::is_free_slot(int w_l)
{
	for (int i = 0; i < 12; i++)
		if (slots[w_l][i] == 0) return true;

		 return false;
}
void engine::add_passenger(int w_l, int dest)
{
	if (is_free_slot(w_l))
	{
		float pom = (4 - w_l)*150.0f;
		passengers.push_back(people(dest, pow(-1, w_l), PointF((w_l % 2)*800.0f, pom+90.0f),w_l));
	}


}





void MyOnPaint(HDC hdc)
{
	value++;
	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,0));
	SolidBrush mybrush(Color(255, 0, 102, 255));
	SolidBrush floorbrush(Color(255, 204, 51, 255));
	SolidBrush person_color(Color(255, 0, 0, 0));

	//graphics.Dr awLine(&pen,0,0,200,100);
	int l_y = 150;
	int l_x = 300;
	for (int i = 0; i < 5; i++)
	{
		graphics.FillRectangle(&mybrush, i%2*500,l_y*(i+1) , 300, 10);

	}
	graphics.DrawRectangle(&pen, winda.position.X, winda.position.Y, winda.size.X, winda.size.Y);
	graphics.FillRectangle(&floorbrush, winda.position.X, winda.position.Y+85, winda.size.X, 10.0f);
	for (size_t i = 0; i < main_engine.passengers.size(); i++)
		graphics.FillRectangle(&person_color, main_engine.passengers[i].position.X, main_engine.passengers[i].position.Y, main_engine.passengers[i].size.X, main_engine.passengers[i].size.Y);

	


	
}


int OnCreate(HWND window)
{
   SetTimer(window, TMR_1, 25, 0);
   return 0;
}



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
	value= 10;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
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

	return (int) msg.wParam;
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
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
  
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 720,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 700,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON2,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 680,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON3,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 660,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON4,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 570,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON5,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 550,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON6,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 530,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON7,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 510,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON8,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 420,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON9,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 400,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON10,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 380,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON11,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 360,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON12,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 270,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON13,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 250,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON14,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 230,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON15,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 210,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON16,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 120,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON17,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 100,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON18,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 80,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON19,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 60,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON20,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   
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
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//OnCreate(hWnd,wParam,lParam);
	//OnTimer(hWnd,wParam,lParam);

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_BUTTON1:
			main_engine.add_passenger(0, 1);
			
			break;
		case ID_BUTTON2:
			main_engine.add_passenger(0, 2);

			break;
		case ID_BUTTON3:
			main_engine.add_passenger(0, 3);

			break;
		case ID_BUTTON4:
			main_engine.add_passenger(0, 4);

			break;
		case ID_BUTTON5:
			main_engine.add_passenger(1, 0);

			break;
		case ID_BUTTON6:
			main_engine.add_passenger(1, 2);

			break;
		case ID_BUTTON7:
			main_engine.add_passenger(1, 3);

			break;
		case ID_BUTTON8:
			main_engine.add_passenger(1, 4);

			break;
		case ID_BUTTON9:
			main_engine.add_passenger(2, 0);

			break;
		case ID_BUTTON10:
			main_engine.add_passenger(2, 1);

			break;
		case ID_BUTTON11:
			main_engine.add_passenger(2, 3);

			break;
		case ID_BUTTON12:
			main_engine.add_passenger(2, 4);

			break;
		case ID_BUTTON13:
			main_engine.add_passenger(3, 0);

			break;
		case ID_BUTTON14:
			main_engine.add_passenger(3, 1);

			break;
		case ID_BUTTON15:
			main_engine.add_passenger(3, 2);

			break;
		case ID_BUTTON16:
			main_engine.add_passenger(3, 4);

			break;
		case ID_BUTTON17:
			main_engine.add_passenger(4,0);

			break;
		case ID_BUTTON18:
			main_engine.add_passenger(4, 1);

			break;
		case ID_BUTTON19:
			main_engine.add_passenger(4, 2);

			break;
		case ID_BUTTON20:
			main_engine.add_passenger(4, 3);

			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		
		MyOnPaint(hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		switch (wParam)
		{
			case TMR_1:
				//force window to repaint
				InvalidateRect(hWnd, NULL, TRUE);
				hdc = BeginPaint(hWnd, &ps);
				MyOnPaint(hdc);
				EndPaint(hWnd, &ps);
				main_engine.walk();
				winda.load();
				
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
