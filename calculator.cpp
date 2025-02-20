#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

HWND text, buttonplus, buttonminus, buttonmulti, buttondivide, textbox1, textbox2;
char box1[100], box2[100];
int getstat1 = 0;
int getstat2 = 0;
double result = 0.0;
char answer[100];

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = CreateSolidBrush(RGB(57, 255, 20));

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("My Calculator"),       /* Title Text */
           WS_MINIMIZEBOX | WS_SYSMENU, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           250,                 /* The programs width */
           200,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            text = CreateWindow("STATIC",
                                "Please input two numbers",
                                WS_VISIBLE | WS_CHILD | WS_BORDER,
                                20, 20, 200, 25,
                                hwnd, nullptr, nullptr, nullptr);
            textbox1 = CreateWindow("EDIT",
                                    "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    50, 50, 150, 20,
                                    hwnd, nullptr, nullptr, nullptr);
            textbox2 = CreateWindow("EDIT",
                                    "",
                                    WS_VISIBLE | WS_CHILD | WS_BORDER,
                                    50, 80, 150, 20,
                                    hwnd, nullptr, nullptr, nullptr);
            buttonplus = CreateWindow("BUTTON",
                                      "+",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      70, 110, 20, 20,
                                      hwnd, (HMENU) 1, nullptr, nullptr);
            buttonminus = CreateWindow("BUTTON",
                                      "-",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      100, 110, 20, 20,
                                      hwnd, (HMENU) 2, nullptr, nullptr);
            buttonmulti = CreateWindow("BUTTON",
                                      "*",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      130, 110, 20, 20,
                                      hwnd, (HMENU) 3, nullptr, nullptr);
            buttondivide = CreateWindow("BUTTON",
                                      "/",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER,
                                      160, 110, 20, 20,
                                      hwnd, (HMENU) 4, nullptr, nullptr);

        break;


        case WM_COMMAND:
            {

                getstat1 = GetWindowText(textbox1, box1, 100);
                getstat2 = GetWindowText(textbox2, box2, 100);

                double num1 = strtod(box1, nullptr);
                double num2 = strtod(box2, nullptr);
                double result = 0.0;
                char resultText[100];

                if (LOWORD(wParam) == 1)
                {
                    result = num1 + num2;
                }
                else if (LOWORD(wParam) == 2)
                {
                    result = num1 - num2;
                }
                else if (LOWORD(wParam) == 3)
                {
                    result = num1 * num2;
                }
                else if (LOWORD(wParam) == 4)
                {
                    if (num2 != 0)
                        result = num1 / num2;
                    else
                    {
                        MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_OK | MB_ICONERROR);
                        return 0;
                    }
                }
                else
                {
                    return 0;
                }
                if(strlen(box1) > 0 && strlen(box2) > 0){
                    sprintf(resultText, "%f", result);
                    MessageBox(hwnd, resultText, "Result", MB_OK);
                }

        break;

            }


        case WM_DESTROY:
            {
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
            }
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
