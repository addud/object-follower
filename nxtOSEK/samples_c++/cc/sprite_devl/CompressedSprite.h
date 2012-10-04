class Sprite
{
public:
	Sprite(const char* sprite);
	~Sprite();
	char const * const getDecompressedSprite(U8 frameNumber);
private:
	void decompressSprite(U8 frameNumber);

	//compressed data
	char mSentinal;
	U8 mNumFrames;
	U8 mWidth;
	U8 mHeight;
	
	U16 mNumflagBytes;
	char const * mCompressedSprite;
	char const * mCompressedFlags;
	char const * mFrameOffsets;

	//char *mDecompressBuffer;
	char mDecompressBuffer[100];

	//uncompressed data
	U8 mCurrentFrame;

    //1 byte - sentinel value
	//1 byte - num frames
    //1 byte - width
    //1 byte - height
	//1 byte - offset to compressed offset data
    //max 32 bytes for 255 framse for compressed flag bitfield
    //max 512 bytes for data offset into frames

	static const U8 mSentinalIndex = 0;
	static const U8 mNumFramesIndex = 1;
	static const U8 mWidthIndex = 2;
	static const U8 mHeightIndex = 3;
	static const U8 mNumFlagBytes = 4;
	static const U8 mHeaderPad00 = 5;
	static const U8 mStartOfCompressedFlags = 6;

	static const U8 mInvalidFrameNumber = 255;

};

Sprite::Sprite(const char* sprite)
:	mSentinal(sprite[mSentinalIndex])
,	mNumFrames(sprite[mNumFramesIndex])
,	mWidth(sprite[mWidthIndex])
,	mHeight(sprite[mHeightIndex])
,	mCurrentFrame(mInvalidFrameNumber)
{
	//mDecompressBuffer = new char[(mWidth*mHeight)/8];
	//memset(mDecompressBuffer, 0, (mWidth*mHeight)/8);

	mNumflagBytes = sprite[mNumFlagBytes];
	
	mCompressedFlags = &sprite[mStartOfCompressedFlags];

	int bufferOffset = 0;
	bufferOffset += mStartOfCompressedFlags + mNumflagBytes;

	mFrameOffsets = &sprite[bufferOffset];

	bufferOffset = bufferOffset + (mNumFrames * 2);
	mCompressedSprite = &sprite[bufferOffset];
}

Sprite::~Sprite()
{
	//delete [] mDecompressBuffer;
}

char const * const Sprite::getDecompressedSprite(U8 frameNumber)
{
	if(mCurrentFrame != frameNumber)
	{
		decompressSprite(frameNumber);
	}
	return mDecompressBuffer;
}

void Sprite::decompressSprite(U8 frameNumber)
{
	int numCompressedBytes = 0;
	char const *frameToDecompress = 0;

	if(frameNumber == 0)
	{
		numCompressedBytes = reinterpret_cast<const unsigned short*>(mFrameOffsets)[frameNumber];
		frameToDecompress = mCompressedSprite;
	}
	else
	{
		unsigned short nextOffset = reinterpret_cast<const unsigned short*>(mFrameOffsets)[frameNumber];
		unsigned short currentOffset = reinterpret_cast<const unsigned short*>(mFrameOffsets)[frameNumber - 1];

		numCompressedBytes = nextOffset - currentOffset;
		frameToDecompress = &mCompressedSprite[currentOffset];
	}

	if(mCompressedFlags[frameNumber/8] & (1<<frameNumber))
	{
		//decompress the frame
		int i = 0;
		int uncmpBuffer = 0;

		while(i < numCompressedBytes)
		{
			char character = frameToDecompress[i];
			if(mSentinal == character)
			{
				unsigned char numChars = frameToDecompress[i + 1];

				for(int j = 0; j < numChars; ++j)
				{
					if(uncmpBuffer < (mWidth*mHeight)/8)
					{
						mDecompressBuffer[uncmpBuffer++] = frameToDecompress[i + 2];
					}
				}
	 
				i += 3;
			}
			else
			{
				if(uncmpBuffer < (mWidth*mHeight)/8)
				{
					mDecompressBuffer[uncmpBuffer++] = character;
				}
				i++;
			}
		}
	}
	else
	{
		memcpy(mDecompressBuffer, frameToDecompress, (mWidth*mHeight)/8);
	}
}
