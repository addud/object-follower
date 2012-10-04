#ifndef _SPRITE_H_
#define _SPRITE_H_

#ifndef _MSC_VER
	extern "C" {
	#include "ecrobot_interface.h"
	#include "kernel.h"
	#include "nxt_avr.h"
	};
#else
	#include "Types.h"
#endif

#include "ScriptInterface.h"
#include "Vector.h"


#define SPITE_HEADER_SIZE 3

class Sprite
{
public:
	enum EAnimCommand
	{
		eAnimCommand_Move = 252,
		eAnimCommand_Trait = 253,
		eAnimCommand_Stop = 254,
		eAnimCommand_LoopToAnimFrame = 255,

		eAnimCommand_Start = eAnimCommand_Move,
	};

	enum ETrait
	{

		eTrait_HFlip,
		eTrait_VFlip,
		eTrait_Invert,
		eTrait_Transparent
	};

	Sprite();
	Sprite(char const * const sprite, char const * const animation = 0, VectorT<S8> position = VectorT<S8>(0,0), bool hflip = false, bool vflip = false, bool invert = false, bool trans = false);
	void changeGfx(char const * const sprite, char const * const animation)
	{
		mWidth = sprite[0];
		mHeight = sprite[1];
		mNumFrames = sprite[2];

		mCurrentAnim = 0;
		mCurrentFrame = 0;
		mCurrentTime = 0;
		mSpritePtr = sprite + SPITE_HEADER_SIZE;
		mAnimPtr = animation;
	}
	void update();

	char const * const getCurrentFramePtr() const;
	char const * const getFramePtr(U8 frameNumber) const;

	U8 getWidth() const { return mWidth; }
	U8 getHeight() const { return mHeight; }

	bool frameIsRenderable() const { return  mCurrentFrame < mNumFrames; }
	bool getHFlip() const { return static_cast<bool>(mTraits & (1<<eTrait_HFlip)); }
	bool getVFlip() const { return static_cast<bool>(mTraits & (1<<eTrait_VFlip)); }
	bool getInvert() const { return static_cast<bool>(mTraits & (1<<eTrait_Invert)); }
	bool getTransparent() const { return static_cast<bool>(mTraits & (1<<eTrait_Transparent)); }
	S8 getID() const { return mID; }
	void setID(S8 id) { mID = id; } 

	void setTrait(ETrait trait) { mTraits |= (1 << trait); }
	void setTraits(U8 traits) { mTraits = traits; }
	void clearTrait(ETrait trait) { mTraits &= ~(1 << trait); }
	void clearAllTraits() { mTraits = 0; }
	//void setCallback(CallbackFunc func) { mFunc = func; }
	void setScriptInterface(ScriptInterface *scriptInterface) { mInterface = scriptInterface; }

	VectorT<S8> getPosition() const { return mPosition; }

	void setPosition(VectorT<S8> position);
	void moveBy(VectorT<S8> direction) { mPosition += direction; }
	void moveTo(VectorT<S8> target) {}
	U16 getSptiteByteCount() const;

private:
	void setNextAnimFrame();

	U8 mWidth;
	U8 mHeight;
	U8 mNumFrames;
	U8 mTraits;

	U8 mCurrentAnim;
	U8 mCurrentFrame;
	U8 mCurrentTime;
	S8 mID;

	VectorT<S8> mPosition;

	char const *mSpritePtr;
	char const *mAnimPtr;

	ScriptInterface *mInterface;
};

#endif


