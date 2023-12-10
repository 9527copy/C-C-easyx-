#include <stdio.h>
#include <easyx.h>
#include <tchar.h>
#include <time.h>
#include <graphics.h>
#include <string.h>
#define	TITLEL 100
#define WIDTH 100
#define HEIGHT 150

int flag[4],count=0;

//void centertext(char str[])
//{
//	char text[50];
//	strcmp(text, str);
//	int textWidth = textwidth(text);
//	int textHeight = textheight(text);
//
//	int centerX = (400 - textWidth) / 2;
//	int centerY = (700 - textHeight) / 2;
//
//	outtextxy(centerX, centerY, text);
//}

void init()
{
	srand((unsigned)time(NULL));

	for (int  i = 0; i < 4; i++)
	{
		flag[i] = rand() % 4;
	}
}

void draw()
{
	//��������
	setlinestyle(PS_SOLID, 1);
	
	setlinecolor(BLACK);

	for (int i = 0; i < 5; i++)
	{
		line(i * WIDTH, TITLEL, i * WIDTH, TITLEL+4*HEIGHT);

		line(0, TITLEL + i * HEIGHT, 400, TITLEL + i * HEIGHT);
	}

	//����
	settextstyle(38, 0, _T("Arial"));
	settextcolor(BLACK);
	
	char title[50] = "��Ȱ׿��";

	int titleWidth = textwidth(title);
	int titleHeight = textheight(title);

	int centerX = (4*WIDTH - titleWidth) / 2;
	int centerY = (TITLEL - titleHeight) / 2;

	outtextxy(centerX, centerY, title);

	//�ڿ�
	setfillcolor(BLACK);
	for (int  i = 0; i < 4; i++)
	{
		int x = flag[i]*WIDTH;
		int y = 100+i*HEIGHT;

		if (i == 3)
		{
			setfillcolor(RGB(51, 51, 51));
		}

		fillrectangle(x, y, x+WIDTH, y + HEIGHT);
	}
}

bool mousePressMsg(ExMessage *msg)
{
	int x = flag[2] * WIDTH;
	int y = 2 * HEIGHT + TITLEL;

	if (msg->x > x && msg->x<x + WIDTH && msg->y>y && msg->y < y + HEIGHT)
	{
		for (int i = 3; i > 0; i--)
		{
			int temp = flag[i];
			flag[i] = flag[i - 1];
			flag[i - 1] = temp;
		}

		flag[0] = rand() % 4;

		count++;
		printf("��������ȷ�ĺڿ飡��ǰ�÷�Ϊ%d\n",count);
		
		return true;
	}
	else
	{
		printf("���������Ϸ������\n");

		cleardevice();
		settextcolor(RED);
		settextstyle(50, 0, _T("Arial"));

		char text[] = "���������Ϸ����";
		int textWidth = textwidth(text);
		int textHeight = textheight(text);

		int centerX = (400 - textWidth) / 2;
		int centerY = (700 - textHeight) / 2;

		outtextxy(centerX, centerY, text);

		char score[30];
		sprintf_s(score, "Score:%d", count);
		outtextxy(centerX, centerY + 50, score);

		system("pause");
	}

	return false;
	
}

void ui()
{
	ExMessage msg;

	bool isDown = false;

	while (isDown!=true)
	{
		if (peekmessage(&msg))
		{
			switch (msg.message)
			{
			case WM_KEYDOWN:
				if (msg.vkcode == VK_ESCAPE)
				{
					isDown = true;
				}
				break;
			case WM_LBUTTONDOWN:
				mousePressMsg(&msg);
				break;
			default:
				break;
			}
		}

		BeginBatchDraw();
		cleardevice();
		draw();
		EndBatchDraw();
	}

}

//void beginning()
//{
//	char tips[3];
//
//	settextcolor(BLACK);
//
//	settextstyle(30, 0, "΢���ź�");
//
//	for (int i = 0; i < 3; i++)
//	{
//		cleardevice();
//		
//		sprintf_s(tips, "���뿪ʼ����%d��", i + 1);
//
//		outtextxy(100, 100, tips);
//
//		Sleep(1000);
//
//		system("pause");
//	 }
//}

int main()
{
	initgraph(400, 700, 1);

	setbkcolor(WHITE);

	cleardevice();
	//beginning();

	init();


	draw();

	ui();

	//easyx��������
	/*
	initgraph(400, 700);//���һ���ڴ���

	line(0, 0, 400, 700);

	setlinecolor(RED);

	setlinestyle(PS_SOLID, 3);//styleΪ��ʵ��ʽ��thicknessΪ3������

	rectangle(10, 10, 100, 100);

	fillrectangle(10, 100, 100, 200);
	*/

	return 0;
}