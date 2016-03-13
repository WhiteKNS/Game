
#include "stdafx.h"

#include "Gun.h"

#include "Bullet.h"
#include "Bul.h"
#include "Background.h"
#include "AimWidget.h"
#include "Aim.h"

Gun::Gun(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	,_scale(0)
	,_angle(0)
	, _eff(NULL)
	,_timer(0)

{
	Init();
}

void Gun::Init()
{

	Start();

	for (unsigned int i = 0; i < 5; ++i)
	bul.push_back(new Bul());

	InitField();
	for (int i = 0; i < save.at(0); ++i)
		aim.push_back(new Aim());

	bul.at(0)->Speed = save.at(1);
	bul.at(0)->texBullet.y = -150;
	_tex1 = Core::resourceManager.Get<Render::Texture>("Gun");
	_curTex = 0;
	texGun = _tex1->getBitmapRect();
}

int Gun::SaveToGame(std::string current_str)
{
	int start = 0;
	int number=0;
	for (unsigned int i = 0; i < current_str.length(); ++i)
	{
		if (current_str.at(i) == '=')
		{
			std::string final_str = "";
			for (unsigned int j = i+1; j < current_str.length(); j++)
			{
				final_str += current_str.at(j);
			}
			number = atoi(final_str.c_str());
			break;
		}
	}

	return number;
}

void Gun::InitField()
{
	std::fstream fin;
	fin.open("input.txt");
	std::string current_str="";
	if (!fin.is_open())
	{
		std::cerr << "Can't open file!" << std::endl;
		Render::PrintString(10, 100, std::string("can't open file: "), 1.0f, BottomAlign);
	}
	else
	{
		int i = 0;
		while (!fin.eof())
		{
			std::getline(fin, current_str, '\n');
			if (current_str.empty()) { break; }
			save.push_back(SaveToGame(current_str));
		//	Render::PrintString(10, 100, std::string("vecotr ") + utils::lexical_cast(save.at(i)), 1.0f, CenterAlign);
			i++;
		}
	}
	fin.close();
}

void Gun::DrawGun()
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	if ((float)mouse_pos.x < 1024 - texGun.Width()*0.1)
	{
		FRect rect(texGun);
		FRect uv(0, 1, 0, 1);

		_tex1->TranslateUV(rect, uv);

		Render::device.MatrixScale(0.1);

		Render::device.MatrixTranslate((float)mouse_pos.x / 0.1, 15, 0.0f);


		_tex1->Bind();

		Render::DrawRect(rect, uv);
	}
	else
	{
		//Render::device.PushMatrix();
		FRect rect(texGun);
		FRect uv(0, 1, 0, 1);

		_tex1->TranslateUV(rect, uv);

	
		Render::device.MatrixTranslate(960, 1, 0.0f);

		Render::device.MatrixScale(0.1);

		_tex1->Bind();

		Render::DrawRect(rect, uv);
		//Render::device.PopMatrix();
	}
}

void Gun::Draw()
{
	
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	Render::device.PushMatrix();
	for (unsigned int i = 0; i < aim.size(); ++i) 
	{
		aim.at(i)->Draw();
	}

	Render::device.PopMatrix();
	Render::device.PushMatrix();
	DrawGun();

	Render::device.PopMatrix();

	_effCont.Draw();

	if (_curTex==1)
	{
		Render::device.PushMatrix();
	
		bul[0]->Draw();
		
		Render::device.PopMatrix();
		
	}
	
	if (_curTex == 2)
	{
		_curTex = 0;
	}
	for (unsigned int i = 0; i < aim.size(); ++i)
	{

		FRect gunRect(bul[0]->texBullet);
		gunRect.xStart = gunRect.xStart + aim.at(i)->ReturnAimPoints().Width()/2;
		if (gunRect.Intersects(aim.at(i)->ReturnAimPoints()))
		{
			aim.erase(aim.begin() + i);
			if (aim.empty())
			{
				
			}
			_curTex = 2;
		}
	
	}

	Render::BindFont("arial");

	int dy = Render::getFontHeight();
	int x = Render::device.Width() - 100;
	int y = Render::device.Height() - 200;

	Render::PrintString(x, y, std::string("Time: ") + utils::lexical_cast((int)getElapsedTime()), 1.0f, RightAlign, BottomAlign);

	Render::BindFont("arial");
	dy = Render::getFontHeight();
	x = Render::device.Width() - 5;
	y = Render::device.Height() - 20;

	Render::PrintString(x, y, std::string("Aims: ") + utils::lexical_cast(aim.size()), 1.0f, RightAlign, BottomAlign);
	//Render::PrintString(924 + 100 / 2, 35, "vector.size=" + utils::lexical_cast(aim.size()), 1.f, CenterAlign);
}


void Gun::Update(float dt)
{
	
	_effCont.Update(dt);

	_timer += dt * 100;


	while (_timer >100 * math::PI)
	{
		_timer -= 100* math::PI;
	}

	_scale = 0.8f + 0.25f * sinf(_timer);

	for (unsigned int i = 0; i < aim.size(); ++i)
	{
		aim.at(i)->Update();
	}

	if (_curTex == 1) {
	
		if (bul[0]->Update())
		{
			_curTex = 0;
			bul[0]->texBullet.y = -100;
		}
	
	}

	if (_curTex == 0)
	{
		bul[0]->texBullet.y = -100;
	}

}


bool Gun::MouseDown(const IPoint &mouse_pos)
{
	if (Core::mainInput.GetMouseLeftButton())
	{
		if (_curTex == 0)
		{
			_curTex = 1;
			Render::device.PushMatrix();
			IPoint mouse_pos = Core::mainInput.GetMousePos();
			Render::device.PopMatrix();
				bul.at(0)->texBullet.x = (float)mouse_pos.x*0.5 + 15;
				bul.at(0)->texBullet.y = 15;
		}
	}
	return false;
}

void Gun::MouseMove(const IPoint &mouse_pos)
{
	if (_eff)
	{
		
		_eff->posX = mouse_pos.x + 0.f;
		_eff->posY = mouse_pos.y + 0.f;
	}
}


/*
Render::device.PushMatrix();
Render::device.SetTexturing(false);

Render::BeginColor(Color(255, 128, 0, 255));

Render::DrawRect(924, 0, 100, 100);

Render::EndColor();
Render::device.SetTexturing(true);
Render::device.PopMatrix();
*/