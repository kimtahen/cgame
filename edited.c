#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include<mmsystem.h>
#pragma comment(lib, "winmm.lib")

#define FILENAME "data.dat"
#define LEFT 75
#define RIGHT 77
#define ENTER 13

#define DOG_ESCAPE 5
#define CAT_ESCAPE 100
#define PANGUIN_ESCAPE 20
#define HAMSTER_ESCAPE 2
#define CHICKEN_ESCAPE 1

#define MUSIC "music.wav"

struct cs
{
    int work;
    int day;
    int money;
} currentStatus = {5, 1, 0};

struct as
{
    int currentLove[5];
    int win;
    
}   animalStatus = {{0,},0};

struct ps
{
    int day;
    int isPlanted;
    int win;
} plantStatus = {
    .day = 0, .win = 0
};

struct m
{
    int diyNumber;
    int win;
} makingStatus = {0,0};

struct g
{
    int data;
} gameStatus = {0};

struct a
{
    int data;
} achievementStatus = {0};

struct s
{
    int data;
} storeStatus = {0};

struct i
{
    char *animal[5];
    int animalNumber[5];
    char *plant[5];
    int plantNumber[5];
    char *diy[7];
    int diyNumber[7];
    char *ingredient[7];
    int ingredientNumber[7];
} inventoryStatus = {
    .animalNumber = {
        0,
    },
    .plantNumber = {
        0,
    },
    .diyNumber = {
        0,
    },
    .ingredientNumber = {
        0,
    },
};

void gotoxy(int x, int y, const char *s)
{
    COORD pos = {2 * x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    printf("%s", s);
}

void mainMenu();
int checkStatus();
void loadData();
void saveData();
void drawLine(int x1, int y1, int x2, int y2, const char *symbol);
void drawModule();
void initialize();
void title();
void story();
void endingscreen();

void animalGrowth();
void plantGrowth();
void making();
void game();
void sleep();
void achievement();
void store();
void inventory();
void saveAndExit();

const char *character[4] = {"\\(*_*)", "(   (>", "(   )", "/   \\"};
const char *character2[4] = {"( ^▽^)\n", "( /   )/\n", " )    )\n", "/     \\"};

const char *wakedup[5]={"     ∧_∧","　　 ('ω')","　 ＿|　⊃／(＿＿_","／　└-(＿＿＿_／","￣￣￣￣￣￣￣"};
const char *wakedupClear[5]={"                                 ","                                 ","                                 ","                                 ","                                 "};
const char *sleeping[3]={"　＜⌒／`-._＿_","／＜_/＿＿＿＿／","￣￣￣￣￣￣￣"};

int main()
{
    initialize();
    system("mode con cols=150 lines=40");
    loadData();

    int choice;
    int menuChoose = 0;
    int execute;
    int start = 3;
    int isX = 1;
    int cnt1, cnt2, cnt4;
    title();
    while (!_kbhit())
        ;

    getchar();

    system("cls");

    story();

    while (!_kbhit())
        ;

    getchar();

    system("cls");

    while (1)
    {
        mainMenu();
        while (1)
        {
            gotoxy(menuChoose, 22, "");
            if (_kbhit())
            {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER)
                {
                    continue;
                }
                if (choice == LEFT)
                {
                    if (menuChoose > 0)
                    {
                        menuChoose -= 7;
                        start--;
                    }
                }
                else if (choice == RIGHT)
                {
                    if (menuChoose < 56)
                    {
                        menuChoose += 7;
                        start++;
                    }
                }
                else
                {
                    switch (menuChoose)
                    {
                    case 0:
                        if (checkStatus())
                        {
                            animalGrowth();
                        }
                        saveData();
                        break;

                    case 7:
                        if (checkStatus())
                        {
                            plantGrowth();
                        }
                        saveData();
                        break;

                    case 14:
                        if (checkStatus())
                        {
                            making();
                        }
                        saveData();
                        break;

                    case 21:
                        if (checkStatus())
                        {
                            game();
                        }
                        saveData();
                        break;

                    case 28:
                        sleep();
                        saveData();
                        break;

                    case 35:
                        achievement();
                        saveData();
                        break;

                    case 42:
                        if(checkStatus()){
                            store();    
                        }
                        saveData();
                        break;

                    case 49:
                        inventory();
                        saveData();
                        break;

                    case 56:
                        saveAndExit();
                        break;
                    }
                    break;
                }
            }
        }
    }
}

