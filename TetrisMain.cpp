#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Console.h"

// 4�����迭�� ������ ����
// [FORM][ROTATE][x][y]
int Minos[7][4][4][4] = {
	{ // T ��
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
	{    // S ��
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
	{   // Z ��
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
	{   // 1���� ��
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
	{   // L ��
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
	{   // J ��
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
	{   // O ��
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

int Map[20 + 1][12 + 2] = { NULL }; // ���� ĭ + �� ĭ 

int MinoForm = 0;
int MinoRotate = 0;
int Minox = 4, Minoy = 0;

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
void CheckGameFail();
void GUI();

int main() {
	// ���Ӽ���
	Init();

	// ��ŸƮ�޴�
	StartMenu();

	// ó�� ������ �� ����
	RandomM();

	// �� ����
	CreateMap();

	// ���� ����
	GameMain();
}

void Init() {
	// ��� Ŀ�� �����
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand(time(NULL));
	
	// �ܼ�â ũ�� ���� / ���� : 70 , ���� 21
	system("mode con cols=70 lines=21");
}

// ���۸޴�
void StartMenu() {
	while (1) {
		Clear();
		GotoXY(30,7);
		printf("��Ʈ����");
		GotoXY(18,15);
		printf("�����Ϸ��� �ƹ� Ű�� �����ּ���");

		// �ƹ� Ű�� �Է� ���� ��� ���� ����
		if (_kbhit()) {
			break;
		}
		Sleep(100);
	}
}

// �� ����
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

// ���ӽ���
void GameMain() {
	while (1) {
		Clear();

		// �� �׸���
		DrawMap();

		// ����Ű �� GUI ǥ��
		GUI();

		// ������ �� �׸���
		DrawMinos();

		// �� ������
		DropMinos();
		
		// ���� �� / ���� ���� ��� ���߰��ϰ� ���� �� �����ϱ�
		MinoToMap();
		
		// ������ �� á�� ��� �����
		RemoveMap();

		// Ű ����
		InputProcess();

		// ���� ���� üũ
		CheckGameFail();

		Sleep(50);
	}
}

void DrawMap() {
	GotoXY(0, 0);

	// �迭�� ������ �� �׸��� 
	// 1 : �� , 0 : ����� , 2 : ���κ�
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 14; j++) {
			if (Map[i][j] == 1) {
				GotoXY(j * 2, i);
				printf("��");
			}
			else if (Map[i][j] == 2) {
				GotoXY(j * 2, i);
				printf("��");
			}
			else {
				GotoXY(j * 2, i);
				printf(".");
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
				printf("��");
			}
		}
	}
}

// �浹 üũ
bool CrashCheck(int x,int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (Minos[MinoForm][MinoRotate][i][j] == 1) {
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
	// �浹���� ���� ��� ������
	if (CrashCheck(Minox, Minoy + 1) == true) {
		return;
	}
	else {
		Minoy++;
	}
}

void MinoToMap() {
	// ���̳� ���� ����� ��� Map�� 2�� ����
	if (CrashCheck(Minox, Minoy + 1) == true) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (Minos[MinoForm][MinoRotate][i][j] == 1) {
					Map[i + Minoy][j + Minox / 2] = 2;
				}
			}
		}
		// ���ο� �� ����
		Minox = 6;
		Minoy = 0;
		RandomM();
	}
}

void RemoveMap() {
	// ������ ���� ����
	for (int i = 15; i >= 0; i--) {
		int count = 0;
		for (int j = 1; j < 11; j++) {
			if (Map[i][j] == 2) {
				count++;
			}
		}

		// ������ ���� ���ٿ� �� á�� �� �����
		if (count >= 10) {
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
	// �������� �̵�
	if (GetAsyncKeyState(VK_LEFT) && 0x8000) {
		if (CrashCheck(Minox - 2,Minoy) == false) {
			Minox -= 2;
		}
	}
	// ���������� �̵�
	if (GetAsyncKeyState(VK_RIGHT) && 0x8000) {
		if (CrashCheck(Minox + 2, Minoy) == false) {
			Minox += 2;
		}
	}
	// ȸ��
	if (GetAsyncKeyState(VK_LCONTROL) && 0x8000) {
		MinoRotate++;
		if (MinoRotate >= 4) {
			MinoRotate = 0;
		}
	}
}

void CheckGameFail() {
	for (int j = 0; j < 14; j++) {
		// �� �� ������ á�� ��� ���� ����
		if (Map[1][j] == 2) {
			Sleep(1000);
			GameFail();
		}
	}
}

// ���ӽ���
void GameFail() {
	Clear();
	GotoXY(0, 0);
	printf("Ŭ���� ����!\n");
	printf("1�� �� ������ ����˴ϴ�.");
	Sleep(1000);
	exit(0);
}

void GUI() {
	GotoXY(30, 3);
	printf("���۹�");
	GotoXY(30, 6);
	printf("left = �� / right = ��");
	GotoXY(30, 9);
	printf("Rotate = LCtrl");
}