
#include "GSSetting.h"
extern bool statusSound, statusMusic;
GSSetting::GSSetting()
{
}

GSSetting::~GSSetting()
{
}

void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);


	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx.tga");
	soundOn = std::make_shared<GameButton>(model, shader, texture);
	soundOn->Set2DPosition(350, Globals::screenHeight / 2);
	soundOn->SetSize(70, 70);
	soundOn->SetOnClick([this]() {
		});

	texture = ResourceManagers::GetInstance()->GetTexture("btn_sfx_off.tga");
	soundOff = std::make_shared<GameButton>(model, shader, texture);
	soundOff->Set2DPosition(350, Globals::screenHeight / 2);
	soundOff->SetSize(70, 70);
	soundOff->SetOnClick([this]() {
		});
	// music
	texture = ResourceManagers::GetInstance()->GetTexture("btn_music.tga");
	musicOn = std::make_shared<GameButton>(model, shader, texture);
	musicOn->Set2DPosition(450, Globals::screenHeight / 2);
	musicOn->SetSize(70, 70);
	musicOn->SetOnClick([this]() {
		});

	texture = ResourceManagers::GetInstance()->GetTexture("btn_music_off.tga");
	musicOff = std::make_shared<GameButton>(model, shader, texture);
	musicOff->Set2DPosition(450, Globals::screenHeight / 2);
	musicOff->SetSize(70, 70);
	musicOff->SetOnClick([this]() {
		});
}

void GSSetting::Exit()
{
}

void GSSetting::Pause()
{
}

void GSSetting::Resume()
{
}

void GSSetting::HandleEvents()
{
}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto button : m_listButton)
	{
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
	soundOff->HandleTouchEvents(x, y, bIsPressed);
	soundOn->HandleTouchEvents(x, y, bIsPressed);
	if (bIsPressed && x <= 350 + 30 && x >= 350 - 30 && y <= 400 + 30 && y >= 400 - 30) {
		if (Globals::statusSound)Globals::statusSound = false;
		else Globals::statusSound = true;
	}
	if (bIsPressed && x <= 450 + 30 && x >= 450 - 30 && y <= 400 + 30 && y >= 400 - 30) {
		if (Globals::statusMusic) {
			Globals::statusMusic = false;
			ResourceManagers::GetInstance()->StopSound(music_name);
		}
		else {
			Globals::statusMusic = true;
			ResourceManagers::GetInstance()->PlaySound(music_name, true);
		}
	}
}

void GSSetting::HandleMouseMoveEvents(int x, int y)
{
}

void GSSetting::Update(float deltaTime)
{
	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	soundOff->Update(deltaTime);
	soundOn->Update(deltaTime);
	musicOn->Update(deltaTime);
	musicOff->Update(deltaTime);

}

void GSSetting::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	if (Globals::statusSound) {
		soundOn->Draw();
	}
	else {
		soundOff->Draw();
	}

	if (Globals::statusMusic) {
		musicOn->Draw();
	}
	else {
		musicOff->Draw();
	}
}
