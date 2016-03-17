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
	
	ParticleEffectPtr _eff;
private:

	int counter;
	float Speed;
	Render::Texture* _bullet;
	
	
	EffectsContainer _effCont;

};