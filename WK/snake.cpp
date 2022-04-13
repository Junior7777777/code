// 课程设计 贪吃蛇游戏 最后编辑时间：2021 / 3 / 3
/********************************部分问题与日志***********************************

***********************************头文件*****************************************/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<time.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>   // easyX
#include<mmsystem.h>//加入背景音乐
#pragma comment(lib,"Winmm.lib")
/**********************************宏定义****************************************/
#define High 675    //屏幕尺寸
#define Width 1200  //同上
#define Long 200    //蛇最大长度
#define size 20     //蛇的一节尺寸
/**********************************定义全局变量***********************************/
//坐标
typedef struct
{
    int x, y;
}spoint;
//蛇
struct
{
    spoint xys[Long];     //蛇的坐标
    int position;        //蛇的方向
    int num;            //蛇的长度
}snake;
//食物
struct
{
    spoint xyf;           //食物坐标
    int style;           //食物样式
    int grade;           //食物分数
}food;
//枚举

enum position { up, down, left, right };

int HighScore = 0;

/*********************************函  数  声  明 **********************************/
void welcometogame();       //开始界面
void menu();                //游戏菜单
void createMap();           //绘制地图
void explation();           //游戏说明
void snakebasic();          //蛇的基础设计
void foodbasic();           //食物基础设计
void snakestyle();          //蛇的绘制
void foodstyle();           //食物绘制
void move();                //蛇的移动
void keycontrol();          //键盘控制
void eat_food();            //吃食物
void show_Grade();          //显示分数
int  snake_die();           //蛇死亡判断
void File_in();             //最高分写入
void File_out();            //读取最高分
void endgame();             //结束界面
/**********************************************************************************/

