#include "main.h"
#include "Scene.h"

#pragma warning(disable:4996)

void Scene::Draw2D()
{
	switch (sceneType)
	{
	case 0:
		if (true)
		{
			Math::Matrix TitleMat = DirectX::XMMatrixTranslation(0.0f, 100.0f, 0.0f);
			SHADER.m_spriteShader.SetMatrix(TitleMat);
			SHADER.m_spriteShader.DrawTex(&TitleTex, Math::Rectangle(0, 0, 251, 50), 1.0f);

			Math::Matrix StartMat = DirectX::XMMatrixTranslation(0.0f, -100.0f, 0.0f);
			SHADER.m_spriteShader.SetMatrix(StartMat);
			SHADER.m_spriteShader.DrawTex(&StartTex, Math::Rectangle(0, 0, 276, 36), 0.5f);
		}
		break;
	case 1:
		MapChipDraw();
		PlayerDraw();
		TextDraw();
		ObjDraw();

		if (tutmode == 0)
		{
			Math::Matrix stutMat = DirectX::XMMatrixTranslation(TUT_X - scrollX, TUT_Y - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(stutMat);
			SHADER.m_spriteShader.DrawTex(&tut[0].mTex, Math::Rectangle(0, 0, 448, 32), 0.5f);
		}
		else if (tutmode == 1)
		{
			Math::Matrix stutMat = DirectX::XMMatrixTranslation(TUT_X - scrollX + 100, TUT_Y - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(stutMat);
			SHADER.m_spriteShader.DrawTex(&tut[1].mTex, Math::Rectangle(0, 0, 768, 32), 0.5f);
		}
		else if (tutmode == 2)
		{
			Math::Matrix stutMat = DirectX::XMMatrixTranslation(TUT_X - scrollX + 100, TUT_Y - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(stutMat);
			SHADER.m_spriteShader.DrawTex(&tut[2].mTex, Math::Rectangle(0, 0, 832, 32), 0.5f);
		}
		else if (tutmode == 3)
		{
			Math::Matrix stutMat = DirectX::XMMatrixTranslation(TUT_X - scrollX + 25, TUT_Y - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(stutMat);
			SHADER.m_spriteShader.DrawTex(&tut[3].mTex, Math::Rectangle(0, 0, 288, 32), 0.5f);
		}
		else if(tutmode == 4)
		{
			Math::Matrix stutMat = DirectX::XMMatrixTranslation(TUT_X - scrollX, TUT_Y - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(stutMat);
			SHADER.m_spriteShader.DrawTex(&tut[4].mTex, Math::Rectangle(0, 0, 224, 32), 0.5f);
		}

		if (CLR_FLG)
		{
			Math::Matrix sClrMat = DirectX::XMMatrixTranslation(clrX - scrollX, clrY - scrollY, 0.0f);
			SHADER.m_spriteShader.SetMatrix(sClrMat);
			SHADER.m_spriteShader.DrawTex(&clrTex, Math::Rectangle(0, 0, 501, 202), true);
		}

		/*for (int i = 0; i < SMOKE_MAX; i++)
		{
			smoke[i].Draw();
		}*/

		break;
	}
}

void Scene::Update()
{
	if (GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		if (keyFlg == 0)
		{
			keyFlg = 1;
			sceneType = 1;
		}
	}
	else
	{
		keyFlg = 0;
	}

	if (sceneType == 1)
	{
		MapChipUpdate();
		PlayerUpdate();
		TextUpdate();
		ObjUpdate();
		PlyMapHitCheck();

		if (obj[0].mFlg)
		{
			ObjHitCheck();
		}
		ObjMapHitChk();
		ObjText0HitChk();
		ObjText1HitChk();
		ObjText2HitChk();
		ObjText3HitChk();
		ObjText4HitChk();
		ObjText5HitChk();
		if (text[0].mFlg)
		{
			PlyText0HitChk();
		}
		if (text[1].mFlg)
		{
			PlyText1HitChk();
		}
		if (text[2].mFlg)
		{
			PlyText2HitChk();
		}
		if (text[3].mFlg)
		{
			PlyText3HitChk();
		}
		if (text[4].mFlg)
		{
			PlyText4HitChk();
		}
		if (text[5].mFlg)
		{
			PlyText5HitChk();
		}

		// スクロール量を算出
		scrollX = player.mPosX;
		scrollY = player.mPosY;

		// 画面端のリミット定義
		const float SCR_X_MIN = mapChipX[0][0] + 640;
		const float SCR_X_MAX = mapChipX[0][MAP_CHIP_W - 1] - 640;
		const float SCR_Y_MIN = mapChipY[MAP_CHIP_H - 1][0] + 360;
		const float SCR_Y_MAX = mapChipY[0][0] - 360;

		// 端チェック
		if (scrollX < SCR_X_MIN) scrollX = SCR_X_MIN;
		if (scrollX > SCR_X_MAX) scrollX = SCR_X_MAX;
		if (scrollY < SCR_Y_MIN) scrollY = SCR_Y_MIN;
		if (scrollY > SCR_Y_MAX) scrollY = SCR_Y_MAX;

		/*if (GetAsyncKeyState(VK_SPACE) & 0x8000)
		{
			obj[1].mFlg = false;
			obj[2].mFlg = false;
		}*/

		if (GetAsyncKeyState('R') & 0x8000)
		{
			switch (stg)
			{
			case 0:
				ObjInit0();
				PlayerInit0();
				break;
			case 1:
				ObjInit1();
				PlayerInit1();
				break;
			case 2:
				ObjInit2();
				PlayerInit2();
				break;
			}
		}

		for (int i = 0; i < TUTTEXT_NUM; i++)
		{
			tut[i].mMat = DirectX::XMMatrixTranslation(TUT_X, TUT_Y, 0.0f);
		}

		clrMat = DirectX::XMMatrixTranslation(clrX, clrY, 0.0f);
	}

	
	if (tutmode == 0)
	{
		if (player.mPosX > 120.0f || player.mPosX < -80.0f || player.mPosY > 100.0f || player.mPosY < -100.0f)
		{
			tutmode = 1;
		}
	}
	if (tutmode == 1)
	{
		if (text[0].mFlg && text[1].mFlg)
		{
			tutmode = 2;
		}
	}
	if (tutmode == 2)
	{
		if (!obj[1].mFlg && !obj[2].mFlg && (obj[0].mPosX != -224.0f && obj[0].mPosY != 0.0f))
		{
			tutmode = 3;
		}
	}
	if (stg == 1)
	{
		tutmode = 4;
	}

	/*for (int i = 0; i < SMOKE_MAX; i++)
	{
		smoke[i].Emit(
			Math::Vector2(player.mPosX, player.mPosY),
			Math::Vector2(0, 0),
			0,
			Math::Color(0.0f, 0.0f, 0.0f, 0.0f),
			0,
			true);
	}

	for (int i = 0; i < SMOKE_MAX; i++)
	{
		smoke[i].UpdateFire(0.0f, 0.0f - 32.0f);
		smoke[i].UpdateSmoke(0.0f, 0.0f - 32.0f);
	}*/
}

void Scene::Init()
{
	player.mTex.Load("Texture/player2.png");
	mapChipTex.Load("Texture/mapchip.png");
	obj[0].mTex.Load("Texture/す.png");
	obj[1].mTex.Load("Texture/せ.png");
	obj[2].mTex.Load("Texture/ん.png");
	text[0].mTex.Load("Texture/text0.png");
	text[1].mTex.Load("Texture/text1.png");
	text[2].mTex.Load("Texture/text2.png");
	text[3].mTex.Load("Texture/text3.png");
	text[4].mTex.Load("Texture/text4.png");
	text[5].mTex.Load("Texture/text5.png");
	tut[0].mTex.Load("Texture/descrip1.png");
	tut[1].mTex.Load("Texture/descrip2.png");
	tut[2].mTex.Load("Texture/descrip3.png");
	tut[3].mTex.Load("Texture/descrip6.png");
	tut[4].mTex.Load("Texture/descrip5.png");
	TitleTex.Load("Texture/title0.png");
	StartTex.Load("Texture/title1.png");

	/*smokeTex.Load("Texture/煙.png");
	for (int i = 0; i < SMOKE_MAX; i++)
	{
		smoke[i].SetTexture(&smokeTex);
		smoke[i].Init();
	}*/

	clrTex.Load("Texture/clear.png");

	PlayerInit0();
	ObjInit0();
	TextInit();
	LoadMapFile();
	MapChipInit();

	stg = 0;
	stg0 = true;
	stg1 = false;
	stg2 = false;

	CLR_FLG = false;
	clrX = 688.0f;
	clrY = -400.0f;

	sceneType = 0;
	keyFlg = 0;

	tutmode = 0;
}

void Scene::Release()
{
	player.mTex.Release();
	mapChipTex.Release();
	TitleTex.Release();
	StartTex.Release();
	clrTex.Release();
	//smokeTex.Release();
	for (int i = 0; i < OBJ_NUM; i++)
	{
		obj[i].mTex.Release();
	}
	for (int i = 0; i < TEXT_NUM; i++)
	{
		text[i].mTex.Release();
	}
	for (int i = 0; i < TUTTEXT_NUM; i++)
	{
		tut[i].mTex.Release();
	}

	delete spriteFont;
}

void Scene::ImGuiUpdate()
{
	//return;

	ImGui::SetNextWindowPos(ImVec2(20, 20), ImGuiSetCond_Once);
	ImGui::SetNextWindowSize(ImVec2(200, 500), ImGuiSetCond_Once);

	// デバッグウィンドウ
	if (ImGui::Begin("Debug Window"))
	{
		ImGui::Text("FPS : %d", APP.m_fps);
		ImGui::SliderFloat("PlayerX : %f", &player.mPosX, -640, 800);
		ImGui::SliderFloat("PlayerY : %f", &player.mPosY, -800, 360);
		ImGui::SliderFloat("Obj[0] : %f", &obj[0].mPosX, -640, 800);
		ImGui::SliderFloat("Obj[0] : %f", &obj[0].mPosY, -800, 360);
		ImGui::Checkbox("Obj[0]Flg", &obj[0].mFlg);
		ImGui::Checkbox("text[4]Flg", &text[4].mFlg);
		ImGui::Checkbox("text[5]Flg", &text[5].mFlg);
		ImGui::SliderFloat("Text0X : %f", &text[0].mPosX, -640, 800);
		ImGui::SliderFloat("Text0Y : %f", &text[0].mPosY, -800, 360);
		ImGui::SliderFloat("Text1X : %f", &text[1].mPosX, -640, 800);
		ImGui::SliderFloat("Text1Y : %f", &text[1].mPosY, -800, 360);
		ImGui::SliderFloat("Text2X : %f", &text[2].mPosX, -640, 800);
		ImGui::SliderFloat("Text2Y : %f", &text[2].mPosY, -800, 360);
		ImGui::SliderFloat("Text3X : %f", &text[3].mPosX, -640, 800);
		ImGui::SliderFloat("Text3Y : %f", &text[3].mPosY, -800, 360);
		ImGui::SliderFloat("Text4X : %f", &text[4].mPosX, -640, 800);
		ImGui::SliderFloat("Text4Y : %f", &text[4].mPosY, -800, 360);
		ImGui::SliderFloat("Text5X : %f", &text[5].mPosX, -640, 800);
		ImGui::SliderFloat("Text5Y : %f", &text[5].mPosY, -800, 360);
	}
	ImGui::End();
}

void Scene::PlayerUpdate()
{
	player.mMoveX = 0.0f;
	player.mMoveY = 0.0f;

	// 一回押して一回移動
	/*if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		if (player.mMoveFlg)
		{
			player.mMoveX += 32.0f;
			player.mMoveFlg = false;
		}
	}
	else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		if (player.mMoveFlg)
		{
			player.mMoveX -= 32.0f;
			player.mMoveFlg = false;
		}
	}
	else if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		if (player.mMoveFlg)
		{
			player.mMoveY += 32.0f;
			player.mMoveFlg = false;
		}
	}
	else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		if (player.mMoveFlg)
		{
			player.mMoveY -= 32.0f;
			player.mMoveFlg = false;
		}
	}
	else
	{
		player.mMoveFlg = true;
	}*/

	if (player.mPosX < CLR_X)
	{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			player.mMoveX += 8.0f;
			player.mAnimeWait++;
			if (player.mAnimeWait == 10)
			{
				player.mAnime++;
				player.mAnimeWait = 0;
			}
			player.mAnime %= 4;
		}
		else if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			player.mMoveX -= 8.0f;
			player.mAnimeWait++;
			if (player.mAnimeWait == 10)
			{
				player.mAnime++;
				player.mAnimeWait = 0;
			}
			player.mAnime %= 4;
		}
		else if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			player.mMoveY += 8.0f;
			player.mAnimeWait++;
			if (player.mAnimeWait == 10)
			{
				player.mAnime++;
				player.mAnimeWait = 0;
			}
			player.mAnime %= 4;
		}
		else if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			player.mMoveY -= 8.0f;
			player.mAnimeWait++;
			if (player.mAnimeWait == 10)
			{
				player.mAnime++;
				player.mAnimeWait = 0;
			}
			player.mAnime %= 4;
		}
	}
	else
	{
		CLR_FLG = true;
	}

	player.mPosX += player.mMoveX;
	player.mPosY += player.mMoveY;

	player.mMat = DirectX::XMMatrixTranslation(player.mPosX, player.mPosY, 0.0f);
}

void Scene::PlayerDraw()
{
	int charaWalk[4] = { 0,64,0,128 };
	Math::Matrix sPlayerMat = DirectX::XMMatrixTranslation(player.mPosX - scrollX, player.mPosY - scrollY, 0.0f);
	SHADER.m_spriteShader.SetMatrix(sPlayerMat);
	SHADER.m_spriteShader.DrawTex(&player.mTex, Math::Rectangle(charaWalk[player.mAnime], 0, 32, 32), 1.0f);
}

void Scene::PlayerInit0()
{
	player.mPosX = 20.0f;
	player.mPosY = 0.0f;
	player.mMoveX = 0.0f;
	player.mMoveY = 0.0f;
	player.mMoveFlg = true;
}

void Scene::PlayerInit1()
{
	player.mPosX = 800.0f;
	player.mPosY = 90.0f;
	player.mMoveX = 0.0f;
	player.mMoveY = 0.0f;
	player.mMoveFlg = true;
}

void Scene::PlayerInit2()
{
	player.mPosX = 800.0f;
	player.mPosY = -310.0f;
	player.mMoveX = 0.0f;
	player.mMoveY = 0.0f;
	player.mMoveFlg = true;
}

void Scene::ObjUpdate()
{
	if (obj[0].mFlg&& text[1].mFlg)
	{
		obj[0].mMat = DirectX::XMMatrixTranslation(obj[0].mPosX, obj[0].mPosY, 0.0f);
	}
	if (obj[1].mFlg && text[0].mFlg)
	{
		obj[1].mMat = DirectX::XMMatrixTranslation(obj[1].mPosX, obj[1].mPosY, 0.0f);
	}
	if (obj[2].mFlg && text[0].mFlg)
	{
		obj[2].mMat = DirectX::XMMatrixTranslation(obj[2].mPosX, obj[2].mPosY, 0.0f);
	}
	if (obj[0].mFlg && text[2].mFlg)
	{
		obj[0].mMat = DirectX::XMMatrixTranslation(obj[0].mPosX, obj[0].mPosY, 0.0f);
	}
	if (obj[1].mFlg && text[3].mFlg)
	{
		obj[1].mMat = DirectX::XMMatrixTranslation(obj[1].mPosX, obj[1].mPosY, 0.0f);
	}
	if (obj[2].mFlg && text[3].mFlg)
	{
		obj[2].mMat = DirectX::XMMatrixTranslation(obj[2].mPosX, obj[2].mPosY, 0.0f);
	}
	if (obj[0].mFlg && text[4].mFlg)
	{
		obj[0].mMat = DirectX::XMMatrixTranslation(obj[0].mPosX, obj[0].mPosY, 0.0f);
	}
	if (obj[1].mFlg && text[5].mFlg)
	{
		obj[1].mMat = DirectX::XMMatrixTranslation(obj[1].mPosX, obj[1].mPosY, 0.0f);
	}
	if (obj[2].mFlg && text[5].mFlg)
	{
		obj[2].mMat = DirectX::XMMatrixTranslation(obj[2].mPosX, obj[2].mPosY, 0.0f);
	}

}

void Scene::ObjDraw()
{
	if (obj[0].mFlg&& text[1].mFlg)
	{
		Math::Matrix sObj0Mat = DirectX::XMMatrixTranslation(obj[0].mPosX - scrollX, obj[0].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj0Mat);
		SHADER.m_spriteShader.DrawTex(&obj[0].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[1].mFlg&& text[0].mFlg)
	{
		Math::Matrix sObj1Mat = DirectX::XMMatrixTranslation(obj[1].mPosX - scrollX, obj[1].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj1Mat);
		SHADER.m_spriteShader.DrawTex(&obj[1].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[2].mFlg&& text[0].mFlg)
	{
		Math::Matrix sObj2Mat = DirectX::XMMatrixTranslation(obj[2].mPosX - scrollX, obj[2].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj2Mat);
		SHADER.m_spriteShader.DrawTex(&obj[2].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[0].mFlg && text[2].mFlg)
	{
		Math::Matrix sObj0Mat = DirectX::XMMatrixTranslation(obj[0].mPosX - scrollX, obj[0].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj0Mat);
		SHADER.m_spriteShader.DrawTex(&obj[0].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[1].mFlg && text[3].mFlg)
	{
		Math::Matrix sObj1Mat = DirectX::XMMatrixTranslation(obj[1].mPosX - scrollX, obj[1].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj1Mat);
		SHADER.m_spriteShader.DrawTex(&obj[1].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[2].mFlg && text[3].mFlg)
	{
		Math::Matrix sObj2Mat = DirectX::XMMatrixTranslation(obj[2].mPosX - scrollX, obj[2].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj2Mat);
		SHADER.m_spriteShader.DrawTex(&obj[2].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[0].mFlg && text[4].mFlg)
	{
		Math::Matrix sObj2Mat = DirectX::XMMatrixTranslation(obj[0].mPosX - scrollX, obj[0].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj2Mat);
		SHADER.m_spriteShader.DrawTex(&obj[0].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[1].mFlg && text[5].mFlg)
	{
		Math::Matrix sObj2Mat = DirectX::XMMatrixTranslation(obj[1].mPosX - scrollX, obj[1].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj2Mat);
		SHADER.m_spriteShader.DrawTex(&obj[1].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
	if (obj[2].mFlg && text[5].mFlg)
	{
		Math::Matrix sObj2Mat = DirectX::XMMatrixTranslation(obj[2].mPosX - scrollX, obj[2].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sObj2Mat);
		SHADER.m_spriteShader.DrawTex(&obj[2].mTex, Math::Rectangle(0, 0, 32, 32), true);
	}
}

void Scene::ObjInit0()
{
	obj[0].mPosX = -224.0f;
	obj[0].mPosY = 0.0f;
	obj[1].mPosX = 60.0f;
	obj[1].mPosY = 224.0f;
	obj[2].mPosX = 92.0f;
	obj[2].mPosY = 224.0f;

	for (int i = 0; i < OBJ_NUM; i++)
	{
		obj[i].mFlg = true;
	}
}

void Scene::ObjInit1()
{
	obj[0].mPosX = 511.0f;
	obj[0].mPosY = 260.0f;
	obj[1].mPosX = 691.0f;
	obj[1].mPosY = 140.0f;
	obj[2].mPosX = 723.0f;
	obj[2].mPosY = 140.0f;

	for (int i = 0; i < OBJ_NUM; i++)
	{
		obj[i].mFlg = true;
	}
}

void Scene::ObjInit2()
{
	obj[0].mPosX = 896.0f;
	obj[0].mPosY = -260.0f;
	obj[1].mPosX = -416.0f;
	obj[1].mPosY = -300.0f;
	obj[2].mPosX = -384.0f;
	obj[2].mPosY = -300.0f;

	for (int i = 0; i < OBJ_NUM; i++)
	{
		obj[i].mFlg = true;
	}
}

void Scene::MapChipUpdate()
{
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			mapChipMat[h][w] = DirectX::XMMatrixTranslation(mapChipX[h][w] - scrollX, mapChipY[h][w] - scrollY, 0.0f);
		}
	}
}

void Scene::MapChipDraw()
{
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (mapChipData[h][w] == 0)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(0, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 1)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(64, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 2)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(32, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 3 || mapChipData[h][w] == 4)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(96, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 5 || mapChipData[h][w] == 6 || mapChipData[h][w] == 8)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(128, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 7)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(160, 0, 32, 32), 1.0f);
			}
			if (mapChipData[h][w] == 9)
			{
				SHADER.m_spriteShader.SetMatrix(mapChipMat[h][w]);
				SHADER.m_spriteShader.DrawTex(&mapChipTex, Math::Rectangle(192, 0, 32, 32), 1.0f);
			}
		}
	}
}

void Scene::MapChipInit()
{
	//マップチップの座標を初期化　　左上が（0,0）に補正
	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			mapChipX[h][w] = (32.0f * w) - 640;
			mapChipY[h][w] = (-32.0f * h) + 360;
		}
	}
}

void Scene::LoadMapFile()
{
	FILE* fp;
	if ((fp = fopen("Data/Map/Stage1.txt", "r")) != nullptr)
	{
		printf("ファイル読み込み成功\n\n");

		char ch;
		int h = 0;
		int w = 0;

		while ((ch = fgetc(fp)) != EOF)
		{
			if (ch == '\n')
			{
				h++;
				w = 0;
			}
			else
			{
				mapChipData[h][w] = ch - 0x30;
				w++;
			}
		}
		fclose(fp);
	}
	else
	{
		printf("ファイル読み込み失敗\n\n");
	}

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			printf("%d", mapChipData[h][w]);
		}
		printf("\n");
	}
}

