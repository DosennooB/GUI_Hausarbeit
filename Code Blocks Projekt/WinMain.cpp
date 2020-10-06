//Author: DosennooB
//

///Fehlercodes
#define FEHLER_ZU_LANG         -300
#define FEHLER_KEINE_ZAHL      -301

#include <windows.h>
#include <CommCtrl.h>
#include <bitset>
#include <sstream>
#include <algorithm>
#include "resource1.h"
using namespace std;


//Beschreibt das Verhalten der Hauptfensters
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Implementiert die Funktionen der Dialogfeldes
INT_PTR CALLBACK DlgProc(HWND hwndDlg, UINT msg, WPARAM wParam, LPARAM lParam);

//Wandelt einen Integer Wert in die Passende Binärzähl als String um
basic_string<TCHAR> DecZuBin(int Dec);

//List einen String ein. Prüft ihn ob es eine 8 Bit Binär Zahl entspricht.
//wandelt es in  eine eine Integer Zahle im Wertebereich von -128 bis 127 und gibt diesn zurück.
//alternative werden Fehlercodes zurück gegeben.
int BiZuDec(TCHAR *bin);

//Globale Instans
HINSTANCE hinst;

//Einsprungs Methode
//Abgewandelt aus Grundgerüst von
//https://docs.microsoft.com/en-us/windows/win32/learnwin32/your-first-windows-program
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    const TCHAR CLASS_NAME[]  = TEXT("Sample Window Class");

    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU2); //nutze die Resourece Datei um das Menu zu erstellen

    RegisterClass(&wc);

    //Handel für Dialog
    hinst = hInstance;



    // Erstelle Haupfenster
    HWND hwnd = CreateWindowEx(
            0,
            CLASS_NAME,
            TEXT("Decimal- Binaer Umrechner"),
            WS_OVERLAPPEDWINDOW,

            // Größe und Position
            CW_USEDEFAULT, CW_USEDEFAULT, 900, 600,

            NULL,       // Parent window
            NULL,       // Menu
            hInstance,  // Instance handle
            NULL        // Additional application data
    );

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    //Durchläuft den Message Loop
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        //Beendet den Messageloop
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

            //zeichnet fenster mit passender Farbe
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
            return 0;
            //bei gößenänderung wird farbe erhalten
        case WM_SIZE: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW + 1));
            EndPaint(hwnd, &ps);
        }
            //Rotine für das aufrufen des Dialogfeldes
        case WM_COMMAND: {
            switch(wParam){
                case ID_DIALOG_INTEGERZUDECIMAL:
                    //Der Dialog wird aufgerufen solannge wird der Message Loop Blockiert
                    DialogBoxParam(hinst,MAKEINTRESOURCE(IDD_PROPPAGE_LARGE),hwnd,DlgProc,lParam);
                    break;
            }
        }
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

