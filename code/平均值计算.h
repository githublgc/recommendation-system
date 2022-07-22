#include"数据预处理.h"

//求总体平均值
double allitemaverge()
{
	
	double sum = 0;
	int count = 0;//（u，i）对数

	for (int i = 0; i < usernum; i++)//遍历所有用户
	{
		for (int j = 0; j < itemnumtable[i]; j++)//遍历每个用户对商品打分
		{
			sum = sum + data0[i][j].rate;//将分值累加
			count++;//每产生一个打分记录就加1
		}
	}
	cout << "打分记录（u,i）对数有" << count << "条" << endl;
	double x = sum / count;
	return x;
}

//求用户x对所有产品打分的平均值
double useraverage(int UserID)
{
	double sum = 0;
	for (int i = 0; i < itemnumtable[UserID]; i++)//遍历自己所有的商品
	{
		sum = sum + data0[UserID][i].rate;//打分相加
	}
	double x = sum / itemnumtable[UserID];//平均 
	return x;
}

//求产品item的所有评分的平均值
double itemaverage(int itemID)
{
	double sum = 0;
	int count = 0;

	for (int i = 0; i < usernum; i++) //遍历所有用户
	{
			//在该用户对这个商品的打分处进行累加计算
			sum = sum + data0[i][itemID].rate;
			count++;
	}

	double x = sum / count;
	return x;
}

