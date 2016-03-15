#pragma once

#include "Bullet.h"
#include "Aim.h"
#include "Background.h"
#include "Gun.h"
#include "DataBase.h"

class MainWidget: public GUI::Widget, public Core::Timer
{
public:
	MainWidget(const std::string& name, rapidxml::xml_node<>* elem);

private:

	void Draw();
	void Update(float dt);

	void AcceptMessage(const Message& message);
	bool MouseDown(const IPoint& mouse_pos);
	void MouseMove(const IPoint& mouse_pos);

	void Init();
	void DrawGameOver();
	void DrawGameWin();

private:

	Render::Texture* _tex1;
	Render::Texture* _bullet;
	Render::Texture*  _gameOver;
	Render::Texture*  _gameWin;

	IRect texBullet;
	IRect texGun;

	Background *back;
	Gun *gun;
	DataBase *data;

	std::vector<Bullet*> bul;
	std::vector<Aim*> aim;

	int _curTex;
	int timer;
	int counter;

	float _scale;
	float _angle;
	float _timer;

	int sound;

	std::vector<int> save;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
};