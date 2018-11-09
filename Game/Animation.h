#pragma once
#include <functional>
#include "AnimationSprite.h"

namespace Animation {
	AnimationSprite::CommandFunction Repeat();
	AnimationSprite::CommandFunction Once();

	AnimationSprite::CommandFunction Static(int frame);
}
