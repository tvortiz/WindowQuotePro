

#include "framework.h"
#include "Windows_Quote_List.h"
#include "Table_Quote.h"
#include <list>
//#include "commctrl.h"
#include "CommCtrl.h"


void createwindow_quote_list(WNDCLASSEX& wincl_2, HINSTANCE& hThisInstance, int nCmdShow, WCHAR szWindowClass[100])
{
    wincl_2.hInstance = hThisInstance;
    wincl_2.lpszClassName = szWindowClass;
    wincl_2.lpfnWndProc = (WNDPROC)windowprocessforwindow_quote_list;      /* This function is called by windows */
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
        0,                   /* Extended possibilites for variation */
        szWindowClass,         /* Classname */
        _T("List Quotes"),       /* Title Text */
        WS_OVERLAPPEDWINDOW, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        640,                 /* The programs width */
        640,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );
    /* Make the window visible on the screen */
    ShowWindow(handleforwindow2, nCmdShow);
}



void AddControls2(HWND hwnd)
{
    HWND hWndListView = CreateWindowW(WC_LISTVIEW, L"", WS_BORDER | WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS, 10, 10, 600, 580, hwnd, (HMENU)2, NULL, NULL);

    WCHAR col[6][50] = { L"ID", L"Quote Name" , L"Customer Name" , L"Material" , L"Size" , L"Price" };

    for (int i = 0; i < 6; i++)
    {
        LVCOLUMN lvc;
        lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
        lvc.iSubItem = 0;
        lvc.pszText = col[i];
        lvc.cx = 100;
        lvc.fmt = LVCFMT_LEFT;

        ListView_InsertColumn(hWndListView, i, &lvc);
    }


    LVITEM lvI;

    lvI.pszText = LPSTR_TEXTCALLBACK;
    lvI.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_STATE;
    lvI.stateMask = 0;
    lvI.iSubItem = 0;
    lvI.state = 0;

    std::list<Quote> reply = select_all();
    int i = 0;

    for (const auto quote : reply)
    {
        WCHAR wsz[64];
        swprintf_s(wsz, L"%d", quote.id);

        lvI.iItem = i;
        lvI.pszText = wsz;

        ListView_InsertItem(hWndListView, &lvI);
        

        swprintf_s(col[1], L"%S", quote.quote_name);
        swprintf_s(col[2], L"%S", quote.customer);
        swprintf_s(col[3], L"%S", quote.material);
        swprintf_s(col[4], L"%S", quote.size);
        swprintf_s(col[5], L"US$ %.2f", quote.price);


        for (int j = 1; j < 6; j++)
        {
            LV_ITEM lvi;
            lvi.iSubItem = j;
            lvi.pszText = col[j];
            SNDMSG(hWndListView, LVM_SETITEMTEXT, (WPARAM)i, (LPARAM)(LV_ITEM*)&lvi);
        }

        i++;
    }


    

    //ListView_SetItemText(hWndListView, 1, 1, TEXT("ASD");


    //CreateWindowW(L"Button", L" A NEW WINDOW", WS_VISIBLE | WS_CHILD, 215, 285, 300, 30, hwnd, (HMENU)2, NULL, NULL);
}

LRESULT CALLBACK windowprocessforwindow_quote_list(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_COMMAND:
    {
        switch (wParam)
        {

        }
    }
    return 0;
    case WM_CREATE:
    {
        AddControls2(hwnd);
        break;
    }
    case WM_DESTROY:
        //PostQuitMessage(0);
        DestroyWindow(hwnd);
        //ShowWindow(hwnd, SW_HIDE);
        break;
    default:

        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}