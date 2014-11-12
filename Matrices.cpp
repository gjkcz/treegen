#pragma warning( disable : 4996 ) // disable deprecated warning
#include "start.h"
//#include "Tree.h"

long axX, axY, axZ, nmX,nmY;
byte Keys[256];
float							 v_X, v_Y, v_Z, vt_X, vt_Y, vt_Z;
bool							 Buttons[8];
bool							 v_XY = true;
bool bRust=false;
float  CamRotRad = iPatra*iObsah*9000.f; //78000
float fDalka=950000.f; //0
float  RotUp=D3DX_PI/18.3f, CamRot = -D3DX_PI; //D3DX_PI/2.5;
float CamRotVel = 0.0f;
float fVel=iObsah * 500.8; //5000
float fFOV = D3DX_PI/3;
XMFLOAT3 velocity[10];
#pragma warning( default : 4996 )









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





