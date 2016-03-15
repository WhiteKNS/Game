#pragma once


class Background
{
public:
	Background();
	void Draw();

private:

	Render::Texture* _tex1;
	float _timer;
};