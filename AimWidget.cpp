#include "stdafx.h"
#include "AimWidget.h"

AimWidget::AimWidget(const std::string& name, rapidxml::xml_node<>* elem)
	: Widget(name)
	, _curTex(0)
	, _timer(0)
	, _angle(0)
	, _eff(NULL)
	, _scale(0.f)
{
	Init();
}

void AimWidget::Init()
{
	_tex1 = Core::resourceManager.Get<Render::Texture>("Aim");
	texRect = _tex1->getBitmapRect();
	texRect.y = 90;
	
	//Render::Texture::CreateAlphaMask(LoadImageA());
	//_tex2 = Core::resourceManager.Get<Render::Texture>("Circle");

	_curTex = 0;
	_angle = 0;

	x = rand()%15;
	y = rand()%13;
}

void AimWidget::Draw()
{
	
	IPoint mouse_pos = Core::mainInput.GetMousePos();

	Render::device.PushMatrix();

	//texRect = _tex1->getBitmapRect();
	
		FRect rect(texRect);
		FRect uv(0, 1, 0, 1);

		_tex1->TranslateUV(rect, uv);
		//dx += 50;
		
		Render::device.MatrixTranslate(texRect.x, texRect.y, 0.0f);
		//Render::device.MatrixTranslate(texRect.height*0.8, texRect.width*0.6, 0.0f);
		Render::device.MatrixScale(0.4);

		_tex1->Bind();
		_tex1->Draw();
		//Render::DrawRect(rect, uv);


	Render::device.PopMatrix();

	//Render::device.SetTexturing(false);

//	Render::BeginColor(Color(255, 128, 0, 255));

	//Render::DrawRect(924, 0, 100, 100);

	//Render::EndColor();

	//Render::device.SetTexturing(true);

	_effCont.Draw();

	Render::BindFont("arial");
	Render::PrintString(924 + 100 / 2, 35, utils::lexical_cast(mouse_pos.x) + ", " + utils::lexical_cast(mouse_pos.y), 1.f, CenterAlign);

	
}

void AimWidget::Update(float dt)
{
	
	_effCont.Update(dt);

	_timer += dt * 2;

	
	while (_timer > 2 * math::PI)
	{
		_timer -= 2 * math::PI;
	}

	if (texRect.y >768 - texRect.height*0.4|| texRect.y<0)
	{
		y = -y;
	}
	if (texRect.x>1024 - texRect.width*0.4 || texRect.x<0)
	{
		x = -x;
	}

	texRect.x += x;
	texRect.y += y;

	_scale = 0.8f + 0.25f * sinf(_timer);
	//_scale = 0.8f + 0.25f * sinf(_timer);
}

IRect AimWidget::ReturnAimPoints()
{
	//AimWidget widget = this;
	return texRect;
	
}
void AimWidget::AcceptMessage(const Message& message)
{
	
	if (message.getPublisher() == "KeyPress")
	{
		int code = utils::lexical_cast<int>(message.getData());
		if (code < 0)
		{
			
			return;
		}

		
		if (code == 'a')
		{
		}
	}
}
