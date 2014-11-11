#pragma warning( disable : 4996 ) // disable deprecated warning
#include "start.h"
//#include "Tree.h"

long axX, axY, axZ, nmX,nmY;
LPDIRECTINPUT8          diiDI = NULL; // DirectInput interface
LPDIRECTINPUTDEVICE8    diMouse = NULL; // Device interface
LPDIRECTINPUTDEVICE8    diKeybrd = NULL; // Device interface
byte Keys[256];
float							 v_X, v_Y, v_Z, vt_X, vt_Y, vt_Z;
bool							 Buttons[8];
bool							 v_XY = true;
int iObsah=1;
int iPatra=2;
bool bRust=false;
float  CamRotRad = iPatra*iObsah*9000.f; //78000
float fDalka=950000.f; //0
int width = 1920/*3200*/, height = 1080;
bool bFScreen=false;
float  RotUp=D3DX_PI/18.3f, CamRot = -D3DX_PI; //D3DX_PI/2.5;
float CamRotVel = 0.0f;
float fVel=iObsah * 500.8; //5000
int gRndm; //rozhoduje o barve pozadi...
float fFOV = D3DX_PI/3;
XMFLOAT3 velocity[10];
#pragma warning( default : 4996 )




//-----------------------------------------------------------------------------
// Global variables
//-----------------------------------------------------------------------------
LPDIRECT3D9             g_pD3D = NULL; // Used to create the D3DDevice
LPDIRECT3DDEVICE9       g_pd3dDevice = NULL; // Our rendering device
LPDIRECT3DVERTEXBUFFER9* g_pVB = new LPDIRECT3DVERTEXBUFFER9[iObsah]; // Buffer to hold vertices
D3DXMATRIXA16* TMatX = new D3DXMATRIXA16[iObsah];
int* i_aPocetV = new int[iObsah];
// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)




