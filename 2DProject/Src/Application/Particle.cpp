#include "Particle.h"

Particle::Particle() :
	m_pos(0, 0),
	m_move(0, 0),
	m_size(1),
	m_color(1, 1, 1, 1),
	m_lifespan(0),
	m_loopFlg(false),
	m_mat(),
	m_pTexture(nullptr)
{

}

Particle::~Particle()
{

}

void Particle::Init()
{
	//m_move = { 1,1 };
	//m_move = { (float)(rand() % 10),1 };
	//m_move = { rand() / (float)RAND_MAX, rand() / (float)RAND_MAX };

	//m_move.x = rand() / (float)RAND_MAX;
	//m_move.y = rand() / (float)RAND_MAX;

	//m_move.x = Rnd() * 2 - 1;
	//m_move.y = Rnd() * 2 - 1;
	//m_size = 5;
	//m_color = { 0.8f,1.0f,0.5f,0.3f };

	m_color = { 0.0f,0.0f,0.0f,0.0f };
}

void Particle::UpdateSmoke(float aPosX, float aPosY)
{
	m_lifespan--;
	if (m_lifespan < 0)
	{
		m_lifespan = 0;
		if (!m_loopFlg) return;

		Emit(
			Math::Vector2(aPosX, aPosY),
			Math::Vector2(Rnd() * 2, 2.5),
			Rnd() * 4 - 1.5,
			Math::Color(1.0f, 1.0f, 1.0f, 0.3f),
			Rnd() * 90 + 10,
			true);
	}

	/*m_pos.x += m_move.x;
	m_pos.y += m_move.y;*/
	m_pos += m_move;

	m_size *= 0.98f;

	//m_mat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0.0f);

	Math::Matrix scaleMat, transMat;
	transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);
	scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 0);
	m_mat = scaleMat * transMat;
}

void Particle::UpdateFire(float aPosX, float aPosY)
{
	m_lifespan--;
	if (m_lifespan < 0)
	{
		m_lifespan = 0;
		if (!m_loopFlg) return;

		Emit(
			Math::Vector2(aPosX, aPosY),
			Math::Vector2(Rnd() * 2, 2.5),
			Rnd() * 6 - 3,
			Math::Color(1.0f, 0.0f, 0.0f, 0.7f),
			Rnd() * 30 + 10,
			true);
	}

	m_pos += m_move;
	m_size *= 0.98f;

	Math::Matrix scaleMat, transMat;
	transMat = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);
	scaleMat = DirectX::XMMatrixScaling(m_size, m_size, 0);
	m_mat = scaleMat * transMat;
}

void Particle::Draw()
{
	SHADER.m_spriteShader.SetMatrix(m_mat);
	Math::Rectangle srcRect = { 0,0,32,32 };
	SHADER.m_spriteShader.DrawTex(m_pTexture, 0, 0, 32, 32, &srcRect, &m_color, Math::Vector2(0.5f, 0.5f));
}

void Particle::SetTexture(KdTexture* apTexture)
{
	if (apTexture == nullptr) return;

	m_pTexture = apTexture;
}

float Particle::Rnd()
{
	return rand() / (float)RAND_MAX;
}

void Particle::Emit(Math::Vector2 aPos, Math::Vector2 aMove,
	float aSize, Math::Color aColor, int aLifespan, bool aLoopFlg)
{
	m_pos = aPos;
	m_move = aMove;
	m_size = aSize;
	m_color = aColor;
	m_lifespan = aLifespan;
	m_loopFlg = aLoopFlg;

}
