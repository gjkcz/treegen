#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <string>
#include <functional>   // aby fungoval bind
#include <random>       // Generatory
#include <chrono>       // Casove fce
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
//#include <d3dx9math.h>
#include "SWU/Okno.hpp"
#include "SWU/Konzole.hpp"
#include "Input.hpp"
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
    void prectiVstup();
    void render3d();
    void dejKonzoli(const sk::Konzole& x){iKonzole = x;}
    int* vemPocetVrcholuStromu() {return aPocetVrcholuStromu;}
    const LPDIRECT3DDEVICE9& vemG_pD3DDevice(){return g_pd3dDevice;}
    D3DXMATRIX* vemTreeMatrixy(){return treeMatrix;}
    LPDIRECT3DVERTEXBUFFER9* vemTreeVertexBuffers(){return treeVertexBuffers;}
    byte* vemKeys(){return iInput.Keys;}
    float* vemAxs(){return iInput.axs;}
private:
    sw::Okno okno;
    si::Input iInput;
    sk::Konzole iKonzole;
    LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointer
    LPDIRECT3D9 g_pD3D; // Used to create the D3DDevice
    void pripravView();
    void pripravGeometrii();

    static const bool bRust=false;
    float fDalka; //0
    int* aPocetVrcholuStromu;
    D3DXMATRIX* treeMatrix;
    LPDIRECT3DVERTEXBUFFER9* treeVertexBuffers;
};


}

#endif // __ENGINE_H_INCLUDED__

