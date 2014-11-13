#include "view.h"

int gRndm = 1; //rozhoduje o barve pozadi... 0=cerna, 1=bila
bool bFScreen=false;
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
float							 v_X, v_Y, v_Z, vt_X, vt_Y, vt_Z;
bool							 v_XY = true;
float  CamRotRad = iPatra*iObsah*9000.f; //78000
float  RotUp=D3DX_PI/18.3f, CamRot = -D3DX_PI; //D3DX_PI/2.5;
float CamRotVel = 0.0f;
float fVel=iObsah * 500.8; //5000
float fFOV = D3DX_PI/3;
XMFLOAT3 velocity[10];


//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd, LPDIRECT3DDEVICE9& g_pd3dDevice, D3DXMATRIXA16* TMatX )
{
    // Create the D3D object.
    if( NULL == ( g_pD3D = Direct3DCreate9( D3D_SDK_VERSION ) ) )
        return E_FAIL;

    // Set up the structure used to create the D3DDevice
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory( &d3dpp, sizeof( d3dpp ) );
    if(bFScreen)
        d3dpp.Windowed = false; //fullscreeen
    else
        d3dpp.Windowed = true;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;

    g_pd3dDevice = NULL;
    // Create the D3DDevice
    if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                     D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                     &d3dpp, &g_pd3dDevice ) ) )
    {
        return E_FAIL;
        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                        &d3dpp, &g_pd3dDevice )))
        {
            if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                            D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                            &d3dpp, &g_pd3dDevice )))
            {
                if( FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, hWnd,
                                                 D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                 &d3dpp, &g_pd3dDevice ) ) )
                {
                    if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
                                                    D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                    &d3dpp, &g_pd3dDevice )))
                    {
                        if(FAILED(g_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_FORCE_DWORD, hWnd,
                                                        D3DCREATE_HARDWARE_VERTEXPROCESSING,
                                                        &d3dpp, &g_pd3dDevice )))
                        {

                        }
                    }
                }
            }
        }
    }


    // Turn off culling, so we see the front and back of the triangle
    g_pd3dDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

    // Turn off D3D lighting, since we are providing our own vertex colors
    g_pd3dDevice->SetRenderState( D3DRS_LIGHTING, FALSE );

    //TMatX = new D3DXMATRIXA16[iObsah];

    if( g_pD3D != NULL )
        g_pD3D->Release();

    return S_OK;
}



