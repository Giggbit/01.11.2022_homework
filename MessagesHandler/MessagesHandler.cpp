#include <windows.h>
#include <tchar.h>
#include <ctime>

//�������� ������� ���������
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassWindow[] = TEXT("��������� ����������"); /* ��� ������ ���� */

INT WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG Msg;
	WNDCLASSEX wcl;

	/* 1. ����������� ������ ����  */
	wcl.cbSize = sizeof (wcl);	// ������ ��������� WNDCLASSEX 
	wcl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	// ���� ������ �������� ��������� � ������� ������ (DBLCLK)
	wcl.lpfnWndProc = WindowProc;	// ����� ������� ���������
	wcl.cbClsExtra = 0;		// ������������ Windows 
	wcl.cbWndExtra  = 0; 	// ������������ Windows 
	wcl.hInstance = hInst;	// ���������� ������� ����������
	wcl.hIcon = LoadIcon(NULL, IDI_APPLICATION);	// �������� ����������� ������
	wcl.hCursor = LoadCursor(NULL, IDC_ARROW);		// �������� ������������ �������
	wcl.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);	//���������� ���� ����� ������			
	wcl.lpszMenuName = NULL;	// ���������� �� �������� ����
	wcl.lpszClassName = szClassWindow;	// ��� ������ ����
	wcl.hIconSm = NULL;	// ���������� ��������� ������ ��� ����� � ������� ����


	/*  2. ����������� ������ ����  */
	if (!RegisterClassEx(&wcl))
		return 0;	// ��� ��������� ����������� - �����

	/*  3. �������� ����  */
	// ��������� ���� �  ���������� hWnd ������������� ���������� ����
	hWnd = CreateWindowEx(
		0,		// ����������� ����� ����
		szClassWindow,	// ��� ������ ����
		TEXT("������  Windows ����������"),	// ��������� ����
		/* ���������, �����, ����������� ������ �������, ��������� ����,
			������ ������������ � ���������� ����  */
		WS_OVERLAPPEDWINDOW,	// ����� ����
		CW_USEDEFAULT,	// �-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// y-���������� ������ �������� ���� ����
		CW_USEDEFAULT,	// ������ ����
		CW_USEDEFAULT,	// ������ ����
		NULL,			// ���������� ������������� ����
		NULL,			// ���������� ���� ����
		hInst,		// ������������� ����������, ���������� ����
		NULL);		// ��������� �� ������� ������ ����������


	/* 4. ����������� ���� */
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);	// ����������� ����


	/* 5. ������ ����� ��������� ���������  */
	// ��������� ���������� ��������� �� ������� ���������
	while (GetMessage(&Msg, NULL, 0, 0)) 
	{
		TranslateMessage(&Msg);	// ���������� ���������
		DispatchMessage(&Msg);	// ��������������� ���������
	}
	return Msg.wParam;
}


// ������� ��������� ���������� ������������ �������� � �������� � �������� 
// ���������� ��������� �� ������� ��������� ������� ����������	
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	srand(time(0));

	TCHAR str_quest_1[50] = TEXT("Are you 18 years old ?");
	TCHAR str_quest_2[50] = TEXT("Are you human ?");
	TCHAR str_quest_3[50] = TEXT("Are you from America ?");
	TCHAR str_quest_4[50] = TEXT("Is your favorite green color ?");
	TCHAR* mas[] = {str_quest_1, str_quest_2, str_quest_3, str_quest_4};
	TCHAR str[50];

	int num = 0, min = 0, max = 100;
	TCHAR str_num[50];
	int answer = IDNO;

	switch(uMessage) {
	case WM_LBUTTONDOWN: {
		int rez = MessageBox(0, TEXT("������ �������� ?"), TEXT("������"), MB_OKCANCEL | MB_ICONQUESTION);
		if (rez == IDOK) {
			MessageBox(0, TEXT("��������� ����� �� 1 �� 100"), "", MB_OK | MB_ICONINFORMATION);
			while (answer != IDYES) {
				num = rand() % (max - min) + min;
				wsprintf(str_num, "���� ����� = %d ?", num);
				answer = MessageBox(0, str_num, "", MB_YESNO | MB_ICONQUESTION);
			}
			if (answer == IDYES) {
				MessageBox(0, TEXT("� ������ !"), "Win box", MB_OK);
			}
		}
		else {
			MessageBox(0, "��� ������ :(", "", MB_OK | MB_ICONHAND);
		}
		break;
	}	

	//case WM_LBUTTONUP:
	//	MessageBox(0, TEXT("�������� ����� ������ ����"), TEXT("WM_LBUTTONUP"), MB_OK | MB_ICONINFORMATION);
	//	break;

	//case WM_RBUTTONDOWN:
	//	MessageBox(0, TEXT("������ ������ ������ ����"), TEXT("WM_RBUTTONDOWN"), MB_OK | MB_ICONINFORMATION);
	//	break;
	//	
	//case WM_MOUSEMOVE: 
	//	wsprintf(str, TEXT("X=%d  Y=%d"), LOWORD(lParam), HIWORD(lParam)); // ������� ���������� ������� ����
	//	SetWindowText(hWnd, str);	// ������ ��������� � ��������� ����
	//	break;

	case WM_CHAR: {
		for (int i = 0; i < 4; i++) {
			MessageBox(hWnd, mas[i], TEXT("WM_CHAR"), MB_OKCANCEL | MB_ICONINFORMATION);
		}
		size_t sizeStr = strlen(str_quest_1);
		sizeStr += strlen(str_quest_2);
		sizeStr += strlen(str_quest_3);
		sizeStr += strlen(str_quest_4);
		sizeStr /= 4;

		wsprintf(str, TEXT("������� ����� ��������: %d"), sizeStr);
		MessageBox(hWnd, str, TEXT("Counter"), MB_OK | MB_ICONINFORMATION);
		break;
	}

	case WM_DESTROY: // ��������� � ���������� ���������
		PostQuitMessage(0);	// ������� ��������� WM_QUIT
		break;

	default:
		// ��� ���������, ������� �� �������������� � ������ ������� 
		// ������� ������������ ������� Windows �� ��������� �� ���������
		return DefWindowProc(hWnd, uMessage, wParam, lParam);
	}
	return 0;
}
