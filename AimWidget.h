#pragma once

//#include "stdafx.h"


class AimWidget : public GUI::Widget
{
public:
	AimWidget(const std::string& name, rapidxml::xml_node<>* elem);
	
	void Draw();
	void Update(float dt);

	void AcceptMessage(const Message& message);

	IRect ReturnAimPoints();

private:
	void Init();

	float _timer;

	float _scale;
	float _angle;

	Render::Texture* _tex1;
	//Render::Texture* _tex2;

	IRect texRect;
	int _curTex;

	int x;
	int y;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
};