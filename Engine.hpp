#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

#include <d3dx9.h>
#include "SWU/Okno.hpp"
#include "Input.hpp"
#include "CustomVertex.hpp"
#include "JednoduchyVertex.h"
#include "TreeType.hpp"
#include "Helper.hpp"
#include "Tree.h"

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
    int* vemPocetVrcholuStromu() {return aPocetVrcholuStromu;}
    const LPDIRECT3DDEVICE9& vemG_pD3DDevice(){return g_pd3dDevice;}
    D3DXMATRIXA16* vemTreeMatrixy(){return treeMatrix;}
    LPDIRECT3DVERTEXBUFFER9* vemTreeVertexBuffers(){return treeVertexBuffers;}
    byte* vemKeys(){return oInput.Keys;}
    float* vemAxs(){return oInput.axs;}
private:
    sw::Okno okno;
    si::Input oInput;
    LPDIRECT3DDEVICE9 g_pd3dDevice; // Our rendering device, lp= neco pointer
    LPDIRECT3D9 g_pD3D; // Used to create the D3DDevice
    void pripravView();
    void pripravGeometrii();

    static const bool bRust=false;
    float fDalka; //0
    int* aPocetVrcholuStromu;
    D3DXMATRIXA16* treeMatrix;
    LPDIRECT3DVERTEXBUFFER9* treeVertexBuffers;
};


}

#endif // __ENGINE_H_INCLUDED__