void Scene::TextUpdate()
{
	for (int i = 0; i < TEXT_NUM; i++)
	{
		if (text[i].mFlg)
		{
			text[i].mMat = DirectX::XMMatrixTranslation(text[i].mPosX, text[i].mPosY, 0.0f);
		}
	}
}

void Scene::TextDraw()
{
	if (text[0].mFlg)
	{
		Math::Matrix sText0Mat = DirectX::XMMatrixTranslation(text[0].mPosX - scrollX, text[0].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText0Mat);
		SHADER.m_spriteShader.DrawTex(&text[0].mTex, Math::Rectangle(0, 0, 288, 32), true);
	}

	if (text[1].mFlg)
	{
		Math::Matrix sText1Mat = DirectX::XMMatrixTranslation(text[1].mPosX - scrollX, text[1].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText1Mat);
		SHADER.m_spriteShader.DrawTex(&text[1].mTex, Math::Rectangle(0, 0, 160, 32), true);
	}

	if (text[2].mFlg)
	{
		Math::Matrix sText2Mat = DirectX::XMMatrixTranslation(text[2].mPosX - scrollX, text[2].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText2Mat);
		SHADER.m_spriteShader.DrawTex(&text[2].mTex, Math::Rectangle(0, 0, 160, 32), true);
	}

	if (text[3].mFlg)
	{
		Math::Matrix sText3Mat = DirectX::XMMatrixTranslation(text[3].mPosX - scrollX, text[3].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText3Mat);
		SHADER.m_spriteShader.DrawTex(&text[3].mTex, Math::Rectangle(0, 0, 320, 32), true);
	}

	if (text[4].mFlg)
	{
		Math::Matrix sText4Mat = DirectX::XMMatrixTranslation(text[4].mPosX - scrollX, text[4].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText4Mat);
		SHADER.m_spriteShader.DrawTex(&text[4].mTex, Math::Rectangle(0, 0, 160, 32), true);
	}

	if (text[5].mFlg)
	{
		Math::Matrix sText5Mat = DirectX::XMMatrixTranslation(text[5].mPosX - scrollX, text[5].mPosY - scrollY, 0.0f);
		SHADER.m_spriteShader.SetMatrix(sText5Mat);
		SHADER.m_spriteShader.DrawTex(&text[5].mTex, Math::Rectangle(0, 0, 160, 32), true);
	}
}

