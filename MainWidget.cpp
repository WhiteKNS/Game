
#include "stdafx.h"

#include "MainWidget.h"
#include "Bullet.h"
#include "Background.h"
#include "Aim.h"
#include "DataBase.h"
#include "Gun.h"

enum MODE{BULLET_NOT_EXISTS=0,  MOUSE_PRESS, BULLET_EXIST, GAME_OVER, GAME_WIN};

MainWidget::MainWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	,_scale(0)
	,_angle(0)
	, _eff(NULL)
	,_timer(0)
{
	Init();
}

void MainWidget::Init()
{
	MM::manager.PlaySample("Arkanoid", true);
	back = new Background();
	for (unsigned int i = 0; i < 5; ++i)
	bul.push_back(new Bullet());
	data = new DataBase();
	data->InitField();
	gun = new Gun();
	for (int i = 0; i < data->GetTarget(); ++i)
		aim.push_back(new Aim());

	bul.at(0)->Speed = data->GetSpeed();
	bul.at(0)->texBullet.y = -150;
	
	counter = 0;
	_gameOver = Core::resourceManager.Get<Render::Texture>("Over");
	_gameWin = Core::resourceManager.Get<Render::Texture>("Win");
	_curTex = 0;
	
	Core::Timer::Start();
	timer = data->GetTime()+Core::Timer::getElapsedTime();

	music_counter = 0;
}

void MainWidget::DrawGameOver()
{
	Render::device.PushMatrix();

	IRect texOver = _gameOver->getBitmapRect();
	FRect rect(texOver);
	FRect uv(0, 1, 0, 1);
	_gameOver->TranslateUV(rect, uv);
	Render::device.MatrixTranslate(-150, 1, 0.0f);
	Render::device.MatrixScale(0.5);
	_gameOver->Bind();
	Render::DrawRect(rect, uv);
	Render::BindFont("arial");
	Render::PrintString(1024 / 2 + 700, 768-150, std::string("You hit: ") + utils::lexical_cast(counter) + std::string(" aims\n Push any key to restart"), 5.0f, CenterAlign);
	Render::device.PopMatrix();
}

void MainWidget::DrawGameWin()
{
	Render::device.PushMatrix();
	IRect texWin = _gameWin->getBitmapRect();
	FRect rect(texWin);
	FRect uv(0, 1, 0, 1);
	_gameWin->TranslateUV(rect, uv);
	Render::device.MatrixTranslate(0, -20, 0.0f);
	Render::device.MatrixScale(2.3);
	_gameWin->Bind();
	Render::DrawRect(rect, uv);
	Render::device.PopMatrix();
}


void MainWidget::Collision()
{
	for (unsigned int i = 0; i < aim.size(); ++i)
	{
		FRect gunRect(bul[0]->texBullet);

		gunRect.xStart = bul[0]->texBullet.x + bul[0]->texBullet.Width() / 2;
		gunRect.xEnd = bul[0]->texBullet.x + bul[0]->texBullet.Width() / 2 ;
		gunRect.yStart = bul[0]->texBullet.y - bul[0]->texBullet.height/2;
		gunRect.yEnd = bul[0]->texBullet.y - bul[0]->texBullet.height / 2;

		if (gunRect.Intersects(aim.at(i)->ReturnAimPoints()))
		{
			MM::manager.PlaySample("BonusStar");
			_eff->Finish();
			_eff = _effCont.AddEffect("FindCoin2");

			_eff->posX = bul[0]->texBullet.x * 2 - bul[0]->texBullet.height;
			_eff->posY = bul[0]->texBullet.y * bul[0]->texBullet.width / 3 + bul[0]->texBullet.height * 3;
			_eff->Reset();
			aim.erase(aim.begin() + i);
			counter++;
			if (aim.empty())
			{
				_curTex = GAME_WIN;
			}
			else _curTex = BULLET_EXIST;
		}
	}
}


