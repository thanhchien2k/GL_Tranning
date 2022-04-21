#include "GSPlay.h"

#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "GameButton.h"
#include "SpriteAnimation.h"

std::string shoot1 = "shoot1.wav";
std::string explosion = "explosion.wav";

GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{
}


void GSPlay::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play3.tga");

	// background
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2);
	m_background->SetSize(Globals::screenWidth, Globals::screenHeight);

	m_background2 = std::make_shared<Sprite2D>(model, shader, texture);
	m_background2->Set2DPosition((float)Globals::screenWidth / 2, (float)Globals::screenHeight / 2 + 800);
	m_background2->SetSize(Globals::screenWidth, Globals::screenHeight);

	// pause background
	texture = ResourceManagers::GetInstance()->GetTexture("pause1.tga");
	m_pause_bg = std::make_shared<Sprite2D>(model, shader, texture);
	m_pause_bg->Set2DPosition(Globals::screenWidth / 2, Globals::screenHeight / 2);
	m_pause_bg->SetSize(291, 173);

	// button pause
	texture = ResourceManagers::GetInstance()->GetTexture("btn_pause.tga");
	std::shared_ptr<GameButton>  button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(Globals::screenWidth - 50, 50);
	button->SetSize(50, 50);
	button->SetOnClick([this]() {
		status_pause = !status_pause;
		});
	m_listButton.push_back(button);

	// close
	texture = ResourceManagers::GetInstance()->GetTexture("btn_close.tga");
	m_close = std::make_shared<GameButton>(model, shader, texture);
	m_close->Set2DPosition(Globals::screenWidth / 2 - 50, Globals::screenHeight / 2);
	m_close->SetSize(50, 50);
	m_close->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		});
	// restart

	texture = ResourceManagers::GetInstance()->GetTexture("btn_restart.tga");
	m_restart = std::make_shared<GameButton>(model, shader, texture);
	m_restart->Set2DPosition(Globals::screenWidth / 2 + 50, Globals::screenHeight / 2);
	m_restart->SetSize(50, 50);
	m_restart->SetOnClick([this]() {
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateType::STATE_PLAY);
		});

	// score
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("Brightly Crush Shine.otf");
	m_score = std::make_shared< Text>(shader, font, "score:", TextColor::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));

	// ship
	shader = ResourceManagers::GetInstance()->GetShader("Animation");
	texture = ResourceManagers::GetInstance()->GetTexture("ship1.tga");
	std::shared_ptr<SpriteAnimation> obj = std::make_shared<SpriteAnimation>(model, shader, texture, 3, 1, 0, 0.1f);

	obj->Set2DPosition(240, 400);
	obj->SetSize(334, 223);
	//obj->SetRotation(Vector3(0.0f, 3.14f, 0.0f));
	m_listAnimation.push_back(obj);

}

void GSPlay::Exit()
{
	printf("%d", m_Test);
}


void GSPlay::Pause()
{
}

void GSPlay::Resume()
{
}

void GSPlay::shoot(int x, int y) {
	b res;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture("shoot2.tga");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	res.tx = std::make_shared<Sprite2D>(model, shader, texture);
	res.tx->Set2DPosition(x, y);
	res.tx->SetSize(20, 40);
	res.isMoving = 1;
	bullet1.push_back(res);
}

void GSPlay::createBomber(int x, int y, int type)
{
	std::string nameEnemy;
	if (type == 1) {
		nameEnemy = "enemy1.tga";
	}
	else if (type == 2) {
		nameEnemy = "enemy2.tga";
	}
	else {
		nameEnemy = "enemy3.tga";
	}
	enemy res;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D.nfg");
	auto texture = ResourceManagers::GetInstance()->GetTexture(nameEnemy);
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	res.tx = std::make_shared<GameButton>(model, shader, texture);
	res.tx->Set2DPosition(x, y);
	res.tx->SetSize(100, 120);
	res.heal = rand() % 3 + 3;
	bomber.push_back(res);
}


void GSPlay::HandleEvents()
{
}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{


}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!status_pause) {
	
		if (bIsPressed) {
			shoot(x, y);
			if (Globals::statusSound) ResourceManagers::GetInstance()->PlaySound(shoot1);

		}


	}
	else
	{
		m_close->HandleTouchEvents(x, y, bIsPressed);
		m_restart->HandleTouchEvents(x, y, bIsPressed);
	}
	
	if (!status_GO)
	for (auto button : m_listButton) {
		if (button->HandleTouchEvents(x, y, bIsPressed))
		{
			break;
		}
	}
}

