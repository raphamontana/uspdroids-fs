#ifndef ENGINE_H
#define ENGINE_H

#include "../worldmodel.h"

/**
 *
 */
class Engine
{

public:

    /**
     *
     */
    Engine();

    /**
     *
     */
    void setWheelsSpeed(WorldModel wm);

    /**
     *
     */
    WorldModel getWorldModel();

};

#endif // ENGINE_H
