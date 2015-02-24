#include "Kamera.hpp"
namespace skam
{


Kamera::Kamera()
{
    At = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
    Eye = new D3DXVECTOR3( 0.f, 0.f, 0.0f);
    Up = new D3DXVECTOR3( 1.0f, 0.0f, 0.0f);
    vTranslace = new D3DXVECTOR3( 0.f, 0.f, 0.0f);

    vZaxis = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f);
    vKolmice = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f);


    CamRotRad = iPatra*iObsah*9000.f; //78000
    RotUp = D3DX_PI/18.3f;
    CamRot = -D3DX_PI; //D3DX_PI/2.5;
    CamRotVel = 0.0f;
    fVel = iObsah * 50.8; //5000

    nasobitelKoeficientu = 2;
    koeficienRotaceOs[0] = nasobitelKoeficientu*0.0005f;
    koeficienRotaceOs[1] = nasobitelKoeficientu*D3DX_PI/11520;
    koeficienRotaceOs[2] = 3.;

}

Kamera::~Kamera()
{
#ifdef DESTRUCTORVERBOSE
    std::cout << "Kamera destructor." << std::endl;
#endif // DESTRUCTORVERBOSE
    delete At;
    delete Eye;
    delete Up;
#ifdef DESTRUCTORVERBOSE
    std::cout << "delete 3 comma separ." << std::endl;
#endif // DESTRUCTORVERBOSE
    delete vTranslace, vZaxis, vKolmice;
#ifdef DESTRUCTORVERBOSE
    std::cout << "ok." << std::endl;
#endif // DESTRUCTORVERBOSE
}


void Kamera::otocKameru(Smer kam)
{
    if ( kam == nahoru )
    {
        rotaceKolemOs[0] += PI;//*koeficienRotaceOs[2];
    }
    if ( kam == dolu)
    {
        rotaceKolemOs[0] -= PI;//*koeficienRotaceOs[2];
    }
    if ( kam == doleva )
    {
        rotaceKolemOs[1] -= PI*5./6.;//*koeficienRotaceOs[2];
    }
    if ( kam == doprava )
    {
        rotaceKolemOs[1] += PI*5./6.;//*koeficienRotaceOs[2];
    }
}

void Kamera::upravRotaciKamery(float * aOsy)
{

    // Rotate the view
//        axY+= D3DX_PI/180;
//        D3DXMatrixRotationX(&mRotateVX,RotUp);
    D3DXMatrixRotationX(&mRotateVX, (rotaceKolemOs[0] + (aOsy[1]* koeficienRotaceOs[0])*200.) * koeficienRotaceOs[0]); //mys nahoru dolu
//        D3DXMatrixRotationX(&mRotateVX,aOsy[0] * 0.001f);

    D3DXMatrixRotationZ(&mRotateVZ, aOsy[2] *0.001f); //mys okolo
//        D3DXVECTOR3* At = new D3DXVECTOR3( 0.0f, 0.0f, 0.0f );

    //At = XMVector3Transform( At, mRotateVX);
    //At = XMVector3Transform( At, mRotateVY);
    if(CamRot <= 2 * 3.14159265358979323846)
        CamRot += CamRotVel*3.14159265358979323846/180;
    else
        CamRot = 0.f;

    D3DXMatrixRotationY(&mRotateVY, -3.14159265358979323846/2 + CamRot + (-rotaceKolemOs[1] + (aOsy[0]* koeficienRotaceOs[1])*200.) * koeficienRotaceOs[1]);
    //CamRot = 3.14159265358979323846/2;
//    D3DXMATRIX mRotateW;
//    D3DXMatrixRotationX(&mRotateW, -3.14159265358979323846/2);

//    Eye = new D3DXVECTOR3( cos(CamRot) * CamRotRad, sin(CamRot) * CamRotRad, 0.0f);
    Eye->x = cos(CamRot) * CamRotRad;
    Eye->y = sin(CamRot) * CamRotRad;
//        D3DXVECTOR3 vTranslace = *(new D3DXVECTOR3( cos(CamRot) * CamRotRad + cos((float)aOsy[0] * D3DX_PI/11520),
//                                                  vt_Y,
//                                                    sin(CamRot) * CamRotRad +sin((float)axs[0] * D3DX_PI/11520)+ vt_X ));

//        D3DXVECTOR3* Eye = new D3DXVECTOR3( cos(CamRot) * CamRotRad, sin(CamRot) * CamRotRad, 0.0f);
//        D3DXVECTOR3* Eye = vTranslace;
//        D3DXMATRIX posun;
//        D3DXMatrixTranslation(&posun, , , );
//    D3DXVECTOR3* Up = new D3DXVECTOR3( 1.0f, 0.0f, 0.0f);

//D3DXMatrixLookAtLH( &g_View, Eye, At, Up );



//        D3DXMATRIX mOrbitionx;
//        D3DXMatrixRotationY(&mOrbitionx, (velocity[1].x) / 4);
//        D3DXMATRIX mOrbition;
//        D3DXMatrixRotationX(&mOrbition, velocity[1].x);
//        D3DXMATRIX mTranslation;
//        D3DXMatrixTranslation(&mTranslation, 0.f,-(3.f + y), 0.f);
//        D3DXMATRIX mTranslationx;
//        D3DXMatrixTranslation(&mTranslationx,-(-1.f + y/3),0.f, 0.f);
    //g_World1 = mScale * (mTranslation *  mOrbition) * mTranslationx * mOrbitionx;
//        XMMATRIX translate = XMMatrixTranslation(vt_X, vt_Y, vt_Z);
//        D3DXMatrixTranslation(&translate, cos(CamRot) * CamRotRad + cos((float)axs[0] * D3DX_PI/11520) , vt_Y, sin(CamRot) * CamRotRad +sin((float)axs[0] * D3DX_PI/11520)+ vt_X);
//        D3DXMatrixTranslation(&translate, 0.0f,0.0f,0.0f);
    D3DXMatrixTranslation(&translate, vTranslace->x, vTranslace->y, vTranslace->z);

    g_View = translate * mRotateVZ * mRotateVY * mRotateVX; //potrebuji k zjisteni at




}

