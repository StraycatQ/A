#include<stdio.h>
#include <time.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#define LINE_SIZE 256

//0.��¼����΢�Ŵ���Ϸ����ڶ��غ��˳�
//1.�򿪵���΢�� - ���½������� - ���� - �ļ����� - ���ļ���
//2.����wxid_��Ҫ�ĵ�΢��ID ���ļ��� - Applet - wxһ��������(����������������ļ���) 
//- usr - gamecaches- resources
//3.����С�����ҵ�һ��2kb���ļ� - ճ�������ļ���



/*********   ������https://www.cnblogs.com/EmbeddedChicken/p/16086425.html
 * ��������Subit
 * ���ܣ���pathname�ļ��е��ַ���s1�滻��s2
 * ������
 *      @s1:���滻�ַ���
 *      @s2:�滻�ַ���
 *      @pathname:�ļ����а����ո�ʱ����Ҫ��˫����������
 *      ���磺Subit("s1","s2","C:\\Users\\Administrator\\Documents\\WeChat Files\\wxid_��Ҫ�ĵ�΢��ID\\Applet\\wxһ��������\\usr\\gamecaches\\resources\\123.josn")
 * ����ֵ��
 *      ��
 * *******/
void Subtit(const char*s1,const char *s2,const char *pathname)
{

    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);
    FILE *fileline=fopen(pathname,"r+");

    if(fileline==NULL)
    {
        perror("Fopen error!");
        exit(0);
    }
    struct stat filestate;
    stat(pathname,&filestate);
    char *filebuffer=(char *)malloc(sizeof(char)*(filestate.st_size+1));
    for (int i = 0,ch=0;ch!=EOF;i++)
    {
        ch = fgetc(fileline);
        filebuffer[i]=ch;
    }  
    fseek(fileline,0,SEEK_SET);    
    for (char *index_1 = filebuffer,*index_2 = filebuffer;;)
    {
        index_2 = strstr(index_1,s1);
        if(index_2)
        {
            for(int i=0;i<index_2-index_1;i++)
            {
                fputc(index_1[i],fileline);
            }
            for(int i=0;i<len_s2;i++)
            {
                fputc(s2[i],fileline);
            }
            index_1=index_2+len_s1;
        }
        else
        {
            while(*index_1!=EOF)
            {
                fputc(*index_1++,fileline);
            }
            break;
        }
    }
    free(filebuffer);
    fclose(fileline);
}

int main()
{   
    //��ȡ��ǰ�·ݺ����� 
    int i=0,month,day,id=0;
    char PATH[1000]="D:\\111 333\\16633335324844.json";
    struct tm t;   //tm�ṹָ��
	time_t now;  //����time_t���ͱ���
	time(&now);      //��ȡϵͳ���ں�ʱ��
	localtime_s(&t, &now);   //��ȡ�������ں�ʱ��
	//��ȡ����
    month = t.tm_mon + 1;
    day = t.tm_mday;
    //printf("������%d��%d��\n",month,day);
    id = month*10000+day;
    // id2 = id;
    // printf("%d",id2);

    char id_str[6];
    //��IDת�����ַ���
    while(id)
    {
        id_str[i++] = id%10 + '0';
        id = id/10;
    }
    //�����ַ���
    for(int j=0;j<i/2;j++)
    {
        char temp = id_str[j];
        id_str[j] = id_str[i-j-1];
        id_str[i-j-1] = temp;
    }
    //��ӡ�ַ���
    // printf("id_str = %s\n",id_str);



    //�޸��ļ�
    printf("========================================================================================\n");
    printf("id=%s %dλ\n\n",id_str,i);
    printf("0.��¼����΢�Ŵ���Ϸ����ڶ��غ��˳�\n\n");
    printf("1.�򿪵���΢�� - ���½������� - ���� - �ļ����� - ���ļ���\n\n");
    printf("2.����wxid_��Ҫ�ĵ�΢��ID ���ļ��� - Applet - wxһ��������(����������������ļ���)\n\n");
    printf("- usr - gamecaches- resources\n\n");
    printf("3.����С�����ҵ�һ��2kb���ļ� - ��exeճ����Ŀ¼�� - �Թ���Ա�������\n\n");
    printf("4.�����ļ��� ��:16633335324844.json\n\n");
    printf("========================================================================================\n");
    printf("�������ļ���(ctrl+V ճ��):\n");
    scanf("%s",PATH);
    printf("%s\n",PATH);

    //��ȡ�ļ���
    char *p = PATH;
    char *q = PATH;
    while(*p!='\0')
    {
        if(*p=='\\')
        {
            q = p;
        }
        p++;
    }
    //q++;
    printf("�ļ���:%s\n",q);


    //�����ļ���C:\\ q
    char cmd[5000];

    sprintf(cmd,"copy %s C:\\%s",PATH,q);
    system(cmd);



    //���ļ������� id_str ���滻 80001
    Subtit(id_str,"80001",PATH);

    printf("�޸ĳɹ��� ����΢�Ż�����С����\n\n");
    printf("����������Ϸ�ڶ��غ�ʣ���һ������ʱ�������\n\n");
    system("pause");


    //ɾ�� PATH �ļ�
    sprintf(cmd,"del %s",PATH);
    system(cmd);
    //����C:\\ q�ļ��� PATH
    sprintf(cmd,"copy C:\\%s %s",q,PATH);
    system(cmd);
    //ɾ��C:\\ q�ļ�
    sprintf(cmd,"del C:\\%s",q);
    system(cmd);


    printf("�ָ��ɹ�\n");
    printf("���������Ϸ\n\n");
    system("pause");

    return 0;
}

