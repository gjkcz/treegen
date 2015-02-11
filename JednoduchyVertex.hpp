#ifndef __SIMPLEVERTEX_H_INCLUDED__
#define __SIMPLEVERTEX_H_INCLUDED__


#include <d3dx9math.h>
// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_SIMPLEVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)// DX9 NEMA odpovidajici

struct SimpleVertex
{
    D3DXVECTOR3 Pos;  // Position
    D3DXVECTOR3 Normal; // Light Normal
    D3DXVECTOR4 Color; // Color
    //XMFLOAT2 Tex; // Texture Co
};


#endif // __SIMPLEVERTEX_H_INCLUDED__
