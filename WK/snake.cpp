// �γ���� ̰������Ϸ ���༭ʱ�䣺2021 / 3 / 3
/********************************������������־***********************************

***********************************ͷ�ļ�*****************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>   // easyX
#include<mmsystem.h>//���뱳������
#pragma comment(lib,"Winmm.lib")
/**********************************�궨��****************************************/
#define High 675    //��Ļ�ߴ�
#define Width 1200  //ͬ��
#define Long 200    //����󳤶�
#define size 20     //�ߵ�һ�ڳߴ�
/**********************************����ȫ�ֱ���***********************************/
//����
typedef struct
{
    int x, y;
}spoint;
//��
struct
{
    spoint xys[Long];     //�ߵ�����
    int position;        //�ߵķ���
    int num;            //�ߵĳ���
}snake;
//ʳ��
struct
{
    spoint xyf;           //ʳ������
    int style;           //ʳ����ʽ
    int grade;           //ʳ�����
}food;
//ö��

enum position { up, down, left, right };

int HighScore = 0;

/*********************************��  ��  ��  �� **********************************/
void welcometogame();       //��ʼ����
void menu();                //��Ϸ�˵�
void createMap();           //���Ƶ�ͼ
void explation();           //��Ϸ˵��
void snakebasic();          //�ߵĻ������
void foodbasic();           //ʳ��������
void snakestyle();          //�ߵĻ���
void foodstyle();           //ʳ�����
void move();                //�ߵ��ƶ�
void keycontrol();          //���̿���
void eat_food();            //��ʳ��
void show_Grade();          //��ʾ����
int  snake_die();           //�������ж�
void File_in();             //��߷�д��
void File_out();            //��ȡ��߷�
void endgame();             //��������
/**********************************************************************************/