INT_PTR CALLBACK DlgProc(HWND hwndDilog, UINT msg, WPARAM wParam, LPARAM lParam)
{
    HWND hwndTrackbar;
    int PufferBin = 0;
    int ScollbarZahl = 0;
    basic_string<TCHAR> bintext;
    UINT binzudec;
    TCHAR einbin[40]{0};
    switch(msg)
    {
        case WM_INITDIALOG:
            //initialisiere Trackbar
            hwndTrackbar = GetDlgItem(hwndDilog, IDC_SLIDER1);
            SendMessage(hwndTrackbar, TBM_SETRANGE,
                        (WPARAM) TRUE,
                        (LPARAM) MAKELONG(-128, 127));
            //setzt einen der Radioboxen auf checkt
            CheckRadioButton(hwndDilog,IDC_DECZUBIN, IDC_BINZUDEC, IDC_DECZUBIN);

            return FALSE;
        case WM_HSCROLL:
            //Event für die Trackbar verändert Werte im Binär Textfeld
            hwndTrackbar = GetDlgItem(hwndDilog, IDC_SLIDER1);
            ScollbarZahl = SendMessage(hwndTrackbar,TBM_GETPOS,0, 0);
            SetDlgItemText(hwndDilog, IDC_TEXTBIN, DecZuBin(ScollbarZahl).c_str());


        case WM_COMMAND: switch (wParam){
                case IDC_BUTTONUMRECHNEN:
                    binzudec = IsDlgButtonChecked(hwndDilog,IDC_BINZUDEC);
                    //wenn Radiobutten "binär zu dezimal" ausgewählt wurde
                    if(binzudec == BST_CHECKED){
                        GetDlgItemText(hwndDilog, IDC_TEXTBIN, einbin,40);
                        int einint = BiZuDec(einbin);

                        //Fehler handling
                        if(einint == FEHLER_ZU_LANG) {
                            MessageBox(hwndDilog,
                                       TEXT("Die eingegebene Zahl ist zu lang. \n Es dürfen maximal 8 Zeichen verwendet werden."),
                                       TEXT("Eingabefehler"),
                                       MB_OK | MB_ICONEXCLAMATION);
                        }else if(einint == FEHLER_KEINE_ZAHL){
                            MessageBox(hwndDilog,
                                       TEXT("Die eingegebene Zahl ist keine Binärzahl. \n Verwenden Sie nur 1 und 0."),
                                       TEXT("Eingabefehler"),
                                       MB_OK | MB_ICONEXCLAMATION);
                        }else{
                            //Wert in decimal Textfeld gesetzt
                            SetDlgItemInt(hwndDilog, IDC_TEXTDEC,einint,true);
                            //Trackbar wird Synchronisiert
                            hwndTrackbar = GetDlgItem(hwndDilog, IDC_SLIDER1);
                            SendMessage(hwndTrackbar, TBM_SETPOS,
                                        (WPARAM) TRUE,
                                        (LPARAM) einint);
                        }
                        //für den Weg "decimal zu binär"
                    }else{
                        BOOL geht = TRUE;
                        PufferBin =  GetDlgItemInt(hwndDilog, IDC_TEXTDEC, &geht,TRUE);
                        bintext = DecZuBin(PufferBin);

                        //Fehlerhändling
                        if(!geht){
                            MessageBox(hwndDilog,
                                       TEXT("Bitte geben sie nur eine Natürliche Zahl ein"),
                                       TEXT("Eingabefehler"),
                                       MB_OK | MB_ICONEXCLAMATION);
                        }
                        else if(bintext == TEXT("")){
                            MessageBox(hwndDilog,
                                       TEXT("Die eigegebene Zahle ist zu klein oder Groß. \n Verwenden Sie eine Zahl von -128 bis 127"),
                                       TEXT("Eingabefehler"),
                                       MB_OK | MB_ICONEXCLAMATION);
                        }else{
                            //Wert in binär Textfeld gesetzt
                            SetDlgItemText(hwndDilog,IDC_TEXTBIN,bintext.c_str());
                            //Trackbar wird Synchronisiert
                            hwndTrackbar = GetDlgItem(hwndDilog, IDC_SLIDER1);
                            SendMessage(hwndTrackbar, TBM_SETPOS,
                                        (WPARAM) TRUE,
                                        (LPARAM) PufferBin);
                        }

                    }
                    return TRUE;
                    //Schließt den dialog
                case IDC_BUTTONSCHLIESEN:
                    EndDialog(hwndDilog, 0);
                    return TRUE;

                    //Schließt den Dialog
                case IDCANCEL:
                    EndDialog(hwndDilog, 0);
                    return TRUE;
            }
        default:
            return FALSE;
    }
}

//Beispiel aus der Standarbibliothek adaptiert
//https://en.cppreference.com/w/cpp/utility/bitset/operator_ltltgtgt2
int BiZuDec(TCHAR *bin){

    //Prüft ob der String im gewünschten Bereich ist
    if(bin[8]){
        return FEHLER_ZU_LANG;
    } else {
        basic_string<TCHAR> strings{bin};

        //Testet ob der String nur 1 und 0 enthält
        bool ok = all_of(strings.begin(),strings.end(), [](const auto & c)
        {
            return c== TEXT('0')||c == TEXT('1');
        });

        if(ok){
            basic_istringstream<TCHAR> ss{bin};
            bitset<8> bst;
            ss >> bst;
            int i = reinterpret_cast<int8_t &>(bst);
            return i;
        }else{
            return FEHLER_KEINE_ZAHL;
        }

    }
}
basic_string<TCHAR> DecZuBin(int Dec){
    if(Dec>127  |  Dec < -128 ){
        return TEXT("");
    }
    else{
        basic_stringstream<TCHAR> ret;
        ret << reinterpret_cast<bitset<8> &>(Dec);
        return ret.str();
    }
}
