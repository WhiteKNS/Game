#pragma once
#include "Bul.h"
#include "Aim.h"

class Gun : public GUI::Widget, public Core::Timer
{
public:
	Gun(const std::string& name, rapidxml::xml_node<>* elem);

	void Draw();
	void Update(float dt);

	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);

	void DrawGun();
	void InitField();

private:
	void Init();
	int SaveToGame(std::string current_str);

private:

	Render::Texture* _tex1;
	Render::Texture* _bullet;

	IRect texBullet;
	IRect texGun;

	std::vector<Bul*> bul;
	std::vector<Aim*> aim;

	int _curTex;

	float _scale;
	float _angle;
	float _timer;

	std::vector<int> save;
	EffectsContainer _effCont;
	ParticleEffectPtr _eff;

};