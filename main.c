#include <stdio.h>
#include <stdlib.h>
#include <string.h> //֧���ַ�������
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#define MAX 6      //����MAX��ʾϵͳҪ��������������
/*
 * ��Ҫ�ر��г�����չ֪ʶ�㣺
 * 1�����������ĺ���������������
 * 2��Sleep()����
 * 3���ַ������鼰�򵥵��ַ�����������Ƚϡ�����
 * 4��ʱ�亯����exit����
 */
#pragma comment(lib, "Winmm.lib")
#define DAY_COUNT 10
int main()
{
    PlaySound(TEXT("sounds\\��������.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    int i,j,temp;           //ѭ�������Լ���ʱ���α���
    int count = 5;          //��ǰδ�����乬����������
    char tempName[20];      //���������ʱ��������
    int index = -1;         //������ʾ�Ƿ��ҵ���ѡ����
    int searchIndex = -1;   //������Ų���Ԫ�ص��±�
    int choice;             //�ʵ۵�ѡ��1-4֮��
    int sum = 0,add = 0;    //�����жϻʵ�ִ������
    //ʹ���ַ������ʾ�ַ���

    char emperorName[50];   //�ʵ۵�����
    char names[MAX][10] = {"����","����","��ʩ","����","��Ŀ"};      //����������
    char levelNames[5][10] = {"����","����","����","�ʹ���","�ʺ�"};   //�����ļ���

    //�������ÿλ���ӵļ���ÿ������Ԫ�ض�Ӧÿ�����ӵĵ�ǰ����
    int levels[MAX] = {0,0,0,0,0,-1};

    //loves�е�ÿ��Ԫ�ض�Ӧÿ�����ӵĺøжȣ���ʼ���ÿ���˵ĺøжȶ���100
    int loves[MAX] = {100,100,100,100,100,-1};

    printf("\n*******************************************************************\n");
    printf("�鿴��ǰ������״̬��\n");
    printf("%-12s����\t�øж�\n\n","����");
    for(i = 0;i < count; i++)
    {
        printf("%-12s%s\t%d\t\n\n",names[i],levelNames[levels[i]],loves[i]);
    }
    printf("\n*******************************************************************\n");


    //����Ŀ¼
    printf("�����뵱ǰ�ǻ��Ļʵ����ţ�\n");
    scanf("%s",emperorName);//¼���ַ���ʱ������Ҫ&����
    printf("�ʵ�%s�ǻ�������",emperorName);
    printf("�������������꣡����\n");
    for(i = 0;i < DAY_COUNT;i++)
    {
        PlaySound(TEXT("sounds\\��������.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        printf("1���ʵ���ּѡ����\t\t(���ӹ���)\n");
        printf("2�����Ƴ��ң�\t\t\t(�޸�״̬����)\n");
        printf("3�������乬��\t\t\t(ɾ������)\n");
        printf("4�������ټ�����!\n");
        printf("������ѡ��\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                    PlaySound(TEXT("sounds\\ѡ��.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                   //�ʵ���ּѡ����\t\t(���ӹ���)
                   //1.����ǰ���ж�������û�пռ�
                   //2.��������Ԫ��(names,loves,levels)
                if(count < MAX)//�����ǰ��������С��ϵͳ�����
                {
                    //ִ����Ӳ���
                    printf("���������ӵ����䣺\n");
                    scanf("%s",names[count]);
                    //����count��Ԫ�ص�״̬��ʼ��
                    levels[count] = 0;  //�����ʼΪ0
                    loves[count] = 100; //�øжȳ�ʼΪ100
                    count++; //�����������ǵ����Ӽ�����
                }
                else
                {
                    printf("������Ϊ����\n���ʧ�ܣ�\n");
                }
                for(i = 0;i < count - 1;i++)
                {
                    loves[i] -= 10;
                }
                break;

            case 2: //���Ƴ��ң�\t\t(�޸�״̬����)\n
                    //1.�ҵ�Ҫ�������ӵ��±�
                    //2.�޸����Ӻõ�״̬
                    //�øж�+10�����������������߼�������
                    //3.�޸���������״̬   �øж�-10��
                PlaySound(TEXT("sounds\\����.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("���£���������췭�����ӵ����䣺\n");
                scanf("%s",tempName);
                //�ַ����Ĳ���strcmp,��Ҫ����<string.h>ͷ�ļ�
                //trcmp(tempName,"abc") == 0  ---�����ַ������
                //trcmp(tempName,"abc") == 1  ---ǰһ���ַ�����
                //trcmp(tempName,"abc") == -1 ---��һ���ַ�����
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)
                    {
                        loves[i] += 10;
                        //�����ܳ���5����0-4֮�䣩
                        levels[i] = levels[i] >= 4 ? 4:levels[i] + 1;
                        index = i;
                        continue;
                    }
                        loves[i] -= 10;
                }
                if(index == -1) printf("���޴��ˣ�\n");
                break;
            case 3:
                //1.����
                //2.����һ����ֵ��ǰ��һ��Ԫ��
                //3.����--
                //4.�޸���������״̬���øж�ͳһ����
                PlaySound(TEXT("sounds\\�乬.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("���£�������Ҫ�����乬�����ӵ�����\n");
                scanf("%s",tempName);
                //ѭ������
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)//�Ƚ��ַ����Ƿ����
                    {
                        //��¼��Ҫ���ҵ��±꣬Ȼ�����
                        searchIndex = i;
                        break;
                    }
                }
                if(searchIndex == -1)//��ʾû���ҵ�
                {
                    printf("������˼��������Ц\n");
                }
                else
                {
                    for(i = searchIndex;i < count - 1;i++)
                    {
                        //names[i] = names[i + 1];
                        //��Ϊ���ַ���
                        //c�в�֧�������ֱ�Ӹ�ֵ
                        //��Ҫʹ��strcpy����ʵ�����鸳ֵ
                        //�����γ���ϸ����
                        strcpy(names[i],names[i + 1]);
                        loves[i] = loves[i + 1];
                        levels[i] = levels[i + 1];
                    }
                    count--;
                }
                break;

            case 4:
                //1.����
                //2.���Ӻøжȼ���
                //3.��������ʹ���������ʫ��
                //ʹ��������ֵķ�ʽ�����ֻʵ��Ĳ�
                PlaySound(TEXT("sounds\\�ټ�.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                printf("���£���ѡ��Ҫ�ټ������ӣ�\n");
                scanf("%s",tempName);
                for(i = 0;i < count;i++)
                {
                    if(strcmp(tempName,names[i]) == 0)
                    {
                        loves[i] += 10;
                        //�����ܳ���5����0-4֮�䣩
                        levels[i] = levels[i] >= 4 ? 4:levels[i] + 1;
                        index = i;
                        break;
                    }
                }
                if(index == -1)  printf("���޴��ˣ�\n");
                break;
        }
        //����ӡ��������״̬ǰ
        //�Լ����������ʹ��ð������
        for(i = 0;i < count - 1;i++)
        {
            for(j = 0;j < count - i - 1;j++)
            {
                if(levels[j] < levels[j + 1])
                {
                    //��Ҫ��������������ͺøж�
                    temp = levels[j];
                    levels[j] = levels[j + 1];
                    levels[j + 1] = temp;
                    temp = loves[j];
                    loves[j] = loves[j + 1];
                    loves[j + 1] = temp;
                    //ע���ַ�����
                    strcpy(tempName,names[j]);
                    strcpy(names[j],names[j + 1]);
                    strcpy(names[j + 1],tempName);
                }
            }
        }
        printf("\n*******************************************************************\n");
        printf("�鿴��ǰ������״̬��\n");
        printf("%-12s����\t�øж�\n\n","����");
        for(i = 0;i < count; i++)
        {
            printf("%-12s%s\t%d\t\n\n",names[i],levelNames[levels[i]],loves[i]);
        }
        printf("\n*******************************************************************\n\n");

        sum++;

        printf("���Ǳ���ִ���ĵ�%d��,",sum);
        for(i = 0;i < count;i++)
        {
            if(loves[i] < 60)
            add++;
        }
        if(add > 2)  printf("��͢�Ѿ��췴������%s������λ\n",emperorName);
        else if(add == 1||add == 2) printf("����ҹҹ�ϸ裬��˼��������͢���´�������\n������¼�ʱ�ع�״̬��\n");
        else printf("��̩�񰲣��Һ������ˣ�\n");
    }
    return 0;
}
