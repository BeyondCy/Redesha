/*
-----------------------------------------------------------------------------
Filename:    GameApplication.h
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#ifndef __GameApplication_h_
#define __GameApplication_h_

#include "baseapplication.h"

class GameApplication : public BaseApplication
{
public:
    GameApplication(void);
    virtual ~GameApplication(void);

protected:
    virtual void createScene(void);
};

#endif // #ifndef __GameApplication_h_
