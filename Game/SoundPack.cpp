#include "SoundPack.h"

SoundPack::~SoundPack()
{
}

std::shared_ptr<SoundPack> SoundPack::FromFile(std::string path)
{
	std::shared_ptr<sf::SoundBuffer> buffer = std::make_shared<sf::SoundBuffer>();
	buffer->loadFromFile(path);

	return std::shared_ptr<SoundPack>(new SoundPack(buffer));
}

SoundPack::SoundPack(std::shared_ptr<sf::SoundBuffer> buffer) : sf::Sound(*buffer)
{
	m_SoundBuffer = buffer;
}
