#pragma once

class Bullet : public GUI::Widget
{
public:
	Bullet(const std::string& name, rapidxml::xml_node<>* elem);
	Bullet();

	virtual void Draw();
	virtual void Update(float dt);
	void AcceptMessage(const Message& message);

private:
	void Init();

private:
	float _timer;

	float _scale;
	float _angle;

	Render::Texture* _texBullet;

	IRect texRect;

	int _curTex;

	EffectsContainer _effCont;
	ParticleEffectPtr _eff;
};