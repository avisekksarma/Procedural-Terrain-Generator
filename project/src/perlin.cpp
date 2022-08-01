#include <iostream>
#include "../include/PerlinNoise.hpp"

int main()
{
	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise perlin{seed};
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			const double noise = perlin.octave2D_01((x * 1), (y * 1), 10);

			std::cout << noise << '\t';
		}

		std::cout << '\n';
	}
}