#include "AnimationSprite.h"
#include "SpriteUtils.h"

AnimationSprite::AnimationSprite(
	sf::Vector2f frameStartPosition, 
	sf::Vector2f frameSize, 
	int frameCount, 
	int framePeriod, 
	std::shared_ptr<sf::Texture> texture, 
	std::shared_ptr<std::vector<CommandFunction>> commands)
{
	SetFrameStartPosition(frameStartPosition);
	SetFrameSize(frameSize);
	SetFramePeriod(framePeriod);
	SetFrameCount(frameCount);

	m_FrameCount = frameCount;

	SetTexture(texture);
	m_Commands = commands;

	m_AnimationMutex = std::make_unique<sf::Mutex>();

	SpriteReset = std::make_unique<AnimationSpriteFinishEvent>();
}

AnimationSprite::~AnimationSprite()
{
}

void AnimationSprite::DrawWithControl(std::shared_ptr<Control> control)
{
	std::weak_ptr<AnimationSprite> weak = weak_from_this();

	m_BindedFunction = control->WhenDraw->Then([weak](std::shared_ptr<ControlDrawEventArgs> args) {
		std::shared_ptr<AnimationSprite> shared;
		if (shared = weak.lock()) {
			shared->RunNext();
		}
	});

	m_CurrentBindedControl = control;
}

void AnimationSprite::NextCommand()
{
	if (m_IsTerminated) {
		return;
	}
	if (m_CurrentCommandIndex < (int)m_Commands->size()) {
		m_CurrentCommandIndex++;
	}
	else {
		m_IsTerminated = true;
	}
}

void AnimationSprite::Reset()
{
	if (!m_IsTerminated) {
		SendEndedFinishSignal();
	}

	m_IsTerminated = false;

	SetCurrentFrameIndex(0);
	m_CurrentCommandIndex = 0;
}

void AnimationSprite::End()
{
	m_IsTerminated = true;
}

bool AnimationSprite::CountDelay()
{
	if (m_IsTerminated) {
		return false;
	}

	if (m_DelayCount <= 0) {
		return true;
	}

	m_DelayCount--;
	return false;
}

void AnimationSprite::SendEndedFinishSignal()
{
	auto args = std::make_shared<AnimationSpriteFinishEventArgs>();
	args->Type = EndedFinish;

	SendFinishSignal(args);
}

void AnimationSprite::SendContinuousFinishSignal()
{
	auto args = std::make_shared<AnimationSpriteFinishEventArgs>();
	args->Type = ConinuousFinish;

	SendFinishSignal(args);
}

void AnimationSprite::SendFinishSignal(std::shared_ptr<AnimationSpriteFinishEventArgs> args)
{
	SpriteReset->Emit(args);
}

bool AnimationSprite::IsTerminated()
{
	return m_IsTerminated;
}

bool AnimationSprite::NextFrame()
{
	if (!m_IsTerminated && GetCurrentFrameIndex() == GetFrameCount() - 1) {
		m_IsTerminated = true;
		SendEndedFinishSignal();
	}

	if (m_IsTerminated) {
		return false;
	}

	SetCurrentFrameIndex(GetCurrentFrameIndex() + 1);
	return true;
}

bool AnimationSprite::RunNext()
{
	sf::Lock Lock(*m_AnimationMutex);

	if (m_IsTerminated) {
		return false;
	}

	if (m_Commands->size() <= (int)m_CurrentCommandIndex) {
		return false;
	}

	m_Commands->at(m_CurrentCommandIndex)(shared_from_this());

	return true;
}


void AnimationSprite::SetCurrentFrameIndex(int frameIndex)
{
	if (frameIndex >= m_FrameCount || frameIndex < 0) {
		throw "E_OUTOFRANGE frameIndex is not in acceptable range.";
	}

	m_CurrentFrameIndex = frameIndex;
	m_DelayCount = m_FramePeriod;

	ApplyTextureRect();
}

int AnimationSprite::GetCurrentFrameIndex()
{
	return m_CurrentFrameIndex;
}

int AnimationSprite::GetFrameCount()
{
	return m_FrameCount;
}

std::shared_ptr<SpriteControlModifier> AnimationSprite::GetModifier()
{
	std::shared_ptr<Control> binded = m_CurrentBindedControl.lock();

	if (binded) {
		return SpriteControlModifier::For(shared_from_this())
			->BindWithControl(binded);
	}
	else {
		return SpriteControlModifier::For(shared_from_this());
	}
}

void AnimationSprite::SetTexture(std::shared_ptr<sf::Texture> texture)
{
	m_Texture = texture;
	sf::Sprite::setTexture(*m_Texture);
}

void AnimationSprite::SetFrameStartPosition(sf::Vector2f startPosition)
{
	m_FrameStartPosition = startPosition;
}

void AnimationSprite::SetFrameSize(sf::Vector2f frameSize)
{
	m_FrameSize = frameSize;
}

void AnimationSprite::SetFramePeriod(int period)
{
	if (period <= 0) {
		throw "E_OUTOFRANGE period is out of range";
	}

	m_FramePeriod = period;
}

void AnimationSprite::SetFrameCount(int frameCount)
{
	if (frameCount <= 0) {
		throw "E_OUTOFRANGE frameCount can't be equals to or less than 0";
	}

	m_FrameCount = frameCount;
}

void AnimationSprite::ApplyTextureRect()
{
	m_TextureRect.left = (int)(m_FrameStartPosition.x + m_FrameSize.x * (float)m_CurrentFrameIndex);
	m_TextureRect.top = (int)m_FrameStartPosition.y;

	m_TextureRect.width = (int)m_FrameSize.x;
	m_TextureRect.height = (int)m_FrameSize.y;

	sf::Sprite::setTextureRect(m_TextureRect);
}
