#include <stdio.h>
#include <stdlib.h>
#include <string.h> //支持字符串操作
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#define MAX 6      //常量MAX表示系统要求的最大妃子数量
/*
 * 需要特别列出的扩展知识点：
 * 1、播放声音的函数及链接器设置
 * 2、Sleep()函数
 * 3、字符串数组及简单的字符串函数，如比较、复制
 * 4、时间函数和exit函数
 */
#pragma comment(lib, "Winmm.lib")
#define DAY_COUNT 10
int main()
{
    PlaySound(TEXT("sounds\\背景音乐.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    int i,j,temp;           //循环变量以及临时整形变量
    int count = 5;          //当前未打入冷宫的嫔妃个数
    char tempName[20];      //用来存放临时姓名变量
    int index = -1;         //用来表示是否找到所选妃子
    int searchIndex = -1;   //用来存放查找元素的下标
    int choice;             //皇帝的选择1-4之间
    int sum = 0,add = 0;    //用来判断皇帝执政天数
    //使用字符数组表示字符串

    char emperorName[50];   //皇帝的名号
    char names[MAX][10] = {"貂蝉","杨玉环","西施","初音","夏目"};      //嫔妃的姓名
    char levelNames[5][10] = {"贵人","嫔妃","贵妃","皇贵妃","皇后"};   //嫔妃的级别

    //用来存放每位妃子的级别，每个数组元素对应每个妃子的当前级别
    int levels[MAX] = {0,0,0,0,0,-1};

    //loves中的每个元素对应每个妃子的好感度，初始情况每个人的好感度都是100
    int loves[MAX] = {100,100,100,100,100,-1};

    printf("\n*******************************************************************\n");
    printf("查看当前嫔妃的状态：\n");
    printf("%-12s级别\t好感度\n\n","姓名");
    for(i = 0;i < count; i++)
    {
        printf("%-12s%s\t%d\t\n\n",names[i],levelNames[levels[i]],loves[i]);
    }
    printf("\n*******************************************************************\n");


    //设置目录
    printf("请输入当前登基的皇帝名号：\n");
    scanf("%s",emperorName);//录入字符串时，不需要&符号
    printf("皇帝%s登基！！！",emperorName);
    printf("万岁万岁万万岁！！！\n");
    for(i = 0;i < DAY_COUNT;i++)
    {
        PlaySound(TEXT("sounds\\背景音乐.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        printf("1、皇帝下旨选妃：\t\t(增加功能)\n");
        printf("2、翻牌宠幸：\t\t\t(修改状态功能)\n");
        printf("3、打入冷宫！\t\t\t(删除功能)\n");
        printf("4、单独召见爱妃!\n");
        printf("陛下请选择：\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                    PlaySound(TEXT("sounds\\选妃.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                   //皇帝下旨选妃：\t\t(增加功能)
                   //1.增加前先判断数组有没有空间
                   //2.增加数组元素(names,loves,levels)
                if(count < MAX)//如果当前妃子数量小于系统最大量
                {
                    //执行添加操作
                    printf("请输入妃子的名讳：\n");
                    scanf("%s",names[count]);
                    //将第count个元素的状态初始化
                    levels[count] = 0;  //级别初始为0
                    loves[count] = 100; //好感度初始为100
                    count++; //添加完人数后记得增加计数器
                }
                else
                {
                    printf("后宫人满为患！\n添加失败！\n");
                }
                for(i = 0;i < count - 1;i++)
                {
                    loves[i] -= 10;
                }
                break;

            case 2: //翻牌宠幸：\t\t(修改状态功能)\n
                    //1.找到要宠幸妃子的下标
                    //2.修改妃子好的状态
                    //好感度+10，级别升级，如果最高级则不升级
                    //3.修改其他妃子状态   好感度-10，
                PlaySound(TEXT("sounds\\翻牌.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("陛下，请输入今天翻牌妃子的名讳：\n");
                scanf("%s",tempName);
                //字符串的查找strcmp,需要引入<string.h>头文件
                //trcmp(tempName,"abc") == 0  ---两个字符串相等
                //trcmp(tempName,"abc") == 1  ---前一个字符串大
                //trcmp(tempName,"abc") == -1 ---后一个字符串大
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)
                    {
                        loves[i] += 10;
                        //级别不能超过5级（0-4之间）
                        levels[i] = levels[i] >= 4 ? 4:levels[i] + 1;
                        index = i;
                        continue;
                    }
                        loves[i] -= 10;
                }
                if(index == -1) printf("查无此人！\n");
                break;
            case 3:
                //1.查找
                //2.后面一个赋值给前面一个元素
                //3.总数--
                //4.修改其他妃子状态，好感度统一上升
                PlaySound(TEXT("sounds\\冷宫.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("陛下，请输入要打入冷宫的妃子的姓名\n");
                scanf("%s",tempName);
                //循环查找
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)//比较字符串是否相等
                    {
                        //记录下要查找的下标，然后结束
                        searchIndex = i;
                        break;
                    }
                }
                if(searchIndex == -1)//表示没有找到
                {
                    printf("不好意思，开个玩笑\n");
                }
                else
                {
                    for(i = searchIndex;i < count - 1;i++)
                    {
                        //names[i] = names[i + 1];
                        //因为是字符串
                        //c中不支持数组的直接赋值
                        //需要使用strcpy函数实现数组赋值
                        //后续课程详细讲解
                        strcpy(names[i],names[i + 1]);
                        loves[i] = loves[i + 1];
                        levels[i] = levels[i + 1];
                    }
                    count--;
                }
                break;

            case 4:
                //1.查找
                //2.增加好感度即可
                //3.可以自行使用数组设计诗歌
                //使用随机数字的方式，表现皇帝文采
                PlaySound(TEXT("sounds\\召见.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("陛下，请选择要召见的妃子：\n");
                scanf("%s",tempName);
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)
                    {
                        loves[i] += 10;
                        //级别不能超过5级（0-4之间）
                        levels[i] = levels[i] >= 4 ? 4:levels[i] + 1;
                        index = i;
                        break;
                    }
                }
                if(index == -1)  printf("查无此人！\n");
                break;
        }
        //最后打印所有妃子状态前
        //以级别进行排序，使用冒泡排序
        for(i = 0;i < count - 1;i++)
        {
            for(j = 0;j < count - i - 1;j++)
            {
                if(levels[j] < levels[j + 1])
                {
                    //需要交换姓名、级别和好感度
                    temp = levels[j];
                    levels[j] = levels[j + 1];
                    levels[j + 1] = temp;
                    temp = loves[j];
                    loves[j] = loves[j + 1];
                    loves[j + 1] = temp;
                    //注意字符交换
                    strcpy(tempName,names[j]);
                    strcpy(names[j],names[j + 1]);
                    strcpy(names[j + 1],tempName);
                }
            }
        }
        printf("\n*******************************************************************\n");
        printf("查看当前嫔妃的状态：\n");
        printf("%-12s级别\t好感度\n\n","姓名");
        for(i = 0;i < count; i++)
        {
            printf("%-12s%s\t%d\t\n\n",names[i],levelNames[levels[i]],loves[i]);
        }
        printf("\n*******************************************************************\n\n");

        sum++;

        printf("这是陛下执政的第%d天,",sum);
        for(i = 0;i < count;i++)
        {
            if(loves[i] < 60)
            add++;
        }
        if(add > 2)  printf("朝廷已经造反，陛下%s被逼退位\n",emperorName);
        else if(add == 1||add == 2) printf("陛下夜夜笙歌，不思朝政，朝廷上下蠢蠢欲动\n还请陛下及时回归状态！\n");
        else printf("国泰民安，家和万事兴！\n");
    }
    return 0;
}