void Kamera::posunKameru(Smer kam, float jakMoc = 1.f)
{
    if ( kam == dopredu )
    {
//            CamRotRad -= fVel;
        HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( hstdout, 0xC );

//        clearScreen();
//        cout << "x: " << g_View._13 << "\n";            // base
//        cout << "y: " << g_View._23 << "\n";
//        cout << "z: " << g_View._33 << "\n";            // base
//        vZaxis->x = g_View._13;
//        vZaxis->y = g_View._23;
//        vZaxis->z = g_View._33; // toto je presne smer, kterym hledim
        obnovSmerHledi();
        //i.e.: zaxis = normal(Eye - At)
        (*vTranslace) += (*vZaxis) * -fVel * jakMoc;
//            std::cout << "&g_View = " << g_View << "\n";

    }
    if ( kam == dozadu )
    {
//        clearScreen();
//        cout << "x: " << g_View._13 << "\n";            // base
//        cout << "y: " << g_View._23 << "\n";
//        cout << "z: " << g_View._33 << "\n";            // base
//            CamRotRad += fVel;
//        vZaxis->x = g_View._13;
//        vZaxis->y = g_View._23;
//        vZaxis->z = g_View._33; // toto je presne smer, kterym hledim
        obnovSmerHledi();
        //i.e.: zaxis = normal(Eye - At)
        (*vTranslace) += (*vZaxis) * fVel * jakMoc;

    }
    if ( kam == nahoru )
    {
        vKolmice->x = 0.f;
        vKolmice->y = -1.f;
        vKolmice->z = 0.f;
        (*vTranslace) += (*vKolmice) * fVel * jakMoc;
    }
    if ( kam == dolu)
    {
        vKolmice->x = 0.f;
        vKolmice->y = 1.f;
        vKolmice->z = 0.f;
        (*vTranslace) += (*vKolmice) * fVel * jakMoc;
    }
    if ( kam == doleva )
    {
        vKolmice->x = g_View._33;
        vKolmice->y = 0.f;
        vKolmice->z = -g_View._13;
        (*vTranslace) += (*vKolmice) * fVel * jakMoc;
    }
    if ( kam == doprava )
    {
        vKolmice->x = -g_View._33;
        vKolmice->y = 0.f;
        vKolmice->z = g_View._13;
        (*vTranslace) += (*vKolmice) * fVel * jakMoc;
    }
    g_View = translate * mRotateVZ * mRotateVY * mRotateVX;
}

void Kamera::posunKameru(Smer kam)
{
    if ( kam == dopredu )
    {
//            CamRotRad -= fVel;
        HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
        SetConsoleTextAttribute( hstdout, 0xC );

//        clearScreen();
//        cout << "x: " << g_View._13 << "\n";            // base
//        cout << "y: " << g_View._23 << "\n";
//        cout << "z: " << g_View._33 << "\n";            // base
        vZaxis->x = g_View._13;
        vZaxis->y = g_View._23;
        vZaxis->z = g_View._33; // toto je presne smer, kterym hledim
        //i.e.: zaxis = normal(Eye - At)
        (*vTranslace) += (*vZaxis) * -fVel;
//            std::cout << "&g_View = " << g_View << "\n";

    }
    if ( kam == dozadu )
    {
//        clearScreen();
//        cout << "x: " << g_View._13 << "\n";            // base
//        cout << "y: " << g_View._23 << "\n";
//        cout << "z: " << g_View._33 << "\n";            // base
//            CamRotRad += fVel;
        vZaxis->x = g_View._13;
        vZaxis->y = g_View._23;
        vZaxis->z = g_View._33; // toto je presne smer, kterym hledim
        //i.e.: zaxis = normal(Eye - At)
        (*vTranslace) += (*vZaxis) * fVel;

    }
    if ( kam == nahoru )
    {
        vKolmice->x = 0.f;
        vKolmice->y = -1.f;
        vKolmice->z = 0.f;
        (*vTranslace) += (*vKolmice) * fVel;
    }
    if ( kam == dolu)
    {
        vKolmice->x = 0.f;
        vKolmice->y = 1.f;
        vKolmice->z = 0.f;
        (*vTranslace) += (*vKolmice) * fVel;
    }
    if ( kam == doleva )
    {
        vKolmice->x = g_View._33;
        vKolmice->y = 0.f;
        vKolmice->z = -g_View._13;
        (*vTranslace) += (*vKolmice) * fVel;
    }
    if ( kam == doprava )
    {
        vKolmice->x = -g_View._33;
        vKolmice->y = 0.f;
        vKolmice->z = g_View._13;
        (*vTranslace) += (*vKolmice) * fVel;
    }
    g_View = translate * mRotateVZ * mRotateVY * mRotateVX;
}


}
