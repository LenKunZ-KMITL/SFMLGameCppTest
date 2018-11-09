#include <memory>
#include "Animation.h"

AnimationSprite::CommandFunction Animation::Repeat()
{
	return [](std::shared_ptr<AnimationSprite> sprite)
	{
		if (!sprite->CountDelay()) {
			return;
		}

		if (sprite->GetCurrentFrameIndex() == sprite->GetFrameCount() - 1) {
			sprite->SetCurrentFrameIndex(0);
			sprite->SendContinuousFinishSignal();
			return;
		}

		sprite->NextFrame();
	};
}

AnimationSprite::CommandFunction Animation::Once()
{
	return [](std::shared_ptr<AnimationSprite> sprite)
	{
		if (!sprite->CountDelay()) {
			return;
		}

		sprite->NextFrame();
	};
}

AnimationSprite::CommandFunction Animation::Static(int frame)
{
	return [frame](std::shared_ptr<AnimationSprite> sprite)
	{
		if (sprite->GetCurrentFrameIndex() != frame) {
			sprite->SetCurrentFrameIndex(frame);
		}

		if (sprite->CountDelay()) {
			sprite->SendContinuousFinishSignal();
		}
	};
}
