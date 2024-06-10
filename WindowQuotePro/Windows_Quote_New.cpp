
#include "framework.h"
#include "Windows_Quote_New.h"
#include "CommCtrl.h"
#include "Table_Quote.h"
#include <list>

void createwindow_quote_new(WNDCLASSEX& wincl_2, HINSTANCE& hThisInstance, int nCmdShow, WCHAR szWindowClass[100])
{
    wincl_2.hInstance = hThisInstance;
    wincl_2.lpszClassName = szWindowClass;
    wincl_2.lpfnWndProc = (WNDPROC)windowprocessforwindow_quote_new;      /* This function is called by windows */
    wincl_2.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl_2.cbSize = sizeof(WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl_2.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wincl_2.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl_2.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl_2.lpszMenuName = NULL;                 /* No menu */
    wincl_2.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl_2.cbWndExtra = 0;                      /* structure or the window instance */

    /* Use Windows's default colour as the background of the window */
    wincl_2.hbrBackground = (HBRUSH)COLOR_WINDOW;

    RegisterClassEx(&wincl_2);
    //if (!RegisterClassEx(&wincl_2))
        //return;

    HWND handleforwindow2 = CreateWindowEx(
        0,                          /* Extended possibilites for variation */
        szWindowClass,              /* Classname */
        _T("Create new Quotes"),    /* Title Text */
        WS_OVERLAPPEDWINDOW,        /* default window */
        CW_USEDEFAULT,              /* Windows decides the position */
        CW_USEDEFAULT,              /* where the window ends up on the screen */
        450,                        /* The programs width */
        500,                        /* and height in pixels */
        HWND_DESKTOP,               /* The window is a child-window to desktop */
        NULL,                       /* No menu */
        hThisInstance,              /* Program Instance handler */
        NULL                        /* No Window Creation data */
    );
    
    ShowWindow(handleforwindow2, nCmdShow);
}

HWND txt_name;
HWND txt_customer;
HWND cmbx_material;
HWND cmbx_size;
HWND txt_price;
HWND btn_insert;

void AddControls(HWND hwnd)
{
    #define CreateWindowSimple(lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight) \
    CreateWindowExW(0L, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hwnd, (HMENU)2000, NULL, NULL)

    CreateWindowSimple(L"STATIC", L"Create new Quote", WS_VISIBLE | WS_CHILD, 150, 50, 500, 100);
    CreateWindowSimple(L"STATIC", L"Name of the quote:", WS_VISIBLE | WS_CHILD, 20, 100, 200, 100);
    CreateWindowSimple(L"STATIC", L"Name of the customer:", WS_VISIBLE | WS_CHILD, 20, 150, 200, 100);
    CreateWindowSimple(L"STATIC", L"Door material:", WS_VISIBLE | WS_CHILD, 20, 200, 200, 100);
    CreateWindowSimple(L"STATIC", L"Door size:", WS_VISIBLE | WS_CHILD, 20, 250, 200, 100);
    CreateWindowSimple(L"STATIC", L"Pirce:", WS_VISIBLE | WS_CHILD, 20, 300, 200, 100);

    txt_name       = CreateWindowSimple(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 147, 99, 160, 20);
    txt_customer   = CreateWindowSimple(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER, 170, 149, 160, 20);

    cmbx_material = CreateWindowSimple(L"ComboBox", L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 115, 198, 100, 300);
    
    SendMessage(cmbx_material, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)((const TCHAR*)L"Wood"));
    SendMessage(cmbx_material, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)((const TCHAR*)L"Metal"));

    cmbx_size = CreateWindowSimple(L"ComboBox", L"", CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE, 95, 248, 100, 300);

    SendMessage(cmbx_size, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)((const TCHAR*)L"Small"));
    SendMessage(cmbx_size, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)((const TCHAR*)L"Medium"));
    SendMessage(cmbx_size, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)((const TCHAR*)L"Large"));


    txt_price = CreateWindowSimple(L"Edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | WS_DISABLED, 65, 299, 280, 20);

    //TCHAR buff[1024];
    //GetWindowText(hWndCtrl, buff, 1024);

    //SetWindowText(txt_price, L"123");
    
    btn_insert = CreateWindowW(L"Button", L"Insert", WS_VISIBLE | WS_CHILD, 150, 350, 100, 30, hwnd, (HMENU)2, NULL, NULL);
}