void mainMenu()
{
    system("cls");
    gotoxy(0, 0, "");
    drawModule(2, 14, character, 4);
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");

    gotoxy(0, 20, "오늘은 무엇을 할까?? (선택후 enter!) ");
    for (int i = 0; i < currentStatus.work; i++)
        printf("♥");
    for (int i = 0; i < 5 - currentStatus.work; i++)
        printf("♡");
    printf("  현재 잔액: %d", currentStatus.money);
    printf("  DAY %d", currentStatus.day);
    gotoxy(0, 22, "동물키우기");
    gotoxy(7, 22, "식물기르기");
    gotoxy(14, 22, "DIY");
    gotoxy(21, 22, "게임");
    gotoxy(28, 22, "잠자기");
    gotoxy(35, 22, "업적");
    gotoxy(42, 22, "상점");
    gotoxy(49, 22, "인벤토리");
    gotoxy(56, 22, "저장 후 종료");
}
int checkStatus()
{
    if (currentStatus.work <= 0)
    {
        gotoxy(4, 2, "더 이상 작업을 실행할 수 없습니다. 잠을 자야 일을 더 할 수 있을것 같네.");
        Sleep(1000);
        return 0;
    }
    else
    {
        return 1;
    }
}
void loadData()
{
    FILE *fp;
    fopen_s(&fp, FILENAME, "r");
    if (fp == NULL)
    {
        fopen_s(&fp, FILENAME, "w");
        fwrite(&currentStatus, sizeof(struct cs), 1, fp);
        fwrite(&animalStatus, sizeof(struct as), 1, fp);
        fwrite(&plantStatus, sizeof(struct ps), 1, fp);
        fwrite(&makingStatus, sizeof(struct m), 1, fp);
        fwrite(&storeStatus, sizeof(struct s), 1, fp);
        fwrite(&achievementStatus, sizeof(struct a), 1, fp);
        fwrite(&gameStatus, sizeof(struct g), 1, fp);
        fwrite(&inventoryStatus, sizeof(struct i), 1, fp);
    }
    else
    {
        fread(&currentStatus, sizeof(struct cs), 1, fp);
        fread(&animalStatus, sizeof(struct as), 1, fp);
        fread(&plantStatus, sizeof(struct ps), 1, fp);
        fread(&makingStatus, sizeof(struct m), 1, fp);
        fread(&storeStatus, sizeof(struct s), 1, fp);
        fread(&achievementStatus, sizeof(struct a), 1, fp);
        fread(&gameStatus, sizeof(struct g), 1, fp);
        fread(&inventoryStatus, sizeof(struct i), 1, fp);
    }
    fclose(fp);
}
void saveData()
{
    FILE *fp;
    fopen_s(&fp, FILENAME, "w");
    fwrite(&currentStatus, sizeof(struct cs), 1, fp);
    fwrite(&animalStatus, sizeof(struct as), 1, fp);
    fwrite(&plantStatus, sizeof(struct ps), 1, fp);
    fwrite(&makingStatus, sizeof(struct m), 1, fp);
    fwrite(&storeStatus, sizeof(struct s), 1, fp);
    fwrite(&achievementStatus, sizeof(struct a), 1, fp);
    fwrite(&gameStatus, sizeof(struct g), 1, fp);
    fwrite(&inventoryStatus, sizeof(struct i), 1, fp);
    fclose(fp);
}
void drawLine(int x1, int y1, int x2, int y2, const char *symbol)
{
    if (x1 == x2)
    {
        for (int i = y1; i <= y2; i++)
        {
            gotoxy(x1, i, symbol);
        }
    }
    else
    {
        for (int i = x1; i <= x2; i++)
        {
            gotoxy(i, y1, symbol);
        }
    }
}
void drawModule(int x, int y, const char *symbol[], int size)
{
    for (int i = 0; i < size; i++)
    {
        gotoxy(x, y + i, symbol[i]);
    }
}

void animalGrowth()
{
    srand(time(NULL));
    int escape = rand() % 100;
    system("cls");
    int i, j;
    int maxLove[5] = {30,100,80,50,40};
    if (plantStatus.day == 0) {
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(4, 4, "1. 강아지");
        gotoxy(4, 6, "2. 고양이");
        gotoxy(4, 8, "3. 펭귄");
        gotoxy(4, 10, "4. 햄스터");
        gotoxy(4, 12, "5. 병아리");
        gotoxy(4, 15, "어떤 동물과 놀아주시겠습니까? ");
        
        scanf("%d(1~5)", &j);
        if(inventoryStatus.animalNumber[j-1] <= 0){
            system("cls");
             drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4,4,"");
            printf("%s(이)가 없습니다.",inventoryStatus.animal[j-1]);
            Sleep(1000);
            return;
        }
        
        
        if(animalStatus.currentLove[j-1]==maxLove[j-1]){
            animalStatus.win++;
            animalStatus.currentLove[j-1] = 0;
            inventoryStatus.animalNumber[j-1] -= 1;
            int a = 0;
             system("cls");
             drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4,4,"동물은 어엿한 어른이 되었습니다 ...");
            gotoxy(4,6,"");
            printf("바이바이 %s...", inventoryStatus.animal[j-1]);
        
            // PlaySound(TEXT(MUSIC), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            // while (1) {
            //     a = _getch();
            //     if (a != 0) {
            //         PlaySound(NULL, 0, 0);
            //         return;
            //     }
            Sleep(1000);
            return;
        }
            
        
        if (j == 1) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "강아지와 놀아줬습니다!");
            gotoxy(4, 6, "애정도가 10 상승.");
            animalStatus.currentLove[j-1] += 10;
            currentStatus.work--;
            if(escape < DOG_ESCAPE){
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                gotoxy(4, 4, "과잉 보호는 일탈을 불러올 수 있습니다...");
                gotoxy(4, 6, "그는 그의 삶을 찾아 떠납니다...");
                inventoryStatus.animalNumber[j-1]--;
                animalStatus.currentLove[j-1] = 0;
            }
        }
        else if (j == 2) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "고양이와 놀아줬습니다!");
            gotoxy(4, 6, "애정도가 10 상승.");
            animalStatus.currentLove[j-1] += 10;
            currentStatus.work--;
            if(escape < CAT_ESCAPE){
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                gotoxy(4, 4, "과잉 보호는 일탈을 불러올 수 있습니다...");
                gotoxy(4, 6, "그는 그의 삶을 찾아 떠납니다...");
                inventoryStatus.animalNumber[j-1]--;
                animalStatus.currentLove[j-1] = 0;
            }
        }
        if (j == 3) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "펭귄과 놀아줬습니다!");
            gotoxy(4, 6, "애정도가 10 상승.");
            animalStatus.currentLove[j-1] += 10;
            currentStatus.work--;
            if(escape < PANGUIN_ESCAPE){
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                gotoxy(4, 4, "과잉 보호는 일탈을 불러올 수 있습니다...");
                gotoxy(4, 6, "그는 그의 삶을 찾아 떠납니다...");
                inventoryStatus.animalNumber[j-1]--;
                animalStatus.currentLove[j-1] = 0;
            }
        }
        if (j == 4) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "햄스터와 놀아줬습니다!");
            gotoxy(4, 6, "애정도가 10 상승.");
            animalStatus.currentLove[j-1] += 10;
            currentStatus.work--;
            if(escape < HAMSTER_ESCAPE){
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                gotoxy(4, 4, "과잉 보호는 일탈을 불러올 수 있습니다...");
                gotoxy(4, 6, "그는 그의 삶을 찾아 떠납니다...");
                inventoryStatus.animalNumber[j-1]--;
                animalStatus.currentLove[j-1] = 0;
            }
        }
        if (j == 5) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "병아리와 놀아줬습니다!");
            gotoxy(4, 6, "애정도가 10 상승.");
            animalStatus.currentLove[j-1] += 10;
            currentStatus.work--;
            if(escape < CHICKEN_ESCAPE){
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                gotoxy(4, 4, "과잉 보호는 일탈을 불러올 수 있습니다...");
                gotoxy(4, 6, "그는 그의 삶을 찾아 떠납니다...");
                inventoryStatus.animalNumber[j-1]--;
                animalStatus.currentLove[j-1] = 0;
            }
        }
    }    
    Sleep(1000);
    return;
}




