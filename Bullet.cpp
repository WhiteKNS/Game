
#include "stdafx.h"

#include "Bullet.h"

Bullet::Bullet()
{
	_bullet = Core::resourceManager.Get<Render::Texture>("Bullet");
	texBullet = _bullet->getBitmapRect();

	IPoint mouse_pos = Core::mainInput.GetMousePos();

	texBullet.x = (float)mouse_pos.x/2 + 15;
	texBullet.y = 15;
	_eff = _effCont.AddEffect("BulletTrace");
	
	counter = 0;
}


void Bullet::Draw()
{
	
	FRect rect(texBullet);
	FRect uv(0, 1, 0, 1);

	_bullet->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(texBullet.x, texBullet.y, 0.0f);

	_bullet->Bind();

	Render::DrawRect(rect, uv);

		_effCont.Draw();
	
}


Bullet::~Bullet()
{
	_eff->Finish();
}

void Bullet::SetSpeed(int _speed)
{
	Speed = _speed;
}

bool Bullet::Update(float dt)
{
	
	texBullet.y += Speed*dt;
	
	_eff->posX = texBullet.x + texBullet.width / 2;
	_eff->posY = texBullet.y;

	_effCont.Update(dt);
	if (texBullet.y > 400)
	{
		
		return true;
	}

	return false;
}

const IRect Bullet::GetBullet()
{
	return texBullet;
}