void calculate_price(HWND hwnd, int index_cmbx_material, int index_cmbx_size)
{
    if (index_cmbx_material == -1 || index_cmbx_size == -1)
        return;

    TCHAR size[20];
    TCHAR material[20];

    (TCHAR)SendMessage((HWND)cmbx_material, (UINT)CB_GETLBTEXT, (WPARAM)index_cmbx_material, (LPARAM)material);
    (TCHAR)SendMessage((HWND)cmbx_size, (UINT)CB_GETLBTEXT, (WPARAM)index_cmbx_size, (LPARAM)size);
    
    if (_tcscmp(size, L"Small")  == 0 && _tcscmp(material, L"Wood") == 0)  SetWindowText(txt_price, L"20.10");
    if (_tcscmp(size, L"Medium") == 0 && _tcscmp(material, L"Wood") == 0)  SetWindowText(txt_price, L"30.20");
    if (_tcscmp(size, L"Large")  == 0 && _tcscmp(material, L"Wood") == 0)  SetWindowText(txt_price, L"32.30");

    if (_tcscmp(size, L"Small")  == 0 && _tcscmp(material, L"Metal") == 0) SetWindowText(txt_price, L"80.0");
    if (_tcscmp(size, L"Medium") == 0 && _tcscmp(material, L"Metal") == 0) SetWindowText(txt_price, L"90.0");
    if (_tcscmp(size, L"Large")  == 0 && _tcscmp(material, L"Metal") == 0) SetWindowText(txt_price, L"99.90");

    //SetWindowText(txt_price, L"0.0");
}

void insert_quote(HWND hwnd)
{
    char quote_name[100];
    char customer_name[100];
    char size[20];
    char material[20];
    char price_char[20];

    TCHAR quote_name_tchar[100];
    TCHAR customer_name_tchar[100];
    TCHAR size_tchar[20] = _T("");
    TCHAR material_tchar[20] = _T("");
    TCHAR price_char_tchar[20];
    
    int index_cmbx_material = SendMessage((HWND)cmbx_material, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
    int index_cmbx_size = SendMessage((HWND)cmbx_size, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

    (TCHAR)SendMessage((HWND)cmbx_material, (UINT)CB_GETLBTEXT, (WPARAM)index_cmbx_material, (LPARAM)material_tchar);
    (TCHAR)SendMessage((HWND)cmbx_size, (UINT)CB_GETLBTEXT, (WPARAM)index_cmbx_size, (LPARAM)size_tchar);

    GetWindowText(txt_name, quote_name_tchar, 99);
    GetWindowText(txt_customer, customer_name_tchar, 99);
    GetWindowText(txt_price, price_char_tchar, 19);

    size_t charsConverted = 0;
    wcstombs_s(&charsConverted, quote_name, 100, quote_name_tchar, 100);
    wcstombs_s(&charsConverted, customer_name, 100, customer_name_tchar, 100);
    wcstombs_s(&charsConverted, size, 20, size_tchar, 20);
    wcstombs_s(&charsConverted, material, 20, material_tchar, 20);
    wcstombs_s(&charsConverted, price_char, 20, price_char_tchar, 20);

    float price = atof(price_char);
    
    if (strlen(quote_name) == 0 ||
        strlen(customer_name) == 0 ||
        strlen(size) == 0 ||
        strlen(material) == 0 ||
        strlen(price_char) == 0)
    {
        MessageBox(hwnd, TEXT("Insert failed! You need to fill all the fields"), TEXT("Insert failed"), MB_OK);
    }
    else
    {
        insert(quote_name, customer_name, material, size, price);

        MessageBox(hwnd, TEXT("Insert made successfully!"), TEXT("Quote inserted!"), MB_OK);
    }
    
    /*
    std::list<Quote> reply = select_all();

    for (const auto quote : reply)
    {
        WCHAR wsz[64];
        swprintf_s(wsz, L"%d %S %S %S %S %f", quote.id, quote.quote_name, quote.customer, quote.material, quote.size, quote.price);

        LPCWSTR p = wsz;

        MessageBox(hwnd, (LPCWSTR)p, TEXT("Item Selected"), MB_OK);
    } // */
}

LRESULT CALLBACK windowprocessforwindow_quote_new(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        int index_cmbx_material;
        int index_cmbx_size;

        switch (HIWORD(wParam))
        {
            case CBN_SELCHANGE:

                index_cmbx_material = SendMessage((HWND)cmbx_material, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
                index_cmbx_size = SendMessage((HWND)cmbx_size, (UINT)CB_GETCURSEL, (WPARAM)0, (LPARAM)0);

                calculate_price(hwnd, index_cmbx_material, index_cmbx_size);
                
                break;

            case BN_CLICKED:

                insert_quote(hwnd);

                break;
        }

        switch (wParam)
        {
            
        }
    }
    return 0;
    case WM_CREATE:
    {
        AddControls(hwnd);
        break;
    }
    case WM_DESTROY:
        //PostQuitMessage(0);
        DestroyWindow(hwnd);
        break;
    default:

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}