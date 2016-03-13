#include "stdafx.h"

#include "Aim.h"


Aim::Aim()
{
	_aim = Core::resourceManager.Get<Render::Texture>("Aim");
	texAim = _aim->getBitmapRect();
	texAim.y = 90;
	_angle = 0;

	x = rand() % 15;
	y = rand() % 13;
}

void Aim::Draw()
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	
	Render::device.PushMatrix();

	FRect rect(texAim);
	FRect uv(0, 1, 0, 1);

	_aim->TranslateUV(rect, uv);
	
	//rand() % 1;

	//Render::BeginAlphaMul(0.3f);


	Render::device.MatrixRotate(math::Vector3(0, 0, 1), 0);

	Render::device.MatrixTranslate(texAim.x, texAim.y, 0.0f);
	Render::device.MatrixTranslate(-texAim.width * 0.5f, -texAim.height * 0.5f, 0.0f);
	
	Render::device.MatrixScale(1);


	_aim->Bind();
	Render::DrawRect(rect, uv);

	//Render::EndAlphaMul();

	Render::device.PopMatrix();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);
}

void Aim::Update()
{
	if (texAim.y > 768*0.5 - texAim.height / 2 || texAim.y < 0)
	{
		y = -y;
	}
	if (texAim.x > 1024*0.5-texAim.width/2 || texAim.x < 0)
	{
		x = -x;
	}

	texAim.x += x;
	texAim.y += y;

	_scale = 0.8f + 0.25f * sinf(_timer);
}

FRect Aim::ReturnAimPoints()
{
	FRect rect(texAim);
	return rect;
}