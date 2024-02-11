#include <Novice.h>
#include "matrix.h"

const char kWindowTitle[] = "GC1D_03_イトウシュンヤ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 480, 960);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Ball ball1 = {
		{160,960},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0,0},
		{0,0},
		10,
		1,
		WHITE,
		{0},
		{0}
	};

	Ball ball2 = {
		{320,960},
		{0.0f,0.0f},
		{0.0f,0.0f},
		{0,0},
		{0,0},
		10,
		1,
		WHITE,
		{0},
		{0}
	};

	float Gravity = -9.8f;
	bool IsFall = false;
	float speed = 5;


	Vector2 cameraPos = { 240,480 };
	float Left = -240, Right = 240, Top = 490, Bottom = -490;
	Matrix3x3 cameraMatrix = {};
	Matrix3x3 viewMatrix = {};
	Matrix3x3 orthoMatrix = {};
	Matrix3x3 viewportMatrix = {};
	Matrix3x3 vpVpMatrix = {};






	Line localLine1 = { -1000,0,1000,0 };
	Line Screenline1 = {};

	Line localLine2 = { 0,-200,0,1000 };
	Line Screenline2 = {};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		
		

		cameraMatrix = MakeTrancelateMatrix(cameraPos);
		viewMatrix = Inverse(cameraMatrix);
		orthoMatrix = MakeOrthographicMatrix(Left, Top, Right, Bottom);
		viewportMatrix = MakeViewportMatrix(0, 0, 480, 980);

		vpVpMatrix = Multiply(viewMatrix, orthoMatrix);
		vpVpMatrix = Multiply(vpVpMatrix, viewportMatrix);

		

		if (keys[DIK_UP]) {
			cameraPos.y += speed;
		}

		if (keys[DIK_DOWN]) {
			cameraPos.y -= speed;
		}

		if (keys[DIK_LEFT]) {
			cameraPos.x -= speed;
		}

		if (keys[DIK_RIGHT]) {
			cameraPos.x += speed;
		}

		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
			IsFall = true;
		}

		if (IsFall == true) {
			ball1.Acceleration.y = Gravity;
			ball2.Acceleration.y = Gravity;
		}

		ball1.Velocity.y += ball1.Acceleration.y / 60.0f;
		ball2.Velocity.y += ball2.Acceleration.y / 60.0f;
		ball1.Pos.y += ball1.Velocity.y / 60.0f;
		ball2.Pos.y += ball2.Velocity.y / 60.0f;

		ball1.WorldMatrix = MakeTrancelateMatrix(ball1.Pos);
		ball2.WorldMatrix = MakeTrancelateMatrix(ball2.Pos);

		ball1.WvpVpMatrix = Multiply(vpVpMatrix, ball1.WorldMatrix);
		ball2.WvpVpMatrix = Multiply(vpVpMatrix, ball2.WorldMatrix);

		ball1.Screen = Tranceform(ball1.Local, ball1.WvpVpMatrix);
		ball2.Screen = Tranceform(ball2.Local, ball2.WvpVpMatrix);



		Screenline1.begin = Tranceform(localLine1.begin, vpVpMatrix);
		Screenline1.end = Tranceform(localLine1.end, vpVpMatrix);

		Screenline2.begin = Tranceform(localLine2.begin, vpVpMatrix);
		Screenline2.end = Tranceform(localLine2.end, vpVpMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(100, 100, "ballposY=%f", ball1.Pos.y);

		Novice::DrawLine((int)Screenline1.begin.x, (int)Screenline1.begin.y, (int)Screenline1.end.x, (int)Screenline1.end.y, GREEN);
		Novice::DrawLine((int)Screenline2.begin.x, (int)Screenline2.begin.y, (int)Screenline2.end.x, (int)Screenline2.end.y, RED);
		
		Novice::DrawEllipse((int)ball1.Screen.x, (int)ball1.Screen.y, (int)ball1.Radius, (int)ball1.Radius, 0.0f, ball1.Color, kFillModeSolid);
		Novice::DrawEllipse((int)ball2.Screen.x, (int)ball2.Screen.y, (int)ball2.Radius, (int)ball2.Radius, 0.0f, ball2.Color, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
