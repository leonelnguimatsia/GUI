
/*****************************************************************
 * Autor: Leonel Nguimatsia                                      *
 * @version: Code-block Version 20.03                            *
 * Hochschule: TH-Kloen                                          *
 * Ort: Deutz Technische Hochschule                              *
 * Webmail: leonel.nguimatsia_tsobguim@smail.th-koeln.de         *
 * Beschreibung: EntitaetKlasse QuadratDarstellen                *
 *                                                               *
 *****************************************************************/

#include <windows.h> //Sammeln von Header-datei fuer die Windows API
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include"ressource.h"

/* Definition fuer die Globale Variablen.Wird in Unterprogramm verwendet und
Kann Irrgendwo aufrufen. Es dient dazu, die Intanzen zu Identifizieren*/

HINSTANCE Instanz;                       //Deklaration unsere Instanze Variable f¸r Unsere Fenster.
long int seitenlaenge = 40;              // Deklaration Variablen fuer die Initialisuerug der SeitenLaenge
long int winkel = 45;                    //Deklaration der Variable fuer die Drehwinkel
bool seitenlaengeGeaendert = TRUE;       // seitenlaengeGeaendert Wird auf True gesetzt


void transformAndDraw(int,HWND);       //Prototyp der TransformAndDraw
INT_PTR FAR PASCAL UmrechnungsFunktion(HWND, UINT, WPARAM, LPARAM);  //Prototyp der FAR PASCAL Funktion fuer die Umrechnung
void TransformAndDraw(int iTransform, HWND hWnd);   //Prototyp der TransforAndDraw fuer das Drehen des Quadrat

/*  Deklaration der Fensterfunktion mit dem Rueckgabetyp CALLBACK
und liefert die Reihenfolge der Parameter gem‰ﬂ FIFO */
LRESULT CALLBACK fensterFunktion (HWND, UINT, WPARAM, LPARAM);