void welcometogame()
{
    File_out();               //读取文件
    HWND hwnd = initgraph(Width, High);
    SetWindowTextA(hwnd, "贪吃蛇游戏   开发者：万");
    IMAGE img_wbk;
    loadimage(&img_wbk, _T("back.jpg"),1200,675);
    putimage(0, 0, &img_wbk);
    //FlushBatchDraw();//批量绘制

    settextstyle(180, 0, "Goudy Stout");//设置文字格式
    settextcolor(RGB(130, 133, 136));
    setbkmode(TRANSPARENT);     //去掉文字背景
    outtextxy(200, 50, "Snake");

    setfillcolor(RGB(170, 172, 146));//开始绘画启动菜单
    fillrectangle(400, 300, 800, 400);
    fillrectangle(400, 425, 800, 525);
    fillrectangle(400, 550, 800, 650);

    settextstyle(60, 0, "华文琥珀");//设置文字格式
    settextcolor(RGB(239, 236, 217));
    setbkmode(TRANSPARENT);     //去掉文字背景
    outtextxy(480, 320, "开始游戏");
    outtextxy(480, 445, "  说    明");
    outtextxy(480, 570, "退出游戏");

    menu();
    _getch();//防止闪屏
    closegraph();
}
void menu()
{
    mciSendString("open 3.mp3", NULL, 0, NULL);  //目录背景音乐
    mciSendString("play 3.mp3", 0, 0, 0);


    MOUSEMSG m; //鼠标控制
    while (1)
    {
        m = GetMouseMsg();
        if (m.x >= 400 && m.x <= 800 && m.y >= 300 && m.y <= 400)//检测鼠标的位置 是否满足条件
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 300, 800, 400);//画新的边框
            outtextxy(480, 320, "开始游戏");
            //如果点击了
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                mciSendString("close 3.mp3", 0, 0, 0);//关闭目录背景音乐
                createMap();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 425 && m.y <= 525)//检测鼠标的位置 是否满足条件
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 425, 800, 525);//画新的边框
            outtextxy(480, 445, "  说    明");
            //如果点击了
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                explation();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 550 && m.y <= 650)//检测鼠标的位置 是否满足条件
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 550, 800, 650);//画新的边框
            outtextxy(480, 570, "退出游戏");
            //如果点击了
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                exit(0);
            }
        }
        else
        {
            setlinecolor(WHITE);
            fillrectangle(400, 300, 800, 400);
            outtextxy(480, 320, "开始游戏");
            fillrectangle(400, 425, 800, 525);
            outtextxy(480, 445, "  说    明");
            fillrectangle(400, 550, 800, 650);
            outtextxy(480, 570, "退出游戏");
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

    setfillcolor(RGB(170, 172, 146));//开始绘画启动菜单
    fillrectangle(400, 425, 800, 525);
    fillrectangle(400, 550, 800, 650);

    settextstyle(60, 0, "华文琥珀");//设置文字格式
    settextcolor(RGB(239, 236, 217));
    setbkmode(TRANSPARENT);     //去掉文字背景
    outtextxy(480, 445, "开始游戏");
    outtextxy(480, 570, "退回菜单");

    MOUSEMSG m;
    while (1)
    {
        m = GetMouseMsg();
         if (m.x >= 400 && m.x <= 800 && m.y >= 425 && m.y <= 525)//检测鼠标的位置 是否满足条件
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 425, 800, 525);//画新的边框
            outtextxy(480, 445, "开始游戏");
            //如果点击了
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                mciSendString("close 3.mp3", 0, 0, 0);//关闭目录背景音乐
                createMap();
            }
        }
        else if (m.x >= 400 && m.x <= 800 && m.y >= 550 && m.y <= 650)//检测鼠标的位置 是否满足条件
        {
            setlinecolor(RGB(156, 159, 132));
            fillrectangle(400, 550, 800, 650);//画新的边框
            outtextxy(480, 570, "退回菜单");
            //如果点击了
            if (m.uMsg == WM_LBUTTONDOWN)
            {
                welcometogame();
            }
        }
        else
        {
            setlinecolor(WHITE);
            fillrectangle(400, 425, 800, 525);
            outtextxy(480, 445, "开始游戏");
            fillrectangle(400, 550, 800, 650);
            outtextxy(480, 570, "退回菜单");
        }
    }
}
void createMap()
{
    mciSendString("open 1.mp3", NULL, 0, NULL);  //目录背景音乐
    mciSendString("play 1.mp3 repeat", 0, 0, 0);

    setbkcolor(RGB(209, 254, 253));
    cleardevice();


    snakebasic();
    snakestyle();
    //移动函数的调用
    while (1)
    {
        cleardevice();   //更新最新图块，清屏
        show_Grade();
        move();
        snakestyle();
        if (food.style == 0)//当食物不存在的时候
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

        Sleep(100);  //速度
    }
}
void snakebasic()
{
    /************蛇的起始初始化**************/
    snake.xys[2].x = 0;
    snake.xys[2].y = 0;

    snake.xys[1].x = size;
    snake.xys[1].y = 0;

    snake.xys[0].x = 2* size;
    snake.xys[0].y = 0;
    /*************蛇的方向初始化************/
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
    //蛇身体的移动
    for (int i = snake.num - 1; i > 0; i--)
    {
        snake.xys[i].x = snake.xys[i - 1].x;
        snake.xys[i].y = snake.xys[i - 1].y;
    }
    //蛇头的移动
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
    food.xyf.x = rand() % 40 * 20;//食物生成限定
    food.xyf.y = rand() % 30 * 20;
    food.style = 1;//代表食物存在

    for (int i = 0; i < snake.num; i++)//防止食物生成在蛇身上
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
        sprintf(grade, "目前得分： %d", food.grade);
        settextstyle(60, 0, "华文琥珀");//设置文字格式
        settextcolor(RGB(239, 236, 217));
        setbkmode(TRANSPARENT);     //去掉文字背景
        outtextxy(700, 50, grade);

        char grade1[20] = "";
        sprintf(grade1, "最高得分： %d", HighScore);
        settextstyle(60, 0, "华文琥珀");//设置文字格式
        settextcolor(RGB(239, 236, 217));
        setbkmode(TRANSPARENT);     //去掉文字背景
        outtextxy(700, 130, grade1);
}
int snake_die()
{

    //撞墙
    if (snake.xys[0].x > 1200 || snake.xys[0].x < 0 || snake.xys[0].y>675 || snake.xys[0].y < 0)
    {
        endgame();
        return 1;
    }
    //撞蛇身
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
    fp = fopen("highscore.txt", "w");        //以读写的方式建立一个名为high_score.txt的文件
    rewind(fp);
    fprintf(fp, "%d", food.grade);            //把分数写进文件中
    fclose(fp);                               //关闭文件
}
void File_out()
{
    FILE* fp;
    fp = fopen("highscore.txt", "r");          //打开文件high_score.txt
    rewind(fp);
    fscanf(fp, "%d", &HighScore);              //把文件中的最高分读出来
    fclose(fp);                                //关闭文件
}
HWND hwnd = NULL;
void endgame()
{


    if (food.grade >= HighScore)
    {
        char grade1[100] = "";
        sprintf(grade1, "得分：%d\n创纪录啦！最高分被你刷新啦，真棒！！！", food.grade);
        MessageBox(hwnd, grade1, "gameover", MB_OK | MB_SYSTEMMODAL);
        if (food.grade >= HighScore)
        File_in();
    }
    else
    {
        char grade2[100] = "";
        sprintf(grade2, "继续努力吧~ 你离最高分还差：%d", HighScore-food.grade);
        MessageBox(hwnd, grade2, "gameover", MB_OK | MB_SYSTEMMODAL);
    }
    food.grade = 0;
    mciSendString("close 1.mp3", NULL, 0, NULL);

}
/****************************************主函数*************************************/
int main()
{
    srand((unsigned int)time(NULL));  //随机种子
    welcometogame();


    return 0;
}
