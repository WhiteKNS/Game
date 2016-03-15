#pragma once


class Gun
{
public:
	Gun();
	void Draw();

private:

	IRect texGun;
	Render::Texture* _gun;
};