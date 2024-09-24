#include<stdio.h>
#include<stdlib.h>
#include<cstdlib>
#include<conio.h> //getch()���� 
#include<ctime> //time()���� 
#include<windows.h> //Sleep()���� 

#define H 40
#define W 20

#define OFFSET_X 40 //��ͼ��ƫ����
#define OFFSET_Y 5 //��ͼ��ƫ����

//�ߵ��ٶ�
#define SPEED_1 400 
#define SPEED_2 300
#define SPEED_3 200

int FOOD_X, FOOD_Y;  //ʳ�������
void initView(void);   //��ʼ����
void Start(void); //��ӡ���� ���ߣ���ͼ��ʳ�
void gameView(void); //��ʼ��Ϸ ����
int pauseView(void);  //��ͣ����
void selectionView(void); //�Ѷ�ѡ�����
void OverView(); //��������
void init(void); //��ʼ��Ϸ��ʼ��
void generateFood(void); //����ʳ��
void updateDir(char ch); //�޸ķ�����
int HeadFront(void); //�ж���ͷǰ����ʲô
void move(int result); //���ƶ�����������

int map[H][W];  //��ͼ
int s[H * W][2];   //s[i][j]  i��ʾ��i������   j��ʾ����  0��ʾx����  1��ʾy����
int len = 3;  //�ߵĵ�ǰ����
char dir = 'd';  //�ߵĵ�ǰ����
int OPT = 1; //��ǰ�Ѷ�

