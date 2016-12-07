#include <Windows.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;

LPCWSTR ClassName = L"Klasa WINAPI"; 
HWND hwnd; 
MSG msg;
HWND btnO, btnW;
HWND txtBoxGTC, txtBoxSTC , txtBoxT1, txtBoxT2, txtBoxT3, txtBoxT4, txtBoxT5;
int czasGTC;
char Str_INTERVAL[10];	

#define ID_timer 1


void CALLBACK TimerProc(HWND hwnd, UINT msg, UINT nIDEvent, DWORD dwTime)
{
	
	KillTimer(hwnd,ID_timer);
	LockWorkStation();
	
	
	
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Odliczanie(LPWSTR czas)
{
	int roznica;
	float czasK;
	
	czasK = wcstod(czas, NULL);
	roznica=czasK - czasGTC;

	if (roznica<0) MessageBox(NULL, L"Podany czas juz minal!", L"Upss...", MB_OK);
	else 
	{
		SetWindowText(txtBoxT5,L"Odliczanie...");
		WCHAR buf[20];
		_ltow_s(roznica, buf, sizeof(buf)/sizeof(WCHAR), 10);
		LPCWSTR a;
		std::wstring s = buf;
		a = (LPCWSTR)s.c_str();
		SetWindowText(txtBoxT4, a);
		SetTimer( hwnd, ID_timer, roznica, TimerProc);
		
	}

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{ 
	WNDCLASSEX wc;	

	wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground =(HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wc);
	
	hwnd = CreateWindowEx(WS_EX_WINDOWEDGE, ClassName, L"WINAPI", WS_OVERLAPPEDWINDOW, 300, 300, 480, 200, NULL, NULL, hInstance, NULL);
	btnO =  CreateWindowEx(0, L"BUTTON", L"Odswiez", WS_CHILD|WS_VISIBLE, 350, 5, 100, 30, hwnd, NULL, hInstance, NULL);
	txtBoxT1 = CreateWindowEx(SS_GRAYFRAME, L"STATIC", L"Czas od uruchomienia komputera (ms):" , WS_CHILD|WS_VISIBLE, 5, 5, 260, 30, hwnd, NULL, hInstance, NULL);
	txtBoxGTC = CreateWindowEx(SS_GRAYFRAME, L"STATIC", NULL , WS_CHILD|WS_VISIBLE, 265,5, 80, 30, hwnd, NULL, hInstance, NULL);
	txtBoxT2 = CreateWindowEx(SS_GRAYFRAME, L"STATIC", L"Kiedy ma siê zatrzymac (ms):" , WS_CHILD|WS_VISIBLE, 5, 45, 260, 30, hwnd, NULL, hInstance, NULL);	
	txtBoxSTC = CreateWindowEx(SS_GRAYFRAME, L"EDIT", NULL , WS_CHILD|WS_VISIBLE|WS_BORDER, 265,45, 80, 30, hwnd, NULL, hInstance, NULL);
	btnW =  CreateWindowEx(0, L"BUTTON", L"Wczytaj", WS_CHILD|WS_VISIBLE, 350, 45, 100, 30, hwnd, NULL, hInstance, NULL);
	txtBoxT3 = CreateWindowEx(SS_GRAYFRAME, L"STATIC", L"Zatrzyma sie za (ms):" , WS_CHILD|WS_VISIBLE, 5, 85, 260, 30, hwnd, NULL, hInstance, NULL);	
	txtBoxT4 = CreateWindowEx(SS_GRAYFRAME, L"STATIC", NULL , WS_CHILD|WS_VISIBLE, 265,85, 80, 30, hwnd, NULL, hInstance, NULL);
	txtBoxT5 = CreateWindowEx(SS_GRAYFRAME, L"STATIC", NULL , WS_CHILD|WS_VISIBLE, 350,85, 100, 30, hwnd, NULL, hInstance, NULL);
	
	czasGTC = GetTickCount64();
	
	WCHAR buf[20];
	_ltow_s(czasGTC, buf, sizeof(buf)/sizeof(WCHAR), 10);
	LPCWSTR a;
	std::wstring s = buf;				
	a = (LPCWSTR)s.c_str();
	 
	SetWindowText(txtBoxGTC, a );


	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	if( hwnd == NULL )
	{
		MessageBox( NULL, L"Bond", L"Okno nie chce sie pojawic", MB_ICONEXCLAMATION );
	 return 1;
	}
	
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{	
    switch(msg)
    {
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;       
		case WM_DESTROY:
			
			PostQuitMessage(0);

			break;
		case WM_COMMAND:		   
			if ((HWND) lParam == btnO) 
				{
					WCHAR buf[20];
					_ltow_s(GetTickCount(), buf, sizeof(buf)/sizeof(WCHAR), 10);
					LPCWSTR a;
					std::wstring s = buf;
					a = (LPCWSTR)s.c_str();
					SetWindowText(txtBoxGTC, a );
			     }
			if ((HWND) lParam == btnW) 
			{
				DWORD l = GetWindowTextLength(txtBoxSTC);
				LPWSTR buf = (LPWSTR) GlobalAlloc(GPTR, l+1);
				if (GetWindowText(txtBoxSTC, buf, l+1))	
				{
					Odliczanie(buf); 
				}

				else MessageBox(NULL, L"Podaj wartosc!!!", L"B£¥D", MB_SYSTEMMODAL | MB_OK); 

				
			}

			break;

       default:

			return DefWindowProc(hwnd, msg, wParam, lParam);
    }   
    return 0;
}			
