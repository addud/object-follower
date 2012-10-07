#include "App.h"

//the sprite graphics frames
extern const char shiki_intro_spr_start[];
extern const char shiki_walkforward_spr_start[];
extern const char shiki_taunt_spr_start[];
extern const char shiki_breathe_spr_start[];

//the set of all of the sprites
const char* shikiDataSet[] = 
{
	shiki_intro_spr_start,
	shiki_walkforward_spr_start,
	shiki_taunt_spr_start,
	shiki_breathe_spr_start,
};

//anim command come in pairs of 2 (frame number, time in 20msec) or (anim command, parameter)
const char shikiAppearAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,254,0};
const char shikiWalkAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,253,1,0,3,1,3,2,3,3,3,4,3,5,3,255,0};
const char shikiTauntAnim[] = {0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,255,0};
const char shikiBreatheAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,6,3,7,3,8,3,255,0};

//the set of all animations for shiki since we'll be chaining them together
const char* shikiAnimset[] = 
{
	shikiAppearAnim,
	shikiWalkAnim,
	shikiTauntAnim,
	shikiBreatheAnim
};


App::App()
:	mCurrentAnim(0)
,	mShiki(shikiDataSet[0], shikiAnimset[0])
{
	mShiki.setScriptInterface(this);
	mShiki.setID(eSprite_Shiki);
}

void App::init()
{
	mScreen.newSprite(&mShiki);
}

//run animation actions on the sprites as they call new commands
void App::animCommand(Sprite *sprite, int command)
{
	switch(sprite->getID())
	{
		case eSprite_Shiki:
			runShikiAnim(sprite, command);
			break;
	}
}

void App::runShikiAnim(Sprite *sprite, int command)
{
	if(++mCurrentAnim == 4)
	{
		mCurrentAnim = 0;
	}
	sprite->changeGfx(shikiDataSet[mCurrentAnim], shikiAnimset[mCurrentAnim]);
}

void App::update()
{
	mScreen.update();
}

