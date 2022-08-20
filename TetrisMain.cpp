#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Console.h"

// 4차원배열로 블럭형태 생성
// [FORM][ROTATE][x][y]
int Minos[7][4][4][4] = {
	{ // T 블럭
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{0,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{    // S 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,1,0,0}
		}
	},
	{   // Z 블럭
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{1,0,0,0}
		}
	},
	{   // 1자형 블럭
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		},
		{
			{0,0,0,0},
			{0,0,0,0},
			{1,1,1,1},
			{0,0,0,0}
		}
	},
	{   // L 블럭
		{
			{0,0,0,0},
			{1,0,0,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{1,0,0,0},
			{1,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{0,0,1,0},
			{0,0,0,0}
		},
		{
			{0,1,0,0},
			{0,1,0,0},
			{1,1,0,0},
			{0,0,0,0}
		}
	},
	{   // J 블럭
		{
			{0,0,0,0},
			{0,0,1,0},
			{1,1,1,0},
			{0,0,0,0}
		},
		{
			{1,0,0,0},
			{1,0,0,0},
			{1,1,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,1,0},
			{1,0,0,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{1,1,0,0},
			{0,1,0,0},
			{0,1,0,0}
		}
	},
	{   // O 블럭
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		},
		{
			{0,0,0,0},
			{0,1,1,0},
			{0,1,1,0},
			{0,0,0,0}
		}
	}
};

int Map[20 + 1][12 + 2] = { NULL }; // 내부 칸 + 벽 칸 

int MinoForm = 0;
int MinoRotate = 0;
int Minox = 10, Minoy = 0;

void Init();
void DrawMap();
void RandomM();
void DrawMinos();
void DropMinos();
void MinoToMap();
void RemoveMap();
void InputProcess();
void GameMain();
void StartMenu();
void GameFail();
void CreateMap();
void GUI();
void Loading();
bool CheckGameFail();

int main() {
	// 게임세팅
	Init();

	// 스타트메뉴
	StartMenu();

	// 처음 생성될 블럭 생성
	RandomM();

	// 맵 생성
	CreateMap();

	// 로딩 표시
	Loading();

	// 게임 시작
	GameMain();
}

void Init() {
	// 흰색 커서 지우기
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
	
	// 콘솔창 크기 지정 / 가로 : 70 , 세로 21
	system("mode con cols=70 lines=21");
}

// 시작메뉴
void StartMenu() {
	while (1) {
		Clear(); 
		GotoXY(30,7);
		printf("테트리스");
		GotoXY(18,15);
		printf("시작하려면 스페이스바를 눌러주세요");

		// 아무 키나 입력 됐을 경우 게임 시작
		if (GetAsyncKeyState(VK_SPACE) && 0x8000) {
			
		
			break;
		}
		Sleep(100);
	}
}

// 맵 생성
void CreateMap() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 14; j++) {
			if (i == 20) {
				Map[i][j] = 1;
			}
			else {
				if (j == 0 || j == 13) {
					Map[i][j] = 1;
				}
				else {
					Map[i][j] = 0;
				}
			}
		}
	}
}

void Loading() {
	Clear();
	for (int i = 0; i < 3; i++) {
		GotoXY(31 + (i * 2), 10);
		printf(".");
		Sleep(500);
	}
	GotoXY(31, 12);
	printf("시작!");
	Sleep(200);
}

// 게임시작
void GameMain() {
	while (1) {
		Clear();

		// 맵 그리기
		DrawMap();

		// 조작키 등 GUI 표시
		GUI();

		// 생성된 블럭 그리기
		DrawMinos();

		// 블럭 떨구기
		DropMinos();

		// 키 조작
		InputProcess();
		
		// 블럭이 땅 / 블럭에 닿을 경우 멈추게하고 다음 블럭 생성하기
		MinoToMap();
		
		// 한줄이 꽉 찼을 경우 지우기
		RemoveMap();

		// 게임 실패 체크
		GameFail();

		Sleep(100);
	}
}

void DrawMap() {
	GotoXY(0, 0);

	// 배열로 지정된 맵 그리기 
	// 1 : 벽 , 0 : 빈공간 , 2 : 쌓인블럭
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == 1) {
				GotoXY(j * 2, i);
				printf("□");
			}
			else if (Map[i][j] == 2) {
				GotoXY(j * 2, i);
				printf("■");
			}
			else {
				GotoXY(j * 2, i);
				printf("·");
			}
		}
	}
}

