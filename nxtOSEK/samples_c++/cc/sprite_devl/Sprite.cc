#include "Sprite.h"


Sprite::Sprite()
:	mWidth(0)
,	mHeight(0)
,	mNumFrames(0)
,	mTraits(0)
,	mCurrentAnim(0)
,	mCurrentFrame(0)
,	mCurrentTime(0)
,	mID(-1)
,	mSpritePtr(0)
,	mAnimPtr(0)
,	mInterface((ScriptInterface*)0)
{
}

Sprite::Sprite(char const * const sprite, char const * const animation, VectorT<S8> position, bool hflip, bool vflip, bool invert, bool trans)
:	mWidth(sprite[0])
,	mHeight(sprite[1])
,	mNumFrames(sprite[2])
,	mTraits(0)
,	mCurrentAnim(0)
,	mCurrentFrame(0)
,	mCurrentTime(0)
,	mID(-1)
,	mPosition(position)
,	mSpritePtr(sprite + SPITE_HEADER_SIZE)
,	mAnimPtr(animation)
,	mInterface((ScriptInterface*)0)
{
	//ensures that the value is either 0 or 1 (U8 bool)
	hflip = !!hflip;
	vflip = !!vflip;
	invert = !!invert;
	trans = !!trans;

	//set the traits for this sprite, they are only meaningful at render time
	mTraits = (hflip*(1<<eTrait_HFlip)) | (vflip*(1<<eTrait_VFlip)) | (invert*(1<<eTrait_Invert)) | (trans*(1<<eTrait_Transparent));
}

void Sprite::update()
{
	//go to the next frame
	if((mCurrentTime--) == 0)
	{
		setNextAnimFrame();
	}
}

char const * const Sprite::getCurrentFramePtr() const
{
	//return a pointer to the current frame
	U16 offset = mCurrentFrame * (mWidth * mHeight)/8;
	return &(mSpritePtr[offset]);
}

U16 Sprite::getSptiteByteCount() const
{
	//return the number of bytes in a frame
	return mWidth * mHeight;
}

void Sprite::setPosition(VectorT<S8> position) { mPosition = position; }

void Sprite::setNextAnimFrame()
{
	if(!mAnimPtr)
	{
		return;
	}

	mCurrentFrame = mAnimPtr[mCurrentAnim];
	mCurrentTime = mAnimPtr[mCurrentAnim + 1];

	//check this frame and see if it is really a command. If so, execute command code and call the script object
	//to let it know about the command
	switch(mCurrentFrame)
	{
	case eAnimCommand_Move:
		if(mInterface)
		{
			mInterface->animCommand(this, eAnimCommand_Move);
		}
		break;

	case eAnimCommand_Trait:
		setTraits(mAnimPtr[mCurrentAnim + 1]);
		break;

	case eAnimCommand_Stop:
		if(mInterface)
		{
			mInterface->animCommand(this, eAnimCommand_Stop);
		}
		else
		{
			//don't allow the current frame to be displayed (it's a command frame)
			mCurrentAnim -= 2;
			mCurrentFrame = mAnimPtr[mCurrentAnim];
			mCurrentTime = mAnimPtr[mCurrentAnim + 1];
		}
		return;
		break;

	case eAnimCommand_LoopToAnimFrame:
		mCurrentAnim = mAnimPtr[mCurrentAnim + 1];
		mCurrentFrame = mAnimPtr[mCurrentAnim];
		mCurrentTime = mAnimPtr[mCurrentAnim + 1];

		if(mInterface)
		{
			mInterface->animCommand(this, eAnimCommand_LoopToAnimFrame);
		}
	
		//the anim has been set so don't increment it
		return;
		break;
	}

	//anim command come in pairs of 2 (frame number, time) or (anim command, parameter)
	mCurrentAnim += 2;
}


