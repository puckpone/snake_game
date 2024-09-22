#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h> //getch()函数 
#include<ctime> //time()函数 
#include<windows.h> //Sleep()函数 

#define H 40
#define W 20

#define OFFSET_X 40 //地图的偏移量
#define OFFSET_Y 5 //地图的偏移量

//蛇的速度
#define SPEED_1 400 
#define SPEED_2 300
#define SPEED_3 200

int FOOD_X, FOOD_Y;  //食物的坐标
void initView(void);   //初始界面
void Start(void); //打印界面 （蛇，地图。食物）
void gameView(void); //开始游戏 界面
int pauseView(void);  //暂停界面
void selectionView(void); //难度选择界面
void OverView(); //结束界面
void init(void); //开始游戏初始化
void generateFood(void); //生成食物
void updateDir(char ch); //修改方向函数
int HeadFront(void); //判断蛇头前面是什么
void move(int result); //蛇移动后的数据情况

int map[H][W];  //地图
int s[H * W][2];   //s[i][j]  i表示第i节身体   j表示坐标  0表示x坐标  1表示y坐标
int len = 3;  //蛇的当前长度
char dir = 'd';  //蛇的当前方向
int OPT = 1; //当前难度

void gotoXY(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//清理指定矩形区域(从(x,y)到(x+w,y+h)的矩形
void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}
//设置打印颜色
void setPrintColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/*
* 1.初始界面
            展示选项 开始游戏
                      在初始界面右上方 打印 游戏操作说明：
                                                    w：向上移动
                                                    s：向下移动
                                                    a：向左移动
                                                    d：向右移动
                                                    游戏中输入Q暂停
                     难度选择
                     退出游戏


            用ws控制选项 移动光标 回车选中

                     开始游戏：进入 开始游戏 界面
                     难度选择：进入 难度选择 界面
                     退出游戏：进入 退出游戏 界面

2.开始游戏 界面
               展示地图：****蛇  #食物
               展示难度及分数
               右上方 Q 键 （暂停界面）

               用户wasd移动
               蛇定时移动
               移动后：
                      撞墙/自己：死亡，游戏结束
                      吃到食物：长度+1，食物消失 生成新的食物 移动一格
                      空地：移动一格
*/
//隐藏/显示光标

void HideConsoleCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void ShowConsoleCursor()
{
    CONSOLE_CURSOR_INFO cursorInfo;
    cursorInfo.dwSize = 100;
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}


// ---------------------------------------------------------- 数据设计 ------------------------------------------------------

            /*
              1.打印地图
              int map[H][W];

              0表示空地
              1表示墙
              2表示食物




              2.蛇身
              int s[H * W][2];

              s[i][j]
                  i表示第i节身体
                  j表示坐标  0表示x坐标  1表示y坐标

                  s[2][0] = 5;  	第[2]节身体x坐标 = 5
                  s[2][1] = 3;	    第[2]节身体y坐标 = 3
                  蛇的第[2]节身体  坐标是(5,3)


              3.len  蛇的长度


              4.
              char dir;   //蛇的当前方向

              5.蛇身 ；'*'

              6.食物：'#'

              7.墙：'口'

             */

             // ---------------------------------------------------------- 数据设计 ------------------------------------------------------





int main()
{
    srand(time(0));

    // srand(static_cast<unsigned int>(time(0)));  // 使用当前时间作为种子进行初始化
    while (1)
    {
        initView();
    }


    return 0;
}

//-----------------------------------------------------------view-zhou------------------------------------------------------------

