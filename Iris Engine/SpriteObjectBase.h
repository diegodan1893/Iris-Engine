#pragma once

#include"Object.h"

class SpriteObjectBase : public Object
{
public:
	SpriteObjectBase(int zindex);
	virtual ~SpriteObjectBase();

protected:
	

private:
	bool isValid;
};