#include <windows.h>

namespace sw
{

struct rozmery {
public:
    float x;
    float y;
    rozmery(float _x = 320, float _y = 480)
    {
        x=_x;
        y=_y;
    }
};

struct pozice{
public:
    int x, y;
    pozice(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};


class Okno
{
public:
    Okno(pozice, rozmery, LPCWSTR);
    ~Okno();
    static void init();
protected:
private:
};

}
