#include "Helper.hpp"


namespace helper
{


boost::random::mt11213b nahodakMersenne {};
boost::random::taus88 nahodakTaus {};
std::mt19937 generator(1551);
std::uniform_int_distribution<int> distribution(0,1000);
//    auto kostka = std::bind ( distribution, generator );        //nejak nejde
Okamzik zacatek;
//    unsigned predchoziCislo = sysCas::now().time_since_epoch().count();
Doba d, d1;
float cislo = 0.f, predchoziCislo = 0.f;
unsigned seminko2;

void zapniStopky()
{
    zacatek = stopky::now();
}

float nahodneCislo()
{
//    boost::random::random_device trueRandomnessGenerator{};
//    std::cout << "Entropie: " << trueRandomnessGenerator.entropy() << std::endl;
    // obtain a seed from the timer
//    Doba d = stopky::now() - zacatek;
//    for(int y=0; y!=45000; ++y)            // Zdrzeni
//        d = sysCas::now().time_since_epoch();
//    pockej(1);
    while( cislo == predchoziCislo )
    {
//        d1 = stopky::now() - zacatek;
//        seminko2 = d1.count();
//    unsigned seminko = d.count();
//    nahodakTaus.seed((stopky::now()-zacatek).count());
        nahodakMersenne.seed(++seminko2);
//    generator.seed(seminko);
//    predchoziCislo = distribution(generator);
        cislo = (float)distribution(nahodakMersenne);
    }
    predchoziCislo = cislo;
    return cislo/777.3f;
}

//template <>
//float nahodneCislo<float>()
//{
//    std::cout << "Pouzita float template specializace." << std::endl;
//    return 0.f;
//}
//auto lambdaFce = [&]() -> float
//    {
//        d1 = stopky::now() - zacatek;
//        seminko2 = d1.count();
//        srand(seminko2);
//        predchoziCislo = rand()/32000.f;
//        return (rand()/32000.f);
//    };

float random()
{
//    float _rndm=0.f;
    //_rndm = abs(sin((timeGetTime() % 360)*(rand()/32767.f)*D3DX_PI/180));
    /*while(_rndm<0.998f)
    {*/
//    while(timeGetTime()%1000>=999) {
//        srand(timeGetTime());
//    }
    //OLD
//    while ( cislo == predchoziCislo )
//    {
//    d1 = stopky::now() - zacatek;
//    seminko2 = d1.count();
//    srand(seminko2);
//    while ( lambdaFce() == predchoziCislo)
//    {
////        lambdaFce();
//    }
//    cislo = (rand()/32000.f == predchoziCislo)? lambdaFce() : rand()/32000.f;
////    }
//    predchoziCislo = cislo;

    return nahodneCislo();
//    return nahodneCislo();
}


int integratePower(int _zakl, float _doMocniny)
{
    int _v = 0;
    int _mv = 1;
    if (_doMocniny <0)
        return 0;
    for(int i = 0; i < _doMocniny; i++)
    {
        for(int x = 0; x < i; x++)
            _mv*=_zakl;
        _v+=_mv;
        _mv=1;
    }
    return _v;
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

void pockej(int t)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(t));
}


}
