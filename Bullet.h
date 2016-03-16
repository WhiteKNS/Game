#pragma once

class Bullet
{
public:
	Bullet();
	void Draw();
	bool Update(float dt);
	const IRect GetBullet();
	//void SetBullet()
	float Speed;

	IRect texBullet;

private:

	Render::Texture* _bullet;
	
};