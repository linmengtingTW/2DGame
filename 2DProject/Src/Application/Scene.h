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

	// 初期設定
	void Init();
	// 解放
	void Release();

	// 更新処理
	void Update();
	// 描画処理
	void Draw2D();

	// GUI処理
	void ImGuiUpdate();

	// プレイヤー関係
	void PlayerUpdate();
	void PlayerDraw();
	void PlayerInit0();
	void PlayerInit1();
	void PlayerInit2();

	// オブジェクト関係
	void ObjUpdate();
	void ObjDraw();
	void ObjInit0();
	void ObjInit1();
	void ObjInit2();

	// マップチップ関係
	void MapChipUpdate();
	void MapChipDraw();
	void MapChipInit();
	void LoadMapFile();

	// テクスト関係
	void TextUpdate();
	void TextDraw();
	void TextInit();

	// 当たり判定
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

	// タイトル
	void TitleUpdate();
	void TitleDraw();

	// チュートリアル
	void LoadTutMapFile();

	float Rnd();

	//void kannjiHit(float HitX1, float HitY1, float HitMoveX, float HitMoveY, float HitX2, float HitY2);

private:
	Math::Matrix matrix;	//汎用行列
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

// 点とOBBとの最近接点を求める
inline void PointToBox(const Math::Vector2& point, const Math::Vector2& obbCenterPos, const Math::Vector2& obbHalfSize, const Math::Matrix& obbMat, Math::Vector2& outNearestPos)
{
	// ※参考:[書籍]「ゲームプログラミングのためのリアルタイム衝突判定」
	Math::Vector2 d = point - obbCenterPos;
	// ボックスの中心における結果から開始、そのから段階的に進める。
	outNearestPos = obbCenterPos;
	// 各OBBの軸に対して
	for (int i = 0; i < 2; i++)
	{
		// dをその軸に投影して
		// ボックスの中心からdの軸に沿った距離を得る
		float dist = d.Dot((Math::Vector2&)obbMat.m[i]);
		// ボックスの範囲よりも距離が大きい場合、ボックスまでクランプ
		if (dist > (&obbHalfSize.x)[i]) dist = (&obbHalfSize.x)[i];
		if (dist < -(&obbHalfSize.x)[i]) dist = -(&obbHalfSize.x)[i];
		// ワールド座標を得るためにその距離だけ軸に沿って進める
		outNearestPos += dist * (Math::Vector2&)obbMat.m[i];
	}

}


//========================
// オブジェクト基本クラス
//========================
class ObjectBase
{
public:
	virtual ~ObjectBase() {}

	virtual void Update() {}
	virtual void Draw() {}

	virtual bool HitTest_Circle(const Math::Vector2& pos, float radius, Math::Vector2* hitPos) { return false; }

	virtual void DebugDraw() {}

	// 座標
	Math::Vector2	m_pos;
	float			m_z = 0;
};

//========================
// キャラ
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

	// 更新処理
	virtual void Update() override
	{
		// キー移動
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			m_pos.x -= 5.0f;
		}
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_pos.x += 5.0f;

		}

	}

	// 描画処理
	virtual void Draw() override
	{
		Math::Matrix m;
		// キャラの行列
		m = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, 0);

		// 行列セット
		SHADER.m_spriteShader.SetMatrix(m);
		// 描画
		SHADER.m_spriteShader.DrawTex(m_pTex, 0, 0, 48, 48, &Math::Rectangle(0, 0, 48, 48), &Math::Color(1,1,1,1), Math::Vector2(0.5f, 0.5f));
	}

private:
	KdTexture*	m_pTex = nullptr;
};