void gotoXY(int x, int y)
{
    COORD c;
    c.X = x - 1;
    c.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//����ָ����������(��(x,y)��(x+w,y+h)�ľ���
void clear(int x, int y, int w, int h)
{
    for (int i = 0; i < h; i++) {
        gotoXY(x, y + i);
        for (int j = 0; j < w; j++) putchar(' ');
    }
}
//���ô�ӡ��ɫ
void setPrintColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
/*
* 1.��ʼ����
            չʾѡ�� ��ʼ��Ϸ
                      �ڳ�ʼ�������Ϸ� ��ӡ ��Ϸ����˵����
                                                    w�������ƶ�
                                                    s�������ƶ�
                                                    a�������ƶ�
                                                    d�������ƶ�
                                                    ��Ϸ������Q��ͣ
                     �Ѷ�ѡ��
                     �˳���Ϸ


            ��ws����ѡ�� �ƶ���� �س�ѡ��

                     ��ʼ��Ϸ������ ��ʼ��Ϸ ����
                     �Ѷ�ѡ�񣺽��� �Ѷ�ѡ�� ����
                     �˳���Ϸ������ �˳���Ϸ ����

2.��ʼ��Ϸ ����
               չʾ��ͼ��****��  #ʳ��
               չʾ�Ѷȼ�����
               ���Ϸ� Q �� ����ͣ���棩

               �û�wasd�ƶ�
               �߶�ʱ�ƶ�
               �ƶ���
                      ײǽ/�Լ�����������Ϸ����
                      �Ե�ʳ�����+1��ʳ����ʧ �����µ�ʳ�� �ƶ�һ��
                      �յأ��ƶ�һ��
*/
//����/��ʾ���

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


// ---------------------------------------------------------- ������� ------------------------------------------------------

            /*
              1.��ӡ��ͼ
              int map[H][W];

              0��ʾ�յ�
              1��ʾǽ
              2��ʾʳ��




              2.����
              int s[H * W][2];

              s[i][j]
                  i��ʾ��i������
                  j��ʾ����  0��ʾx����  1��ʾy����

                  s[2][0] = 5;  	��[2]������x���� = 5
                  s[2][1] = 3;	    ��[2]������y���� = 3
                  �ߵĵ�[2]������  ������(5,3)


              3.len  �ߵĳ���


              4.
              char dir;   //�ߵĵ�ǰ����

              5.���� ��'*'

              6.ʳ�'#'

              7.ǽ��'��'

             */

             // ---------------------------------------------------------- ������� ------------------------------------------------------





int main()
{
    srand(time(0));

    // srand(static_cast<unsigned int>(time(0)));  // ʹ�õ�ǰʱ����Ϊ���ӽ��г�ʼ��
    while (1)
    {
        initView();
    }


    return 0;
}

//-----------------------------------------------------------view-zhou------------------------------------------------------------

/*
    �����ˣ�
    ���ܣ�
    while(1)
    {
      1.չʾѡ��
            ��ʼ��Ϸ
                   �ڳ�ʼ�������Ϸ� ��ӡ ��Ϸ����˵����
                                                    w�������ƶ�
                                                    s�������ƶ�
                                                    a�������ƶ�
                                                    d�������ƶ�
                                                    ��Ϸ������Q��ͣ
            �Ѷ�ѡ��
            �˳���Ϸ
                   �ڳ�ʼ�������·� ��ӡ �����ߵĻ�

      2.�����������
          ����ws �ƶ���� ѡ�лس�
                ��ʼ��Ϸ������ ��ʼ��Ϸ ����
                �Ѷ�ѡ�񣺽��� �Ѷ�ѡ�� ����
                �˳���Ϸ������ �˳���Ϸ ����
    }
    ������void
    ����ֵ��void
*/
void initView(void)   //��ʼ����
{
    system("cls");
    int userChoose = 0;
    while (1) {
        // ----------------- ��ӡ���� -----------------
        system("title ̰����");//���Ĵ�����
        gotoXY(87, 5);
        printf(" ��������");
        gotoXY(87, 6);
        printf("w:�����ƶ�");
        gotoXY(87, 7);
        printf("s:�����ƶ�");
        gotoXY(87, 8);
        printf("a:�����ƶ�");
        gotoXY(87, 9);
        printf("d:�����ƶ�");
        gotoXY(87, 10);
        printf("q:��ͣ��Ϸ");

        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(54, 9);
        printf("��ʼ��Ϸ");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(54, 12);
        printf("�Ѷ�ѡ��");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(54, 15);
        printf("�˳���Ϸ");
        if (userChoose == 2) setPrintColor(0x0f);
        // ---------------- �����û����� --------------
        char input = _getch();
        // -------------�ж��Ƿ������»��ǻس�------------
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
                gameView();  //���� ��ʼ��Ϸ���� ����
                break;
            case 1:
                selectionView();  // �����Ѷ�ѡ��
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
*  �����ˣ�
*  ���ܣ���ӡ�ߵĳ�ʼ��״ ��ӡ��ͼ
*  ������void
*  ����ֵ��void
*/
void Start(void)  //��ӡ���� ���ߣ���ͼ��ʳ�   
{
    //system("cls");
    HideConsoleCursor();
    init();
    //��ӡ��ͼ
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            int X = i + OFFSET_X;
            int Y = j + OFFSET_Y;
            gotoXY(X, Y);
            switch (map[i][j])
            {
            case 1:
                printf("#");
                break;
            case 0:
                break;
            case 2:
                printf("+");
                break;
            }
        }
    //��ӡ��
    gotoXY(s[0][0] + OFFSET_X, s[0][1] + OFFSET_Y);
    printf("@");
    for (int i = 1; i < len; i++)
    {
        int X = s[i][0] + OFFSET_X;
        int Y = s[i][1] + OFFSET_Y;
        gotoXY(X, Y);
        printf("*");
    }
}

/*
    �����ˣ�
    ����:
        start:
        1. ��ʼ����Ϸ����: ��(����, ����, ����), ��ͼ(ǽ,ʳ��) init()
        while(1)
        {
            if OPT=
                sleep()
            2. ��ӡ/���ƽ���: ��, ��ͼ	Start()
            3. �ж��û���û������
            {
                �����:
                    �ж��û���������� 
                        ����: �޸ķ���:     updateDir()

                        Q�� : ��ͣ��Ϸ: չʾ��ͣ���� pauseView()
							�������ֵ��1: ��Ϸ����
							�������ֵ��0: ���¿�ʼ goto start
							�������ֵ��2: �ص���ʼ���� return
            }
            4. �ƶ�
            {
                �ж�:
                    �ж���ͷ ǰ���λ�� ��ʲô����   headFront()
                    ������ǽ/����, ʳ��, �յ�,

                ִ��:
                    headFront()����ֵ����move()�޸�����
                    ��ǰ�����������ǽ����Ϸ���� OverView().
            }
        }
    ����: void
    ����ֵ: void
*/
void gameView(void)  //��ʼ��Ϸ ����     //�����ߵ��ٶ� sleep(int)  gotoXY��ӡ����
{
restart:           //���¿�ʼ
    system("cls");
    Start();
    int flag;  //��ͷǰ����ʲô 0:����/ǽ��  1��ʳ��  2���յ�
    while (1)
    {
        if (OPT == 1)
        {
            Sleep(SPEED_1);
        }
        else if (OPT == 2)
        {
            Sleep(SPEED_2);
        }
        else if (OPT == 3)
        {
            Sleep(SPEED_3);
        }

        int pause_choose = 3;
        if (_kbhit())  //�ж��û���û������
        {
            int ch = _getch(); //��ȡ�û�����
            switch (ch)
            {
            case'q':
            case'Q':
                pause_choose = pauseView();
                break;
            default:
                updateDir(ch);
            }

        }
        if (pause_choose == 1) {
            //��ӡ��ͼ
            for (int i = 0; i < H; i++)
                for (int j = 0; j < W; j++)
                {
                    int X = i + OFFSET_X;
                    int Y = j + OFFSET_Y;
                    gotoXY(X, Y);
                    switch (map[i][j])
                    {
                    case 1:
                        printf("#");
                        break;
                    case 0:
                        break;
                    case 2:
                        printf("+");
                        break;
                    }
                }
            //��ӡ��
            gotoXY(s[0][0] + OFFSET_X, s[0][1] + OFFSET_Y);
            printf("@");
            for (int i = 1; i < len; i++)
            {
                int X = s[i][0] + OFFSET_X;
                int Y = s[i][1] + OFFSET_Y;
                gotoXY(X, Y);
                printf("*");
            }
        }//1������Ϸ��2�������˵�,0���¿�ʼ
        else if (pause_choose == 2)
        {
            system("cls");
            return;
        }
        else if (pause_choose == 0) goto restart;
        flag = HeadFront();
        if (flag == 0) {
            OverView();
            return;
        }
        move(flag);

        //int count = 0;
        if (flag == 1)
        {
            generateFood();   //�Ե�ʳ���������һ��
            //count++;
        }



        clear(1 + OFFSET_X, 1 + OFFSET_Y, H - 2, W - 2);
        gotoXY(FOOD_X + OFFSET_X, FOOD_Y + OFFSET_Y);
        printf("+");
        gotoXY(s[0][0] + OFFSET_X, s[0][1] + OFFSET_Y);
        printf("@");
        for (int i = 1; i < len; i++)
        {
            gotoXY(s[i][0] + OFFSET_X, s[i][1] + OFFSET_Y);
            printf("*");
        }
    }
}


//��ͣ����
/*

 �����ˣ�
	���ܣ�
		��һ�д�ӡ ��Ϸ��ͣ
		����ֱ� ��ӡ ������Ϸ
					  ���¿�ʼ
					  �ص��˵�

		��ws����ѡ�� �ƶ���� �س�ѡ��
	������void
	����ֵ��int
	���ؼ�����Ϸ->���� 1
	���¿�ʼ->���� 0
	�ص��˵�->���� 2
*/
int pauseView(void)  //��ͣ����
{
    clear(1, 1, 100, 30);
    //system("cls");
    int userChoose = 0;
    while (1)
    {
        // ----------------- ��ӡ���� -----------------
        gotoXY(56, 9);
        printf("---�� Ϸ �� ͣ---");

        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(60, 12);
        printf("������Ϸ");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(60, 15);
        printf("���¿�ʼ");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(60, 18);
        printf("�ص��˵�");
        if (userChoose == 2) setPrintColor(0x0f);

        // ---------------- �����û����� --------------
        char input = _getch();

        // -------------�ж��Ƿ������»��ǻس�------------
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



//�Ѷ�ѡ�����
/*
 *    �����ˣ� 
 * ���ܣ���һ�� ��ӡ �Ѷ�ѡ��
 * �����ӡ�� ����
 * ��
 * ����
 * ����
 * ��ws����ѡ�� �ƶ���� �س�ѡ��
 * �޸�ȫ�ֱ���OPT
 * ������void
 * ����ֵ��void
*/
void  selectionView(void)
{
    system("cls");
    int userChoose = 0;
    while (1)
    {
        // ----------------- ��ӡ���� -----------------
        gotoXY(58, 9);
        printf("---�� �� ѡ ��---");
        if (userChoose == 0) setPrintColor(0x6f);
        gotoXY(64, 12);
        printf("����\t");
        if (userChoose == 0) setPrintColor(0x0f);

        if (userChoose == 1) setPrintColor(0x6f);
        gotoXY(64, 15);
        printf("��\t");
        if (userChoose == 1) setPrintColor(0x0f);

        if (userChoose == 2) setPrintColor(0x6f);
        gotoXY(64, 18);
        printf("����\t");
        if (userChoose == 2) setPrintColor(0x0f);

        if (userChoose == 3) setPrintColor(0x6f);
        gotoXY(63, 24);
        printf("��  ��");
        if (userChoose == 3) setPrintColor(0x0f);

        //if (userChoose == 3) setPrintColor(0x6f);
        //gotoXY(64, 24);
        //printf("��  ��");
        //if (userChoose == 3) setPrintColor(0x0f);

        // ---------------- �����û����� --------------
        char input = _getch();
        // -------------�ж��Ƿ������»��ǻس�------------
        switch (input)
        {
        case 'w':
            userChoose -= 1;
            if (userChoose == -1) userChoose = 3;
            break;
        case 's':
            userChoose = (userChoose + 1) % 4;
            break;
        case '\r':
            clear(3, 2, 80, 20);
            switch (userChoose)
            {
            case 0:
                OPT = 1;
                gameView();
                break;
            case 1:
                OPT = 2;
                gameView();
                break;
            case 2:
                OPT = 3;
                gameView();
                break;
            case 3:
                initView();
            default:
                break;
            }
            clear(3, 2, 36, 20);
            break;
        }
    }
}

//��������
/*
     �����ˣ�
     ���ܣ���һ�� ��ӡ ��Ϸ����
     �����ӡ�� ����һ��
     ��ѡ�Ѷ�
     ���ز˵�
     ��ws����ѡ�� �ƶ���� �س�ѡ��
     ������void
*/
void OverView()
{
    system("cls");
    int userChoose = 0;
    while (1) {
        // ----------------- ��ӡ���� -----------------
        gotoXY(54, 6);
        printf("---�� Ϸ �� ��---");
        setPrintColor(0x6f);
        gotoXY(58, 9);
        printf("");
        setPrintColor(0x0f);

        setPrintColor(0x6f);
        gotoXY(58, 18);
        printf("���ز˵�");
        setPrintColor(0x0f);

        // ---------------- �����û����� --------------
        char input = _getch();

        // -------------�ж��Ƿ������»��ǻس�------------
        switch (input) {
        case '\r':
            clear(3, 2, 80, 20);
            return;
            break;
        }
    }
    return;
}


//-----------------------------------------------------------view-zhou------------------------------------------------------------




//-----------------------------------------------------------service-wu---------------------------------------------------------
// ��ʼ������
/*
    ������: 
    ����:
        ��ͼ �߳��� ��λ��
        ��ͼ:
            ��ͼ��ΧһȦǽ(1)
            ��ͼ�м��ʼ��Ϊ�յ�(0)

        ��λ��:
            ��ͼ�м�λ��
            ������
        �߷���: d

        ʳ��:
            �ڵ�ͼ���������һ��ʳ��
            ע�� ʳ�ﲻ�ܺ������ص�
    ����: void
    ����ֵ: void
*/
void init(void)  //��ʼ��Ϸ��ʼ��
{
    for (int i = 0; i < H; i++)
        for (int j = 0; j < W; j++)
        {
            if (i == 0 || j == 0 || i == H - 1 || j == W - 1)
                map[i][j] = 1;
            else
                map[i][j] = 0;
        }

    len = 3;
    s[0][0] = 5;  //��ͷ��ʼX����
    s[0][1] = W - 4;  //��ͷ��ʼY����
    for (int i = 1; i < 3; i++)
    {
        s[i][0] = s[i - 1][0] - 1;
        s[i][1] = s[i - 1][1];
    }
    generateFood();  //����һ��ʳ��
}


//����ʳ��
/*
*    �����ˣ�
*    ���ܣ�
*   	        �������ʳ������ FOOD_X,FOOD_Y   
*              ʳ�ﲻ�ܺ������غ�  rand()
     ������void
     ����ֵ��void
*/

void generateFood(void)  //����ʳ��
{
    int t = 1; //t==1��˵���������غϣ���������
    while (t)
    {
        t = 0;
        FOOD_X = rand() % (H - 2) + 1;
        FOOD_Y = rand() % (W - 2) + 1;
        for (int i = 0; i < len; i++)
            if (s[i][0] == FOOD_X && s[i][1] == FOOD_Y) t = 1;
    }
    map[FOOD_X][FOOD_Y] = 2;
}




// �޸ķ�����
/*

       ������ :
       ����:
           �ж��û�����ķ��� ���ߵķ���  �Ƿ��ͻ
               1.�����ͻ(�෴) : ���޸�
               2. �ߵķ��� = �û����뷽�� : ���޸�
               3. �Ϸ����� : �޸��ߵķ���
               
       ���� :
             ch: �û�����ķ���
       ����ֵ :
              ��
*/
void updateDir(char ch)   // �޸ķ�����
{
    if ((ch == 'w' || ch == 'W') && (dir == 's' || dir == 'S'));
    else if ((ch == 's' || ch == 'W') && (dir == 'w' || dir == 'W'));
    else if ((ch == 'a' || ch == 'A') && (dir == 'd' || dir == 'D'));
    else if ((ch == 'd' || ch == 'D') && (dir == 'a' || dir == 'A'));
    else if (ch == 'w' || ch == 'W' || ch == 's' || ch == 'S' || ch == 'a' || ch == 'A' || ch == 'd' || ch == 'D')
        dir = ch;
}



// �ж���ͷǰ����ʲô 
 /*
       ������:
       ����:
           1. ������ͷ���� ���ߵķ���  ��ȡ��ͷǰһ�������
           2. �ж� ��ͼ�� ��ͷǰһ���������ʲô����
                 �����ǽ : ����0
                 �����ʳ�� : ����1

                3. (����ǿյ�)
                 �������� �ж�������� �Ƿ�������غ�
                     ����� : ����0
                     ������� ����2

       ���� : void
       ����ֵ :
            0��ʾǰ�������� / ǽ
            1��ʾǰ����ʳ��
            2��ʾǰ���ǿյ�
*/
int HeadFront(void)  // �ж���ͷǰ����ʲô 
{
    int X = s[0][0]; //��ͷ��X����
    int Y = s[0][1];  //��ͷ��Y����

    int X_next;  //��ͷ��һ��λ�õ�X����
    int Y_next;  //��ͷ��һ��λ�õ�X����

    switch (dir)
    {
    case 'w':
    case 'W':
        X_next = X;
        Y_next = Y - 1;
        break;

    case 's':
    case 'S':
        X_next = X;
        Y_next = Y + 1;
        break;

    case 'a':
    case 'A':
        X_next = X - 1;
        Y_next = Y;
        break;

    case 'd':
    case 'D':
        X_next = X + 1;
        Y_next = Y;
        break;
    }
    for (int i = 1; i < len; i++)
    {
        if (s[i][0] == X_next && s[i][1] == Y_next) return 0;   //��ͷ����һ��λ��������
    }

    if (map[X_next][Y_next] == 1) return 0; //ǽ��
    else if (X_next == FOOD_X && Y_next == FOOD_Y) return 1; //ʳ��

    return 2; //�յ� 
}



//���ƶ�����������
/*
    ������:
    ����:
        1. �ж��ǳԵ�ʳ������ ���ǿյص����
        2. �����ʳ��:
            1. �߳���+1
            2. ȥ����ͼ�ϵ�ʳ�� ���긳Ϊ����
            3. ���ƶ�һ�� (�ͷ����й�)
            4. �����µ�ʳ�� random��������ʳ������
        3. ����ǿյ�:
            1. ���ƶ�һ��

    ����:
        result:
            1 ��ʾ�Ե�ʳ��������޸�
            2: ��ʾ�յص������޸�
    ����ֵ: void

*/
void move(int result)  //���ƶ�����������
{
    if (result == 1) len++;
    for (int i = len - 1; i >= 1; i--)
    {
        s[i][0] = s[i - 1][0];
        s[i][1] = s[i - 1][1];
    }
    switch (dir)
    {
    case 's':
    case 'S':
        if (result == 1) map[s[0][0]][s[0][1] + 1] = 0;  //ɾ��ʳ��
        s[0][1]++;   //�����ƶ���Y�����1
        if (s[0][1] == W - 1) s[0][1] = 1;
        break;
    case 'w':
    case 'W':
        if (result == 1) map[s[0][0]][s[0][1] - 1] = 0;  //ɾ��ʳ��
        s[0][1]--;   //�����ƶ���Y�����1
        if (s[0][1] == 0) s[0][1] = W - 2;
        break;
    case 'a':
    case 'A':
        if (result == 1) map[s[0][0] - 1][s[0][1]] = 0;  //ɾ��ʳ��
        s[0][0]--;   //�����ƶ���X�����1
        if (s[0][0] == 0) s[0][0] = H - 2;
        break;
    case 'd':
    case 'D':
        if (result == 1) map[s[0][0] + 1][s[0][1]] = 0;  //ɾ��ʳ��
        s[0][0]++;   //�����ƶ���X�����1
        if (s[0][0] == H - 1) s[0][0] = 1;
        break;
    }

}


//-----------------------------------------------------------service-wu---------------------------------------------------------