/*
    负责人：
    功能：
    while(1)
    {
      1.展示选项
            开始游戏
                   在初始界面右上方 打印 游戏操作说明：
                                                    w：向上移动
                                                    s：向下移动
                                                    a：向左移动
                                                    d：向右移动
                                                    游戏中输入Q暂停
            难度选择
            退出游戏
                   在初始界面右下方 打印 开发者的话

      2.接收玩家输入
          控制ws 移动光标 选中回车
                开始游戏：进入 开始游戏 界面
                难度选择：进入 难度选择 界面
                退出游戏：进入 退出游戏 界面
    }
    参数：void
    返回值：void
*/
void initView(void)   //初始界面
{
    system("cls");
    int userChoose = 0;
    while (1) {
        // ----------------- 打印界面 -----------------
        system("title 贪吃蛇");//更改窗口名
        gotoXY(87, 5);
        printf(" 操作设置");
        gotoXY(87, 6);
        printf("w:向上移动");
        gotoXY(87, 7);
        printf("s:向下移动");
        gotoXY(87, 8);
        printf("a:向左移动");
        gotoXY(87, 9);
        printf("d:向右移动");
        gotoXY(87, 10);
        printf("q:暂停游戏");

        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(54, 9);
        printf("开始游戏");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(54, 12);
        printf("难度选择");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(54, 15);
        printf("退出游戏");
        if (userChoose == 2) setPrintColor(0x0f);
        // ---------------- 接收用户输入 --------------
        char input = _getch();
        // -------------判断是方向上下还是回车------------
        switch (input) {
        case 'w':
        case 'W':
            userChoose -= 1;
            if (userChoose == -1) userChoose = 3;
            break;
        case 's':
        case 'S':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            clear(3, 2, 100, 30);
            switch (userChoose) {
            case 0:
                gameView();  //调用 开始游戏界面 函数
                break;
            case 1:
                selectionView();  // 调用难度选择
                break;

            case 2:
                exit(0);
                break;
            }
            clear(3, 2, 36, 20);
            break;
        }
    }
}

/*
*  负责人：
*  功能：打印蛇的初始形状 打印地图
*  参数：void
*  返回值：void
*/
void Start(void)  //打印界面 （蛇，地图。食物）   
{

}

/*
    负责人：
    功能:
        start:
        1. 初始化游戏数据: 蛇(蛇身, 长度, 方向), 地图(墙,食物) init()
        while(1)
        {
            if OPT=
                sleep()
            2. 打印/绘制界面: 蛇, 地图	Start()
            3. 判断用户有没有输入
            {
                如果有:
                    判断用户输入的类型 
                        方向: 修改方向:     updateDir()

                        Q键 : 暂停游戏: 展示暂停界面 pauseView()
							如果返回值是1: 游戏继续
							如果返回值是0: 重新开始 goto start
							如果返回值是2: 回到初始界面 return
            }
            4. 移动
            {
                判断:
                    判断蛇头 前面的位置 是什么东西   headFront()
                    可能是墙/蛇身, 食物, 空地,

                执行:
                    headFront()返回值传给move()修改数据
                    若前方是蛇身或者墙，游戏结束 OverView().
            }
        }
    参数: void
    返回值: void
*/
void gameView(void)  //开始游戏 界面     //考虑蛇的速度 sleep(int)  gotoXY打印蛇身
{

}


//暂停界面
/*

 负责人：
	功能：
		第一行打印 游戏暂停
		下面分别 打印 继续游戏
					  重新开始
					  回到菜单

		用ws控制选项 移动光标 回车选中
	参数：void
	返回值：int
	返回继续游戏->返回 1
	重新开始->返回 0
	回到菜单->返回 2
*/
int pauseView(void)  //暂停界面
{
    clear(1, 1, 100, 30);
    //system("cls");
    int userChoose = 0;
    while (1)
    {
        // ----------------- 打印界面 -----------------
        gotoXY(56, 9);
        printf("---游 戏 暂 停---");

        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(60, 12);
        printf("继续游戏");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(60, 15);
        printf("重新开始");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(60, 18);
        printf("回到菜单");
        if (userChoose == 2) setPrintColor(0x0f);

        // ---------------- 接收用户输入 --------------
        char input = _getch();

        // -------------判断是方向上下还是回车------------
        switch (input)
        {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) userChoose = 3;
            break;
        case 's':
            userChoose = (userChoose + 1) % 3;
            break;
        case '\r':
            //clear(3, 2, 80, 20);
            switch (userChoose)
            {
            case 0:
                return 1;
                break;
            case 1:
                return 0;
                break;
            case 2:
                return 2;
                break;
            default:
                break;
            }
            //clear(3, 2, 36, 20);
            break;
        }
    }
}



