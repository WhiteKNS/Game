#include "stdafx.h"

#include "Background.h"


Background::Background(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	,_timer(0)
{
}

void Background::Draw()
{

	Render::device.PushMatrix();
	_tex1 = Core::resourceManager.Get<Render::Texture>("Back");
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

	_effCont.Draw();

}

void Background::Update(float dt)
{

	_effCont.Update(dt);

	_timer += dt * 2;


	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
	}

}
/*
Background::Background()
{

}

void Background::Draw()
{
	Render::device.PushMatrix();
	_tex1 = Core::resourceManager.Get<Render::Texture>("Back");
	IRect texRect = _tex1->getBitmapRect();

	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);

	_tex1->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(0, 0, 0.0f);
	Render::device.MatrixScale(1.0);

	//Render::Target::
		_tex1->Bind();
	_tex1->Draw();

	Render::device.PopMatrix();

	Render::device.SetTexturing(false);

	Render::device.SetTexturing(true);

	//_effCont.Draw();
}*/