//--------- windows Hauptprogramm---------------------
int WINAPI WinMain (HINSTANCE dieseInstanz,          //Diese Parameter als Typ HINSTANCE sind  schon im Betriebssystem festgelegt
                    HINSTANCE vorherigeInstanz,      //wo die Nachrichten geschickt werden muessen.
                    LPSTR Kommando,               // Dieser Paramter als Typ Long-Pointer-string fuer die Argument
                    int fenstertyp)                 //Gibt die Informationen,wie das Programm direkt beim aufruf gestartet werden muss.
{

    HWND Hauptfenster;               /* Das ist der Handle fuer unser Fenster */
    MSG meldung;            /* Lokale Variable Meldung.Hier werden Nachrichten an die Anwendung gespeichert  */
    Instanz = dieseInstanz;


    if(!vorherigeInstanz)
    {

        /* Die Fensterstruktur  */
        WNDCLASSEX wincl;        /* Datenstruktur f¸r die Fensterklasse. Hier wird ein local Variable wincl angelegt */
        wincl.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;  /* Das Style hier wird festgelegt und man kann hier die Fenstergroesse veraendern */
        wincl.lpfnWndProc = fensterFunktion;  //Die Adresse der CALLBACK-Funktion innerhalb der Struktur festlegen. Diese Funktion wird von Windows aufgerufen.
        wincl.hInstance = dieseInstanz;      //Handle fuer die erste Instanz
        wincl.lpszClassName = "Eingabe";    //Hier Nennen wir einen freiwahlbaren Name fuer unser Fenster
        wincl.cbSize = sizeof (WNDCLASSEX);  //Hier wird Die Groessse der Fenster-Inhalt erhalten

        /* Verwendung des Standardsymbols und des Mauszeigers  */
        wincl.hIcon = LoadIcon(NULL,IDI_ASTERISK);      //Festlegung der Icon so ,dass unser Applikation auf dem Bildschirm gibt.
        wincl.hIconSm = LoadIcon(NULL,IDI_APPLICATION) ;  //Dient dazu, unser Applikation auf dem Bildschirm zu minimieren oder maximieren
        wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
        wincl.lpszMenuName = "SimpelMenu";                  //Hier haben wir fuer unser minimale Programm mit Menu(SimpelMenue)
        wincl.cbClsExtra = 0;                      /* Reservierte Variable und spreichert den ersten Wert unser Intanz beim aufruf.Keine zus‰tzlichen Bytes nach der Fensterklasse  */
        wincl.cbWndExtra = 0;                      /* Struktur oder die Fensterinstanz.Reservierte Variable und spreichert den ersten Wert unser Intanz beim aufruf  */
        wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND; //Verwendung der Windows-Standardfarbe als Hintergrund des Fensters

        if(!RegisterClassEx (&wincl)) return 255; //Registrieren der FesnterKlasse des Hauptfensters und wenn es fehlschl‰gt, beenden Sie das Programm
    }


    /* Die Klasse ist registriert, erstellen wir das Fenster*/
    Hauptfenster = CreateWindowEx (
                       0,                   /* Erweiterte Variationsmˆglichkeiten. Rueckgabewert der Variable createwindows()  */
                       "Eingabe",           /* Name der FernsterKlasse */
                       "QuadratDarstellung", /* setzt der Titelleiste */
                       WS_OVERLAPPEDWINDOW, /* Standardfenster. */
                       CW_USEDEFAULT,       /* Die Programmbreite(gesetzt als Default) */
                       CW_USEDEFAULT,       /* und Hˆhe(gesetzt als Default) in Pixel  */
                       CW_USEDEFAULT,       /* Windows bestimmt die Position  */
                       CW_USEDEFAULT,       /* wo das Fenster auf dem Bildschirm endet */
                       NULL,
                       NULL,
                       dieseInstanz,       /* Programminstanz-Handle.Aktuelle Instanz der Parameterliste WinMain*/
                       NULL                 /* Keine Fenstererstellungsdaten  */
                   );

    if(!Hauptfenster) return 255;  // Ueberpruefung der Gueltigkeit des Handle des Hauptfenster

    /* Machen Sie das Fenster auf dem Bildschirm sichtbar  */
    ShowWindow (Hauptfenster, fenstertyp);
    UpdateWindow(Hauptfenster);

    /* F¸hren Sie die Nachrichtenschleife aus. Es wird ausgef¸hrt, bis GetMessage() 0 zur¸ckgibt */
    while (GetMessage (&meldung, 0, 0, 0))
    {
        /* ‹bersetzen Sie virtuelle Schl¸ssel-Nachrichten in Zeichen-Nachrichten  */
        TranslateMessage(&meldung);
        /* Nachricht an WindowProcedure senden  */
        DispatchMessage(&meldung);
    }

    /* Der R¸ckgabewert des Programms ist 0 - Der Wert, den PostQuitMessage() gegeben hat*/
    return meldung.wParam;
}


/*  Diese Funktion wird von der Windows-Funktion DispatchMessage() aufgerufen
    So zu sagen, Hier ist die Funktionalitaet des Hauptfenster */