HRESULT InitInputDevice(HWND hInstance)
{
    HRESULT hr;
    for (int i = 8; i < 8; i++)
        Buttons[i] = false;
    if (FAILED(hr=DirectInput8Create(GetModuleHandle(NULL), 0x0800, IID_IDirectInput8, ( VOID** )&diiDI, NULL )))
        return hr;
    if (FAILED (hr=diiDI->CreateDevice(GUID_SysMouse,&diMouse, NULL)))
        return hr;
    if (FAILED (hr=diMouse->SetDataFormat(&c_dfDIMouse2)))
        return hr;
    if (FAILED (hr=diMouse->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        return hr;
    //mouse

    if (FAILED (hr=diiDI->CreateDevice(GUID_SysKeyboard,&diKeybrd, NULL)))
        return hr;
    if (FAILED (hr=diKeybrd->SetDataFormat(&c_dfDIKeyboard)))
        return hr;
    if (FAILED (hr=diKeybrd->SetCooperativeLevel(hInstance, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE)))
        return hr;


    return S_OK;
}
//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT InitD3D( HWND hWnd )
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

    return S_OK;
}


//-----------------------------------------------------------------------------
// Name: InitGeometry()
// Desc: Creates the scene geometry
//-----------------------------------------------------------------------------
int* InitGeometry()
{
    /*while(gRndm==0)
    	gRndm=zaokrouhli(random()*1.0);
    */
    int vPocet, iPocetV=0;
    CUSTOMVERTEX* g_Vertices;

    float xoffset = -2*fDalka;
    float yoffset = -2*fDalka;
    UINT uiTime=0;
    SimpleVertex* Tvertices;
    uiTime = timeGetTime();
    for(int i = 0; i<iObsah; i++)
    {
        xoffset = (i/sqrt((float)iObsah)) * fDalka-(sqrt((float)iObsah)/2)*fDalka+random()*fDalka-fDalka*0.5;
        yoffset = (i-(i/(int)sqrt((float)iObsah)*(int)sqrt((float)iObsah)))* fDalka-(sqrt((float)iObsah)/2)*fDalka+random()*fDalka-fDalka*0.5;
        D3DXMatrixTranslation(&TMatX[i], xoffset, yoffset, 0.f);
        int iTypu=8;
        int iTyp=0;
        bool bIAm = false;
        int l = 0;
        tType type;
        for(int c=0; c<3; c++)
        {
            while(!bIAm)
            {
                if (i%iTypu==l)
                {
                    bIAm=true;
                    iTyp=l;
                }
                l++;
            }
            (c==0)?(type._iSType=iTyp):((c==1)?(type._iRType=iTyp):(type._iDType=iTyp));
            iTypu=(c==0)?5:3;
            l = 0;
            bIAm = false;
        }
        type._iRType=5;
        type._iDType=4;
        vPocet = GenerateTree(iPatra, type);
        iPatra+=bRust?1:0;
        iPocetV+=vPocet;
        i_aPocetV[i] = vPocet;
        g_Vertices = new CUSTOMVERTEX[vPocet];

        // Create the vertex buffer.
        if( FAILED( g_pd3dDevice->CreateVertexBuffer( vPocet * sizeof( CUSTOMVERTEX ),
                    0, D3DFVF_CUSTOMVERTEX,
                    D3DPOOL_DEFAULT, &g_pVB[i], NULL ) ) )
        {
            return NULL;
        }

        Tvertices = UnpackTree();
        if( FAILED( g_pVB[i]->Lock( 0, 0, ( void** )&g_Vertices, 0 ) ) )
            return NULL; //pozor do pole nejde e_fail
        int tempColor;
        float colorK;
        for(int x=0; x<vPocet; x++)
        {
            g_Vertices[x].x = Tvertices[x].Pos.x;
            g_Vertices[x].y = Tvertices[x].Pos.y;
            g_Vertices[x].z = Tvertices[x].Pos.z;
//			g_Vertices[x].color = 0xF000000;
            for(int b = 0; b<3; b++)
            {
                switch(b)
                {
                case 0:
                {
                    colorK = Tvertices[x].Color.z;
                    break;
                }
                case 1:
                {
                    colorK = Tvertices[x].Color.y;
                    break;
                }
                case 2:
                {
                    colorK = Tvertices[x].Color.x;
                    break;
                }
                }
                tempColor=(colorK * 255);
                g_Vertices[x].color += DWORD(tempColor*(pow(float(16),b*2)));
                //tempColor=(colorK * 255)-(int)(colorK * 255/16)*16;
            }
        }
        g_pVB[i]->Unlock();
    }
    uiTime=timeGetTime()-uiTime;
    return i_aPocetV;
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

    if( g_pD3D != NULL )
        g_pD3D->Release();
}



//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform Matrices.
//-----------------------------------------------------------------------------
VOID SetupMatrices(int iWorld)
{
    float x = 0.f;
    float y = 0.f;
    // For our world matrix, we will just rotate the object about the y-axis.

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
        CamRotRad -=0.7;
    if (Keys[DIK_S] & 0x80)
        CamRotRad += 0.7;
    if (Keys[DIK_A] & 0x80)
        CamRot =  D3DX_PI/2;
    if (Keys[DIK_D] & 0x80)
        CamRot =  2*D3DX_PI;
    if (Keys[DIK_Q] & 0x80)
        vt_Y -= 0.7;
    if (Keys[DIK_E] & 0x80)
        vt_Y += 0.7;
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
    D3DXMatrixRotationX(&mRotateVX,RotUp);

    //XMMATRIX mRotateVY =  D3DXMatrixRotationXY(axX * 0.001f); //mouse


    D3DXMatrixRotationZ(&mRotateVZ, axZ *0.001f);
    D3DXVECTOR3* At = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

    //At = XMVector3Transform( At, mRotateVX);
    //At = XMVector3Transform( At, mRotateVY);
    if(CamRot <= 2 * 3.14159265358979323846)
        CamRot += CamRotVel*3.14159265358979323846/180;
    else
        CamRot = 0.f;

    D3DXMATRIXA16 mRotateVY;
    D3DXMatrixRotationY(&mRotateVY, -3.14159265358979323846/2 + CamRot + axX * D3DX_PI/11520);
    //CamRot = 3.14159265358979323846/2;
    D3DXMATRIXA16 mRotateW;
    D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);
    D3DXMATRIXA16 g_View;
    D3DXVECTOR3* Eye = new D3DXVECTOR3( cos(CamRot) * CamRotRad, sin(CamRot) * CamRotRad, 0.0f);
    D3DXVECTOR3* Up = new D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
    D3DXMatrixLookAtLH( &g_View, Eye, At, Up );

    D3DXMATRIXA16 mScale;
    D3DXMatrixScaling(&mScale, 0.2f, 0.2f, 0.2f );
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
    D3DXMatrixTranslation(&translate, cos(CamRot) * CamRotRad + cos((float)axX * D3DX_PI/11520) , vt_Y, sin(CamRot) * CamRotRad +sin((float)axX * D3DX_PI/11520)+ vt_X);
    D3DXMATRIXA16 g_World1 = TMatX[iWorld] * mScale * mRotateW;// * translate;
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
    g_pd3dDevice->SetTransform( D3DTS_WORLD, &g_World1 );

    g_pd3dDevice->SetTransform( D3DTS_VIEW, &g_View );

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
    g_pd3dDevice->SetTransform( D3DTS_PROJECTION, &matProj );
}


