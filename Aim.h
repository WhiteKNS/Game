#pragma once

//#include "stdafx.h"

class Aim
{
	public:
		Aim();
	void Draw();
	void Update();

	//void AcceptMessage(const Message& message);

	FRect ReturnAimPoints();

	Render::Texture* _aim;
	//Render::Texture* _tex2;

	IRect texAim;

private:
	//void Init();

	float _timer;

	float _scale;
	float _angle;

	int x;
	int y;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

};