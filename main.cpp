#include <windows.h>
#include <strsafe.h>
#include <iostream>
#include <string>
#include "msgProc.h"
#include "inits.h"
#include "view.h"
#include "controler.h"
#include "globals.h"
byte* Keys = new byte[256];
long* axs = new long[4];
LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointr
D3DXMATRIXA16* TMatX = new D3DXMATRIXA16[iObsah];
LPDIRECT3DVERTEXBUFFER9* g_pVB = new LPDIRECT3DVERTEXBUFFER9[iObsah]; // Buffer to hold vertices

//int main()
//{
//    std::cout << "Hello!";
//
//    HINSTANCE hInst = GetModuleHandle(0);
//    WNDCLASS cls = { CS_HREDRAW|CS_VREDRAW, MsgProc, 0, 0, hInst, LoadIcon(hInst,MAKEINTRESOURCE(IDI_APPLICATION)),
//        LoadCursor(hInst,MAKEINTRESOURCE(IDC_ARROW)), GetSysColorBrush(COLOR_WINDOW),0,"Window" };
//    RegisterClass( &cls );
//    HWND window = CreateWindow("Window","Hello World",WS_OVERLAPPEDWINDOW|WS_VISIBLE,64,64,640,480,0,0,hInst,0);
//
//    // Initialize Direct3D
//    if( SUCCEEDED( InitD3D( window, g_pd3dDevice, TMatX ) ) )
//    {
//        // Show the window
//        ShowWindow( window, SW_SHOWDEFAULT );
//        UpdateWindow( window );
//
//        // Inicializace mysi a klavesnice
//        if(SUCCEEDED( InitInputDevice( window )) )
//        {
//            // Create the scene geometry
//            int* Pocet = InitGeometry( g_pd3dDevice, TMatX, g_pVB );
//            HRESULT bQuit=NULL;
//
//            // Enter the message loop
//            MSG msg;
//            ZeroMemory( &msg, sizeof( msg ) );
//            while( msg.message != WM_QUIT )
//            {
//
//                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )  //mame msg?
//                {
//                    if( bQuit==WM_QUIT )
//                    {
//                        msg.message = WM_DESTROY;
//                        TranslateMessage( &msg );
//                        DispatchMessage( &msg );
//                        msg.message = WM_QUIT;
//                    }
//                    TranslateMessage( &msg );
//                    DispatchMessage( &msg );
//                }
//                else    //nemame msg..
//                {
//                    bQuit = ReadInputState( axs, Keys );
//                    render( g_pd3dDevice, Pocet, Keys, axs, TMatX, g_pVB );
//                }
//            }
//        }
//    }
//
//    UnregisterClass( "Tree", cls.hInstance );
//    return 0;
//}

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst ); // fakt nevim co to dela

    // Register the window class
    WNDCLASSEX wc =
    {
        sizeof( WNDCLASSEX ), CS_CLASSDC, MsgProc, 0L, 0L,
        GetModuleHandle( NULL ), NULL, NULL, NULL, NULL,
        "Tree", NULL
    };
    RegisterClassEx( &wc );

    // Create the application's window
    HWND hWnd = CreateWindow( "Tree", "Tree",
                              WS_OVERLAPPEDWINDOW, screenX, screenY, width, height, //screen
                              NULL, NULL, wc.hInstance, NULL );


    // Presmeruj IO do nasi nove konzole
    RedirectIOToConsole();
    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd, g_pd3dDevice, TMatX ) ) )
    {
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Inicializace mysi a klavesnice
        if(SUCCEEDED( InitInputDevice( hWnd )) )
        {
            // Create the scene geometry
            int* Pocet = InitGeometry( g_pd3dDevice, TMatX, g_pVB );
            HRESULT bQuit=NULL;

            // Enter the message loop
            MSG msg;
            ZeroMemory( &msg, sizeof( msg ) );
            while( msg.message != WM_QUIT )
            {

                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )  //mame msg?
                {
                    if( bQuit==WM_QUIT )
                    {
                        msg.message = WM_DESTROY;
                        TranslateMessage( &msg );
                        DispatchMessage( &msg );
                        msg.message = WM_QUIT;
                    }
                    TranslateMessage( &msg );
                    DispatchMessage( &msg );
                }
                else    //nemame msg..
                {
                    bQuit = ReadInputState( axs, Keys );
                    render( g_pd3dDevice, Pocet, Keys, axs, TMatX, g_pVB );
                }
            }
        }
    }

    UnregisterClass( "Tree", wc.hInstance );
    return 0;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
VOID Cleanup()
{
    for(int i = 0; i < iObsah; i++)
    {
        if( g_pVB[i] != NULL )
            g_pVB[i]->Release();
    }
    if( g_pd3dDevice != NULL )
        g_pd3dDevice->Release();
}

float random()
{
    float _rndm=0.f;
    //_rndm = abs(sin((timeGetTime() % 360)*(rand()/32767.f)*D3DX_PI/180));
    /*while(_rndm<0.998f)
    {*/
    while(timeGetTime()%1000>=999)
    {
        srand(timeGetTime());
    }
    _rndm = rand()/32000.f;
    return _rndm;
}

int zaokrouhli(float _f)
{
    int _v=0;
    if((_f -(int)_f) < 0.5)
        _v = _f-(_f -(int)_f);
    else
        _v = _f-(_f -(int)_f)+1;
    return _v;
}
