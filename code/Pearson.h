#include"平均值计算.h"
//最后产品得分中的bxi的值





//将原始的打分数据转换为pearson相关系数的数据
void Pearson()
{
	for (int i = 0; i < usernum; i++)
	{
		pearson[i] = new itemrate[itemnumtable[i]];

		for (int j = 0; j < itemnumtable[i]; j++)
		{
			pearson[i][j].itemID = data0[i][j].itemID;//原数据的用户号即为pearson的用户 

			pearson[i][j].rate = data0[i][j].rate;//Pearson的相关系数作为新的值
		}
	}
}



//两个商品间的Pearson相似度
double rateitemsimilar(int item1, int item2)
{
	//求rx*ry累加和后的分子

	double rateitem0[10000];//保存商品的打分
	int count00 = 0;//保存是第几个商品 

	
	
		for (int i = 0; i < itemnumtable[item1]; i++) //遍历商品A的所有打分情况
		{
			int j = insertfind(pearson, item1,item2, itemnumtable[item2], pearson[item1][i].itemID);
			if (j != -1)//在商品A中的打分，找商品B中是否也有打分 
			{
				rateitem0[count00] = (pearson[item1][i].rate- //将那些有对应打分的进行计算
				itemaverage(i))* (pearson[item2][j].rate - itemaverage(i));//(rx-avg)*(ry-avg)
				count00++;
			}
		}
	


		//rx*ry的各项累加和做分子
	double PeaNumerator = 0;
	for (int i = 0; i < count00; i++)
		PeaNumerator = PeaNumerator + rateitem0[i];


	//rx-avg累加平方开根 乘 根号下ry-avg累加平方 开根号做分母

	
	double countitemA; double countitemB;

	for (int i = 0; i < itemnumtable[item1]; i++)
		countitemA = countitemA + (pearson[item1][i].rate-itemaverage(i)) *
		( pearson[item1][i].rate - itemaverage(i));


	for (int i = 0; i < itemnumtable[item2]; i++)
		countitemB = countitemB + (pearson[item2][i].rate - itemaverage(i)) *
		(pearson[item2][i].rate - itemaverage(i));

	//求最终的pearson系数
	double pearson = PeaNumerator / (sqrt(countitemA) * sqrt(countitemB));

	return pearson;
}

double max1(double r,int  itemID,double average,int itemID1)//取所有相似的商品中相似度最大的两个

{
	double maxsimilar = 0;
	double x11 = 0;
	double x22 = 0;
	for (int i = 0; i < 19835; i++)//遍历所有用户
	{
		int j = insertfind(data0, itemID, i, itemnumtable[i], itemID1);//找一下哪些用户买过这两个商品

		if (j != -1)//如果该两个商品被同一个用户购买过
		{
			double a = rateitemsimilar(itemID, i);//计算两者的相似度
			if (a > 0) //如果相似度大于0，说明是有相似关系的
			{
				x11 += a;
				x22 += a * (data0[i][j].rate - bxi(i, data0[i][j].itemID, average));
			}
			if (maxsimilar < a)
				maxsimilar = a;
		}
	}
	return maxsimilar;
}

void rateitemadd(itemrate** a1, int  item1, int item2, double pearson,int user)
//如果没有足够多和商品i相似的，就采用属性相似产品评分进行替代

{
	ifstream attribute;
	attribute.open("itemAttribute.txt");//读取商品属性

	for (int i = 0; i < a1[item1][sizeof(a1[item1]) / sizeof(item1)].itemID; i++)

	{
		string s;
		int itemID00=0;
		int attribute1, attribute2;
		double rate=max1(rateitemsimilar(item1, item2),item1,item2,pearson);
			if (rate < 0.2)//如果连与之相似的商品最大的相似度都不到0.2，
			//说明只通过用户的打分情况，不能找到很合适的相似商品，需要借助商品属性来确定相似的。
			{
				while (getline(attribute, s)) //逐行进行读取
				{
					int flag = s.find("|"); //查找该行中第一次出现"|"所在位置

					string itemstr = s.substr(0, flag);//商品号为|前的数字

					itemID00 = stoi(itemstr);

					string attributestr = s.substr(flag + 1, s.length() - 1);//后面的属性字符串，中间|隔开

					int flag1 = attributestr.find("|");//第二个|分割两个商品类似的属性
					string attribute1str = attributestr.substr(flag + 1, flag1 - 1);
					attribute1 = stoi(attribute1str);
					string attribute2str = attributestr.substr(flag1 + 1, s.length() - 1);
					attribute2 = stoi(attribute2str);//将属性号转换为整数
					
					a1[user][item1].rate = (a1[user][attribute1].rate+a1[user][attribute2].rate) / 2;

				}
			}
	}
	attribute.close();

}