LRESULT CALLBACK fensterFunktion (HWND fenster, UINT nachricht, WPARAM parameter1, LPARAM parameter2)
{

    HDC hdc;
    static long int x1, y1, x2, y2 ;   //Deklaration Variablen fuer die Seiten der Quadrat
    RECT rect = {x1,y1,x2,y2};         //Deklaration  und  Initialisierung der Variable rect f¸r die Seiten der Quadrat
    double centerX, centerY;          //Deklaration der Variable (centerX, centerY) , um die Quadart auf dem Hauptfenster zu positionieren
    double geaenderteWinkel;          // Deklaration der Variable geaenderteWinkel , um die Winkel zu aendern

    XFORM xfm = { 0.0f };            //Deklaration der Variable (xfm) spezifiziert eine Weltraum-zu-Seitenraum-Transformation

    PAINTSTRUCT ps;


    //Prueffe ,ob die Seite der Quadrat geaendert wird
    if(seitenlaengeGeaendert ==TRUE)
    {

        x1 = 100;
        y1 = 100;
        x2 = 100 + seitenlaenge;
        y2 = 100 + seitenlaenge;
        InvalidateRect(fenster, NULL, TRUE);
        seitenlaengeGeaendert = FALSE;
    }


    switch (nachricht)                  /* handle der Nachrichten */
    {

    case WM_PAINT :

        hdc = BeginPaint(fenster,&ps); //Beginn des Zeichnens der Quadrat im Hauptfenster

        geaenderteWinkel = winkel / 180. * 3.1415926; // Initialisierung der geaenderteWinkel, damit der Winkel geaendert wird

        //Berechnung der Positionierung der Quadrat auf dem Hauptfenster
        centerX = (rect.right + rect.left)/2;
        centerY = (rect.bottom + rect.top)/2;

        //Berechnung der Seitenraum-Transformation fuer ein gegebenen Winkel
        xfm.eM11 = (float)cos(geaenderteWinkel);
        xfm.eM12 = (float)sin(geaenderteWinkel);
        xfm.eM21 = (float)-sin(geaenderteWinkel);
        xfm.eM22 = (float)cos(geaenderteWinkel);

        xfm.eDx = (float)(centerX - cos(geaenderteWinkel)*centerX+ sin(geaenderteWinkel)*centerY);
        xfm.eDy = (float)(centerY - cos(geaenderteWinkel)*centerY - sin(geaenderteWinkel)*centerX);
        SetGraphicsMode(hdc,GM_ADVANCED);
        SetWorldTransform(hdc,&xfm); //setzen der berechnete Transformation


        Rectangle(hdc,rect.left,rect.top,rect.right,rect.bottom); //Positionierung der Quadrat auf dem Hauptfenster



        EndPaint(fenster,&ps); // Ende des Zeichnens der Quadrat im Hauptfenster


        return 0;


    case WM_COMMAND :
        switch(parameter1)
        {
        case ID_QUADRAT_EIGENSCHAFTEN :


            DialogBox(Instanz,"Umrechnung",fenster,UmrechnungsFunktion); //Aufruf der DialogBox auf dem MenuItem "QUADRAT_EIGENSCHAFTEN"
            return 0;

        case ID_SCHLIESSEN :

            //Erzeugung des MessageBox, wenn man das Programm schlieﬂen moechte
            int msgboxID=  MessageBox(fenster,"Mˆchten Sie wirklich schlieﬂen?","Bitte Warten!!", MB_ICONEXCLAMATION | MB_YESNO );

            if (msgboxID == IDYES)
            {
                PostQuitMessage (0);       //Senden Sie ein WM_QUIT an die Nachrichtenwarteschlange und Schlieﬂen des Programms
                return 0;
            }

            return msgboxID;

        }
        break;

    case WM_DESTROY:

        int msgboxID=  MessageBox(fenster,"Mˆchten Sie wirklich schlieﬂen?","Bitte Warten!!", MB_ICONEXCLAMATION | MB_YESNO );

        if (msgboxID == IDYES)
        {
            PostQuitMessage (0);       //Senden Sie ein WM_QUIT an die Nachrichtenwarteschlange und Schlieﬂen des Programms
            return 0;
        }

        return msgboxID;
        return 0;
    }
    return DefWindowProc (fenster, nachricht, parameter1, parameter2);  /* fuer alle nicht bearbeiteten Nachrichten */
}



// Implementierung  der FAR PASCAL Funtion fuer die Funktionalitaeten unser DialogBox

