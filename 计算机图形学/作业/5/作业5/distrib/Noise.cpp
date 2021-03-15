#include "Noise.h"
#include "PerlinNoise.h"




Vector3f Noise::getColor(const Vector3f & pos)
{
	//Fill in this function  ONLY.
	//INTERPOLATE BETWEEN TWO COLORS BY WEIGHTED AVERAGE
	double N=PerlinNoise::octaveNoise(pos, octaves);
	double M = sin(frequency*pos.x() + amplitude*N);
	//double M = sin(frequency*pos.y() + amplitude * N);

	return M*color[0]+ (1-M)*color[1];
	//return Vector3f(1,1,1);
}

Noise::Noise(int _octaves,const Vector3f & color1, 
	 const Vector3f &color2,float freq,float amp):
octaves(_octaves),frequency(freq),amplitude(amp){
	color[0] = color1;
	color[1] = color2;
	init = true;
}

Noise::Noise(const Noise & n):
octaves(n.octaves),frequency(n.frequency),
	amplitude(n.amplitude),init(n.init)
{
	color[0] = n.color[0];
	color[1] = n.color[1];
}

bool Noise::valid()
{
	return init;
}

Noise::Noise():
octaves(0),init(false)
{}
