#pragma once


class Background
{
public:
	Background();

	void Draw();
	//void Update(float dt);

private:

	Render::Texture* _tex1;

	float _timer;
};

/*
class Background
{
public:
	Background();

	void Draw();

private:

	Render::Texture* _tex1;

	float _timer;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

};*/