void plantGrowth()
{
    system("cls");
    int i, j;
    int thanksgivingday[5] = {3, 2, 200, 4, 1};
    int price[5] = {60000, 40000,  100000000, 90000, 35000};
    if (plantStatus.day == 0) {
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(4, 4, "1. 방울토마토");
        gotoxy(4, 6, "2. 고추");
        gotoxy(4, 8, "3. 상추");
        gotoxy(4, 10, "4. 완두콩");
        gotoxy(4, 12, "5. 콩나물");
        gotoxy(4, 15, "어떤 작물을 키우시겠습니까? ");
        
        scanf("%d(1~5)", &j);
        if(inventoryStatus.plantNumber[j-1] <= 0){
            system("cls");
             drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4,4,"");
            printf("%s 씨앗이 없습니다.",inventoryStatus.plant[j-1]);
            Sleep(1000);
            return;
        }
        
        
        if (j == 1) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "방울토마토를 심었습니다!");
            gotoxy(4, 6, "작물은 3일 뒤에 자랍니다.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[0]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        else if (j == 2) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "고추를 심었습니다!");
            gotoxy(4, 6, "작물은 2일 뒤에 자랍니다.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[1]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 3) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "상추를 심었습니다!");
            gotoxy(4, 6, "작물은 200일 뒤에 자랍니다.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[2]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 4) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "완두콩을 심었습니다!");
            gotoxy(4, 6, "작물은 4일 뒤에 자랍니다.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[3]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
        if (j == 5) {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "콩나물을 심었습니다!");
            gotoxy(4, 6, "작물은 1일 뒤에 자랍니다.");
            plantStatus.isPlanted = j-1;
            inventoryStatus.plantNumber[4]--;
            plantStatus.day = currentStatus.day;
            currentStatus.work--;
        }
    }
    else if (currentStatus.day - plantStatus.day >= thanksgivingday[plantStatus.isPlanted] ) {
        plantStatus.win++;
        system("cls");
            drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(4, 4, "");
        printf("이전의 작물이 다 자라 수확을 하여 %d원을 획득하였습니다.",price[plantStatus.isPlanted]);
        currentStatus.money += price[plantStatus.isPlanted];
        plantStatus.day = 0;
    }
    else {
        system("cls");
        gotoxy(4, 4, "작물이 아직 다 자라지 않았습니다.");
        
    }
    Sleep(1000);
    return;

}

//////////////////////making start
void making(void)
{
    system("cls");
    int i, k;
    while (currentStatus.work)
    {

        system("cls");
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(4, 2, "어서오세요 FORIF공방입니다!");
        gotoxy(4, 4, "1.공구,작업도구");
        gotoxy(4, 6, "2.동물용품(집,장난감)");
        gotoxy(4, 8, "3.공방 나가기");
        gotoxy(4, 10, "무엇을 만드실 건가요?:");
        scanf("%d", &i);
        if (i == 1)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "1.망치");
            gotoxy(4, 6, "2.삽");
            gotoxy(4, 8, "3.호미");
            gotoxy(4, 10, "무엇을 만드실 건가요?:");
            scanf("%d", &k);

            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "재료는 철과 나무 각각 하나씩입니다.");
            gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
            if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[1] >= 1)
            {
                inventoryStatus.ingredientNumber[0]--;
                inventoryStatus.ingredientNumber[1]--;
                system("cls");
                drawLine(0, 0, 74, 0, "■");
                drawLine(0, 0, 0, 17, "■");
                drawLine(74, 0, 74, 17, "■");
                drawLine(0, 74, 74, 74, "■");
                if (k == 1)
                {
                   
                    gotoxy(4, 4, "망치를 만들었습니다!");
                    inventoryStatus.diyNumber[0]++;
                    currentStatus.work--;
                }
                if (k == 2)
                {
                    gotoxy(4, 4, "삽을 만들었습니다!");
                    inventoryStatus.diyNumber[1]++;
                    currentStatus.work--;
                }
                if (k == 3)
                {
                    gotoxy(4, 4, "호미를 만들었습니다!");
                    inventoryStatus.diyNumber[2]++;
                    currentStatus.work--;
                }
                 makingStatus.win ++;
            }
            else gotoxy(4,4,"재료가 부족하여 만들지 못합니다.");

        }
        else if (i == 2)
        {
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            gotoxy(4, 4, "1.강아지집");
            gotoxy(4, 6, "2.캣타워");
            gotoxy(4, 8, "3.이글루");
            gotoxy(4, 10, "4.햄스터 쳇바퀴");
            gotoxy(4, 12, "무엇을 만드실 건가요?:");
            scanf("%d", &k);
            system("cls");
            drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
            if (k == 1 || k == 2)
            {
                gotoxy(4, 4, "재료는 못과 드라이버,그리고 나무 각각 하나씩입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[0] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[0]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
            drawLine(0, 0, 0, 17, "■");
            drawLine(74, 0, 74, 17, "■");
            drawLine(0, 74, 74, 74, "■");
                    if (k == 1)
                    {
                        gotoxy(4, 4, "강아지집을 만들었습니다!");
                        inventoryStatus.diyNumber[3]++;
                        currentStatus.work--;
                    }
                    if (k == 2)
                    {
                        gotoxy(4, 4, "캣타워를 만들었습니다!");
                        inventoryStatus.diyNumber[4]++;
                        currentStatus.work--;
                    }
                     makingStatus.win ++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
            else if (k == 3)
            {
                gotoxy(4, 4, "재료는 얼음덩어리 세개입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[6] >= 3)
                {
                    inventoryStatus.ingredientNumber[6] -= 3;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
                    drawLine(0, 0, 0, 17, "■");
                    drawLine(74, 0, 74, 17, "■");
                    drawLine(0, 74, 74, 74, "■");
                    gotoxy(4, 4, "이글루를 만들었습니다!");
                    inventoryStatus.diyNumber[5]++;
                    currentStatus.work--;
                     makingStatus.win ++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
            else if (k == 4)
            {
                gotoxy(4, 4, "재료는 플라스틱, 나사, 드라이버 각각 하나씩입니다.");
                gotoxy(4, 6, "재료는 인벤토리에서 차감됩니다.");
                if (inventoryStatus.ingredientNumber[3] >= 1 && inventoryStatus.ingredientNumber[4] >= 1 && inventoryStatus.ingredientNumber[5] >= 1)
                {
                    inventoryStatus.ingredientNumber[3]--;
                    inventoryStatus.ingredientNumber[4]--;
                    inventoryStatus.ingredientNumber[5]--;
                    system("cls");
                    drawLine(0, 0, 74, 0, "■");
                    drawLine(0, 0, 0, 17, "■");
                    drawLine(74, 0, 74, 17, "■");
                    drawLine(0, 74, 74, 74, "■");
                    gotoxy(4, 4, "햄스터 쳇바퀴를 만들었습니다!");
                    inventoryStatus.diyNumber[6]++;
                    currentStatus.work--;
                    makingStatus.win++;
                }
                else
                    gotoxy(4, 4, "재료가 부족하여 만들지 못합니다.");
            }
        }
        else if (i == 3)
            break;
        Sleep(1000);
    }
    if(currentStatus.work <=0){
        system("cls");
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");
    gotoxy(4,2,"더 이상 작업을 실행할 수 없습니다. 잠을 자야 일을 더 할 수 있을것 같네.");
    Sleep(1000);
    }
    return;
}
///////////////////////making end

////////////////////////////////////game start
int Numrandom(void)
{
    srand(time(NULL));
    int num1, num2, num3, num4, temp;
    num1 = rand() % 900 + 100;
    num2 = num1 / 100;
    num3 = (num1 - num2 * 100) / 10;
    num4 = num1 % 10;
    while (num2 == num3 || num2 == num4 || num3 == num4)
    {
        num1 = rand() % 900 + 100;
        num2 = num1 / 100;
        num3 = (num1 - num2 * 100) / 10;
        num4 = num1 % 10;
    }
    return num1;
}
int game1()
{
    system("cls");
    int i;
    srand(time(NULL));
    i = rand() % 3 + 1;
    if (i == 1)
    {
        int ans, realnum, num2, num3, num4, num5, num6, num7, temp, cnt = 0;
        int out, ball = 0;
        int strike = 0;
        realnum = Numrandom();
        num2 = realnum / 100;
        temp = realnum % 100;
        num3 = temp / 10;
        num4 = temp % 10;
        printf("안녕 나는 야구선수 한양이야! 내 특기는 숫자 야구! 혹시 숫자 야구 알아?\n\n");
        printf("혹시 모르는 애들이 있을 수 있으니까 룰을 간단하게 알려줄게!\n\n");
        printf("===============================RULE=================================\n");
        printf("1.정답은 세자리 숫자야! 100~999안에 숫자중 하나이고 너는 그 숫자를 맞추면 되는거야!\n");
        printf("2.너가 숫자를 말하면 백의 자리 숫자와 십의 자리 숫자, 일의 자리 숫자 각각을 비교해\n");
        printf("자리와 숫자가 같으면 스트라이크! 숫자는 포함되는데 자리가 다르면 볼! 숫자가 포함안되면 아웃!\n");
        printf("3.예를 들어 정답이 123이고 너가 말한 숫자가 524라면 1스트라이크 2아웃이 되는거야!\n");
        printf("만약 317을 말한다면 2볼 1아웃이 되겠지??\n");
        printf("\n7번안에 맞춘다면 보상이 주어질거야! 적으면서 하는 것을 추천할게!, 이제 시작하자!!\n\n");
        printf("정답은 무엇일까?:");
        scanf("%d", &ans);
        while (cnt < 7)
        {
            if (ans == realnum && cnt < 7)
            {
                printf("정답이야! %d번만에 맞추다니 대단한걸? 보상을 받아가!", cnt + 1);
                return 1;
            }
            else
            {
                num5 = ans / 100;
                temp = ans % 100;
                num6 = temp / 10;
                num7 = temp % 10;
                if (num2 == num5)
                    strike++;
                if (num2 == num6 || num2 == num7)
                    ball++;
                if (num3 == num5 || num3 == num7)
                    ball++;
                if (num3 == num6)
                    strike++;
                if (num4 == num7)
                    strike++;
                if (num4 == num5 || num4 == num6)
                    ball++;
                out = 3 - (strike + ball);
                printf("%d스트라이크 %d볼 %d아웃!\n\n", strike, ball, out);
                strike = 0;
                ball = 0;
                out = 0;
                cnt++;
                if (cnt >= 7)
                    break;
                printf("정답은 무엇일까?:");
                scanf("%d", &ans);
            }
        }
        printf("정답은 %d 이거로 실패야ㅠㅠㅠ\n", realnum);
        printf("7번이 넘었는걸? 안타깝지만 실패야ㅠㅠㅠㅠ 다음을 바라도록!");
        return 0;
    }
    else if (i == 2)
    {
        int num1, num2, ans;
        printf("다음화면에 나올 클로버의 개수는 홀수일까요? 아니면 짝수일까요??\n\n");
        printf("당신의 운에 맡기세요!!!\n\n");
        printf("당신의 대답은?(홀수면 1, 짝수면 2) : ");
        scanf("%d", &num1);
        printf("\n======================================\n");
        ans = rand() % 2 + 1;
        if (num1 == ans && num1 == 1)
        {
            printf("♣ ♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("5개네요! 정답입니다!!\n\n");
            printf("보상이 있겠습니다.");
            return 1;
        }
        else if (num1 == ans && num1 == 2)
        {
            printf("♣ ♣ ♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("6개네요! 정답입니다!!\n\n");
            printf("보상이 있겠습니다.");
            return 1;
        }
        else if (num1 != ans && num1 == 1)
        {
            printf("♣ ♣ ♣ ♣\n");
            printf("\n=====================================\n");
            printf("4개로 짝수네요ㅠㅠ 다음에 도전하세요!");
            return 0;
        }
        else
        {
            printf("♣ ♣ ♣ \n");
            printf("\n=====================================\n");
            printf("3개로 홀수네요ㅠㅠ 다음에 도전하세요!");
            return 0;
        }
    }
    else
    {
        int ans, realday, num1, cnt = 0;
        realday = rand() % 31 + 1;
        printf("안녕 내 이름은 포리프야! 7월에 해커톤 한다고 수고가 많아\n\n");
        printf("마침 내 생일도 7월인데 내 생일을 맞추어 볼래? 기회는 4번이야!\n\n");
        printf("내 생일은 언제 일까?(1~31):");
        scanf("%d", &ans);
        while (cnt < 3)
        {
            if (ans == realday)
            {
                printf("\n맞아 그 날이 내 생일이야!\n\n");
                printf("보상을 받아가도록해!");
                return 1;
            }
            else if (ans > realday)
            {
                printf("\n내 생일치고는 좀 늦은 감이 있네..\n\n");
                printf("다시 맞춰봐!\n\n");
                printf("내 생일은 언제 일까?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
            else
            {
                printf("\n내 생일치고는 좀 이른 감이 있네..\n\n");
                printf("다시 맞춰봐!\n\n");
                printf("내 생일은 언제 일까?(1~31):");
                scanf("%d", &ans);
                cnt++;
            }
        }
        if (ans != realday)
        {
            printf("\n4번 다 틀렸네 정답은 %d일이야!\n\n", realday);
            printf("틀렸으니까 보상은 없어!");
            return 0;
        }
        else
        {
            printf("\n마지막 기회에 맞추다니!! 아쉽다.. 축하해!\n\n");
            printf("보상을 받아가도록 해!");
            return 1;
        }
    }
}

void game()
{
    int num;
    num = game1();
    currentStatus.work--;
    if (num == 1)
        currentStatus.money += 30000;
    Sleep(2000);
    return;
}
/////////////////////////////////game end

void sleep()
{
    system("cls");
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");
    drawModule(30,10,sleeping,3);
    currentStatus.day++;
    currentStatus.work = 5;
    Sleep(800);
    drawModule(30,10,wakedupClear,5);
    drawModule(30,8,wakedup,5);
    Sleep(500);
    return;
}
void achievement()
{
    // system("cls");
    //         drawLine(0, 0, 74, 0, "■");
    //         drawLine(0, 0, 0, 17, "■");
    //         drawLine(74, 0, 74, 17, "■");
    //         drawLine(0, 74, 74, 74, "■");
    //         gotoxy(4, 4, "1. 자연의 왕 드루이드");
    //         gotoxy(4, 6, "2.캣타워");
    //         gotoxy(4, 8, "3.이글루");
    //         gotoxy(4, 10, "4.햄스터 쳇바퀴");
    //         gotoxy(4, 12, "무엇을 만드실 건가요?:");
    
     system("cls");
    
        gotoxy(33, 15, "업   적   확   인");
        gotoxy(18, 16, "----------------------------------------------------------------------------------------");
        gotoxy(20, 17, "퀘스트 1            5마리 이상 동물 호감도 max");
        printf("       (%d / 5)", animalStatus.win);
        gotoxy(20, 19, "퀘스트 2            작물 10개 이상");
        printf("       (%d / 10)", plantStatus.win);
        gotoxy(20, 21, "퀘스트 3            diy 50개 이상 성공");
        printf("       (%d / 50)", makingStatus.win);

        if (animalStatus.win >= 5)
            gotoxy(55, 17, "달성!");
        else
            gotoxy(55, 17, "미달성");



        if (plantStatus.win>=10)
            gotoxy(55, 19, "달성!");
        else
            gotoxy(55, 19, "미달성");

        if (makingStatus.win >= 50)
            gotoxy(55, 21, "달성!");
        else
            gotoxy(55, 21, "미달성");

    Sleep(5000);
    endingscreen();
    Sleep(2000);
    return;

}
void endingscreen() {
    if (animalStatus.win >= 5 && plantStatus.win>=10 && makingStatus.win >= 50 ){
        system("cls");
        gotoxy(0, 0, "");
        gotoxy(4, 4, "모든 업적을 달성하셨습니다. 축하합니다!");
        drawModule(2, 14, character2, 4);
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
    }
}

void store() {
    if(!checkStatus()){
        return;
    }
    int menuChoose =28;
    int choice;
    int execute;
    system("cls");
    gotoxy(0, 0, "");
    drawModule(2, 14, character, 4);
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");
    gotoxy(28, 22, "동물");
    gotoxy(35, 22, "씨앗");
    gotoxy(42, 22, "DIY재료");
    gotoxy(49, 22, "나가기");
    gotoxy(49, 25, "");
        printf("현재 돈: %d", currentStatus.money);
    while (1) {
        gotoxy(menuChoose, 22, "");
        if (_kbhit()) {
            choice = _getch();
            if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                continue;
            }
            if (choice == LEFT) {
                if (menuChoose > 28) {
                    menuChoose -= 7;
                }
            }
            else if (choice == RIGHT) {
                if (menuChoose < 49) {
                    menuChoose += 7;
                }
            }
            else {
                break;
            }
        }
    }
    switch (menuChoose) {
    case 28:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(21, 22, "강아지");
        gotoxy(28, 22, "고양이");
        gotoxy(35, 22, "펭귄");
        gotoxy(42, 22, "햄스터");
        gotoxy(49, 22, "병아리");
        gotoxy(21, 23, "$100000");
        gotoxy(28, 23, "$100000");
        gotoxy(35, 23, "$100000");
        gotoxy(42, 23, "$100000");
        gotoxy(49, 23, "$100000");

        gotoxy(49, 25, "");
        printf("현재 돈: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 21) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 49) {
                        menuChoose += 7;
                    }
                }
                else {
                    switch (menuChoose) {
                    case 21:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "구매완료");
                                inventoryStatus.animalNumber[0]++;
                            }
                            else {
                                printf("돈이 부족합니다.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 28:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "구매완료");
                                inventoryStatus.animalNumber[1]++;
                            }
                            else {
                                printf("돈이 부족합니다.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 35:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "구매완료");
                                inventoryStatus.animalNumber[2]++;
                            }
                            else {
                                printf("돈이 부족합니다.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 42:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "구매완료");
                                inventoryStatus.animalNumber[3]++;
                            }
                            else {
                                printf("돈이 부족합니다.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    case 49:
                        if (checkStatus()) {
                            if (currentStatus.money >= 100000) {
                                currentStatus.money -= 100000;
                                system("cls");
                                gotoxy(35, 25, "구매완료");
                                inventoryStatus.animalNumber[4]++;
                            }
                            else {
                                printf("돈이 부족합니다.");
                            }
                            currentStatus.work--;
                            Sleep(1000);
                        }
                        break;

                    }
                    break;
                }

            }
        }
        break;
    case 35:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(21, 22, "방울토마토");
        gotoxy(28, 22, "고추");
        gotoxy(35, 22, "상추");
        gotoxy(42, 22, "완두콩");
        gotoxy(49, 22, "콩나물");

        gotoxy(21, 23, "$30000");
        gotoxy(28, 23, "$30000");
        gotoxy(35, 23, "$30000");
        gotoxy(42, 23, "$30000");
        gotoxy(49, 23, "$30000");
        gotoxy(49, 25, "");
        printf("현재 돈: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 21) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 49) {
                        menuChoose += 7;
                    }
                }
                else {
                    break;
                }
            }
        }
        switch (menuChoose) {
        case 21:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.plantNumber[0]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 28:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.plantNumber[1]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 35:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.plantNumber[2]++;
                    currentStatus.money -= 30000;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 42:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.plantNumber[3]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 49:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.plantNumber[4]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;


        }
        break;
    case 42:
        system("cls");
        gotoxy(0, 0, "");
        drawModule(2, 14, character, 4);
        drawLine(0, 0, 74, 0, "■");
        drawLine(0, 0, 0, 17, "■");
        drawLine(74, 0, 74, 17, "■");
        drawLine(0, 74, 74, 74, "■");
        gotoxy(14, 22, "나무");
        gotoxy(21, 22, "철");
        gotoxy(28, 22, "못");
        gotoxy(35, 22, "플라스틱");
        gotoxy(42, 22, "드라이버");
        gotoxy(49, 22, "나사");
        gotoxy(56, 22, "얼음덩어리");
        gotoxy(49, 25, "");
        gotoxy(14, 23, "$20000");
        gotoxy(21, 23, "$20000");
        gotoxy(28, 23, "$10000");
        gotoxy(35, 23, "$20000");
        gotoxy(42, 23, "$30000");
        gotoxy(49, 23, "$10000");
        gotoxy(56, 23, "$10000");
        gotoxy(49, 25, "");
        printf("현재 돈: %d", currentStatus.money);
        while (1) {
            gotoxy(menuChoose, 22, "");
            if (_kbhit()) {
                choice = _getch();
                if (choice != LEFT && choice != RIGHT && choice != ENTER) {
                    continue;
                }
                if (choice == LEFT) {
                    if (menuChoose > 14) {
                        menuChoose -= 7;
                    }
                }
                else if (choice == RIGHT) {
                    if (menuChoose < 56) {
                        menuChoose += 7;
                    }
                }
                else {
                    break;
                }
            }
        }
        switch (menuChoose) {
        case 14:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[0]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 21:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[1]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 28:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[2]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 35:
            if (checkStatus()) {
                if (currentStatus.money >= 20000) {
                    currentStatus.money -= 20000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[3]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 42:
            if (checkStatus()) {
                if (currentStatus.money >= 30000) {
                    currentStatus.money -= 30000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[4]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 49:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[5]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }
            break;

        case 56:
            if (checkStatus()) {
                if (currentStatus.money >= 10000) {
                    currentStatus.money -= 10000;
                    system("cls");
                    gotoxy(35, 25, "구매완료");
                    inventoryStatus.ingredientNumber[6]++;
                }
                else {
                    printf("돈이 부족합니다.");
                }
                currentStatus.work--;
                Sleep(1000);
            }   
            break;
        }
    case 49: break;
        
    }
    return;
}
void inventory()
{
    system("cls");
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");
    gotoxy(1,2,"<동물>");
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,3, inventoryStatus.animal[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,4, "");
        printf("%d",inventoryStatus.animalNumber[i]);
    }

    gotoxy(1,6,"<식물>");
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,7, inventoryStatus.plant[i]);
    }
    for (int i = 0; i < 5; i++)
    {
        gotoxy(1+i*5,8, "");
        printf("%d",inventoryStatus.plantNumber[i]);
    }

    gotoxy(1,10,"<소지품>");
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,11, inventoryStatus.diy[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,12, "");
        printf("%d",inventoryStatus.diyNumber[i]);
    }

    gotoxy(1,14,"<재료>");
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,15, inventoryStatus.ingredient[i]);
    }
    for (int i = 0; i < 7; i++)
    {
        gotoxy(1+i*5,16, "");
        printf("%d",inventoryStatus.ingredientNumber[i]);
    }
    
    gotoxy(0,20,"아무키나 누르십시오...");
    
    while(!_kbhit());
    getchar();
    return;
}
void saveAndExit()
{
    system("cls");
    gotoxy(0, 0, "saveAndExit");
    saveData();
    Sleep(1000);
    exit(0);
    return;
}