INT_PTR FAR PASCAL UmrechnungsFunktion(HWND bezugDialog, UINT nachricht, WPARAM parameter1, LPARAM parameter2)
{


    char puffer[40];          //Deklaration der Variable Puffer zur zwischen Speicher der eingegebenen Werten

    static int minPos = 0;   //Deklaration der variable minPos, um die minimale Winkel zu initialisieren.
    static int maxPos = 90;  //Deklaration der variable maxos, um die maximale Winkel zu initialisieren.
    static int pruefWinkel;  //Deklaration der Variable Pruefwinkel.Prueft,ob die winkel-Inhalt innerhalb der von minPos und maxPos steht
    SCROLLINFO si;          //Deklaration der SCROLLINFO-Struktur,die SetScrollInfo-Funktion festgelegt werden sollen

    switch(nachricht)
    {
    case WM_INITDIALOG:

        //set scrollbar size
        SetScrollRange(GetDlgItem(bezugDialog,ID_SCROLLBAR), SB_CTL, minPos, maxPos, FALSE);
        SetScrollPos(GetDlgItem(bezugDialog,ID_SCROLLBAR),SB_CTL,winkel,TRUE);

        // Eingabe der seitenlaenge und speicherung  auf dem Puffer
        wsprintf(puffer,"%i",seitenlaenge);
        SetDlgItemText(bezugDialog,ID_TXT_XSEITELAENGE,puffer);

        // Eingabe der Winkel und speicherung  auf dem Puffer
        wsprintf(puffer,"%i",winkel);
        SetDlgItemText(bezugDialog,ID_TEXT_WINKEL,puffer);


        return 0;

    case WM_HSCROLL :

        // Ruft Attribute der Bildlaufleiste ab
        si.cbSize = sizeof (si);
        si.fMask  = SIF_ALL;
        GetScrollInfo (GetDlgItem(bezugDialog,ID_SCROLLBAR), SB_CTL, &si);

        switch(LOWORD(parameter1))
        {
        case SB_LINEUP:
            winkel--;
            break;
        case SB_LINEDOWN :
            winkel++;
            break;

        // Der Benutzer hat das Bildlauffeld gezogen.
        case SB_THUMBTRACK:
            winkel = si.nTrackPos;
            break;
        }
        if(winkel > maxPos) winkel = maxPos;
        if(winkel < minPos) winkel = minPos;

        si.fMask = SIF_POS;
        si.nPos = winkel;

        SetScrollPos(GetDlgItem(bezugDialog,ID_SCROLLBAR),SB_CTL,winkel,TRUE);

        wsprintf(puffer,"%i",winkel);
        SetDlgItemText(bezugDialog,ID_TEXT_WINKEL,puffer);

        return TRUE;

    case WM_COMMAND :
        switch(parameter1)
        {


            //Steuerung der IDOk
        case IDOK:
            GetDlgItemText(bezugDialog,ID_TXT_XSEITELAENGE,puffer,10);
            seitenlaenge = strtol(puffer,NULL,0);

            //Ueberprueffung , ob die Seitelaenge auﬂerhalb von 10 und 500 steht.
            if(seitenlaenge < 10 || seitenlaenge > 500 )
            {
                //Erzeugung der Message Box beim Fehler der eingegebenen SeiteLaenge
                MessageBox(bezugDialog,"Die SeiteLaenge soll zwichen 10 und 500 meter und Positiv sein","Achtung!!", MB_ICONEXCLAMATION  | MB_OK);

                return 0;
            }


            GetDlgItemText(bezugDialog,ID_TEXT_WINKEL,puffer,10);
            pruefWinkel = strtol(puffer,NULL,0);

            //Ueberprueffung , ob die Winkel auﬂerhalb von 0 und 90 steht.
            if(pruefWinkel < 0 || pruefWinkel > 90)
            {
                //Erzeugung der Message Box beim Fehler der eingegebenen Winkel
                MessageBox(bezugDialog,"Das Winkel soll zwichen 0 und 90 Grad sein","Achtung!!", MB_ICONEXCLAMATION  | MB_OK);

                return 0;
            }

            winkel = pruefWinkel;
            seitenlaengeGeaendert = TRUE;

            EndDialog(bezugDialog,0);
            return 0;

             //Steuerung der IDCANCEL
        case IDCANCEL:

            EndDialog(bezugDialog,0);


            return TRUE;
        }


    }

    return FALSE;

}
