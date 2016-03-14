#pragma once


class Gun
{
public:
	Gun();
	void Draw();

private:
	//void Init();

	IRect texGun;
	Render::Texture* _gun;
};