void initialize()
{
    currentStatus.money = 13400000;

    //animalStatus.win = 6;
    //plantStatus.win = 11;
    //makingStatus.win = 100;

    inventoryStatus.animal[0] = "강아지";
    inventoryStatus.animal[1] = "고양이";
    inventoryStatus.animal[2] = "펭귄";
    inventoryStatus.animal[3] = "햄스터";
    inventoryStatus.animal[4] = "병아리";
    inventoryStatus.plant[0] = "방울토마토";
    inventoryStatus.plant[1] = "고추";
    inventoryStatus.plant[2] = "상추";
    inventoryStatus.plant[3] = "완두콩";
    inventoryStatus.plant[4] = "콩나물";
    inventoryStatus.diy[0] = "망치";
    inventoryStatus.diy[1] = "삽";
    inventoryStatus.diy[2] = "호미";
    inventoryStatus.diy[3] = "개집";
    inventoryStatus.diy[4] = "캣타워";
    inventoryStatus.diy[5] = "이글루";
    inventoryStatus.diy[6] = "쳇바퀴";
    inventoryStatus.ingredient[0] = "나무" ;
    inventoryStatus.ingredient[1] = "철" ;
    inventoryStatus.ingredient[2] = "못" ;
    inventoryStatus.ingredient[3] = "플라스틱" ;
    inventoryStatus.ingredient[4]= "드라이버" ;
    inventoryStatus.ingredient[5] = "나사" ;
    inventoryStatus.ingredient[6] = "얼음덩어리" ;



    inventoryStatus.animalNumber[0] = 0;
    inventoryStatus.animalNumber[1] = 0;
    inventoryStatus.animalNumber[2] = 0;
    inventoryStatus.animalNumber[3] = 0;
    inventoryStatus.animalNumber[4] = 0;
    inventoryStatus.plantNumber[0] = 0;
    inventoryStatus.plantNumber[1] = 0;
    inventoryStatus.plantNumber[2] = 0;
    inventoryStatus.plantNumber[3] = 0;
    inventoryStatus.plantNumber[4] = 0;
    inventoryStatus.diyNumber[0] = 0;
    inventoryStatus.diyNumber[1] = 0;
    inventoryStatus.diyNumber[2] = 0;
    inventoryStatus.diyNumber[3] = 0;
    inventoryStatus.diyNumber[4] = 0;
    inventoryStatus.diyNumber[5] = 0;
    inventoryStatus.diyNumber[6] = 0;
    inventoryStatus.ingredientNumber[0] = 0;
    inventoryStatus.ingredientNumber[1] = 0;
    inventoryStatus.ingredientNumber[2] = 0;
    inventoryStatus.ingredientNumber[3] = 0;
    inventoryStatus.ingredientNumber[4] = 0;
    inventoryStatus.ingredientNumber[5] = 0;
    inventoryStatus.ingredientNumber[6] = 0;
}