HRESULT ReadInputState()
{
    float PI = 3.14159265358979323846;
    HRESULT hr;
    DIMOUSESTATE2 ms;
    hr = diMouse->Poll();
    if (FAILED(hr))
    {
        hr = diMouse->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diMouse->Acquire();
        return S_OK;
    }
    diMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &ms);

    for (int i = 0; i < 8; i++)
    {
        if (ms.rgbButtons[i])
            Buttons[i] = true;
        else
            Buttons[i] = false;
    }
    if(Buttons[2])
    {
        axX += ms.lX;																	//Mouse
        axY += (ms.lY)*PI/180;
        axZ += ms.lZ;
    }
    if(Buttons[1])
    {
        return WM_QUIT;
    }
    nmX+=ms.lX;
    nmY+=ms.lY;
    //axX += ms.lX;
    hr = diKeybrd->Poll();
    if (FAILED(hr))
    {
        hr = diKeybrd->Acquire();
        while(hr == DIERR_INPUTLOST)
            hr = diKeybrd->Acquire();
        return S_OK;
    }
    diKeybrd->GetDeviceState(256, &Keys);

    return S_OK;
}

int GenerateRndm(int Obor, int Obor1)
{

    while(nmX==0 || nmY==0)
        ReadInputState();
    ReadInputState();
    Obor1-=Obor;
    int x;
    int y;
    int z;
    if (nmX < 0)
        nmX = -nmX;
    if (nmY < 0)
        nmY = -nmY;

    if (Obor1/100!=0)
        x = (int)nmX - ((int)nmX/(Obor1/100))*(Obor1/100);
    else
        x = 0;

    if (((Obor1 - (Obor1/100)*100)/10)!=0 && x < (Obor1/100))
        y = (int)nmY - ((int)nmY/10)*10;
    else if (((Obor1 - (Obor1/100)*100)/10)!=0 && x == (Obor1/100))
        y = (int)nmY - ((int)nmY/((Obor1 - (Obor1/100)*100)/10))*((Obor1 - (Obor1/100)*100)/10);
    else if (((Obor1 - (Obor1/100)*100)/10)==0 && x < (Obor1/100))
        y = (int)nmY - ((int)nmY/10)*10;
    else
        y = 0;

    if (x < Obor1/100)
        z = (int)nmX - ((int)nmX/10)*10;
    else if (y < Obor1/10)
        z = (int)nmX - ((int)nmX/10)*10;
    else if ((Obor1 - (Obor1/100)*100 - (Obor1/10)*10)!=0)
        z = (int)nmX - ((int)nmX/(Obor1 - (Obor1/100)*100 - (Obor1/10)*10))*(Obor1 - (Obor1/100)*100 - (Obor1/10)*10);
    else
        z = 0;

    nmY=0;
    nmX=0;
    if (2==2)
        return Obor+ x*100 + y*10 + z;
    else
        return Obor+ 1;
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
    _rndm = rand()/32767.f;
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

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
VOID render(int* Pocet)
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

        //XMMATRIX mRotateVY =  D3DXMatrixRotationXY(axX * 0.001f); //mouse


        D3DXMatrixRotationZ(&mRotateVZ, axZ *0.001f);
        D3DXVECTOR3* At = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

        //At = XMVector3Transform( At, mRotateVX);
        //At = XMVector3Transform( At, mRotateVY);
        if(CamRot <= 2 * 3.14159265358979323846)
            CamRot += CamRotVel*3.14159265358979323846/180;
        else
            CamRot = 0.f;

        D3DXMATRIXA16 mRotateVY;
        D3DXMatrixRotationY(&mRotateVY, -3.14159265358979323846/2 + CamRot + axX * D3DX_PI/11520);
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
        D3DXMatrixTranslation(&translate, cos(CamRot) * CamRotRad + cos((float)axX * D3DX_PI/11520) , vt_Y, sin(CamRot) * CamRotRad +sin((float)axX * D3DX_PI/11520)+ vt_X);


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




//-----------------------------------------------------------------------------
// Name: MsgProc()
// Desc: The window's message handler
//-----------------------------------------------------------------------------
LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
    switch( msg )
    {
    case WM_DESTROY:
        Cleanup();
        PostQuitMessage( 0 );
        return 0;
    }

    return DefWindowProc( hWnd, msg, wParam, lParam );
}




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

                if( PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ) )
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
                else
                {
                    bQuit=ReadInputState();
                    render( Pocet );
                }
            }
        }
    }

    UnregisterClass( "Tree", wc.hInstance );
    return 0;
}