void Scene::TextInit()
{
	text[0].mPosX = -100.0f;
	text[0].mPosY = 224.0f;

	text[1].mPosX = -320.0f;
	text[1].mPosY = 0.0f;

	text[2].mPosX = 415.0f;
	text[2].mPosY = 260.0f;

	text[3].mPosX = 515.0f;
	text[3].mPosY = 140.0f;

	text[4].mPosX = 800.0f;
	text[4].mPosY = -260.0f;

	text[5].mPosX = -512.0f;
	text[5].mPosY = -300.0f;

	for (int i = 0; i < TEXT_NUM; i++)
	{
		text[i].mFlg = false;
	}

	// テスト用
	//text[0].mFlg = true;
	//text[1].mFlg = true;
	//text[2].mFlg = true;
	//text[3].mFlg = true;
	//text[4].mFlg = true;
	//text[5].mFlg = true;
}

void Scene::PlyMapHitCheck()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			if (mapChipData[h][w] == 1)
			{
				continue;
			}

			const float chipLeft = mapChipX[h][w] - CHIP_RADIUS;
			const float chipRight = mapChipX[h][w] + CHIP_RADIUS;
			const float chipTop = mapChipY[h][w] + CHIP_RADIUS;
			const float chipBottom = mapChipY[h][w] - CHIP_RADIUS;

			if (playerRight > chipLeft&& playerLeft < chipRight)
			{
				if (nextBottom < chipTop && nextTop > chipTop)
				{
					player.mMoveY = 0.0f;
					player.mPosY = chipTop + PL_RADIUS;
					if (mapChipData[h][w] == 0 && player.mPosY == chipTop + PL_RADIUS && stg == 0)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							if (stg0)
							{
								text[0].mFlg = true;
							}
						}
					}
					if (mapChipData[h][w] == 2 && player.mPosY == chipTop + PL_RADIUS && stg == 0)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							if (stg0)
							{
								text[1].mFlg = true;
							}
						}
					}
					if ((mapChipData[h][w] == 4 || mapChipData[h][w] == 3) && player.mPosY == chipTop + PL_RADIUS && stg == 1)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							if (stg1)
							{
								text[2].mFlg = true;
								text[3].mFlg = true;
							}
						}
					}
					if ((mapChipData[h][w] == 5 || mapChipData[h][w] == 6) && player.mPosY == chipTop + PL_RADIUS && stg == 2)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							if (stg2)
							{
								text[4].mFlg = true;
							}
						}
					}
					if (mapChipData[h][w] == 7 && player.mPosY == chipTop + PL_RADIUS && stg == 2)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							if (stg2)
							{
								text[5].mFlg = true;
							}
						}
					}
				}
				else if (nextTop > chipBottom&& nextBottom < chipBottom)
				{
					player.mMoveY = 0.0f;
					player.mPosY = chipBottom - PL_RADIUS;
					if (mapChipData[h][w] == 0 && player.mPosY == chipBottom - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[0].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 2 && player.mPosY == chipBottom - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[1].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 4 || mapChipData[h][w] == 3) && player.mPosY == chipBottom - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[2].mFlg = true;
							text[3].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 5 || mapChipData[h][w] == 6) && player.mPosY == chipBottom - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[4].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 7 && player.mPosY == chipBottom - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[5].mFlg = true;
						}
					}
				}
			}

			// 現在座標：上下めり込み判定
			if (playerTop > chipBottom&& playerBottom < chipTop)
			{
				if (nextRight > chipLeft&& nextLeft < chipLeft)
				{
					player.mMoveX = 0.0f;
					player.mPosX = chipLeft - PL_RADIUS;
					if (mapChipData[h][w] == 0 && player.mPosX == chipLeft - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[0].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 2 && player.mPosX == chipLeft - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[1].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 4 || mapChipData[h][w] == 3) && player.mPosX == chipLeft - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[2].mFlg = true;
							text[3].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 5 || mapChipData[h][w] == 6) && player.mPosX == chipLeft - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[4].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 7 && player.mPosX == chipLeft - PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[5].mFlg = true;
						}
					}
				}
				else if (nextLeft < chipRight && nextRight > chipRight)
				{
					player.mMoveX = 0.0f;
					player.mPosX = chipRight + PL_RADIUS;
					if (mapChipData[h][w] == 0 && player.mPosX == chipRight + PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[0].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 2 && player.mPosX == chipRight + PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[1].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 4 || mapChipData[h][w] == 3) && player.mPosX == chipRight + PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[2].mFlg = true;
							text[3].mFlg = true;
						}
					}
					if ((mapChipData[h][w] == 5 || mapChipData[h][w] == 6) && player.mPosX == chipRight + PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[4].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 7 && player.mPosX == chipRight + PL_RADIUS)
					{
						if (GetAsyncKeyState(VK_SPACE) & 0x8000)
						{
							text[5].mFlg = true;
						}
					}
				}
			}
		}
	}
}

