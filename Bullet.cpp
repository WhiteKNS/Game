
#include "stdafx.h"

#include "Bullet.h"

Bullet::Bullet()
{
	_bullet = Core::resourceManager.Get<Render::Texture>("Bullet");
	texBullet = _bullet->getBitmapRect();
}


void Bullet::Draw()
{
	FRect rect(texBullet);
	FRect uv(0, 1, 0, 1);

	_bullet->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(texBullet.x, texBullet.y, 0.0f);

	_bullet->Bind();


	Render::DrawRect(rect, uv);

}


bool Bullet::Update(float dt)
{

	texBullet.y = texBullet.y + Speed* dt;
	//texBullet.y += Speed;

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