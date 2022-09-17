#include<stdio.h>
#include <time.h>
#include<errno.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/stat.h>
#define LINE_SIZE 256

//0.登录电脑微信打开游戏进入第二关后退出
//1.打开电脑微信 - 左下角三条杠 - 设置 - 文件管理 - 打开文件夹
//2.进入wxid_你要改的微信ID 的文件夹 - Applet - wx一长串数字(进后面最近的日期文件夹) 
//- usr - gamecaches- resources
//3.按大小排序找到一个2kb的文件 - 粘贴输入文件名



/*********   引用自https://www.cnblogs.com/EmbeddedChicken/p/16086425.html
 * 函数名：Subit
 * 功能：将pathname文件中的字符串s1替换成s2
 * 参数：
 *      @s1:被替换字符串
 *      @s2:替换字符串
 *      @pathname:文件名中包含空格时，需要用双引号括起来
 *      例如：Subit("s1","s2","C:\\Users\\Administrator\\Documents\\WeChat Files\\wxid_你要改的微信ID\\Applet\\wx一长串数字\\usr\\gamecaches\\resources\\123.josn")
 * 返回值：
 *      无
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
    //获取当前月份和日期 
    int i=0,month,day,id=0;
    char PATH[1000]="D:\\111 333\\16633335324844.json";
    struct tm t;   //tm结构指针
	time_t now;  //声明time_t类型变量
	time(&now);      //获取系统日期和时间
	localtime_s(&t, &now);   //获取当地日期和时间
	//获取日期
    month = t.tm_mon + 1;
    day = t.tm_mday;
    //printf("今天是%d月%d日\n",month,day);
    id = month*10000+day;
    // id2 = id;
    // printf("%d",id2);

    char id_str[6];
    //把ID转换成字符串
    while(id)
    {
        id_str[i++] = id%10 + '0';
        id = id/10;
    }
    //逆向字符串
    for(int j=0;j<i/2;j++)
    {
        char temp = id_str[j];
        id_str[j] = id_str[i-j-1];
        id_str[i-j-1] = temp;
    }
    //打印字符串
    // printf("id_str = %s\n",id_str);



    //修改文件
    printf("========================================================================================\n");
    printf("id=%s %d位\n\n",id_str,i);
    printf("0.登录电脑微信打开游戏进入第二关后退出\n\n");
    printf("1.打开电脑微信 - 左下角三条杠 - 设置 - 文件管理 - 打开文件夹\n\n");
    printf("2.进入wxid_你要改的微信ID 的文件夹 - Applet - wx一长串数字(进后面最近的日期文件夹)\n\n");
    printf("- usr - gamecaches- resources\n\n");
    printf("3.按大小排序找到一个2kb的文件 - 将exe粘贴到目录中 - 以管理员身份运行\n\n");
    printf("4.输入文件名 例:16633335324844.json\n\n");
    printf("========================================================================================\n");
    printf("请输入文件名(ctrl+V 粘贴):\n");
    scanf("%s",PATH);
    printf("%s\n",PATH);

    //获取文件名
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
    printf("文件名:%s\n",q);


    //复制文件到C:\\ q
    char cmd[5000];

    sprintf(cmd,"copy %s C:\\%s",PATH,q);
    system(cmd);



    //在文件中遇到 id_str 则替换 80001
    Subtit(id_str,"80001",PATH);

    printf("修改成功请 重启微信或重启小程序\n\n");
    printf("重启进入游戏第二关后剩最后一个三连时按任意键\n\n");
    system("pause");


    //删除 PATH 文件
    sprintf(cmd,"del %s",PATH);
    system(cmd);
    //复制C:\\ q文件到 PATH
    sprintf(cmd,"copy C:\\%s %s",q,PATH);
    system(cmd);
    //删除C:\\ q文件
    sprintf(cmd,"del C:\\%s",q);
    system(cmd);


    printf("恢复成功\n");
    printf("继续完成游戏\n\n");
    system("pause");

    return 0;
}