void Scene::ObjHitCheck()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	for (int i = 1; i < OBJ_NUM; i++)
	{

		if (obj[i].mFlg/*&& (text[0].mFlg || text[2].mFlg || text[4].mFlg)*/)
		{
			const float objLeft = obj[i].mPosX - OBJ_RADIUS;
			const float objRight = obj[i].mPosX + OBJ_RADIUS;
			const float objTop = obj[i].mPosY + OBJ_RADIUS;
			const float objBottom = obj[i].mPosY - OBJ_RADIUS;

			if (playerRight > objLeft&& playerLeft < objRight)
			{
				if (nextBottom < objTop && nextTop > objTop)
				{
					player.mMoveY = 0.0f;
					player.mPosY = objTop + PL_RADIUS;
					if (GetAsyncKeyState(VK_SPACE) & 0x8000)
					{
						obj[i].mFlg = false;
					}
				}
				else if (nextTop > objBottom&& nextBottom < objBottom)
				{
					player.mMoveY = 0.0f;
					player.mPosY = objBottom - PL_RADIUS;
					if (GetAsyncKeyState(VK_SPACE) & 0x8000)
					{
						obj[i].mFlg = false;
					}
				}
			}
			else if (playerTop > objBottom&& playerBottom < objTop)
			{
				if (nextRight > objLeft&& nextLeft < objLeft)
				{
					player.mMoveX = 0.0f;
					player.mPosX = objLeft - PL_RADIUS;
					if (GetAsyncKeyState(VK_SPACE) & 0x8000)
					{
						obj[i].mFlg = false;
					}
				}
				else if (nextLeft < objRight && nextRight > objRight)
				{
					player.mMoveX = 0.0f;
					player.mPosX = objRight + PL_RADIUS;
					if (GetAsyncKeyState(VK_SPACE) & 0x8000)
					{
						obj[i].mFlg = false;
					}
				}
			}
			/*else if ((player.mPosY == objTop + PL_RADIUS && (objLeft - PL_RADIUS <= player.mPosX <= objRight + PL_RADIUS)) || 
				     (player.mPosY == objBottom - PL_RADIUS && (objLeft - PL_RADIUS <= player.mPosX <= objRight + PL_RADIUS)) ||
					 (player.mPosX == objLeft - PL_RADIUS && (objBottom - PL_RADIUS <= player.mPosY <= objTop + PL_RADIUS)) ||
				     (player.mPosX == objRight + PL_RADIUS && (objBottom - PL_RADIUS <= player.mPosY <= objTop + PL_RADIUS)))
			{
				if (GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					obj[i].mFlg = false;
				}
			}*/
		}
	}

	//for (int i = 0; i < 1; i++)
	
	if (text[1].mFlg && stg0)
	{
		const float objLeft = obj[0].mPosX - OBJ_RADIUS;
		const float objRight = obj[0].mPosX + OBJ_RADIUS;
		const float objTop = obj[0].mPosY + OBJ_RADIUS;
		const float objBottom = obj[0].mPosY - OBJ_RADIUS;

		if (playerRight > objLeft&& playerLeft < objRight)
		{
			if (nextBottom < objTop && nextTop > objTop)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objTop + PL_RADIUS;
				if (obj[0].mPosY != 224.0f)
				{
					obj[0].mPosY -= 8.0f;
				}
			}
			else if (nextTop > objBottom&& nextBottom < objBottom)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objBottom - PL_RADIUS;
				if (obj[0].mPosY != 224.0f)
				{
					obj[0].mPosY += 8.0f;
				}
			}
		}
		else if (playerTop > objBottom&& playerBottom < objTop)
		{
			if (nextRight > objLeft&& nextLeft < objLeft)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objLeft - PL_RADIUS;
				if (obj[0].mPosX != 60.0f)
				{
					obj[0].mPosX += 8.0f;
				}
			}
			else if (nextLeft < objRight && nextRight > objRight)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objRight + PL_RADIUS;
				if (obj[0].mPosX != 60.0f)
				{
					obj[0].mPosX -= 8.0f;
				}
			}
		}
		if (obj[0].mPosX == 60.0f && obj[0].mPosY == 224.0f)
		{
			for (int h = 0; h < MAP_CHIP_H; h++)
			{
				for (int w = 0; w < MAP_CHIP_W; w++)
				{
					if (mapChipData[h][w] == 2)
					{
						mapChipData[h][w] = 1;
						text[0].mFlg = false;
						text[1].mFlg = false;
						stg0 = false;
						stg1 = true;
						stg = 1;
						ObjInit1();
						for (int i = 0; i < OBJ_NUM; i++)
						{
							obj[i].mFlg = true;
						}
					}
				}
			}
		}
	}

	//for (int i = 0; i < 1; i++)
	
	if (text[2].mFlg && stg1)
	{
		const float objLeft = obj[0].mPosX - OBJ_RADIUS;
		const float objRight = obj[0].mPosX + OBJ_RADIUS;
		const float objTop = obj[0].mPosY + OBJ_RADIUS;
		const float objBottom = obj[0].mPosY - OBJ_RADIUS;

		if (playerRight > objLeft&& playerLeft < objRight)
		{
			if (nextBottom < objTop && nextTop > objTop)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objTop + PL_RADIUS;
				if (obj[0].mPosY != 140.0f)
				{
					obj[0].mPosY -= 8.0f;
				}
			}
			else if (nextTop > objBottom&& nextBottom < objBottom)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objBottom - PL_RADIUS;
				if (obj[0].mPosY != 140.0f)
				{
					obj[0].mPosY += 8.0f;
				}
			}
		}
		else if (playerTop > objBottom&& playerBottom < objTop)
		{
			if (nextRight > objLeft&& nextLeft < objLeft)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objLeft - PL_RADIUS;
				if (obj[0].mPosX != 691.0f)
				{
					obj[0].mPosX += 8.0f;
				}
			}
			else if (nextLeft < objRight && nextRight > objRight)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objRight + PL_RADIUS;
				if (obj[0].mPosX != 691.0f)
				{
					obj[0].mPosX -= 8.0f;
				}
			}
		}
		if (obj[0].mPosX == 691.0f && obj[0].mPosY == 140.0f)
		{
			for (int h = 0; h < MAP_CHIP_H; h++)
			{
				for (int w = 0; w < MAP_CHIP_W; w++)
				{
					if (mapChipData[h][w] == 4)
					{
						mapChipData[h][w] = 1;
						text[2].mFlg = false;
						text[3].mFlg = false;
						stg1 = false;
						stg2 = true;
						stg = 2;
						ObjInit2();
						for (int i = 0; i < OBJ_NUM; i++)
						{
							obj[i].mFlg = true;
						}
					}
				}
			}
		}
	}
	

	//for (int i = 0; i < 1; i++)
	
	if (text[4].mFlg && stg2)
	{
		const float objLeft = obj[0].mPosX - OBJ_RADIUS;
		const float objRight = obj[0].mPosX + OBJ_RADIUS;
		const float objTop = obj[0].mPosY + OBJ_RADIUS;
		const float objBottom = obj[0].mPosY - OBJ_RADIUS;

		if (playerRight > objLeft&& playerLeft < objRight)
		{
			if (nextBottom < objTop && nextTop > objTop)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objTop + PL_RADIUS;
				if (obj[0].mPosY != -300.0f)
				{
					obj[0].mPosY -= 8.0f;
				}
			}
			else if (nextTop > objBottom&& nextBottom < objBottom)
			{
				player.mMoveY = 0.0f;
				player.mPosY = objBottom - PL_RADIUS;
				if (obj[0].mPosY != -300.0f)
				{
					obj[0].mPosY += 8.0f;
				}
			}
		}
		else if (playerTop > objBottom&& playerBottom < objTop)
		{
			if (nextRight > objLeft&& nextLeft < objLeft)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objLeft - PL_RADIUS;
				if (obj[0].mPosX != -416.0f)
				{
					obj[0].mPosX += 8.0f;
				}
			}
			else if (nextLeft < objRight && nextRight > objRight)
			{
				player.mMoveX = 0.0f;
				player.mPosX = objRight + PL_RADIUS;
				if (obj[0].mPosX != -416.0f)
				{
					obj[0].mPosX -= 8.0f;
				}
			}
		}
		if (obj[0].mPosX == -416.0f && obj[0].mPosY == -300.0f)
		{
			for (int h = 0; h < MAP_CHIP_H; h++)
			{
				for (int w = 0; w < MAP_CHIP_W; w++)
				{
					if (mapChipData[h][w] == 6)
					{
						mapChipData[h][w] = 1;
						text[4].mFlg = false;
						text[5].mFlg = false;
						//ObjInit1();
						for (int i = 0; i < OBJ_NUM; i++)
						{
							obj[i].mFlg = true;
						}
					}
					if (mapChipData[h][w] == 8)
					{
						mapChipData[h][w] = 7;
						//ObjInit1();
						for (int i = 0; i < OBJ_NUM; i++)
						{
							obj[i].mFlg = true;
						}
					}
				}
			}
		}
	}
}

