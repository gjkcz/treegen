#ifndef __H_VETEV_INCLUDED__
#define __H_VETEV_INCLUDED__

class Vetev
{
public:
    Vetev();
    ~Vetev();
protected:
private:
    SimpleVertex* vrcholy;
    UINT* indicie;
    D3DXVECTOR3* kolmice;
};


#endif // __H_VETEV_INCLUDED__

