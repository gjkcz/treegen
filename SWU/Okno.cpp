#include "Okno.hpp"
namespace sw
{

Okno::Okno(Pozice P, Rozmery R, LPCSTR jmeno = "Default")
{
    this->nazev = (LPCSTR)jmeno;
    // Register the window class
    WNDCLASSEX _wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        nazev, NULL
    };
    this->wc = _wc;
    RegisterClassEx( &wc );
    // Create the application's window
    this->hWnd = CreateWindow( nazev, (LPCSTR) jmeno,
                              WS_OVERLAPPEDWINDOW, P.x, P.y, R.x, R.y, //screen
                              NULL, NULL, wc.hInstance, NULL );
//    this->ukaz();
}

Okno::~Okno()
{
        this->otevreno = false;
        UnregisterClass( nazev, this->wc.hInstance );
}

void Okno::ukaz()
{
        this->otevreno = true;
        ShowWindow( hWnd, SW_SHOWNORMAL );
        ZeroMemory( &this->msg, sizeof( MSG ) );
}

void Okno::postarejSeOZpravy()
{

//            while( msg.message != WM_QUIT )
//            {

                if( PeekMessage( &this->msg, NULL, 0U, 0U, PM_REMOVE ) )  //mame this->msg?
                {
                    if( this->bQuit==WM_QUIT )
                    {
                        this->otevreno = false;
                        this->~Okno(); // msgProc ma asi tezko pristup k oknu1
                        this->msg.message = WM_DESTROY; //vpodstate se zavola cleanup v msgProc
                        TranslateMessage( &this->msg );
                        DispatchMessage( &this->msg );
                        this->msg.message = WM_QUIT;
                    }
                    TranslateMessage( &this->msg );
                    DispatchMessage( &this->msg );
                }
                else    //nemame this->msg..
                {
//                    bQuit = ReadInputState( axs, Keys );
//                    render( g_pd3dDevice, Pocet, Keys, axs, TMatX, g_pVB );
                }
//            }
}

}