void Scene::ObjMapHitChk()
{
	for (int i = 0; i < OBJ_NUM; i++)
	{
		const float objLeft = obj[i].mPosX - OBJ_RADIUS;
		const float objRight = obj[i].mPosX + OBJ_RADIUS;
		const float objTop = obj[i].mPosY + OBJ_RADIUS;
		const float objBottom = obj[i].mPosY - OBJ_RADIUS;

		const float nextLeft = objLeft + obj[i].mMoveX;
		const float nextRight = objRight + obj[i].mMoveX;
		const float nextTop = objTop + obj[i].mMoveY;
		const float nextBottom = objBottom + obj[i].mMoveY;

		for (int h = 0; h < MAP_CHIP_H; h++)
		{
			for (int w = 0; w < MAP_CHIP_W; w++)
			{
				if (mapChipData[h][w] == 1)
				{
					continue;
				}

				const float chipLeft = mapChipX[h][w] - CHIP_RADIUS;
				const float chipRight = mapChipX[h][w] + CHIP_RADIUS;
				const float chipTop = mapChipY[h][w] + CHIP_RADIUS;
				const float chipBottom = mapChipY[h][w] - CHIP_RADIUS;

				if (objRight > chipLeft&& objLeft < chipRight)
				{
					if (nextBottom < chipTop && nextTop > chipTop)
					{
						obj[i].mPosY = chipTop + PL_RADIUS;
					}
					else if (nextTop > chipBottom&& nextBottom < chipBottom)
					{
						obj[i].mPosY = chipBottom - PL_RADIUS;
					}
				}

				if (objTop > chipBottom&& objBottom < chipTop)
				{
					if (nextRight > chipLeft&& nextLeft < chipLeft)
					{
						obj[i].mPosX = chipLeft - PL_RADIUS;
					}
					else if (nextLeft < chipRight && nextRight > chipRight)
					{
						obj[i].mPosX = chipRight + PL_RADIUS;
					}
				}
			}
		}
	}
}