void MainWidget::Draw()
{
	Render::BindFont("Magneto-Bold");
	int dy = Render::getFontHeight();
	int x = Render::device.Width() - 100;
	int y = Render::device.Height() - 200;

	back->Draw();
	if (_curTex == GAME_OVER)
	{
		DrawGameOver();
	}
	if (_curTex == GAME_WIN)
	{
		DrawGameWin();
	}
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	Render::device.PushMatrix();
	for (unsigned int i = 0; i < aim.size(); ++i) 
	{
		aim.at(i)->Draw();
	}
	Render::device.PopMatrix();
	if (_curTex != GAME_OVER&&_curTex != GAME_WIN)
	{
		Render::device.PushMatrix();
		gun->Draw();
		Render::device.PopMatrix();
	}
	if (_curTex==MOUSE_PRESS)
	{
		Render::device.PushMatrix();
		bul[0]->Draw();
		Render::device.PopMatrix();
	}
	if (_curTex == BULLET_EXIST)
	{
		_curTex = BULLET_NOT_EXISTS;
	}
	
	Collision();

		if (_curTex != GAME_OVER&&_curTex!=GAME_WIN)
		{
			Render::BindFont("Magneto-Bold");
		Render::PrintString(924 + 100 / 2, 35, std::string("Time: ") + utils::lexical_cast((int)getElapsedTime()), 1.f, CenterAlign);
		Render::BindFont("arial");
		x = Render::device.Width() - 5;
		y = Render::device.Height() - 20;
		Render::PrintString(x, y, std::string("Aims: ") + utils::lexical_cast(aim.size()), 1.5f, RightAlign, BottomAlign);
		}
	_effCont.Draw();
}


void MainWidget::Update(float dt)
{
	_effCont.Update(dt);
	_timer += dt * 100;

	while (_timer >100 * math::PI)
	{
		_timer -= 100* math::PI;
	}
	if (_curTex == GAME_WIN)
	{
		if (++music_counter <= 1)
		{
			MM::manager.StopAll();
			MM::manager.PlaySample("Win");
		}
	}
	if (_curTex != GAME_WIN && _curTex != GAME_OVER)
	{
		if (getElapsedTime() >= timer)
		{
			_curTex = GAME_OVER;
		}
	}
	for (unsigned int i = 0; i < aim.size(); ++i)
	{
		aim.at(i)->Update(dt);
	}
	if (_curTex == MOUSE_PRESS) {
	
		if (bul[0]->Update(dt))
		{
			_curTex = BULLET_NOT_EXISTS;
			bul[0]->texBullet.y = -100;
		}
		else
		{
			_eff->posX = bul[0]->texBullet.x * 2 ;
			_eff->posY = bul[0]->texBullet.y * bul[0]->texBullet.width / 3 ;
		}
	}
	if (_curTex == BULLET_NOT_EXISTS)
	{
		bul[0]->texBullet.y = -100;
	}
	if (_curTex == GAME_WIN||_curTex == GAME_OVER)
	{	
		aim.clear();
		if (_eff) _eff->Kill();
		_eff = NULL;
		Core::Timer::Pause();
	}
}


bool MainWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_curTex == BULLET_NOT_EXISTS)
		{
			_curTex = MOUSE_PRESS;
			Render::device.PushMatrix();
			IPoint mouse_pos = Core::mainInput.GetMousePos();
			Render::device.PopMatrix();
				bul.at(0)->texBullet.x = (float)mouse_pos.x*0.5 + 15;
				bul.at(0)->texBullet.y = 15;
				MM::manager.PlaySample("Boom");
				_eff = _effCont.AddEffect("BulletTrace");
				_eff->posX = bul[0]->texBullet.x;
				_eff->posY = bul[0]->texBullet.y;
		}
	}
	return false;
}

void MainWidget::AcceptMessage(const Message& message)
{
	if (message.getPublisher() == "KeyPress")
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			return;
		}

		else
		{
			if (_curTex == GAME_OVER || _curTex == GAME_WIN)
			{
				delete back;
				delete data;
				delete gun;
				for (unsigned int i = 0; i < bul.size(); ++i)
					bul.erase(bul.begin() + i);
				bul.clear();
				if (!aim.empty()) {
					for (unsigned int i = 0; i < aim.size(); ++i)
						aim.erase(aim.begin() + i);
				}
				aim.clear();
				counter = -1;
				if (_eff) _eff->Kill();;
				_eff = NULL;
				MM::manager.StopAll();
				Init();
			}
		}
	}
}
