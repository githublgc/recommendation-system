#include <iostream>
#include <fstream>//进行文件读写
#include <string>
#include <vector>
#include <algorithm>
#include<list>


using namespace std;
int usernum = 19835;
int itemnum = 624961;
int maxitem = 0;//求商品个数
int maxuser = 0;//用户总数


int itemnumtable[19835];//存放一个商品被哪些用户看过，至多19835个

int predicttable[19835][6];//预测19835个用户每人6个商品的保存表

struct itemrate //（i，r）商品得分
{
	int itemID;//哪个商品
	double rate;//打分
};



itemrate** data0 = new itemrate * [usernum];//读取用户历史打分数据

itemrate** pearson = new itemrate * [itemnum];//保存不同商品间的相关系数pearson

//分块保存
void blockSaving()
{
	int count = usernum/1000;//每1000个用户分成一组
	ofstream* out = new ofstream[count];
	char buf[50000];//按50000字符容量缓冲区准备
	for (int i = 0; i < count; i++)
	{
		sprintf_s(buf, "train%d.txt", i);
		out[i].open(buf);
	}
	ifstream in("train.txt");
	int itemID, rate0;
	int current = -1;//头节点，放在第一个节点之前，记为-1
	int count6 = 0;//记录当前记录了多少条，判断是否要换到下一个块记录数据
	list<int> LinkList;
	while (!in.eof())
	{
		int flag = s.find("|");//每个新用户记录都有自己的userid和“|”
		if (flag != -1)//有竖线的是新的用户
		{
			continue;//直接进行下一步，读取下面若干行用户的打分信息
		}
		in >> itemID >> rate0;//输入为产品号和初始的打分
		if (current != itemID)
		{
			int t;
			while (!LinkList.empty())
			{
				t = LinkList.front();
				out[current / blocksize] << current << " " << counttoNode[current - 1] << " " << t << endl;
				LinkList.pop_front();
			}
			current = itemID;
			count6 = 0;
		}

		count6++;
		LinkList.push_back(rate0);//数据写入链表尾部
	}
	cout << "完成分块" << endl;
	cout << endl;

}

//构建稀疏矩阵
class sparsenode
{
	int row, col;
	int rate;
};
class sparsematrix
{
	sparsenode ratadata[5001507];//数组大小为含有打分的总记录数，5001507
	int countrate, userID, itemID;//分别记录每个用户ID对商品ID的打分countrate
public:
	void b1ocksaving() {}//分块
	void spasematr1x() {}//转化稀疏矩阵 
	sparsematrix(int** a, int b, int c)
	{
		itemID = 0;
		countrate = b;
		userID = c;
		int i, j;
		for (i = 0; i < b; i++)
		{
			for (j = 0; j < c; j++)
			{
				if (a[i][j] != 0)
				{
					ratadata[itemID].value = a[i][j];
					ratadata[itemID].row = i;
					ratadata[itemID].col = j;
					itemID++;
				}
			}
		}
	}

//由于商品的序号是无序的，并且分布比较均匀，采用插值查找确定用户是否购买该商品
int insertfind(itemrate** ratetable, int userid0, int left, int right, int key) {

	if (left > right || key < ratetable[userid0][0].itemID || key > ratetable[userid0][sizeof(ratetable[userid0]) / sizeof(int) - 1].itemID) {
		return -1;
	}
	int mid = left + (right - left) * (key - ratetable[userid0][left].itemID) / (ratetable[right] - ratetable[left]);
	int midvalue = ratetable[userid0][mid].itemID;
	if (key > midvalue) {
		return insertfind(ratetable, userid0, mid + 1, right, key);
	}
	else
		if (key < midvalue) {
			return insertfind(ratetable, userid0, 0, mid - 1, key);
		}

		else {
			return mid;
		}
}

void b1ocksaving() {}
void spasematr1x() {}
	
