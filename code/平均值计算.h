#include"����Ԥ����.h"

//������ƽ��ֵ
double allitemaverge()
{
	
	double sum = 0;
	int count = 0;//��u��i������

	for (int i = 0; i < usernum; i++)//���������û�
	{
		for (int j = 0; j < itemnumtable[i]; j++)//����ÿ���û�����Ʒ���
		{
			sum = sum + data0[i][j].rate;//����ֵ�ۼ�
			count++;//ÿ����һ����ּ�¼�ͼ�1
		}
	}
	cout << "��ּ�¼��u,i��������" << count << "��" << endl;
	double x = sum / count;
	return x;
}

//���û�x�����в�Ʒ��ֵ�ƽ��ֵ
double useraverage(int UserID)
{
	double sum = 0;
	for (int i = 0; i < itemnumtable[UserID]; i++)//�����Լ����е���Ʒ
	{
		sum = sum + data0[UserID][i].rate;//������
	}
	double x = sum / itemnumtable[UserID];//ƽ�� 
	return x;
}

//���Ʒitem���������ֵ�ƽ��ֵ
double itemaverage(int itemID)
{
	double sum = 0;
	int count = 0;

	for (int i = 0; i < usernum; i++) //���������û�
	{
			//�ڸ��û��������Ʒ�Ĵ�ִ������ۼӼ���
			sum = sum + data0[i][itemID].rate;
			count++;
	}

	double x = sum / count;
	return x;
}

