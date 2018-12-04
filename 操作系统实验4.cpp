// 操作系统实验4.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//缓存调度算法，用于页面调度

#include "pch.h"
#include <iostream>
using namespace std;
constexpr auto PAGE = 12;
typedef struct page
{
	int num;
	int mark=13;
};
page frame[3];



int page0[PAGE] = { 4,3,2,1,4,3,5,4,3,2,1,5 };

class mainPage
{
public:
	
	void initalize();  //初始化
	void FIFO();       //先进先出页面置换算法
	void OPT();        //理想页面置换算法
	void LRU();        //最近最少使用页面置换算法
};

void mainPage::initalize()
{
	for (int i = 0; i < PAGE; i++)
	{
		cout << page0[i] << ' ';
	}
	cout << "\n";
}

void mainPage::FIFO()  //先进先出页面置换算法
{
	cout << endl;
	int error = 0;
	page frame[3];
	for (int i = 0; i < 3; i++)  //处理前三个
	{
		frame[i].num = page0[i];
		error++;
		cout << frame[i].num << " | ";
		for (int j = 0; j <=i; j++)
		
			cout << frame[j].num << ' ';
		cout << endl;
	}
	for (int i = 3; i < 12; i++)
	{
		int j;
		for(j=0;j<3;j++)
			if (page0[i] == frame[j].num)
			{
				cout << page0[i]<<endl;
				break;
			}
		if (j == 3)
		{
			error++;
			frame[((error - 1) % 3)].num = page0[i]; //换掉最旧的页
			cout << page0[i] << " | ";
			for (int k = 0; k < 3; k++)
				cout << frame[k].num << ' ';
			cout << endl;
			


		}
	}
	cout << "中断次数：" << error<<endl<<endl;

}

void mainPage::OPT()
{
	cout << endl;
	int error = 0;
	
	for (int i = 0; i < 3; i++)//处理前三个
	{
		frame[i].num = page0[i];
		error++;
		cout << frame[i].num << " | ";
		for (int j = 0; j <= i; j++)
			cout << frame[j].num << ' ';
		cout << endl;
	}
	for (int i = 3; i < 12; i++)
	{
		int j;
		for (j = 0; j < 3; j++)
			if (page0[i] == frame[j].num)
			{
				cout <<page0[i] << endl;
				break;
			}
		if (j == 3)
		{
			error++;
			for (j = 0; j < 3; j++)
			{
				frame[j].mark = 12;
				for (int k = 12; k >= i; k--)//向后遍历，找到最长时间不用的页
				{
					if (frame[j].num == page0[k])
						frame[j].mark = k;
				}
			}
			if (frame[0].mark > frame[1].mark&&frame[0].mark > frame[2].mark)
				frame[0].num = page0[i];
			else if (frame[1].mark > frame[0].mark&&frame[1].mark > frame[2].mark)
				frame[1].num = page0[i];
			else
				frame[2].num = page0[i];
			cout << page0[i] << " | ";
			for (int k = 0; k < 3; k++)
				cout << frame[k].num << ' ';
			cout << endl;
		}
	}
	cout << "中断次数：" << error << endl << endl;
}

void mainPage::LRU()
{
	int error = 0;
	
	for (int i = 0; i < 3; i++)//处理前三个
	{
		frame[i].num = page0[i];
		error++;
		cout << frame[i].num << " | ";
		for (int j = 0; j <= i; j++)
			cout << frame[j].num << ' ';
		cout << endl;
	}
	for (int i = 3; i <12; i++)
	{
		int j;
		for (j = 0; j < 3; j++)
			if (page0[i] == frame[j].num)
			{
				cout << page0[i] << endl;
				break;
			}
		if (j == 3)
		{
			error++;
			for (j = 0; j < 3; j++)
			{
				frame[j].mark = 0;
				for (int k = 0; k <= i; k++)//向前遍历，找到最近最少使用的
				{
					if (frame[j].num == page0[k])
						frame[j].mark = k;
				}
			}
			if (frame[0].mark < frame[1].mark&&frame[0].mark < frame[2].mark)
				frame[0].num = page0[i];
			else if (frame[1].mark < frame[0].mark&&frame[1].mark < frame[2].mark)
				frame[1].num = page0[i];
			else
				frame[2].num = page0[i];
			cout << page0[i] << " | ";
			for (int k = 0; k < 3; k++)
				cout << frame[k].num << ' ';
			cout << endl;
		}
	}
	cout << "中断次数：" << error << endl << endl;
}


int main() 
{
	mainPage textpage;
	
	cout << "============================操作系统第四次实验=========================\n";
	cout << "陈子恒2016210889\n";
	cout << "0退出本次实验\n";
	cout << "1先进先出页面置换算法（FIFO）\n";
	cout << "2理想页面置换算法（OPT）\n";
	cout << "3最近最少使用页面置换算法（LRU）\n";
	textpage.initalize();
	int choice;
	cout << "请输入你的选择（数字）\n";
	cin >> choice;

	while (choice!=0)
	{
		switch (choice)
		{
		case 1:
			cout << "您选择的是先进先出页面置换算法\n";
			textpage.FIFO();
			break;
		case 2:
			cout << "您选择的理想页面置换算法\n";
			textpage.OPT();
			break;
		case 3:
			cout << "您选择的是最近最少使用页面置算法\n";
			textpage.LRU();
			break;
		
		}
		cin >> choice;
		cout << "\n";
	}

	cout << "您已推出本次实验";


}

