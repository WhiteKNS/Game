
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
	back = new Background();// init background


	data = new DataBase(); //init database(reading from the file)
	data->InitField();
	gun = new Gun();
	for (int i = 0; i < data->GetTarget(); ++i) //set aims
		aim.push_back(new Aim());

	counter = 0; //counter of points
	_gameOver = Core::resourceManager.Get<Render::Texture>("Over");
	_gameWin = Core::resourceManager.Get<Render::Texture>("Win");
	_curTex = 0;
	
	Core::Timer::Start();
	timer = data->GetTime()+Core::Timer::getElapsedTime(); //get time

	music_counter = 0;
}

void MainWidget::DrawGameOver() //this method draw the "Game over" field
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

void MainWidget::DrawGameWin() //sraw the "game win field"
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


void MainWidget::Collision()//  check, if collision exists
{
	if (!bul.empty())
	{
		for (unsigned int i = 0; i < aim.size(); ++i)
		{
			FRect gunRect(bul[0]->texBullet);

			gunRect.xStart = bul[0]->texBullet.x + bul[0]->texBullet.Width() / 2;
			gunRect.xEnd = bul[0]->texBullet.x + bul[0]->texBullet.Width() / 2;
			gunRect.yStart = bul[0]->texBullet.y + bul[0]->texBullet.height / 2;
			gunRect.yEnd = bul[0]->texBullet.y + bul[0]->texBullet.height / 2;

			if (gunRect.Intersects(aim.at(i)->ReturnAimPoints())) //if collision exists, play sound, delete bullet and checking end of the game
			{
				MM::manager.PlaySample("BonusStar");

				if(_eff) _eff->Kill();
				_eff = _effCont.AddEffect("FindCoin2");

				_eff->posX = bul[0]->texBullet.x * 2 + bul[0]->texBullet.height / 2;
				_eff->posY = bul[0]->texBullet.y * bul[0]->texBullet.width / 3;
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
}


void MainWidget::Draw()
{
	Render::BindFont("Magneto-Bold");
	int dy = Render::getFontHeight();
	int x = Render::device.Width() - 100;
	int y = Render::device.Height() - 200;

	back->Draw();
	if (_curTex == GAME_OVER) //if game over
	{
		DrawGameOver();
	}
	if (_curTex == GAME_WIN) //if game win
	{
		DrawGameWin();
	}
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	for (unsigned int i = 0; i < aim.size(); ++i) //draw aims
	{
		Render::device.PushMatrix();
		aim.at(i)->Draw();
		Render::device.PopMatrix();
	}
	
	if (_curTex != GAME_OVER&&_curTex != GAME_WIN) //draw the gun
	{
		Render::device.PushMatrix();
		gun->Draw();
		Render::device.PopMatrix();
	}
	if (_curTex==MOUSE_PRESS) //draw bullet
	{
		Render::device.PushMatrix();

		bul[0]->Draw();
		Render::device.PopMatrix();
	}
	if (_curTex == BULLET_EXIST)
	{
		_curTex = BULLET_NOT_EXISTS;
	}
	
	Collision(); //check if collision exists

		if (_curTex != GAME_OVER&&_curTex!=GAME_WIN)// draw game info
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
			MM::manager.StopAll();// if win, download new music
			MM::manager.PlaySample("Win");
		}
	}
	if (_curTex != GAME_WIN && _curTex != GAME_OVER)
	{
		if (getElapsedTime() >= timer) //if time elapse - Game over
		{
			_curTex = GAME_OVER;
		}
	}
	for (unsigned int i = 0; i < aim.size(); ++i)
	{
		aim.at(i)->Update(dt); //updating aims
	}
	if (_curTex == MOUSE_PRESS) {
	
		if (bul[0]->Update(dt)) //if bullet out  the field
		{
			bul.erase(bul.begin());
			bul.clear();
			_curTex = BULLET_NOT_EXISTS;
		}
	}
	if (_curTex == BULLET_NOT_EXISTS)
	{
		bul.clear();
	}
	if (_curTex == GAME_WIN||_curTex == GAME_OVER)
	{	
		aim.clear(); //if game end - delete aims and effects
		if (_eff) _eff->Kill();
		_eff = NULL;
		Core::Timer::Pause();
	}
}


bool MainWidget::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_curTex == BULLET_NOT_EXISTS) //if left mouse button pressed, create the bullet
		{
			_curTex = MOUSE_PRESS;

			bul.clear();
			bul.push_back(new Bullet());

			bul.at(0)->SetSpeed(data->GetSpeed());

				MM::manager.PlaySample("Boom");
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
			if (_curTex == GAME_OVER || _curTex == GAME_WIN) //if game end, delete all data
			{
				delete back;
				delete data;
				delete gun;
				bul.clear();
			
				aim.clear();
				counter = -1;
				if (_eff) _eff->Kill();;
				_eff = NULL;
				MM::manager.StopAll();
				Init(); //and init new game here
			}
		}
	}
}