void title() 
{
    gotoxy(0, 0, "");
    drawLine(0, 0, 74, 0, "■");
    drawLine(0, 0, 0, 17, "■");
    drawLine(74, 0, 74, 17, "■");
    drawLine(0, 74, 74, 74, "■");

    gotoxy(10, 5, "                  ###      ##     #######   ##        #####      ##      #####    ##       ");
    gotoxy(10, 6, "                #######    ##           #   ##     ###     ###   ##        ###    ##       ");
    gotoxy(10, 7, "                 ###       ##     #######   ##     ###     ###   ##      ##  ##   ##       ");
    gotoxy(10, 8, "                ##  ##     ##     #         ##     ###     ###   ##     ##    ##  ##       ");
    gotoxy(10, 9, "                 ###       ##     #######   ##        #####      ##                        ");
    gotoxy(10, 10, "                   ########                                      ##       ###   ###        ");
    gotoxy(10, 11, "                          #          ######       ##################      ###   ###        ");
    gotoxy(10, 12, "                   ########         ##    ##                     ##       #########        ");
    gotoxy(10, 13, "                   #                ##    ##                     ##       ###   ###        ");
    gotoxy(10, 14, "                   ########          ######                      ##       #########        ");

    while (!_kbhit())
    {
        gotoxy(7, 16, "                             <      PRESS      ENTER      KEY      TO      START      >    ");
        Sleep(400);
        gotoxy(7, 16, "                                                                                         ");
        Sleep(400);
    }
}