void Scene::PlyText0HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text0Left = text[0].mPosX - 144.0f;
	const float text0Right = text[0].mPosX + 144.0f;
	const float text0Top = text[0].mPosY + 16.0f;
	const float text0Bottom = text[0].mPosY - 16.0f;

	if (playerRight > text0Left&& playerLeft < text0Right)
	{
		if (nextBottom < text0Top && nextTop > text0Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text0Top + PL_RADIUS;
		}
		else if (nextTop > text0Bottom&& nextBottom < text0Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text0Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text0Bottom&& playerBottom < text0Top)
	{
		if (nextRight > text0Left&& nextLeft < text0Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text0Left - PL_RADIUS;
		}
		else if (nextLeft < text0Right && nextRight > text0Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text0Right + PL_RADIUS;
		}
	}
}

void Scene::PlyText1HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text1Left = text[1].mPosX - 80.0f;
	const float text1Right = text[1].mPosX + 80.0f;
	const float text1Top = text[1].mPosY + 16.0f;
	const float text1Bottom = text[1].mPosY - 16.0f;

	if (playerRight > text1Left&& playerLeft < text1Right)
	{
		if (nextBottom < text1Top && nextTop > text1Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text1Top + PL_RADIUS;
		}
		else if (nextTop > text1Bottom&& nextBottom < text1Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text1Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text1Bottom&& playerBottom < text1Top)
	{
		if (nextRight > text1Left&& nextLeft < text1Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text1Left - PL_RADIUS;
		}
		else if (nextLeft < text1Right && nextRight > text1Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text1Right + PL_RADIUS;
		}
	}
}

