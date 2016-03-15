#include "stdafx.h"

#include "Background.h"


Background::Background():_timer(0)
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("Back");
}

void Background::Draw()
{

	Render::device.PushMatrix();

	IRect texRect = _tex1->getBitmapRect();
	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);

	_tex1->TranslateUV(rect, uv);
	Render::BeginAlphaMul(0.7f);
	Render::device.MatrixTranslate(0, 0, 0.0f);
	Render::device.MatrixScale(1.0);

	_tex1->Bind();
	_tex1->Draw();

	Render::EndAlphaMul();
	Render::device.PopMatrix();

	Render::device.SetTexturing(false);

	Render::device.SetTexturing(true);


}
