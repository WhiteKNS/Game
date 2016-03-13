#pragma once

class Bul
{
public:
	Bul();
	void Draw();
	bool Update();

	IRect texBullet;
	int Speed;

private:


	Render::Texture* _bullet;
};