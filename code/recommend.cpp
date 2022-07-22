#include"Pearson.h"

double bxi(int userID, int itemID, double average)
{
	double bx = useraverage(userID) - average;
	double bi = itemaverage(itemID) - average;
	double bxi = average + bx + bi;
	return bxi;
}


//最后产品得分中的加权平均r的值
double rxi(int userID, int itemID, double average)
{
	
	double additem12 = 0;
	double additem123 = 0;
	int itemID2=pearson[userID][itemID].itemID;

	for (int i = 0; i < itemnum; i++)//遍历所有产品 
	{
		int j = insertfind(data0, userID,i, itemnumtable[i], itemID);//查找另一个相似产品是否也被该用户打分

		if (j != -1)//如果该用户也给这个产品打分
		{
			double a = rateitemsimilar(userID, i);//求两个产品相似度
			if (a > 0)
			{
				if (a > 0.2) //如果两产品相似，且相关程度pearson系数大于0.2时
				{
					additem12 += a;
					additem123 += a * (data0[i][j].rate - bxi(i, data0[i][j].itemID, average));
					//直接使用相似度计算来加权平均
				}

				else//否则，引入商品属性来完成推荐

				{
					rateitemadd(data0, itemID, itemID2, average,userID);
				}

			}
		}
	}

}

//预测评分
double ratepredict(int UserID, int ItemID, double average)
{
	//利用相似产品得分情况，预测当前商品会被该用户打多少分。
	double rate =rxi(UserID, ItemID, average) + bxi(UserID, ItemID, average);
	if (rate < 0)//预测得分小于零，就认为没看过，不打分，置为0
		rate = 0;
	return rate;
}



int main()
{
	

	cout << "读取训练集数据" << endl;
	//打开train.txt
	ifstream readtrainfile;
	readtrainfile.open("train.txt");
	string s; //存放读取行数据
	int userID = 0; //user序号从0开始
	int useritem = 0; //当前用户对多少个商品进行打分的个数
	int count = 0;//标记用户x对第几个商品的打分

	while (getline(readtrainfile, s))//逐行读取数据
	{
		int flag1 = s.find("|"); //看当前行中有没有“|”
		if (s == "")
			break;

		if (flag1 != -1) //有"|"，说明进入到下一个用户的评分区域
		{
			count = 0;//新用户，置为0
			//根据find找到|后，后面的数字就是当前用户的看电影数量
			string userxitemstr = s.substr(flag1 + 1, s.length() - flag1);//从|后一个位置一直读到结束
			useritem = stoi(userxitemstr); //用户x的打分数目

			itemnumtable[userID] = useritem;

			//动态初始化data数组中该UserID行
			data0[userID] = new itemrate[useritem];
			maxuser = userID;
			userID++;
		}

		else //没有"|"，且还没有读完所有数据，中间还有两个空格隔开
			//说明正在某个用户评分表中读取打分情况
		{
			int flag2 = s.find(" "); //看当前行是不是有两个空格
			string itemstr = s.substr(0, flag2);//商品号为空格前的数字
			string ratestr = s.substr(flag2 + 2, s.length() - flag2);//字符串表示的打分

			double rate = stof(ratestr);//字符串打分转换为浮点数，便于计算含小数的平均分等
			int itemID = stoi(itemstr);//字符串转换为整数
			if (maxitem < itemID)
				maxitem = itemID;
			struct itemrate ratetable0 = { itemID,rate };//初始记录

			//将该行数据存入效用矩阵对应位置			
			data0[userID][count] = ratetable0;
			count++;
		}

	}
	readtrainfile.close();

	

	maxuser++; maxitem++;
	cout << "用户总数为" << maxuser << endl;
	cout << "物品的数量为" << maxitem << endl;
	cout << "训练集读取完成" << endl;
	cout << "用户总数为：19835" << endl;

	cout << "计算总体平均值" << endl;
	double averageALL = allitemaverge();
	cout << "总体平均值为" << averageALL << endl;

	//读取测试集test.txt
	ifstream infile;
	infile.open("test.txt");
	string s; //存放读取行数据

	int count1 = 0;
	int count2 = 0;
	while (getline(infile, s))
	{
		int flag = s.find("|"); //查找该行中"|"所在位置
		if (s == "")
			break;
		if (flag != -1)
		{
			//有竖线，说明 是新的一组数据
			count2 = 0;
			count1++;
		}
		else
		{
			//没有，说明在某一组内，对本行数据对应的商品进行预测打分 
			predicttable[count1][count2] = stoi(s);
			count2++;
		}
	}
	infile.close();
	b1ocksaving();//分块
	spasematr1x();//转化稀疏矩阵
	

	cout << "计算pearson相关系数" << endl;
	cout << "根据物品相似度进行协同过滤" << endl;
	Pearson();
	cout << "进行预测评分" << endl;

	//把读入的数据进行测试，并写入结果文档（text.txt）
	fstream outresult;
	outresult.open("result.txt");
	for (int i = 0; i < 19835; i++)//9190,19835
	{
		for (int j = 0; j < 6; j++)
		{
			if (!j)
			{
				outresult << i << "|" << "6" << endl;
				outresult << predicttable[i][j] << "  " << int(ratepredict(i, predicttable[i][j], averageALL)) << endl;
			}
			else
				outresult << predicttable[i][j] << "  " << int(ratepredict(i, predicttable[i][j], averageALL)) << endl;
		}
	}
	outresult.close();
	cout << "所有预测完成" << endl;
	return 0;
}











