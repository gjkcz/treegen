#ifndef __CUSTOMVERTEX_H_INCLUDED__
#define __CUSTOMVERTEX_H_INCLUDED__

// Our custom FVF, which describes our custom vertex structure
#define D3DFVF_VrcholB (D3DFVF_XYZ|D3DFVF_DIFFUSE)

// A structure for our custom vertex type
struct VrcholB
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    DWORD color;        // The vertex color
};

#define D3DFVF_VrcholPKB (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE)
struct VrcholPKB
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    D3DXVECTOR3 kolmice;
    DWORD color;        // The vertex color
};
#define D3DFVF_VrcholBK (D3DFVF_XYZ|D3DFVF_NORMAL)
struct VrcholBK
{
    FLOAT x, y, z;      // The untransformed, 3D position for the vertex
    D3DXVECTOR3 kolmice;
    DWORD color;        // The vertex color
};
#endif // __CUSTOMVERTEX_H_INCLUDED__
