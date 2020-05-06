#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    HWND window;    //定义一个窗口句柄变量，用来存储窗口句柄
    POINT mouse;    //定义一个结构体变量，用来存储鼠标位置
    RECT rectangle; //定义一个矩形变量，用来记录四个角的数据
    HANDLE hGame;   //定义一个句柄变量，用来存储进程句柄

    /*FindWindow("窗口类名","窗口标题名");*/
    window = FindWindow(NULL, "Plants vs. Zombies 1.2.0.1073 RELEASE");
    if (window == NULL)
    {
        /*信息弹窗*/
        // MessageBox(NULL, TEXT("未找到植物大战僵尸的窗口"), TEXT("提示！"), MB_OKCANCEL);
        printf("未找到植物大战僵尸窗口，请手动启动植物大战僵尸！\n");
        // char *cmd = "\\pvsz\\PlantsVsZombies.exe";
        // system(cmd);
        // char *cmd = "\\迅雷下载\\植物大战僵尸年度版\\PlantsVsZombies.exe";
        // WinExec(cmd, SW_SHOW);
    }
    else
    {
        // MessageBox(NULL, TEXT("已找到植物大战僵尸的窗口"), TEXT("提示！"), MB_OKCANCEL);
        ShowWindow(window, SW_RESTORE); //还原窗口,SW_HIDE(隐藏窗口)
        printf("已找到植物大战僵尸窗口！\n");
        while (true)
        {
            Sleep(150);
            GetCursorPos(&mouse);            //获取当前鼠标位置
            window = WindowFromPoint(mouse); //获取指定点窗口
            if (window == FindWindow(NULL, "Plants vs. Zombies 1.2.0.1073 RELEASE"))
            {
                //MessageBox(NULL, TEXT("鼠标移动到QQ窗口上了"), TEXT("提示！"), MB_OKCANCEL);
                printf("鼠标已移动到植物大战僵尸窗口！\n");
                break;
            }
        }
        int a = 0;
        GetWindowRect(window, &rectangle); //获取指定窗口句柄的矩形坐标，还有个GetClientRect用于获取窗口矩形坐标
        while (a < 10)
        {
            SetCursorPos(rectangle.right - 50, rectangle.top + 20); //设置鼠标坐标，其中x最大值不超过屏幕宽度（单位像素，下同），y值不超过屏幕高度
            Sleep(1);
            a++;
        }
        //mouse_event(MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
        DWORD qq_pid;                                       //进程ID
        DWORD qq_tid;                                       //线程ID
        qq_tid = GetWindowThreadProcessId(window, &qq_pid); //返回值为线程ID
        printf("<<<---------------当前进程信息---------------->>>\n\n\n");
        printf("植物大战僵尸的进程（Process）ID为：%d\n", qq_pid);
        printf("植物大战僵尸的线程（Thread）ID为：%d\n", qq_tid);
        hGame = ::OpenProcess(PROCESS_ALL_ACCESS, false, qq_pid); //获取进程句柄
        printf("植物大战僵尸的进程句柄为：%d\n", hGame);
        DWORD addr = 0x00428282;
        printf("\n\n<<<-------------------------------------------->>>\n\n");
        printf("正在开始修改... ...");
        DWORD sun = 1000;                      //修改之后的阳光值
        DWORD *addr_sun = (DWORD *)0x0077959c; //要修改的阳光基址
        DWORD p1;
        DWORD p2;
        ReadProcessMemory(hGame, (LPVOID)addr_sun, &p1, sizeof(DWORD), 0);
        p1 = p1 + 0x868;
        ReadProcessMemory(hGame, (LPVOID)p1, &p2, sizeof(DWORD), 0);
        p2 = p2 + 0x5578;
        printf("当前要修改的地址值为：%#X\n", p2);
        DWORD res = 0;
        res = WriteProcessMemory(hGame, (LPVOID)p2, &sun, 4, 0);
        if (res != 0)
        {
            printf("阳光默认修改为1000，阳光修改成功！！！\n");
        }
        else
        {
            printf("阳光修改失败！！！\n");
        }
        printf("请按回车键退出... ...");
        getchar();
        return 0;
    }

    // keybd_event(50, 0, 0, 0);
    // keybd_event(50, 0, KEYEVENTF_KEYUP, 0);
    /*SendWindow(指定窗口,指令,消息附带内容,消息附带内容);*/
    // SendMessage(window, WM_CLOSE, 0, 0);
    getchar();
    return 0;
}