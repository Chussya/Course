#include <cassert>
#include "Constants.h"
#include "SFX.h"

namespace ApplesGame
{
	void InitSounds(SFX& sfx)
	{
		assert(sfx.appleSoundBuf.loadFromFile(RESOURCES_PATH + "AppleEat.wav"));
		assert(sfx.deathSoundBuf.loadFromFile(RESOURCES_PATH + "Death.wav"));
		sfx.eatSound.setBuffer(sfx.appleSoundBuf);
		sfx.deathSound.setBuffer(sfx.deathSoundBuf);
	}

	void PlaySoundUntilEnd(sf::Sound sound)
	{
		sound.play();

		while (sound.getStatus() == sf::Sound::Playing)
		{
			// wait end of...
		}
	}
}