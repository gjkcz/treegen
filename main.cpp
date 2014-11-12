#include <windows.h>
#include <strsafe.h>
#include "msgProc.h"
#include "inits.h"
#include "view.h"
#include "controler.h"
#include "globals.h"
byte* Keys;
long* axs;

//-----------------------------------------------------------------------------
// Name: WinMain()
// Desc: The application's entry point
//-----------------------------------------------------------------------------
INT WINAPI wWinMain( HINSTANCE hInst, HINSTANCE, LPWSTR, INT )
{
    UNREFERENCED_PARAMETER( hInst );

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
                              WS_OVERLAPPEDWINDOW, 0, 0, width, height, //screen
                              NULL, NULL, wc.hInstance, NULL );


    // Initialize Direct3D
    if( SUCCEEDED( InitD3D( hWnd ) ) )
    {
        // Show the window
        ShowWindow( hWnd, SW_SHOWDEFAULT );
        UpdateWindow( hWnd );

        // Inicializace mysi
        if(SUCCEEDED( InitInputDevice( hWnd )) )
        {
            // Create the scene geometry
            int* Pocet = InitGeometry();
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
                    Keys=ReadInputState( axs );
                    render( Pocet, Keys, axs );
                }
            }
        }
    }

    UnregisterClass( "Tree", wc.hInstance );
    return 0;
}