void Scene::PlyText2HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text2Left = text[2].mPosX - 80.0f;
	const float text2Right = text[2].mPosX + 80.0f;
	const float text2Top = text[2].mPosY + 16.0f;
	const float text2Bottom = text[2].mPosY - 16.0f;

	if (playerRight > text2Left&& playerLeft < text2Right)
	{
		if (nextBottom < text2Top && nextTop > text2Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text2Top + PL_RADIUS;
		}
		else if (nextTop > text2Bottom&& nextBottom < text2Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text2Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text2Bottom&& playerBottom < text2Top)
	{
		if (nextRight > text2Left&& nextLeft < text2Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text2Left - PL_RADIUS;
		}
		else if (nextLeft < text2Right && nextRight > text2Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text2Right + PL_RADIUS;
		}
	}
}

void Scene::PlyText3HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text3Left = text[3].mPosX - 160.0f;
	const float text3Right = text[3].mPosX + 160.0f;
	const float text3Top = text[3].mPosY + 16.0f;
	const float text3Bottom = text[3].mPosY - 16.0f;

	if (playerRight > text3Left&& playerLeft < text3Right)
	{
		if (nextBottom < text3Top && nextTop > text3Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text3Top + PL_RADIUS;
		}
		else if (nextTop > text3Bottom&& nextBottom < text3Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text3Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text3Bottom&& playerBottom < text3Top)
	{
		if (nextRight > text3Left&& nextLeft < text3Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text3Left - PL_RADIUS;
		}
		else if (nextLeft < text3Right && nextRight > text3Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text3Right + PL_RADIUS;
		}
	}
}

void Scene::PlyText4HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text4Left = text[4].mPosX - 80.0f;
	const float text4Right = text[4].mPosX + 80.0f;
	const float text4Top = text[4].mPosY + 16.0f;
	const float text4Bottom = text[4].mPosY - 16.0f;

	if (playerRight > text4Left&& playerLeft < text4Right)
	{
		if (nextBottom < text4Top && nextTop > text4Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text4Top + PL_RADIUS;
		}
		else if (nextTop > text4Bottom&& nextBottom < text4Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text4Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text4Bottom&& playerBottom < text4Top)
	{
		if (nextRight > text4Left&& nextLeft < text4Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text4Left - PL_RADIUS;
		}
		else if (nextLeft < text4Right && nextRight > text4Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text4Right + PL_RADIUS;
		}
	}
}

void Scene::PlyText5HitChk()
{
	const float playerLeft = player.mPosX - PL_RADIUS;
	const float playerRight = player.mPosX + PL_RADIUS;
	const float playerTop = player.mPosY + PL_RADIUS;
	const float playerBottom = player.mPosY - PL_RADIUS;

	const float nextLeft = playerLeft + player.mMoveX;
	const float nextRight = playerRight + player.mMoveX;
	const float nextTop = playerTop + player.mMoveY;
	const float nextBottom = playerBottom + player.mMoveY;

	const float text5Left = text[5].mPosX - 80.0f;
	const float text5Right = text[5].mPosX + 80.0f;
	const float text5Top = text[5].mPosY + 16.0f;
	const float text5Bottom = text[5].mPosY - 16.0f;

	if (playerRight > text5Left&& playerLeft < text5Right)
	{
		if (nextBottom < text5Top && nextTop > text5Top)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text5Top + PL_RADIUS;
		}
		else if (nextTop > text5Bottom&& nextBottom < text5Bottom)
		{
			player.mMoveY = 0.0f;
			player.mPosY = text5Bottom - PL_RADIUS;
		}
	}

	if (playerTop > text5Bottom&& playerBottom < text5Top)
	{
		if (nextRight > text5Left&& nextLeft < text5Left)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text5Left - PL_RADIUS;
		}
		else if (nextLeft < text5Right && nextRight > text5Right)
		{
			player.mMoveX = 0.0f;
			player.mPosX = text5Right + PL_RADIUS;
		}
	}
}