void welcometogame()
{
    File_out();               //��ȡ�ļ�
    HWND hwnd = initgraph(Width, High);
    SetWindowTextA(hwnd, "̰������Ϸ   �����ߣ���");
    IMAGE img_wbk;
    loadimage(&img_wbk, _T("back.jpg"),1200,675);
    putimage(0, 0, &img_wbk);
    //FlushBatchDraw();//��������

    settextstyle(180, 0, "Goudy Stout");//�������ָ�ʽ
    settextcolor(RGB(130, 133, 136));
    setbkmode(TRANSPARENT);     //ȥ�����ֱ���
    outtextxy(200, 50, "Snake");

    setfillcolor(RGB(170, 172, 146));//��ʼ�滭�����˵�
    fillrectangle(400, 300, 800, 400);
    fillrectangle(400, 425, 800, 525);
    fillrectangle(400, 550, 800, 650);

    settextstyle(60, 0, "��������");//�������ָ�ʽ
    settextcolor(RGB(239, 236, 217));
    setbkmode(TRANSPARENT);     //ȥ�����ֱ���
    outtextxy(480, 320, "��ʼ��Ϸ");
    outtextxy(480, 445, "  ˵    ��");
    outtextxy(480, 570, "�˳���Ϸ");

    menu();
    _getch();//��ֹ����
    closegraph();
}
void menu()
{
    mciSendString("open 3.mp3", NULL, 0, NULL);  //Ŀ¼��������
    mciSendString("play 3.mp3", 0, 0, 0);


    MOUSEMSG m; //������
    while (1)
    {
        m = GetMouseMsg();
        if (m.x >= 400 && m.x <= 800 && m.y >= 300 && m.y <= 400)//�������λ�� �Ƿ���������
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 300, 800, 400);//���µı߿�
            outtextxy(480, 320, "��ʼ��Ϸ");
            //��������
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                mciSendString("close 3.mp3", 0, 0, 0);//�ر�Ŀ¼��������
                createMap();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 425 && m.y <= 525)//�������λ�� �Ƿ���������
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 425, 800, 525);//���µı߿�
            outtextxy(480, 445, "  ˵    ��");
            //��������
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                explation();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 550 && m.y <= 650)//�������λ�� �Ƿ���������
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 550, 800, 650);//���µı߿�
            outtextxy(480, 570, "�˳���Ϸ");
            //��������
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                exit(0);
            }
        }
        else
        {
            setlinecolor(WHITE);
            fillrectangle(400, 300, 800, 400);
            outtextxy(480, 320, "��ʼ��Ϸ");
            fillrectangle(400, 425, 800, 525);
            outtextxy(480, 445, "  ˵    ��");
            fillrectangle(400, 550, 800, 650);
            outtextxy(480, 570, "�˳���Ϸ");
        }
    }
}
void explation()
{
    BeginBatchDraw();
    IMAGE img_wsk;
    loadimage(&img_wsk, _T("2.jpg"),1200,675);
    putimage(0, 0, &img_wsk);
    EndBatchDraw();

    setfillcolor(RGB(170, 172, 146));//��ʼ�滭�����˵�
    fillrectangle(400, 425, 800, 525);
    fillrectangle(400, 550, 800, 650);

    settextstyle(60, 0, "��������");//�������ָ�ʽ
    settextcolor(RGB(239, 236, 217));
    setbkmode(TRANSPARENT);     //ȥ�����ֱ���
    outtextxy(480, 445, "��ʼ��Ϸ");
    outtextxy(480, 570, "�˻ز˵�");

    MOUSEMSG m;
    while (1)
    {
        m = GetMouseMsg();
         if (m.x >= 400 && m.x <= 800 && m.y >= 425 && m.y <= 525)//�������λ�� �Ƿ���������
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 425, 800, 525);//���µı߿�
            outtextxy(480, 445, "��ʼ��Ϸ");
            //��������
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                mciSendString("close 3.mp3", 0, 0, 0);//�ر�Ŀ¼��������
                createMap();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 550 && m.y <= 650)//�������λ�� �Ƿ���������
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 550, 800, 650);//���µı߿�
            outtextxy(480, 570, "�˻ز˵�");
            //��������
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                welcometogame();
            }
        }
        else
        {
            setlinecolor(WHITE);
            fillrectangle(400, 425, 800, 525);
            outtextxy(480, 445, "��ʼ��Ϸ");
            fillrectangle(400, 550, 800, 650);
            outtextxy(480, 570, "�˻ز˵�");
        }
    }
}
void createMap()
{
    mciSendString("open 1.mp3", NULL, 0, NULL);  //Ŀ¼��������
    mciSendString("play 1.mp3 repeat", 0, 0, 0);

    setbkcolor(RGB(209, 254, 253));
    cleardevice();


    snakebasic();
    snakestyle();
    //�ƶ������ĵ���
    while (1)
    {
        cleardevice();   //��������ͼ�飬����
        show_Grade();
        move();
        snakestyle();
        if (food.style == 0)//��ʳ�ﲻ���ڵ�ʱ��
        {
            foodbasic();
        }
        if (_kbhit())
        {
            keycontrol();
        }
        if (snake_die())
        {
            welcometogame();
        }
        foodstyle();
        eat_food();

        Sleep(100);  //�ٶ�
    }
}
void snakebasic()
{
    /************�ߵ���ʼ��ʼ��**************/
    snake.xys[2].x = 0;
    snake.xys[2].y = 0;

    snake.xys[1].x = size;
    snake.xys[1].y = 0;

    snake.xys[0].x = 2* size;
    snake.xys[0].y = 0;
    /*************�ߵķ����ʼ��************/
    snake.position = right;
    snake.num = 3;
}
void snakestyle()
{
    for (int i = 0; i < snake.num; i++)
    {
        setlinecolor(BLACK);
        setfillcolor(LIGHTGREEN);
        fillrectangle(snake.xys[i].x, snake.xys[i].y, snake.xys[i].x + size, snake.xys[i].y + size);
    }
}
void move()
{
    //��������ƶ�
    for (int i = snake.num - 1; i > 0; i--)
    {
        snake.xys[i].x = snake.xys[i - 1].x;
        snake.xys[i].y = snake.xys[i - 1].y;
    }
    //��ͷ���ƶ�
    switch (snake.position)
    {
    case up:
        snake.xys[0].y -= size;
        break;
    case down:
        snake.xys[0].y += size;
        break;
    case left:
        snake.xys[0].x -= size;
        break;
    case right:
        snake.xys[0].x += size;
        break;
    }
}
void keycontrol() {
    char userKey = _getch();
    switch (userKey)
    {
    case 'w':
    case 'W':
    case 72:
        if (snake.position != down)
            snake.position = up;
        break;
    case 's':
    case 'S':
    case 80:
        if (snake.position != up)
            snake.position = down;
        break;
    case 'a':
    case 'A':
    case 75:
        if (snake.position != right)
            snake.position = left;
        break;
    case 'd':
    case 'D':
    case 77:
        if (snake.position != left)
            snake.position = right;
        break;
    }
}
void foodbasic()
{
    food.xyf.x = rand() % 40 * 20;//ʳ�������޶�
    food.xyf.y = rand() % 30 * 20;
    food.style = 1;//����ʳ�����

    for (int i = 0; i < snake.num; i++)//��ֹʳ��������������
    {
        if (food.xyf.x == snake.xys[i].x && food.xyf.y == snake.xys[i].y)
        {
            food.xyf.x = rand() % 80 * 10;
            food.xyf.y = rand() % 60 * 10;
        }
    }

}
void foodstyle()
{
    BeginBatchDraw();
    IMAGE img_wfk1, img_wfk2;
    loadimage(&img_wfk1, _T("food.jpg"), size, size);
    loadimage(&img_wfk2, _T("food1.jpg"), size, size);
    putimage(food.xyf.x, food.xyf.y, &img_wfk1,NOTSRCERASE);
    putimage(food.xyf.x, food.xyf.y, &img_wfk2,SRCINVERT);
    EndBatchDraw();
}
void eat_food()
{
    if (snake.xys[0].x == food.xyf.x && snake.xys[0].y == food.xyf.y)
    {
        snake.num++;
        food.style = 0;
        food.grade += 10;
    }
}
void show_Grade()
{
        char grade[20] = "";
        sprintf(grade, "Ŀǰ�÷֣� %d", food.grade);
        settextstyle(60, 0, "��������");//�������ָ�ʽ
        settextcolor(RGB(239, 236, 217));
        setbkmode(TRANSPARENT);     //ȥ�����ֱ���
        outtextxy(700, 50, grade);

        char grade1[20] = "";
        sprintf(grade1, "��ߵ÷֣� %d", HighScore);
        settextstyle(60, 0, "��������");//�������ָ�ʽ
        settextcolor(RGB(239, 236, 217));
        setbkmode(TRANSPARENT);     //ȥ�����ֱ���
        outtextxy(700, 130, grade1);
}
int snake_die()
{

    //ײǽ
    if (snake.xys[0].x > 1200 || snake.xys[0].x < 0 || snake.xys[0].y>675 || snake.xys[0].y < 0)
    {
        endgame();
        return 1;
    }
    //ײ����
    for (int i = 1; i < snake.num; i++)
    {
        if (snake.xys[0].x == snake.xys[i].x && snake.xys[0].y == snake.xys[i].y)
        {
            endgame();
            return 1;
        }
    }
    return 0;
}
void File_in()
{
    FILE* fp;
    fp = fopen("highscore.txt", "w");        //�Զ�д�ķ�ʽ����һ����Ϊhigh_score.txt���ļ�
    rewind(fp);
    fprintf(fp, "%d", food.grade);            //�ѷ���д���ļ���
    fclose(fp);                               //�ر��ļ�
}
void File_out()
{
    FILE* fp;
    fp = fopen("highscore.txt", "r");          //���ļ�high_score.txt
    rewind(fp);
    fscanf(fp, "%d", &HighScore);              //���ļ��е���߷ֶ�����
    fclose(fp);                                //�ر��ļ�
}
HWND hwnd = NULL;
void endgame()
{


    if (food.grade >= HighScore)
    {
        char grade1[100] = "";
        sprintf(grade1, "�÷֣�%d\n����¼������߷ֱ���ˢ���������������", food.grade);
        MessageBox(hwnd, grade1, "gameover", MB_OK | MB_SYSTEMMODAL);
        if (food.grade >= HighScore)
        File_in();
    }
    else
    {
        char grade2[100] = "";
        sprintf(grade2, "����Ŭ����~ ������߷ֻ��%d", HighScore-food.grade);
        MessageBox(hwnd, grade2, "gameover", MB_OK | MB_SYSTEMMODAL);
    }
    food.grade = 0;
    mciSendString("close 1.mp3", NULL, 0, NULL);

}
/****************************************������*************************************/
int main()
{
    srand((unsigned int)time(NULL));  //�������
    welcometogame();


    return 0;
}
