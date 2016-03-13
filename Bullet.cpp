#include "stdafx.h"

#include "Bullet.h"

Bullet::Bullet(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name, elem)
	, _curTex(0)
	, _timer(0)
	, _angle(0)
	, _eff(NULL)
	, _scale(0.f)
{
	Init();
}



Bullet::Bullet()
	: Widget("Bullet")
	,_curTex(0)
	, _timer(0)
	, _angle(0)
	, _eff(NULL)
	, _scale(0.f)
{
	Init();
}



void Bullet::Init()
{
	_texBullet = Core::resourceManager.Get<Render::Texture>("Bullet");
	texRect = _texBullet->getBitmapRect();


}
void Bullet::Draw()
{

	//IPoint mouse_pos = Core::mainInput.GetMousePos();

	Render::device.PushMatrix();

	//texRect = _tex1->getBitmapRect();

	FRect rect(texRect);
	FRect uv(0, 1, 0, 1);

	_texBullet->TranslateUV(rect, uv);
	
	Render::device.MatrixTranslate(texRect.x, texRect.y, 0.0f);
	Render::device.MatrixScale(1);

	_texBullet->Bind();
	_texBullet->Draw();


	Render::device.PopMatrix();

	_effCont.Draw();

}

void Bullet::Update(float dt)
{

	_effCont.Update(dt);

	_timer += dt * 2;


	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
	}

	
	
	//texRect.x += x;
	texRect.y += 5;
	if (texRect.y > 768 - texRect.height)
		texRect.y -= 768;
	//_scale = 0.8f + 0.25f * sinf(_timer);
	//_scale = 0.8f + 0.25f * sinf(_timer);
}

void Bullet::AcceptMessage(const Message& message)
{
	if (message.getPublisher() == "Init")
	{
		//rapidxml::file<char> file("bullet.xml");
		//_texBullet = Core::resourceManager.Get<Render::Texture>("Bullet");
		//texRect = _texBullet->getBitmapRect();


	}

	if (message.getPublisher() == "KeyPress")
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			
			return;
		}

		if (code == 'a')
		{
		}
	}
}
