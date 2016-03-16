#pragma once

//#include "stdafx.h"

class Aim
{
	public:
		Aim();
	void Draw();
	void Update(float dt);

	FRect ReturnAimPoints();
	Render::Texture* _aim;
	IRect texAim;

private:

	float _timer;

	float _scale;
	float _angle;
	int Arrow;

	int x;
	int y;

	float speed;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

};