#ifndef __ENGINE_H_INCLUDED__
#define __ENGINE_H_INCLUDED__

namespace se
{

class Engine
{
public:
    Engine();
    static void prepareD3D();
    static void prepareInputDevices();
    ~Engine();
protected:
private:
};

}

#endif // __ENGINE_H_INCLUDED__

