#pragma once
#include "EventListener.h"

enum AnimationSpriteFinishType {
	ConinuousFinish,
	EndedFinish
};

struct AnimationSpriteFinishEventArgs {
	AnimationSpriteFinishType Type = EndedFinish;
};

class AnimationSpriteFinishEvent :
	public EventListener<AnimationSpriteFinishEventArgs>
{
	public:
		AnimationSpriteFinishEvent();
		virtual ~AnimationSpriteFinishEvent();
};

