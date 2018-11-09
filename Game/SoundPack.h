#pragma once
#include <memory>
#include <string>

#include <SFML/Audio.hpp>

class SoundPack: public sf::Sound, public std::enable_shared_from_this<SoundPack>
{
	public:
		~SoundPack();
		static std::shared_ptr<SoundPack> FromFile(std::string path);

	protected:
		SoundPack(std::shared_ptr<sf::SoundBuffer> buffer);

	private:
		std::shared_ptr<sf::SoundBuffer> m_SoundBuffer = nullptr;
};