//难度选择界面
/*
 *    负责人： 
 * 功能：第一行 打印 难度选择
 * 下面打印： 容易
 * 简单
 * 困难
 * 返回
 * 用ws控制选项 移动光标 回车选中
 * 修改全局变量OPT
 * 参数：void
 * 返回值：void
*/
void  selectionView(void)
{

}

//结束界面
/*
     负责人：
     功能：第一行 打印 游戏结束
     下面打印： 再来一次
     重选难度
     返回菜单
     用ws控制选项 移动光标 回车选中
     参数：void
*/
void OverView()
{
    system("cls");
    int userChoose = 0;
    while (1) {
        // ----------------- 打印界面 -----------------
        gotoXY(54, 6);
        printf("---游 戏 结 束---");
        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(58, 9);
        printf("");
        if (userChoose == 0) setPrintColor(0x0f);

        setPrintColor(0x6f);
        gotoXY(58, 18);
        printf("返回菜单");
        setPrintColor(0x0f);

        // ---------------- 接收用户输入 --------------
        char input = _getch();

        // -------------判断是方向上下还是回车------------
        switch (input) {
        case '\r':
            clear(3, 2, 80, 20);
            switch (userChoose) {
            case 1:
                return;  //调用 开始游戏界面 函数
                break;
            case 2:
                selectionView();  //调用 难度选择 函数
                break;
            case 3:
                return;  //调用 初始界面 函数
                break;
            default:
                break;
            }
            clear(3, 2, 36, 20);
            break;
        }
    }
    return;
}


//-----------------------------------------------------------view-zhou------------------------------------------------------------




//-----------------------------------------------------------service-wu---------------------------------------------------------
// 初始化函数
/*
    负责人: 
    功能:
        地图 蛇长度 蛇位置
        地图:
            地图周围一圈墙(1)
            地图中间初始化为空地(0)

        蛇位置:
            地图中间位置
            朝右走
        蛇方向: d

        食物:
            在地图中随机生成一个食物
            注意 食物不能和蛇身重叠
    参数: void
    返回值: void
*/
void init(void)  //开始游戏初始化
{
}


//生成食物
/*
*    负责人：
*    功能：
*   	        随机生成食物坐标 FOOD_X,FOOD_Y   
*              食物不能和蛇身重合  rand()
     参数：void
     返回值：void
*/

void generateFood(void)  //生成食物
{
    
}




// 修改方向函数
/*

       负责人 :
       功能:
           判断用户输入的方向 和蛇的方向  是否冲突
               1.如果冲突(相反) : 不修改
               2. 蛇的方向 = 用户输入方向 : 不修改
               3. 合法方向 : 修改蛇的方向
               
       参数 :
             ch: 用户输入的方向
       返回值 :
              空
*/
void updateDir(char ch)   // 修改方向函数
{

}



// 判断蛇头前面是什么 
 /*
       负责人:
       功能:
           1. 根据蛇头坐标 和蛇的方向  获取蛇头前一格的坐标
           2. 判断 地图中 蛇头前一格的坐标是什么内容
                 如果是墙 : 返回0
                 如果是食物 : 返回1

                3. (如果是空地)
                 遍历蛇身 判断这个坐标 是否和蛇身重合
                     如果是 : 返回0
                     如果不是 返回2

       参数 : void
       返回值 :
            0表示前面是蛇身 / 墙
            1表示前面是食物
            2表示前面是空地
*/
int HeadFront(void)  // 判断蛇头前面是什么 
{
    	return 0;
}



//蛇移动后的数据情况
/*
    负责人:
    功能:
        1. 判断是吃到食物的情况 还是空地的情况
        2. 如果是食物:
            1. 蛇长度+1
            2. 去掉地图上的食物 坐标赋为负数
            3. 蛇移动一格 (和方向有关)
            4. 生成新的食物 random函数生成食物坐标
        3. 如果是空地:
            1. 蛇移动一格

    参数:
        result:
            1 表示吃到食物的数据修改
            2: 表示空地的数据修改
    返回值: void

*/
void move(int result)  //蛇移动后的数据情况
{

}


//-----------------------------------------------------------service-wu---------------------------------------------------------