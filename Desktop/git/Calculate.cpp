#include<stdio.h>
#include<Windows.h>
#include "resource.h"
#include <math.h>
BOOL CALLBACK DialogFun(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	char Text[64];
	double x, y;
	switch(message)
	{
	case WM_COMMAND:
		switch(LOWORD(wParam))
	{
	case IDOK:
		EndDialog(hwnd, LOWORD(wParam));
		return TRUE;
	case IDC_BUTTON1: // Обработка сообщения от кнопки +
	case IDC_BUTTON2: // Обработка сообщения от кнопки -
	SendDlgItemMessage(hwnd, IDC_EDIT1, WM_GETTEXT, 63, (LPARAM)Text); 
	// Получить текст из текстового поля и записать в массивText
	if(sscanf_s(Text, "%lf", &x)<1)
	{
		MessageBox(hwnd, "Неверныйформатпервогооперанда", "Ошибкаформата", MB_OK| MB_ICONHAND);
		return TRUE;
	}
	char func[6]; 
	if (LOWORD(wParam) == IDC_BUTTON1)
	{ y = asin(x) ; func[0] = 'a'; func[1] = 'r'; func[2] = 'c'; func[3] = 's'; func[4] = 'i'; func[5] = 'n';}
	if (LOWORD(wParam) == IDC_BUTTON2)
	{ y=acos(x);  func[0] = 'a'; func[1] = 'r'; func[2] = 'c'; func[3] = 'c'; func[4] = 'o'; func[5] = 's'; }
	sprintf(Text, "%f", y); 
	SendDlgItemMessage(hwnd, IDC_EDIT2, WM_SETTEXT, 0, (LPARAM)Text); 
	// Помещаемтекстизмассивавтекстовоеполе
	sprintf_s(Text, "%c%c%c%c%c%c(%d) = %f", func[0], func[1], func[2], func[3], func[4], func[5], int(x), y);
	SendDlgItemMessage(hwnd, IDC_LIST1, LB_ADDSTRING, 0, (LPARAM)Text);
	return TRUE;
case IDC_BUTTON3: 
	// Обработка сообщения от кнопки "Очистить список"
	SendDlgItemMessage(hwnd, IDC_LIST1, LB_RESETCONTENT, 0, 0);
	return TRUE;
	}
	}
	return FALSE;
}
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR     lpCmdLine,int nCmdShow)
{
	// TODO: Place code here.
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogFun);
	return 0;
}