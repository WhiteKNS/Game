#pragma once

class Bullet
{
public:
	Bullet();
	~Bullet();
	void Draw();
	bool Update(float dt);
	const IRect GetBullet();
	void SetSpeed(int _speed);

	IRect texBullet;

private:
	float Speed;
	Render::Texture* _bullet;
	

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
};