#pragma once

class Particle
{
public:
	Particle();
	~Particle();
	void Init();
	void UpdateFire(float aPosX, float aPosY, bool aPlayerMoveFlg);
	void Draw();
	void SetTexture(KdTexture* apTexture);
	float Rnd();
	void Emit(Math::Vector2 aPos, Math::Vector2 aMove,
		float aSize, Math::Color aColor, int aLifespan, bool aLoopFlg);
private:
	Math::Vector2 m_pos;
	Math::Vector2 m_move;
	float m_size;
	Math::Color m_color;
	int m_lifespan;
	bool m_loopFlg;
	Math::Matrix m_mat;
	KdTexture* m_pTexture;
};

#pragma once
