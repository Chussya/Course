#pragma once
#include <SFML/Audio.hpp>

namespace ApplesGame
{
	struct SFX
	{
		sf::SoundBuffer appleSoundBuf{};
		sf::Sound eatSound{};
		sf::SoundBuffer deathSoundBuf{};
		sf::Sound deathSound{};
	};

	void InitSounds(SFX& sfx);

	void PlaySoundUntilEnd(sf::Sound sound);
}