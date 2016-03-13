#pragma once


class Background: public GUI::Widget
{
public:
	Background(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw();
	void Update(float dt);

private:

	Render::Texture* _tex1;

	float _timer;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
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