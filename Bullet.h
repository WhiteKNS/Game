#pragma once

class Bullet
{
public:
	Bullet();
	void Draw();
	bool Update();

	IRect texBullet;
	
	int Speed;

private:

	Render::Texture* _bullet;
};