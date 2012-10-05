#include "App.h"

//the sprite graphics frames
extern const char nxtOSEK_spr_start[];
extern const char rocks_spr_start[];

//anim command come in pairs of 2 (frame number, time in 20msec) or (anim command, parameter)
const char nxtLogoAnim[] = {0,1, Sprite::eAnimCommand_Move,0, Sprite::eAnimCommand_LoopToAnimFrame,0};
const char   rocksAnim[] = {0,1, Sprite::eAnimCommand_Move,0, Sprite::eAnimCommand_LoopToAnimFrame,0};


App::App()
:	mCurrentAnim(0)
,	mNxtOsek(nxtOSEK_spr_start, nxtLogoAnim)
,	mRocks(rocks_spr_start, rocksAnim)
{
	mNxtOsek.setID(eSprite_NXTLogo);
	mNxtOsek.setScriptInterface(this);

	mRocks.setID(eSprite_Rocks);
	mRocks.setScriptInterface(this);
}

void App::init()
{
	mScreen.newSprite(&mNxtOsek);
	mScreen.newSprite(&mRocks);
}

//run animation actions on the sprites as they call new commands
void App::animCommand(Sprite *sprite, int command)
{
	switch(sprite->getID())
	{
		case eSprite_NXTLogo:
			runNXTLogo(sprite, command);
			break;

		case eSprite_Rocks:
			runRocks(sprite, command);
			break;
	}
}

void App::runRocks(Sprite *sprite, int command)
{
	if(command == Sprite::eAnimCommand_Move)
	{
		sprite->moveBy(VectorT<S8>(1, 0)); /* move horizontally */
	}
}

void App::runNXTLogo(Sprite *sprite, int command)
{
	if(command == Sprite::eAnimCommand_Move)
	{
		sprite->moveBy(VectorT<S8>(0, 1)); /* move vertically */
	}
}

void App::update()
{
	mScreen.update();
}

