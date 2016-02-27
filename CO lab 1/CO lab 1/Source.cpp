/*−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
BTNLOOK.C −− Button Look Program

(c) Charles Petzold, 1998

−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#define ID_CALCULATE     0


const int eps = 0.00001;
const int maxi = 300;
using namespace std;

struct
{
     int     iStyle;
     TCHAR * szText;
}
button={BS_PUSHBUTTON, TEXT("Calculate")};

void AppendText(HWND hwndText, LPCTSTR Text){
     int idx = GetWindowTextLength(hwndText);
     SendMessage(hwndText, EM_SETSEL, (WPARAM)idx, (LPARAM)idx);
     SendMessage(hwndText, EM_REPLACESEL, 0, (LPARAM)Text);
}

float functia(int a, int b, float x[]){
     return a*pow(x[0], 2) + 2 * x[0] * x[1] + b*pow(x[1], 2) - 2 * x[0] - 3 * x[1];
}

float gradient1(int a, float val[]){
     return 2 * a* val[0] + 2 * val[1] - 2;
}
float gradient2(int b, float val[]){
     return 2 * val[0] + 2 * b - 3;
}
float norma(float n1, float n2){
     return sqrt(pow(n1, 2) + pow(n2, 2));
}

int calculate(HDC hdc, char* buffer1, char* buffer2, char* buffer3, char* buffer4, HWND hwnd,  HWND hwndText){
     float x0[2], z[2];
     float alfa = 1.0;
     float beta = 0.5, sigma = 0.6;
     float gr[2], fz, f;
     int   a, b, iteratii;
     CHAR ix1[100];
     wchar_t trToWchar[20];
     LPWSTR ptr3;
     iteratii = 0;
     a = atoi(buffer1);
     b = atoi(buffer2);
     x0[0] = atoi(buffer3);
     x0[1] = atoi(buffer4);
 
     do{
         
     l:
               f = functia(a, b, x0);
               float gr1;
               gr1 = gradient1(a, x0);
               float gr2;
               gr2 = gradient2(b, x0);
               gr[0] = gr1;
               gr[1] = gr2;


               AppendText(hwndText, TEXT("************"));
               sprintf_s(ix1, "%.2f", x0[0]);
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT("\n"));
               AppendText(hwndText, TEXT("x: "));
               AppendText(hwndText, ptr3);
               
               sprintf_s(ix1, "%.2f", x0[1]);
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT(", "));
               AppendText(hwndText, ptr3);

               sprintf_s(ix1, "%.2f", f);
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT("\n"));
               AppendText(hwndText, TEXT("f: "));
               AppendText(hwndText, ptr3);

               sprintf_s(ix1, "%.2f", gr[0]);
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT("\n"));
               AppendText(hwndText, TEXT("gradient: "));
               AppendText(hwndText, ptr3);

               sprintf_s(ix1, "%.2f", gr[1]);
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT(", "));
               AppendText(hwndText, ptr3);

               sprintf_s(ix1, "%.2f", norma(gr1, gr2));
               mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
               ptr3 = trToWchar;
               AppendText(hwndText, TEXT("\n"));
               AppendText(hwndText, TEXT("Norma: "));
               AppendText(hwndText, ptr3);

               AppendText(hwndText, TEXT("\n\n"));
               
           

               do{
                    z[0] = x0[0] - alfa*gr[0];
                                        z[1] = x0[1] - alfa*gr[1];
                                        fz = functia(a, b, z);
                                        
                                        sprintf_s(ix1, "%.2f", z[0]);
                                        mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
                                        ptr3 = trToWchar;
                                        AppendText(hwndText, TEXT("\n\n"));
                                        AppendText(hwndText, TEXT("z:"));
                                        AppendText(hwndText, ptr3);

                                        sprintf_s(ix1, "%.2f", z[1]);
                                        mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
                                        ptr3 = trToWchar;
                                        AppendText(hwndText, TEXT(", "));
                                        AppendText(hwndText, ptr3);

                                        sprintf_s(ix1, "%.2f", fz);
                                        mbstowcs_s(0, trToWchar, ix1, strlen(ix1) + 1);
                                        ptr3 = trToWchar;
                                        AppendText(hwndText, TEXT("\n"));
                                        AppendText(hwndText, TEXT("fz: "));
                                        AppendText(hwndText, ptr3);
                                        
                                        AppendText(hwndText, TEXT("\n\n"));

                                        
                                        if (fz - f <= -sigma*alfa*pow(norma(gr1, gr2), 2)){
                                             x0[0] = z[0];
                                             x0[1] = z[1];
                                             AppendText(hwndText, TEXT("\nconditia se satisface"));
                                             AppendText(hwndText, TEXT("\n"));
                                             goto l;
                                             
                                        }
                                        else{
                                             alfa = alfa*beta;

                                        }


                                   } while (fz - f > -sigma*alfa*pow(norma(gr[0], gr[1]), 2));
     
     } while (fz - f > eps);
   
     //convert from int to char
     CHAR bufferx0[100], bufferx1[100];
          sprintf_s(bufferx0, "%.4f", x0[0]);
          sprintf_s(bufferx1, "%.4f", x0[1]);
          //convert from char to wchar_t
          wchar_t wtext1[20];
          wchar_t wtext2[20];
          mbstowcs_s(0, wtext1, bufferx0, strlen(bufferx0) + 1);
          mbstowcs_s(0, wtext2, bufferx1, strlen(bufferx1) + 1);
     
          //convert from wchar_t to LPWSTR
          LPWSTR ptr1 = wtext1;
          LPWSTR ptr2 = wtext2;
          AppendText(hwndText, TEXT("\n\nRaspuns final x: "));
          AppendText(hwndText,ptr1);
          AppendText(hwndText, TEXT(", "));
          AppendText(hwndText, ptr2);
     return 0;

}

//int adunare(HDC hdc, char* buffer1, char* buffer2){
//
//     int sum, edit1Buff, edit2Buff;
//     CHAR bufferSum[100];
//
//     //convert from char to int
//     edit1Buff = atoi(buffer1);
//     edit2Buff = atoi(buffer2);
//     sum = edit1Buff + edit2Buff;
//
//     //convert from int to char
//     sprintf_s(bufferSum, "%d", sum);
//
//     //convert from char to wchar_t
//     wchar_t wtext[20];
//     mbstowcs_s(0, wtext, bufferSum, strlen(bufferSum) + 1);
//
//     //convert from wchar_t to LPWSTR
//     LPWSTR ptr = wtext;
//     TextOut(hdc, 0, 0, ptr, lstrlen(ptr));
//
//     return 0;
//}


static TCHAR szAppName[] = TEXT("Lab1CO");

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
     PSTR szCmdLine, int iCmdShow)
{
     
     HWND         hwnd;
     MSG          msg;
     WNDCLASS     wndclass;
     wndclass.style = CS_HREDRAW | CS_VREDRAW;
     wndclass.lpfnWndProc = WndProc;
     wndclass.cbClsExtra = 0;
     wndclass.cbWndExtra = 0;
     wndclass.hInstance = hInstance;
     wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
     wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
     wndclass.hbrBackground = (HBRUSH)(COLOR_BTNFACE+1);
     wndclass.lpszMenuName = NULL;
     wndclass.lpszClassName = szAppName;
     if (!RegisterClass(&wndclass))
     {
          MessageBox(NULL, TEXT("This program requires Windows NT!"),
               szAppName, MB_ICONERROR);
          return 0;
     }
     hwnd = CreateWindow(szAppName, TEXT("Laborator nr.1 CO"),
          WS_OVERLAPPEDWINDOW,
          CW_USEDEFAULT, CW_USEDEFAULT,
          500, 400,
          NULL, NULL, hInstance, NULL);
     ShowWindow(hwnd, iCmdShow);
     UpdateWindow(hwnd);
     while (GetMessage(&msg, NULL, 0, 0))
     {
          TranslateMessage(&msg);
          DispatchMessage(&msg);
     }
     return msg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
     static HWND  hwndButton1, hwndEdit1, hwndEdit2, hwndEdit3, hwndEdit4, hwndText;
     static RECT  rect, rectScroll, clipRectScroll;
     static int   cxChar, cyChar;
     HDC          hdc;
     PAINTSTRUCT  ps;
     int          i;

     switch (message)
     {
     case WM_CREATE:
          cxChar = LOWORD(GetDialogBaseUnits());
          cyChar = HIWORD(GetDialogBaseUnits());
          GetClientRect(hwnd, &rect);
               hwndButton1 = CreateWindow(TEXT("BUTTON"),
                    button.szText,
                    WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON,
                    rect.right-200, 100,
                    100, 30,
                    hwnd, NULL,
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);
               

               hwndEdit1 = CreateWindow(TEXT("edit"), NULL,
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                    0, 0, 0, 0, hwnd, (HMENU) 1,
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);

               hwndEdit2 = CreateWindow(TEXT("edit"), NULL,
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                    0, 0, 0, 0, hwnd, (HMENU) 1,
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);

               hwndEdit3 = CreateWindow(TEXT("edit"), NULL,
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                    0, 0, 0, 0, hwnd, (HMENU)1,
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);

               hwndEdit4 = CreateWindow(TEXT("edit"), NULL,
                    WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT,
                    0, 0, 0, 0, hwnd, (HMENU)1,
                    ((LPCREATESTRUCT)lParam)->hInstance, NULL);

               hwndText = CreateWindow(TEXT("EDIT"), NULL,
                    WS_VISIBLE | WS_CHILD | ES_LEFT | WS_BORDER | ES_AUTOVSCROLL | WS_VSCROLL | ES_MULTILINE,
                    10, 10, 250, 300, hwnd, NULL, ((LPCREATESTRUCT)lParam)->hInstance, NULL);

          return 0;

     case WM_SETFOCUS:
          SetFocus(hwndEdit1);
          

          return 0;

     case WM_SIZE:
          GetClientRect(hwnd, &rect);

          MoveWindow(hwndEdit1, rect.right - 130, 30, 30, 20, TRUE);
          MoveWindow(hwndEdit2, rect.right - 130, 50, 30, 20, TRUE);
          MoveWindow(hwndEdit3, rect.right - 40, 30, 30, 20, TRUE);
          MoveWindow(hwndEdit4, rect.right - 40, 50, 30, 20, TRUE);

          return 0;
     case WM_PAINT:
          InvalidateRect(hwnd, &rect, TRUE);
          hdc = BeginPaint(hwnd, &ps);
          SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
          SetBkMode(hdc, TRANSPARENT);
          SetBkColor(hdc, GetSysColor(COLOR_BTNFACE));
          SetTextColor(hdc, GetSysColor(COLOR_WINDOWTEXT));

          DrawText(hdc, TEXT("ax1^2+2x1x2+bx2^2-2x1-3x2"), -1, &rect,TA_RIGHT);
          TextOut(hdc, rect.right - 160, 30, TEXT("a="), 2);
          TextOut(hdc, rect.right - 160, 50, TEXT("b="), 2);
          TextOut(hdc, rect.right - 90, 30, TEXT("x0[1]="), 6);
          TextOut(hdc, rect.right - 90, 50, TEXT("x0[2]="), 6);
          EndPaint(hwnd, &ps);
          
               return 0;
     case WM_DRAWITEM:
     case WM_COMMAND:
          
          hdc = GetDC(hwnd);
          SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
          
          
          if (LOWORD(wParam) == 1)
          if (HIWORD(wParam) == EN_ERRSPACE ||
               HIWORD(wParam) == EN_MAXTEXT)
               MessageBox(hwnd, TEXT("Edit control out of space."),
               szAppName, MB_OK | MB_ICONSTOP);
          
          if (LOWORD(wParam == ID_CALCULATE)){
               int iLength1, iLength2, iLength3, iLength4;
               iLength1 = SendMessage(hwndEdit1, WM_GETTEXTLENGTH, 0, 0);
               iLength2 = SendMessage(hwndEdit2, WM_GETTEXTLENGTH, 0, 0);
               iLength3 = SendMessage(hwndEdit3, WM_GETTEXTLENGTH, 0, 0);
               iLength4 = SendMessage(hwndEdit4, WM_GETTEXTLENGTH, 0, 0);
               char* buffer1;
               char* buffer2;
               char* buffer3;
               char* buffer4;
               buffer1 = new char[iLength1];
               buffer2 = new char[iLength2];
               buffer3 = new char[iLength3];
               buffer4 = new char[iLength4];
               SendMessage(hwndEdit1, WM_GETTEXT, (WPARAM)iLength1 + 1, (LPARAM)buffer1);
               SendMessage(hwndEdit2, WM_GETTEXT, (WPARAM)iLength2 + 1, (LPARAM)buffer2);
               SendMessage(hwndEdit3, WM_GETTEXT, (WPARAM)iLength3 + 1, (LPARAM)buffer3);
               SendMessage(hwndEdit4, WM_GETTEXT, (WPARAM)iLength4 + 1, (LPARAM)buffer4);
               SendMessage(hwndText, EM_SETSEL, 0,-1);
               SendMessage(hwndText, WM_CLEAR, 0, 0);
               calculate(hdc, buffer1, buffer2, buffer3, buffer4, hwnd, hwndText);

               
          }
          
          
          ReleaseDC(hwnd, hdc);
          ValidateRect(hwnd, &rect);
          break;
     case WM_DESTROY:
          PostQuitMessage(0);
          return 0;
     }
     return DefWindowProc(hwnd, message, wParam, lParam);
}