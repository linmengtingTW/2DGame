#pragma once
//#include "Particle.h"

struct tPlayer
{
	float mPosX;
	float mPosY;
	float mMoveX;
	float mMoveY;
	int mAnime;
	int mAnimeWait;
	KdTexture mTex;
	Math::Matrix mMat;
	bool mMoveFlg;
};

struct tObject
{
	float mPosX;
	float mPosY;
	float mMoveX;
	float mMoveY;
	bool mFlg;
	KdTexture mTex;
	Math::Matrix mMat;
};

struct tText
{
	float mPosX;
	float mPosY;
	bool mFlg;
	KdTexture mTex;
	Math::Matrix mMat;
};

struct tTutText
{
	bool mFlg;
	KdTexture mTex;
	Math::Matrix mMat;
};

class Scene
{
private:
	tPlayer player;
	static const int OBJ_NUM = 3;
	tObject obj[OBJ_NUM];
	static const int TEXT_NUM = 6;
	tText text[TEXT_NUM];
	static const int TUTTEXT_NUM = 5;
	tTutText tut[TUTTEXT_NUM];
	const float PL_RADIUS = 16.0f;
	const float CHIP_RADIUS = 16.0f;
	const float OBJ_RADIUS = 16.0f;
	const float CHECK_RANGE = 4.0f;
	const float TUT_X = -300.0f;
	const float TUT_Y = 110.0f;
	float scrollX, scrollY;
	static const int	MAP_CHIP_H = 37;
	static const int	MAP_CHIP_W = 63;
	float				mapChipX[MAP_CHIP_H][MAP_CHIP_W];
	float				mapChipY[MAP_CHIP_H][MAP_CHIP_W];
	int					mapChipData[MAP_CHIP_H][MAP_CHIP_W];
	bool				mapChipFlg[MAP_CHIP_H][MAP_CHIP_W];
	Math::Matrix		mapChipMat[MAP_CHIP_H][MAP_CHIP_W];
	KdTexture			mapChipTex;

	int tutmode;

	bool stg0, stg1, stg2;
	int stg;

	int CNT = 10;

	const float CLR_X = 1352.0f;
	bool CLR_FLG;
	float clrX;
	float clrY;
	KdTexture clrTex;
	Math::Matrix clrMat;

	KdTexture TitleTex;
	Math::Matrix TitleMat;
	KdTexture StartTex;
	Math::Matrix StartMat;

	int sceneType;
	int keyFlg;

	/*static const int SMOKE_MAX = 50;
	Particle smoke[SMOKE_MAX];

	KdTexture smokeTex;*/
public:

	// �����ݒ�
	void Init();
	// ���
	void Release();

	// �X�V����
	void Update();
	// �`�揈��
	void Draw2D();

	// GUI����
	void ImGuiUpdate();

	// �v���C���[�֌W
	void PlayerUpdate();
	void PlayerDraw();
	void PlayerInit0();
	void PlayerInit1();
	void PlayerInit2();

	// �I�u�W�F�N�g�֌W
	void ObjUpdate();
	void ObjDraw();
	void ObjInit0();
	void ObjInit1();
	void ObjInit2();

	// �}�b�v�`�b�v�֌W
	void MapChipUpdate();
	void MapChipDraw();
	void MapChipInit();
	void LoadMapFile();

	// �e�N�X�g�֌W
	void TextUpdate();
	void TextDraw();
	void TextInit();

	// �����蔻��
	void PlyMapHitCheck();
	void ObjHitCheck();
	void ObjMapHitChk();
	void PlyText0HitChk();
	void PlyText1HitChk();
	void PlyText2HitChk();
	void PlyText3HitChk();
	void PlyText4HitChk();
	void PlyText5HitChk();
	void ObjText0HitChk();
	void ObjText1HitChk();
	void ObjText2HitChk();
	void ObjText3HitChk();
	void ObjText4HitChk();
	void ObjText5HitChk();

	// �^�C�g��
	void TitleUpdate();
	void TitleDraw();

	// �`���[�g���A��
	void LoadTutMapFile();

	float Rnd();

	//void kannjiHit(float HitX1, float HitY1, float HitMoveX, float HitMoveY, float HitX2, float HitY2);

private:
	Math::Matrix matrix;	//�ėp�s��
	DirectX::SpriteBatch* spriteBatch;
	DirectX::SpriteFont* spriteFont;

	Scene() {}
public:
	static Scene& GetInstance()
	{
		static Scene instance;
		return instance;
	}
};

#define SCENE Scene::GetInstance()

// �_��OBB�Ƃ̍ŋߐړ_�����߂�
inline void PointToBox(const Math::Vector2& point, const Math::Vector2& obbCenterPos, const Math::Vector2& obbHalfSize, const Math::Matrix& obbMat, Math::Vector2& outNearestPos)
{
	// ���Q�l:[����]�u�Q�[���v���O���~���O�̂��߂̃��A���^�C���Փ˔���v
	Math::Vector2 d = point - obbCenterPos;
	// �{�b�N�X�̒��S�ɂ����錋�ʂ���J�n�A���̂���i�K�I�ɐi�߂�B
	outNearestPos = obbCenterPos;
	// �eOBB�̎��ɑ΂���
	for (int i = 0; i < 2; i++)
	{
		// d�����̎��ɓ��e����
		// �{�b�N�X�̒��S����d�̎��ɉ����������𓾂�
		float dist = d.Dot((Math::Vector2&)obbMat.m[i]);
		// �{�b�N�X�͈̔͂����������傫���ꍇ�A�{�b�N�X�܂ŃN�����v
		if (dist > (&obbHalfSize.x)[i]) dist = (&obbHalfSize.x)[i];
		if (dist < -(&obbHalfSize.x)[i]) dist = -(&obbHalfSize.x)[i];
		// ���[���h���W�𓾂邽�߂ɂ��̋����������ɉ����Đi�߂�
		outNearestPos += dist * (Math::Vector2&)obbMat.m[i];
	}

}


//========================
// �I�u�W�F�N�g��{�N���X
//========================
class ObjectBase
{
public:
	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual bool HitTest_Circle(const Math::Vector2& pos, float radius, Math::Vector2* hitPos) { return false; }

	virtual void DebugDraw() {}

	// ���W
	Math::Vector2	m_pos;
	float			m_z = 0;
};

//========================
// �L����
//========================
class Chara : public ObjectBase
{
public:

	void Init(KdTexture* tex, float x, float y)
	{
		m_pTex = tex;
		m_pos.x = x;
		m_pos.y = y;
	}

	// �X�V����
	virtual void Update() override
	{
		// �L�[�ړ�
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x -= 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x += 5.0f;

		}

	}

	// �`�揈��
	virtual void Draw() override
	{
		Math::Matrix m;
		// �L�����̍s��
		m = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);

		// �s��Z�b�g
		SHADER.m_spriteShader.SetMatrix(m);
		// �`��
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, 48, 48, &Math::Rectangle(0, 0, 48, 48), &Math::Color(1,1,1,1), Math::Vector2(0.5f, 0.5f));
	}

private:
	KdTexture*	m_pTex = nullptr;
};
