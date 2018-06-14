// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw.h"

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
class elevator
{

public:
	elevator();
	PointF position;
	PointF size;

};

elevator::elevator()
{
	position = PointF(300.0f, 665.0f);
		size = PointF(200.0f, 95.0f);

}
elevator winda;



void MyOnPaint(HDC hdc)
{
	value++;
	Graphics graphics(hdc);
	Pen pen(Color(255,0,0,0));
	SolidBrush mybrush(Color(255, 0, 102, 255));
	SolidBrush floorbrush(Color(255, 204, 51, 255));

	//graphics.Dr awLine(&pen,0,0,200,100);
	int l_y = 150;
	int l_x = 300;
	for (int i = 0; i < 5; i++)
	{
		graphics.FillRectangle(&mybrush, i%2*500,l_y*(i+1) , 300, 10);

	}
	graphics.DrawRectangle(&pen, winda.position.X, winda.position.Y, winda.size.X, winda.size.Y);
	graphics.FillRectangle(&floorbrush, winda.position.X, winda.position.Y+85, winda.size.X, 10.0f);
	


	
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
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 680,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 660,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 570,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 550,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 530,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 510,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 420,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 400,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 380,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 360,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 270,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 250,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 230,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("5"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   770, 210,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need


   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("1"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 120,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("2"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 100,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("3"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 80,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
	   hInstance,                            // the instance of your application
	   NULL);                               // extra bits you dont really need
   hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
	   TEXT("4"),                  // the caption of the button
	   WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
	   10, 60,                                  // the left and top co-ordinates
	   20, 20,                              // width and height
	   hWnd,                                 // parent window handle
	   (HMENU)ID_BUTTON1,                   // the ID of your button
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
			

			break;
		case ID_BUTTON2:


			break;
		case ID_BUTTON3:


			break;
		case ID_BUTTON4:


			break;
		case ID_BUTTON5:


			break;
		case ID_BUTTON6:


			break;
		case ID_BUTTON7:


			break;
		case ID_BUTTON8:


			break;
		case ID_BUTTON9:


			break;
		case ID_BUTTON10:


			break;
		case ID_BUTTON11:


			break;
		case ID_BUTTON12:


			break;
		case ID_BUTTON13:


			break;
		case ID_BUTTON14:


			break;
		case ID_BUTTON15:


			break;
		case ID_BUTTON16:


			break;
		case ID_BUTTON17:


			break;
		case ID_BUTTON18:


			break;
		case ID_BUTTON19:


			break;
		case ID_BUTTON20:


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
