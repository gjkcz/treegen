#ifndef __CUSTOMVERTEX_H_INCLUDED__
#define __CUSTOMVERTEX_H_INCLUDED__

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ|D3DFVF_DIFFUSE)

// A structure for our custom vertex type
struct CUSTOMVERTEX
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};
#endif // __CUSTOMVERTEX_H_INCLUDED__