void GSPlay::HandleMouseMoveEvents(int x, int y)
{
	if (!status_pause)
		if (!m_listAnimation.empty()) {
			for (auto it : m_listAnimation)
			{
				it->Set2DPosition(x, y);

			}
		}
	if (!m_listAnimation.empty()) {
		for (auto itr = m_listAnimation.begin(); itr != m_listAnimation.end(); ++itr) {
			auto temp = *itr;
			for (auto itr1 = bomber.begin(); itr1 != bomber.end(); ++itr1) {
				auto enemy = *itr1;
				Vector3 bom = enemy.tx->GetPosition();
				if (bom.x - 50 > x - 167 && bom.y - 60 > y - 112 && bom.x + 50 < x + 167 && bom.y + 60 < y + 112) {
					std::cout << '1';
					m_listAnimation.erase(itr);
					if (Globals::statusSound) ResourceManagers::GetInstance()->PlaySound(explosion);
					 status_pause = true;
					break;
				}
			}
			if (m_listAnimation.empty()) break;
		}
	}

}

void GSPlay::Update(float deltaTime)
{
	if (!status_pause) {
		m_time += deltaTime;
		if (m_time > 1) {
			m_time = 0;
			createBomber((rand() % 13 + 2) * 50, -300, rand() % 3 + 1);
		}
		// background move

		Vector3 vt_bg1 = m_background->GetPosition();
		if (vt_bg1.y >= 1200) vt_bg1.y = -400;
		m_background->Set2DPosition(vt_bg1.x, (vt_bg1.y) + 1);

		Vector3 vt_bg2 = m_background2->GetPosition();
		if (vt_bg2.y >= 1200) vt_bg2.y = -400;
		m_background2->Set2DPosition(vt_bg2.x, (vt_bg2.y) + 1);


		while (!bullet1.empty()) {
			Vector3 v = bullet1.front().tx->GetPosition();
			if (v.y < -50 || bullet1.front().isMoving == false)bullet1.pop_front();
			else break;
		}

		if (bullet1.empty()) ;
		else {
			for (auto itr = bullet1.begin(); itr != bullet1.end(); ++itr) {
				auto bullet = *itr;
				Vector3 vd = bullet.tx->GetPosition();
				if (bullet.isMoving) {
					for (auto itr1 = bomber.begin(); itr1 != bomber.end(); ++itr1) {
						auto enemy = *itr1;
						Vector3 bom = enemy.tx->GetPosition();
						if (vd.y - 20 < bom.y + 60 && vd.x - 10 > bom.x - 50 && vd.x + 10 < bom.x + 50) {
							bomber.erase(itr1);
							if (Globals::statusSound)	ResourceManagers::GetInstance()->PlaySound(explosion);
							bullet1.erase(itr);
							break;
						}
					}
				}
				break;
			}
		}


		for (auto it : bullet1) {
			Vector3 v = it.tx->GetPosition();
			it.tx->Set2DPosition(v.x, v.y - deltaTime * 450);
			if (v.y < 400) {
				it.isMoving = 0;
			}
			it.tx->Update(deltaTime);
		}
		while (!bomber.empty()) {
			Vector3 v = bomber.front().tx->GetPosition();
			if (v.y > 950 || bomber.front().heal == 0)bomber.pop_front();
			else break;
		}
		for (auto it : bomber) {
			Vector3 v = it.tx->GetPosition();
			it.tx->Set2DPosition(v.x, v.y + deltaTime * 250);
			it.tx->Update(deltaTime);
		}
		 


		for (auto it : m_listAnimation)
		{
			it->Update(deltaTime);
		}


		for (auto it : m_listButton)
		{
			it->Update(deltaTime);
		}
	}
	
}

void GSPlay::Draw()
{
	m_background->Draw();
	m_background2->Draw();
	m_score->Draw();


	for (auto it : m_listAnimation)
	{
		it->Draw();
	}
	for (auto it : bullet1) {

			it.tx->Draw();
	}
	for (auto it : bomber) {
		if (it.heal > 0)
			it.tx->Draw();
	}
	
	for (auto it : m_listButton)
	{
		it->Draw();
	}

	if (status_pause) {
		m_pause_bg->Draw();
		m_close->Draw();
		m_restart->Draw();
		if (status_GO)
			m_gameOver->Draw();
		for (auto it : m_text_pause) {
			it->Draw();
		}

	}
}