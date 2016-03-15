#pragma once

class Bullet
{
public:
	Bullet();
	void Draw();
	bool Update();
	const IRect GetBullet();
	//void SetBullet()
	int Speed;

	IRect texBullet;

private:

	Render::Texture* _bullet;
	
};