#include <iostream>
#include <fstream>//�����ļ���д
#include <string>
#include <vector>
#include <algorithm>
#include<list>


using namespace std;
int usernum = 19835;
int itemnum = 624961;
int maxitem = 0;//����Ʒ����
int maxuser = 0;//�û�����


int itemnumtable[19835];//���һ����Ʒ����Щ�û�����������19835��

int predicttable[19835][6];//Ԥ��19835���û�ÿ��6����Ʒ�ı����

struct itemrate //��i��r����Ʒ�÷�
{
	int itemID;//�ĸ���Ʒ
	double rate;//���
};



itemrate** data0 = new itemrate * [usernum];//��ȡ�û���ʷ�������

itemrate** pearson = new itemrate * [itemnum];//���治ͬ��Ʒ������ϵ��pearson

//�ֿ鱣��
void blockSaving()
{
	int count = usernum/1000;//ÿ1000���û��ֳ�һ��
	ofstream* out = new ofstream[count];
	char buf[50000];//��50000�ַ�����������׼��
	for (int i = 0; i < count; i++)
	{
		sprintf_s(buf, "train%d.txt", i);
		out[i].open(buf);
	}
	ifstream in("train.txt");
	int itemID, rate0;
	int current = -1;//ͷ�ڵ㣬���ڵ�һ���ڵ�֮ǰ����Ϊ-1
	int count6 = 0;//��¼��ǰ��¼�˶��������ж��Ƿ�Ҫ������һ�����¼����
	list<int> LinkList;
	while (!in.eof())
	{
		int flag = s.find("|");//ÿ�����û���¼�����Լ���userid�͡�|��
		if (flag != -1)//�����ߵ����µ��û�
		{
			continue;//ֱ�ӽ�����һ������ȡ�����������û��Ĵ����Ϣ
		}
		in >> itemID >> rate0;//����Ϊ��Ʒ�źͳ�ʼ�Ĵ��
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
		LinkList.push_back(rate0);//����д������β��
	}
	cout << "��ɷֿ�" << endl;
	cout << endl;

}

//����ϡ�����
class sparsenode
{
	int row, col;
	int rate;
};
class sparsematrix
{
	sparsenode ratadata[5001507];//�����СΪ���д�ֵ��ܼ�¼����5001507
	int countrate, userID, itemID;//�ֱ��¼ÿ���û�ID����ƷID�Ĵ��countrate
public:
	void b1ocksaving() {}//�ֿ�
	void spasematr1x() {}//ת��ϡ����� 
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

//������Ʒ�����������ģ����ҷֲ��ȽϾ��ȣ����ò�ֵ����ȷ���û��Ƿ������Ʒ
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
	