void RandomM() {
	srand(time(NULL));
	MinoForm = rand() % 7;
}

void DrawMinos() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Minos[MinoForm][MinoRotate][i][j]) {
				GotoXY(Minox + j * 2, Minoy + i);
				printf("■");
			}
		}
	}
}

// 충돌 체크
bool CrashCheck(int x,int y,int Rotate) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Minos[MinoForm][Rotate][i][j] == 1) {
				int t = Map[i + y][j + x / 2];
				if (t == 1 || t == 2) {
					return true;
				}
			}
		}
	}
	return false;
}

void DropMinos() {
	// 충돌하지 않을 경우 떨구기
	if (CrashCheck(Minox, Minoy + 1,MinoRotate) == true) {
		return;
	}
	else {
		Minoy++;
	}
}

void MinoToMap() {
	// 땅이나 블럭에 닿았을 경우 Map에 2로 지정
	if (CrashCheck(Minox, Minoy + 1, MinoRotate) == true) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Minos[MinoForm][MinoRotate][i][j] == 1) {
					Map[i + Minoy][j + Minox / 2] = 2;
				}
			}
		}
		// 새로운 블럭 생성
		MinoRotate = 0;
		Minox = 10;
		Minoy = 0;
		RandomM();
	}
}

void RemoveMap() {
	// 고정된 블럭들 세기
	for (int i = 19; i >= 0; i--) {
		int cnt = 0;
		for (int j = 1; j < 11; j++) {
			if (Map[i][j] == 2) {
				cnt++;
			}
		}

		// 고정된 블럭이 한줄에 꽉 찼을 때 지우기
		if (cnt >= 10) {
			for (int j = 0; j <= i; j++) {
				for (int k = 0; k < 11; k++) {
					if (i - j - 1 >= 0)
						Map[i - j][k] = Map[i - j - 1][k];
					else
						Map[i - j][k] = 0;
				}
			}
		}
	}
}

void InputProcess() {
	// 왼쪽으로 이동
	if (GetAsyncKeyState(VK_LEFT) && 0x8000) {
		if (CrashCheck(Minox - 2, Minoy, MinoRotate) == false) {
			Minox -= 2;
		}
	}
	// 오른쪽으로 이동
	if (GetAsyncKeyState(VK_RIGHT) && 0x8000) {
		if (CrashCheck(Minox + 2, Minoy, MinoRotate) == false) {
			Minox += 2;
		}
	}
	// 회전
	if (GetAsyncKeyState(VK_UP) && 0x8000) {
		MinoRotate++;
		if (MinoRotate >= 4) {
			MinoRotate = 0;
		}
		// 회전했을때 벽과 겹칠경우
		if (CrashCheck(Minox,Minoy,MinoRotate) == true) {
			// 왼쪽벽과 부딪혔을 경우
			if (Minox >= 0 && Minox <= 6) {
				// 겹치지 않을 때까지 좌표 오른쪽으로 이동
				while (CrashCheck(Minox, Minoy, MinoRotate) == true) {
					Minox += 2;
				}
			}
			// 오른쪽벽과 부딪혔을 경우
			else if (Minox <= 22 && Minox >= 16) {
				// 겹치지 않을 때까지 좌표 왼쪽으로 이동
				while (CrashCheck(Minox, Minoy, MinoRotate) == true) {
					Minox -= 2;
				}
			}
		}
	}
}

bool CheckGameFail() {
	for (int j = 0; j < 14; j++) {
		// 맵 맨 윗줄이 찼을 경우 게임 실패
		if (Map[1][j] == 2) {
			return true;
		}
	}
	return false;
}

// 게임실패
void GameFail() {
	if (CheckGameFail() == true) {
		while (1) {
			Clear();
			GotoXY(28, 7);
			printf("클리어 실패!");
			GotoXY(20, 15);
			printf("다시하려면 ↑ / 종료하려면 ↓");
			
			if (GetAsyncKeyState(VK_UP) && 0x8000) {
				main();
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) && 0x8000) {
				Sleep(1000);
				exit(0);
			}
		}
	}
}

void GUI() {
	GotoXY(35, 6);
	printf("조작법");
	GotoXY(35, 9);
	printf("Left = ← / Right = →");
	GotoXY(35, 11);
	printf("Rotate = ↑");
}