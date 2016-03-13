
#include "stdafx.h"

#include "Bul.h"

Bul::Bul()
{
	_bullet = Core::resourceManager.Get<Render::Texture>("Bullet");
	texBullet = _bullet->getBitmapRect();
}


void Bul::Draw()
{
	FRect rect(texBullet);
	FRect uv(0, 1, 0, 1);

	_bullet->TranslateUV(rect, uv);

	Render::device.MatrixTranslate(texBullet.x, texBullet.y, 0.0f);

	_bullet->Bind();


	Render::DrawRect(rect, uv);

}


bool Bul::Update()
{
	texBullet.y += Speed;

	if (texBullet.y > 768 - texBullet.height/2)
	{
		return true;
	}
	return false;
}