void story()
{

    gotoxy(4, 1, "INTRO...");
        Sleep(100);
        gotoxy(4, 3, "안녕하세요! 힐링의 집에 오신 것을 환영합니다!");
        Sleep(300);
        gotoxy(4, 5, "힐링의 집에는 집돌이, 집순이 여러분을 위한 여러가지 활동이 준비되어 있습니다.");
        Sleep(300);
        gotoxy(4, 7, "다양한 동물 키우기, 작물 키우기부터 diy, 게임까지!!!");
        Sleep(300);
        gotoxy(4, 9, "한 번 활동을 할 때마다 체력 1이 소진되고, 모든 체력이 소진되면 잠이 듭니다! ");
        Sleep(300);
        gotoxy(4, 11, "다음날이 되면 다시 체력이 충전되어 다시 활동을 할 수 있습니다.");
        Sleep(300);
        gotoxy(4, 13, "동물 호감도 max가 되면 다양한 event가 준비되어 있으니 매일매일 동물을 잘 돌봐주세요!");
        Sleep(300);
        gotoxy(4, 15, "게임이나 작물 키우기를 통해 모은 돈으로 동물을 위한 diy를 만들 수 있습니다!");
        Sleep(200);
        gotoxy(4, 17, "게임 중 모든 업적을 달성하면 게임이 완료됩니다!");
        Sleep(200);
        gotoxy(4, 19, "그럼 이제 게임을 시작합니다!");
        Sleep(100);
        gotoxy(4, 21, "아무키나 누르십시오...");
}