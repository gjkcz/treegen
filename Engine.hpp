#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <string>
#include <functional>   // aby fungoval bind
#include <random>       // Generatory
#include <chrono>       // Casove fce
#include <thread>
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include <d3d11.h>
#include "SWU/Okno.hpp"
#include "SWU/Konzole.hpp"
#include "Kontroler3d.hpp"
#include "CustomVertex.hpp"
#include "JednoduchyVertex.hpp"
#include "TreeType.hpp"
#include "Helper.hpp"
#include "Tree.hpp"
#include "globals.hpp"

namespace se
{


class Engine
{
public:
    HRESULT stav;   // pouzivam k precteni zpravy (WM_QUIT, etc.)
    Engine(const sw::Okno&);
    ~Engine();
    void priprav();
    void prectiVstupAUpravKameru();
    void render3d();
    void dejKonzoli(const sk::Konzole& x){iKonzole = x;}
private:
    sw::Okno okno;
    sktrl::Kontroler3d iKontroler3d;
    sk::Konzole iKonzole;
    LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointer
    LPDIRECT3D9 g_pD3D; // Used to create the D3DDevice
    void pripravView();
    void pripravGeometrii();

    int bbClearColor = 1;
    float fFOV;
    D3DXMATRIX mScale, mRotateW;
    D3DXMATRIX maticeProjekce;

    static const bool bRust=false;
    float fDalka; //0
    int* aPocetVrcholuStromu;
    D3DXMATRIX* treeMatrix;
    LPDIRECT3DVERTEXBUFFER9* treeVertexBuffers;
};


}

#endif // __ENGINE_H_INCLUDED__