void Scene::ObjText0HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text0Left = text[0].mPosX - 144.0f;
	const float text0Right = text[0].mPosX + 144.0f;
	const float text0Top = text[0].mPosY + 16.0f;
	const float text0Bottom = text[0].mPosY - 16.0f;

	if (objRight > text0Left&& objLeft < text0Right)
	{
		if (nextBottom < text0Top && nextTop > text0Top)
		{
			obj[0].mPosY = text0Top + OBJ_RADIUS;
		}
		else if (nextTop > text0Bottom&& nextBottom < text0Bottom)
		{
			obj[0].mPosY = text0Bottom - OBJ_RADIUS;
		}

		if (objTop > text0Bottom&& objBottom < text0Top)
		{
			if (nextRight > text0Left&& nextLeft < text0Left)
			{
				obj[0].mPosX = text0Left - OBJ_RADIUS;
			}
			else if (nextLeft < text0Right && nextRight > text0Right)
			{
				obj[0].mPosX = text0Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::ObjText1HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text1Left = text[1].mPosX - 80.0f;
	const float text1Right = text[1].mPosX + 80.0f;
	const float text1Top = text[1].mPosY + 16.0f;
	const float text1Bottom = text[1].mPosY - 16.0f;

	if (objRight > text1Left&& objLeft < text1Right)
	{
		if (nextBottom < text1Top && nextTop > text1Top)
		{
			obj[0].mPosY = text1Top + OBJ_RADIUS;
		}
		else if (nextTop > text1Bottom&& nextBottom < text1Bottom)
		{
			obj[0].mPosY = text1Bottom - OBJ_RADIUS;
		}

		if (objTop > text1Bottom&& objBottom < text1Top)
		{
			if (nextRight > text1Left&& nextLeft < text1Left)
			{
				obj[0].mPosX = text1Left - OBJ_RADIUS;
			}
			else if (nextLeft < text1Right && nextRight > text1Right)
			{
				obj[0].mPosX = text1Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::ObjText2HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text2Left = text[2].mPosX - 80.0f;
	const float text2Right = text[2].mPosX + 80.0f;
	const float text2Top = text[2].mPosY + 16.0f;
	const float text2Bottom = text[2].mPosY - 16.0f;

	if (objRight > text2Left&& objLeft < text2Right)
	{
		if (nextBottom < text2Top && nextTop > text2Top)
		{
			obj[0].mPosY = text2Top + OBJ_RADIUS;
		}
		else if (nextTop > text2Bottom&& nextBottom < text2Bottom)
		{
			obj[0].mPosY = text2Bottom - OBJ_RADIUS;
		}

		if (objTop > text2Bottom&& objBottom < text2Top)
		{
			if (nextRight > text2Left&& nextLeft < text2Left)
			{
				obj[0].mPosX = text2Left - OBJ_RADIUS;
			}
			else if (nextLeft < text2Right && nextRight > text2Right)
			{
				obj[0].mPosX = text2Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::ObjText3HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text3Left = text[3].mPosX - 160.0f;
	const float text3Right = text[3].mPosX + 160.0f;
	const float text3Top = text[3].mPosY + 16.0f;
	const float text3Bottom = text[3].mPosY - 16.0f;

	if (objRight > text3Left&& objLeft < text3Right)
	{
		if (nextBottom < text3Top && nextTop > text3Top)
		{
			obj[0].mPosY = text3Top + OBJ_RADIUS;
		}
		else if (nextTop > text3Bottom&& nextBottom < text3Bottom)
		{
			obj[0].mPosY = text3Bottom - OBJ_RADIUS;
		}

		if (objTop > text3Bottom&& objBottom < text3Top)
		{
			if (nextRight > text3Left&& nextLeft < text3Left)
			{
				obj[0].mPosX = text3Left - OBJ_RADIUS;
			}
			else if (nextLeft < text3Right && nextRight > text3Right)
			{
				obj[0].mPosX = text3Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::ObjText4HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text4Left = text[4].mPosX - 80.0f;
	const float text4Right = text[4].mPosX + 80.0f;
	const float text4Top = text[4].mPosY + 16.0f;
	const float text4Bottom = text[4].mPosY - 16.0f;

	if (objRight > text4Left&& objLeft < text4Right)
	{
		if (nextBottom < text4Top && nextTop > text4Top)
		{
			obj[0].mPosY = text4Top + OBJ_RADIUS;
		}
		else if (nextTop > text4Bottom&& nextBottom < text4Bottom)
		{
			obj[0].mPosY = text4Bottom - OBJ_RADIUS;
		}

		if (objTop > text4Bottom&& objBottom < text4Top)
		{
			if (nextRight > text4Left&& nextLeft < text4Left)
			{
				obj[0].mPosX = text4Left - OBJ_RADIUS;
			}
			else if (nextLeft < text4Right && nextRight > text4Right)
			{
				obj[0].mPosX = text4Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::ObjText5HitChk()
{
	const float objLeft = obj[0].mPosX - OBJ_RADIUS;
	const float objRight = obj[0].mPosX + OBJ_RADIUS;
	const float objTop = obj[0].mPosY + OBJ_RADIUS;
	const float objBottom = obj[0].mPosY - OBJ_RADIUS;

	const float nextLeft = objLeft + obj[0].mMoveX;
	const float nextRight = objRight + obj[0].mMoveX;
	const float nextTop = objTop + obj[0].mMoveY;
	const float nextBottom = objBottom + obj[0].mMoveY;

	const float text5Left = text[5].mPosX - 80.0f;
	const float text5Right = text[5].mPosX + 80.0f;
	const float text5Top = text[5].mPosY + 16.0f;
	const float text5Bottom = text[5].mPosY - 16.0f;

	if (objRight > text5Left&& objLeft < text5Right)
	{
		if (nextBottom < text5Top && nextTop > text5Top)
		{
			obj[0].mPosY = text5Top + OBJ_RADIUS;
		}
		else if (nextTop > text5Bottom&& nextBottom < text5Bottom)
		{
			obj[0].mPosY = text5Bottom - OBJ_RADIUS;
		}

		if (objTop > text5Bottom&& objBottom < text5Top)
		{
			if (nextRight > text5Left&& nextLeft < text5Left)
			{
				obj[0].mPosX = text5Left - OBJ_RADIUS;
			}
			else if (nextLeft < text5Right && nextRight > text5Right)
			{
				obj[0].mPosX = text5Right + OBJ_RADIUS;
			}
		}
	}
}

void Scene::TitleUpdate()
{
}

void Scene::TitleDraw()
{
}

void Scene::LoadTutMapFile()
{
	FILE* fp;
	if ((fp = fopen("Data/Map/Tutorial.txt", "r")) != nullptr)
	{
		printf("ファイル読み込み成功\n\n");

		char ch;
		int h = 0;
		int w = 0;

		while ((ch = fgetc(fp)) != EOF)
		{
			if (ch == '\n')
			{
				h++;
				w = 0;
			}
			else
			{
				mapChipData[h][w] = ch - 0x30;
				w++;
			}
		}
		fclose(fp);
	}
	else
	{
		printf("ファイル読み込み失敗\n\n");
	}

	for (int h = 0; h < MAP_CHIP_H; h++)
	{
		for (int w = 0; w < MAP_CHIP_W; w++)
		{
			printf("%d", mapChipData[h][w]);
		}
		printf("\n");
	}
}

float Scene::Rnd()
{
	return rand() / (float)RAND_MAX;
}


