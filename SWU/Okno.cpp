#include "Okno.hpp"
namespace sw
{

Okno::Okno()
{
//        std::cout << "";
}

Okno::Okno(const Pozice& P, const Rozmery& R, LPCSTR jmeno, HINSTANCE _hinst) : otevreno(false)
{
//    std::cout << "Okno constructor called\n";
    this->otevreno = false;

    this->rozmer = R;
    this->pozice = P;
    this->nazev = (LPCSTR)jmeno;

    WNDCLASSEX _wc;
    /* The Window structure */
    _wc.hInstance = _hinst;
    _wc.lpszClassName = jmeno;
    _wc.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    _wc.style = CS_DBLCLKS;                 /* Catch double-clicks */
    _wc.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    _wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    _wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    _wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    _wc.lpszMenuName = NULL;                 /* No menu */
    _wc.cbClsExtra = 0;                      /* No extra bytes after the window class */
    _wc.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    _wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
//    if (!RegisterClassEx (&wincl))
//        return 0;

    // Register the window class
//    WNDCLASSEX _wc =
//    {
//        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
//        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
//        nazev, NULL
//    };
//
    this->wc = _wc;
    RegisterClassEx( &wc );
    // Create the application's window
    /* The class is registered, let's create the program*/
    hWnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               jmeno,               /* Classname */
               jmeno,               /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               P.x,                 /* Windows decides the position */
               P.y,                 /* where the window ends up on the screen */
               R.x,                 /* The programs width */
               R.y,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               _hinst,              /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );

//    this->hWnd = CreateWindow( nazev, (LPCSTR) jmeno,
//                              WS_OVERLAPPEDWINDOW, P.x, P.y, R.x, R.y, //screen
//                              NULL, NULL, wc.hInstance, NULL );
//    std::cout << "Window created\n";
//    this->ukaz();
}

Okno::Okno(const Pozice& P, LPCSTR jmeno, HINSTANCE _hinst) : otevreno(false)
{
    this->otevreno = false;
    int x = GetSystemMetrics(SM_CXSCREEN);
    int y = GetSystemMetrics(SM_CYSCREEN);
    Rozmery R {x, y};
    this->rozmer = R;
    this->pozice = P;
    this->nazev = (LPCSTR)jmeno;

    WNDCLASSEX _wc;
    /* The Window structure */
    _wc.hInstance = _hinst;
    _wc.lpszClassName = jmeno;
    _wc.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    _wc.style = CS_DBLCLKS;                 /* Catch double-clicks */
    _wc.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    _wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    _wc.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    _wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    _wc.lpszMenuName = NULL;                 /* No menu */
    _wc.cbClsExtra = 0;                      /* No extra bytes after the window class */
    _wc.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    _wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    this->wc = _wc;
    RegisterClassEx( &wc );
    // Create the application's window
    /* The class is registered, let's create the program*/
    hWnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               jmeno,               /* Classname */
               jmeno,               /* Title Text */
               WS_OVERLAPPEDWINDOW, /* default window */
               P.x,                 /* Windows decides the position */
               P.y,                 /* where the window ends up on the screen */
               R.x,                 /* The programs width */
               R.y,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               _hinst,              /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );
}



Okno::~Okno()
{
//        this->otevreno = false;
//        system("pause");
#ifdef DESTRUCTORVERBOSE
    std::cout << "Destructor okna." << std::endl;
#endif // DESTRUCTORVERBOSE
}

void Okno::nastavDoPopredi()
{
    SetForegroundWindow(hWnd);
}

void Okno::ukaz()
{
    std::cout << "Ukazuji okno.";
    this->otevreno = true;
    ShowWindow( hWnd, SW_SHOWNORMAL );
    ZeroMemory( &(this->messages), sizeof( MSG ) );
}

void Okno::zavri()
{
    this->otevreno = false;
    DestroyWindow(this->hWnd);
}

bool Okno::postarejSeOZpravy()
{
    if( PeekMessage( &(this->messages), NULL, 0U, 0U, PM_REMOVE ) ) { //mame this->messages?
        /* Translate virtual-key messages into character messages */
        TranslateMessage( &(this->messages) );
//        std::cout << "mes: "<<this->messages.message << std::endl;

        /* Send message to WindowProcedure */
//        DispatchMessage( &(this->messages) );
//        if(this->messages.message == WM_QUIT || this->bQuit==WM_DESTROY ) {
        switch (messages.message)
        {
        case WM_CLOSE:
            this->zavri();
            return false;
            break;
        case WM_DESTROY:
            {
                std::cout << "wmdestroy" << std::endl;
                DispatchMessage( &(this->messages) );
            }
            break;
        case WM_QUIT:
            std::cout << "unregister class and destroy.\n";
            UnregisterClass( nazev, this->wc.hInstance );
            return false;
            break;
        default:
            DispatchMessage( &(this->messages) );
            break;
        }

//        if(this->messages.message == WM_DESTROY) {
//        }
//        else if(this->messages.message == WM_QUIT)
//        {
////            this->otevreno = false;
//        }
//        else
//                        this->~Okno(); // msgProc ma asi tezko pristup k oknu1
//        this->messages.message = WM_DESTROY; //vpodstate se zavola cleanup v msgProc

//                        std::cout << "okno zavreno krizkem";
//            this->messages.message = WM_QUIT;
        /* Translate virtual-key messages into character messages */
//        TranslateMessage( &(this->messages) );
        /* Send message to WindowProcedure */
    } else { //nemame this->messages..
    }
    return true;
}

}
