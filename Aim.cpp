#include "stdafx.h"

#include "Aim.h"

enum ARROW { RIGHT_UP = 0, LEFT_UP, RIGHT_DOWN, LEFT_DOWN };

Aim::Aim()
{
	_aim = Core::resourceManager.Get<Render::Texture>("Aim");

	texAim = _aim->getBitmapRect();

	texAim.x = rand() % 450; //start position
	texAim.y = rand() % 300;

	_angle = 0;

	Arrow = rand() % 4;

	x = rand() % 2 + 1;
	y = rand() % 5 + 1;
}

void Aim::Draw()
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	Render::BeginAlphaMul(0.9f);
	FRect rect(texAim);
	FRect uv(0, 1, 0, 1);

	_aim->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(texAim.x, texAim.y, 0.0f);

	_aim->Bind();
	Render::DrawRect(rect, uv);
	Render::EndAlphaMul();


}

void Aim::Update(float dt) //moving aims here
{

	if (texAim.y > 768 * 0.5 - texAim.height / 2 || texAim.y <= 0)
	{
		y = -y;
	}
	if (texAim.x > 1024 * 0.5 - texAim.width / 2 || texAim.x <= 0)
	{
		x = -x;
	}

	if (Arrow == LEFT_UP)
	{
		texAim.x -= x;
		texAim.y += y;
	}
	else if (Arrow == RIGHT_UP)
	{
		texAim.x += x;
		texAim.y += y;
		
	}
	else if (Arrow == LEFT_DOWN)
	{
		texAim.x -= x;
		texAim.y -= y;
	}
	else if (Arrow == RIGHT_DOWN)
	{
		texAim.x += x;
		texAim.y -= y;
	}



}

FRect Aim::ReturnAimPoints() //get aim coordinates
{
	FRect rect(texAim);
	rect.xEnd = rect.xStart + rect.Width() / 2;
	rect.yEnd = rect.yEnd - rect.Height() / 2;
	return rect;
}