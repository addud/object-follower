#ifndef _APP_H_
#define _APP_H_

#include "Screen.h"
#include "ScriptInterface.h"
#include "Sprite.h"
//#include "Timer.h"
#include "Vector.h"

// application to drive the sprite scripting and animation
class App : public ScriptInterface
{
public:
	App();

	void init();
	//run animation actions on the sprites as they call new commands
	virtual void animCommand(Sprite *sprite, int command);
	void runRocks(Sprite *sprite, int command);
	void runNXTLogo(Sprite *sprite, int command);

	void update();

	enum ESpriteID
	{
		eSprite_NXTLogo,
		eSprite_Rocks,
	};

private:

	U8 mCurrentAnim;
	Sprite mNxtOsek;
	Sprite mRocks;
	Screen mScreen;
};

#endif

