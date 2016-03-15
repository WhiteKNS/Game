#include "stdafx.h"

#include "Gun.h"

Gun::Gun()
{
	_gun = Core::resourceManager.Get<Render::Texture>("Gun");
	texGun= _gun->getBitmapRect();
}


void Gun::Draw()
{
	IPoint mouse_pos = Core::mainInput.GetMousePos();
	if ((float)mouse_pos.x < 1024 - texGun.Width()*0.1)
	{
		FRect rect(texGun);
		FRect uv(0, 1, 0, 1);
		_gun->TranslateUV(rect, uv);
		Render::device.MatrixScale(0.1);
		Render::device.MatrixTranslate((float)mouse_pos.x / 0.1, 15, 0.0f);
		_gun->Bind();
		Render::DrawRect(rect, uv);
	}
	else
	{
		FRect rect(texGun);
		FRect uv(0, 1, 0, 1);
		_gun->TranslateUV(rect, uv);
		Render::device.MatrixTranslate(960, 1, 0.0f);
		Render::device.MatrixScale(0.1);
		_gun->Bind();
		Render::DrawRect(rect, uv);
	}
}

