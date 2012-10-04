#include "App.h"

#ifndef _MSC_VER
//the sprite graphics frames
extern const char shiki_intro_spr_start[];
extern const char shiki_walkforward_spr_start[];
extern const char shiki_taunt_spr_start[];
extern const char shiki_breathe_spr_start[];
extern const char nxtOSEK_spr_start[];
extern const char rocks_spr_start[];
extern const char backdrop_spr_start[];
#else
#include <iostream>
#include <fstream>
#include <string>

char *shiki_intro_spr_start;
char *shiki_walkforward_spr_start;
char *shiki_taunt_spr_start;
char *shiki_breathe_spr_start;
char *nxtOSEK_spr_start;
char *rocks_spr_start;
char *backdrop_spr_start;
char *sqr_spr_start;
#pragma warning (disable : 4309)

using namespace std;
#endif

//the set of all of the sprites
const char* shikiDataSet[] = 
{
	shiki_intro_spr_start,
	shiki_walkforward_spr_start,
	shiki_taunt_spr_start,
	shiki_breathe_spr_start,
};

//the animation indexes and timing
#ifndef _MSC_VER
//anim command come in pairs of 2 (frame number, time in 20msec) or (anim command, parameter)
const char shikiAppearAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,254,0};
const char shikiWalkAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,253,1,0,3,1,3,2,3,3,3,4,3,5,3,255,0};
const char shikiTauntAnim[] = {0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,0,3,1,3,2,3,255,0};
const char shikiBreatheAnim[] = {0,3,1,3,2,3,3,3,4,3,5,3,6,3,7,3,8,3,255,0};
#else
const char shikiAppearAnim[] = {0,60,1,60,2,60,3,60,4,60,5,60,254,0};
const char shikiWalkAnim[] = {0,60,1,60,2,60,3,60,4,60,5,60,253,1,0,60,1,60,2,60,3,60,4,60,5,60,255,0};
const char shikiTauntAnim[] = {0,60,1,60,2,60,0,60,1,60,2,60,0,60,1,60,2,60,0,60,1,60,2,60,0,60,1,60,2,60,255,0};
const char shikiBreatheAnim[] = {0,60,1,60,2,60,3,60,4,60,5,60,6,60,7,60,8,60,255,0};
#endif

const char nxtLogoAnim[] = {0, 1, 252,0, 255, 0};
const char rocksAnim[] = {0, 1, 252,0, 255, 0};

//the set of all animations for shiki since we'll be chaining them together
const char* shikiAnimset[] = 
{
	shikiAppearAnim,
	shikiWalkAnim,
	shikiTauntAnim,
	shikiBreatheAnim
};

#ifdef _MSC_VER
static char* loadAnim(const std::string path)
{
	ifstream file (path.c_str(), ios::in|ios::binary|ios::ate);
	if (file.is_open())
	{
		int size = file.tellg();
		char *memblock = new char [size];
		file.seekg (0, ios::beg);
		file.read (memblock, size);
		file.close();

		return memblock;
	}

	return NULL;
}
#endif

char spriteRoot[] = "C:\\Users\\Jon\\Documents\\nxtOSEK\\samples\\sprite\\";

App::App()
:	mCurrentAnim(0)
#ifndef _MSC_VER
,	mShiki(shikiDataSet[0], shikiAnimset[0])
,	mNxtOsek(nxtOSEK_spr_start, nxtLogoAnim)
,	mRocks(rocks_spr_start, rocksAnim)
,	mBackDrop(backdrop_spr_start, (const char*)null)
#endif
{
#ifdef _MSC_VER
	shikiDataSet[0] = loadAnim(std::string(spriteRoot) + std::string("shiki_intro.spr"));
	shikiDataSet[1] = loadAnim(std::string(spriteRoot) + std::string("shiki_walkforward.spr"));
	shikiDataSet[2] = loadAnim(std::string(spriteRoot) + std::string("shiki_taunt.spr"));
	shikiDataSet[3] = loadAnim(std::string(spriteRoot) + std::string("shiki_breathe.spr"));
	nxtOSEK_spr_start = loadAnim(std::string(spriteRoot) + std::string("nxtOSEK.spr"));
	rocks_spr_start = loadAnim(std::string(spriteRoot) + std::string("rocks.spr"));
	backdrop_spr_start = loadAnim(std::string(spriteRoot) + std::string("backdrop.spr"));
	
	mBackDrop.changeGfx(backdrop_spr_start, 0);
	mShiki.changeGfx(shikiDataSet[0], shikiAnimset[0]);
	mNxtOsek.changeGfx(nxtOSEK_spr_start, nxtLogoAnim);
	mRocks.changeGfx(rocks_spr_start, rocksAnim);
	mSqr.changeGfx(sqr_spr_start, NULL);

#endif
	mShiki.setScriptInterface(this);
	mShiki.setID(eSprite_Shiki);

	mNxtOsek.setID(eSprite_NXTLogo);
	mNxtOsek.setScriptInterface(this);

	mRocks.setID(eSprite_Rocks);
	mRocks.setScriptInterface(this);
}

void App::init()
{
	mScreen.newSprite(&mBackDrop);
	mScreen.newSprite(&mShiki);
	mScreen.newSprite(&mNxtOsek);
	mScreen.newSprite(&mRocks);
}

//run animation actions on the sprites as they call new commands
void App::animCommand(Sprite *sprite, int command)
{
	switch(sprite->getID())
	{
		case eSprite_Shiki:
			runShikiAnim(sprite, command);
			break;

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
	if(command == Sprite::eAnimCommand_Move /*&& mTimer.tick()*/)
	{
		sprite->moveBy(VectorT<S8>(1, 0));
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

void App::runNXTLogo(Sprite *sprite, int command)
{
	if(command == Sprite::eAnimCommand_Move /*&& mTimer.tick()*/)
	{
		sprite->moveBy(VectorT<S8>(-1, 0));
	}
}

void App::update()
{
	mScreen.update();
}

