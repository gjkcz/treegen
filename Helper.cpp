#include "Helper.hpp"

namespace helper {


float random()
{
    float _rndm=0.f;
    //_rndm = abs(sin((timeGetTime() % 360)*(rand()/32767.f)*D3DX_PI/180));
    /*while(_rndm<0.998f)
    {*/
//    while(timeGetTime()%1000>=999) {
//        srand(timeGetTime());
//    }
    _rndm = rand()/32000.f;
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


}
