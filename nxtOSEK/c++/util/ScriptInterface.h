#ifndef _SCRIPTINTERFACE_H_
#define _SCRIPTINTERFACE_H_

class Sprite;
class ScriptInterface
{
public:
	virtual ~ScriptInterface(){};
	virtual void animCommand(Sprite *sprite, int command){}
	virtual void atTarget(){}
};

#endif