//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID render( LPDIRECT3DDEVICE9& g_pd3dDevice, int* Pocet, byte * Keys, long* axs, D3DXMATRIXA16* TMatX, LPDIRECT3DVERTEXBUFFER9* g_pVB)
{

    // Clear the backbuffer to a black color
    if( gRndm==1 )
        g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 255, 255, 255 ), 1.0f, 0 );
    else
        g_pd3dDevice->Clear( 0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB( 0, 0, 0 ), 1.0f, 0 );
    // Begin the scene
    if( SUCCEEDED( g_pd3dDevice->BeginScene() ) )
    {
        g_pd3dDevice->SetFVF( D3DFVF_CUSTOMVERTEX );
        //CamRotRad = 20.f;
        float x = 0.f;
        float y = 0.f;
        // For our world matrix, we will just rotate the object about the y-axis.
        //D3DXMATRIXA16 matWorld= TMatX[iWorld];

        // Set up the rotation matrix to generate 1 full rotation (2*PI radians)
        // every 1000 ms. To avoid the loss of precision inherent in very high
        // floating point numbers, the system time is modulated by the rotation
        // period before conversion to a radian angle.
        if (v_XY && (v_X - 0.1f) > 0.0f)
        {
            v_X -= 0.1f;
            v_Y += 0.1f;
        }
        else if (v_XY && (v_X - 0.1f) <= 0.0f)
        {
            v_XY = false;
        }
        else if (!v_XY && (v_X + 0.1f) < 100.0f)
        {
            v_X += 0.1f;
            v_Y -= 0.1f;
        }
        else if(!v_XY && (v_X + 0.1f) >= 100.0f)
        {
            v_XY = true;
        }

        //KBD

        if (Keys[DIK_W] & 0x80)
            CamRotRad -=fVel;
        //vt_Z -= 0.1;
        if (Keys[DIK_S] & 0x80)
            CamRotRad += fVel;
        if (Keys[DIK_ADD] & 0x80)
            fVel += iObsah*0.42;
        //vt_Z -= 0.1;
        if (Keys[DIK_SUBTRACT] & 0x80)
            fVel -= iObsah*0.42;
        //vt_Z += 0.1;
        if (Keys[DIK_A] & 0x80)
            CamRot =  D3DX_PI/2;
        if (Keys[DIK_D] & 0x80)
            CamRot =  2*D3DX_PI;
        if (Keys[DIK_Q] & 0x80)
            vt_Y -= fVel;
        if (Keys[DIK_E] & 0x80)
            vt_Y += fVel;
        if (Keys[DIK_1] & 0x80)
            CamRotVel -= 0.001;
        if (Keys[DIK_2] & 0x80)
            CamRotVel += 0.001;
        if (Keys[DIK_3] & 0x80)
            CamRot -= D3DX_PI/27;
        if (Keys[DIK_4] & 0x80)
            CamRot +=  D3DX_PI/27;
        if (Keys[DIK_5] & 0x80)
            CamRotVel =  0.f;
        if (Keys[DIK_DOWN] & 0x80)
            RotUp -=  D3DX_PI/32;
        if (Keys[DIK_UP] & 0x80)
            RotUp +=  D3DX_PI/32;
        if (Keys[DIK_INSERT] & 0x80)
        {
        }


        D3DXMATRIXA16 mRotateVX;
        D3DXMATRIXA16 mRotateVZ;
        // Rotate the view
        //axY+= D3DX_PI/180;
        D3DXMatrixRotationX(&mRotateVX,RotUp);

        //XMMATRIX mRotateVY =  D3DXMatrixRotationXY(axs[ * 0.001f); //mouse


        D3DXMatrixRotationZ(&mRotateVZ, axs[2] *0.001f);
        D3DXVECTOR3* At = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

        //At = XMVector3Transform( At, mRotateVX);
        //At = XMVector3Transform( At, mRotateVY);
        if(CamRot <= 2 * 3.14159265358979323846)
            CamRot += CamRotVel*3.14159265358979323846/180;
        else
            CamRot = 0.f;

        D3DXMATRIXA16 mRotateVY;
        D3DXMatrixRotationY(&mRotateVY, -3.14159265358979323846/2 + CamRot + axs[0] * D3DX_PI/11520);
        //CamRot = 3.14159265358979323846/2;
        D3DXMATRIXA16 mRotateW;
        D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);
        D3DXMATRIXA16 g_View;
        D3DXVECTOR3* Eye = new D3DXVECTOR3( cos(CamRot) * CamRotRad, sin(CamRot) * CamRotRad, 0.0f);
        D3DXVECTOR3* Up = new D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
        D3DXMatrixLookAtLH( &g_View, Eye, At, Up );

        D3DXMATRIXA16 mScale;
        D3DXMatrixScaling(&mScale, 0.5f, 0.5f, 0.5f );

        D3DXMATRIXA16 mOrbitionx;
        D3DXMatrixRotationY(&mOrbitionx, (velocity[1].x) / 4);
        D3DXMATRIXA16 mOrbition;
        D3DXMatrixRotationX(&mOrbition, velocity[1].x);
        D3DXMATRIXA16 mTranslation;
        D3DXMatrixTranslation(&mTranslation, 0.f,-(3.f + y), 0.f);
        D3DXMATRIXA16 mTranslationx;
        D3DXMatrixTranslation(&mTranslationx,-(-1.f + y/3),0.f, 0.f);
        //g_World1 = mScale * (mTranslation *  mOrbition) * mTranslationx * mOrbitionx;
        //XMMATRIX translate = XMMatrixTranslation(vt_X, vt_Y, vt_Z);
        D3DXMATRIXA16 translate;
        D3DXMatrixTranslation(&translate, cos(CamRot) * CamRotRad + cos((float)axs[0] * D3DX_PI/11520) , vt_Y, sin(CamRot) * CamRotRad +sin((float)axs[0] * D3DX_PI/11520)+ vt_X);


        g_View = translate * mRotateVZ * mRotateVY * mRotateVX;

        //FLOAT fAngle = iTime * ( 2.0f * D3DX_PI ) / 10000.0f;
        //D3DXMatrixRotationX( &matWorld, -D3DX_PI/2);


        // Set up our view matrix. A view matrix can be defined given an eye point,
        // a point to lookat, and a direction for which way is up. Here, we set the
        // eye five units back along the z-axis and up three units, look at the
        // origin, and define "up" to be in the y-direction.
        //D3DXVECTOR3 vEyePt( 10.0f, 50.0f,-50.0f );
        //D3DXVECTOR3 vLookatPt( 0.0f, 150.0f, 0.0f );
        //D3DXVECTOR3 vUpVec( 0.0f, 1.0f, 0.0f );
        D3DXMATRIXA16 g_World1 = TMatX[0] * mScale * mRotateW;// * translate;
        //g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_World1 );

        //g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_View );

        // For the projection matrix, we set up a perspective transform (which
        // transforms geometry from 3D view space to 2D viewport space, with
        // a perspective divide making objects smaller in the distance). To build
        // a perpsective transform, we need the field of view (1/4 pi is common),
        // the aspect ratio, and the near and far clipping planes (which define at
        // what distances geometry should be no longer be rendered).
        //g_Projection = XMMatrixPerspectiveFovLH( XM_PIDIV2, width / (FLOAT)height, 1.f, 102000.0f );
        //g_Projection = XMMatrixPerspectiveFovLH( 120.0f, width / (FLOAT)height, 0.000001f, 1000000000000000000000.0f );
        //CBChangeOnResize cbChangesOnResize;
        //cbChangesOnResize.mProjection = XMMatrixTranspose( g_Projection );
        //g_pImmediateContext->UpdateSubresource( g_pCBChangeOnResize, 0, NULL, &cbChangesOnResize, 0, 0 );
        //CamRotRad = 2.f;
        D3DXMATRIXA16 matProj;
        D3DXMatrixPerspectiveFovLH( &matProj, fFOV, width / (FLOAT)height, 1.0f, 102000000.0f );

        g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_View );

        g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
        //g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
        for(int i = 0; i < iObsah; i++)
        {
            // Setup the world, view, and projection Matrices
            //SetupMatrices(i);
            D3DXMATRIXA16 g_World1 = TMatX[i] * mScale * mRotateW;// * translate;
            g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_World1 );


            // Render the vertex buffer contents
            g_pd3dDevice->SetStreamSource( 0, g_pVB[i], 0, sizeof( CUSTOMVERTEX ) );

            g_pd3dDevice->DrawPrimitive(
                D3DPT_POINTLIST, 0, Pocet[i] );

            // End the scene
            g_pd3dDevice->EndScene();
        }
    }

    // Present the backbuffer contents to the display
    g_pd3dDevice->Present( NULL, NULL, NULL, NULL );
}

