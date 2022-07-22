#include"ƽ��ֵ����.h"
//����Ʒ�÷��е�bxi��ֵ





//��ԭʼ�Ĵ������ת��Ϊpearson���ϵ��������
void Pearson()
{
	for (int i = 0; i < usernum; i++)
	{
		pearson[i] = new itemrate[itemnumtable[i]];

		for (int j = 0; j < itemnumtable[i]; j++)
		{
			pearson[i][j].itemID = data0[i][j].itemID;//ԭ���ݵ��û��ż�Ϊpearson���û� 

			pearson[i][j].rate = data0[i][j].rate;//Pearson�����ϵ����Ϊ�µ�ֵ
		}
	}
}



//������Ʒ���Pearson���ƶ�
double rateitemsimilar(int item1, int item2)
{
	//��rx*ry�ۼӺͺ�ķ���

	double rateitem0[10000];//������Ʒ�Ĵ��
	int count00 = 0;//�����ǵڼ�����Ʒ 

	
	
		for (int i = 0; i < itemnumtable[item1]; i++) //������ƷA�����д�����
		{
			int j = insertfind(pearson, item1,item2, itemnumtable[item2], pearson[item1][i].itemID);
			if (j != -1)//����ƷA�еĴ�֣�����ƷB���Ƿ�Ҳ�д�� 
			{
				rateitem0[count00] = (pearson[item1][i].rate- //����Щ�ж�Ӧ��ֵĽ��м���
				itemaverage(i))* (pearson[item2][j].rate - itemaverage(i));//(rx-avg)*(ry-avg)
				count00++;
			}
		}
	


		//rx*ry�ĸ����ۼӺ�������
	double PeaNumerator = 0;
	for (int i = 0; i < count00; i++)
		PeaNumerator = PeaNumerator + rateitem0[i];


	//rx-avg�ۼ�ƽ������ �� ������ry-avg�ۼ�ƽ�� ����������ĸ

	
	double countitemA; double countitemB;

	for (int i = 0; i < itemnumtable[item1]; i++)
		countitemA = countitemA + (pearson[item1][i].rate-itemaverage(i)) *
		( pearson[item1][i].rate - itemaverage(i));


	for (int i = 0; i < itemnumtable[item2]; i++)
		countitemB = countitemB + (pearson[item2][i].rate - itemaverage(i)) *
		(pearson[item2][i].rate - itemaverage(i));

	//�����յ�pearsonϵ��
	double pearson = PeaNumerator / (sqrt(countitemA) * sqrt(countitemB));

	return pearson;
}

double max1(double r,int  itemID,double average,int itemID1)//ȡ�������Ƶ���Ʒ�����ƶ���������

{
	double maxsimilar = 0;
	double x11 = 0;
	double x22 = 0;
	for (int i = 0; i < 19835; i++)//���������û�
	{
		int j = insertfind(data0, itemID, i, itemnumtable[i], itemID1);//��һ����Щ�û������������Ʒ

		if (j != -1)//�����������Ʒ��ͬһ���û������
		{
			double a = rateitemsimilar(itemID, i);//�������ߵ����ƶ�
			if (a > 0) //������ƶȴ���0��˵���������ƹ�ϵ��
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
//���û���㹻�����Ʒi���Ƶģ��Ͳ����������Ʋ�Ʒ���ֽ������

{
	ifstream attribute;
	attribute.open("itemAttribute.txt");//��ȡ��Ʒ����

	for (int i = 0; i < a1[item1][sizeof(a1[item1]) / sizeof(item1)].itemID; i++)

	{
		string s;
		int itemID00=0;
		int attribute1, attribute2;
		double rate=max1(rateitemsimilar(item1, item2),item1,item2,pearson);
			if (rate < 0.2)//�������֮���Ƶ���Ʒ�������ƶȶ�����0.2��
			//˵��ֻͨ���û��Ĵ������������ҵ��ܺ��ʵ�������Ʒ����Ҫ������Ʒ������ȷ�����Ƶġ�
			{
				while (getline(attribute, s)) //���н��ж�ȡ
				{
					int flag = s.find("|"); //���Ҹ����е�һ�γ���"|"����λ��

					string itemstr = s.substr(0, flag);//��Ʒ��Ϊ|ǰ������

					itemID00 = stoi(itemstr);

					string attributestr = s.substr(flag + 1, s.length() - 1);//����������ַ������м�|����

					int flag1 = attributestr.find("|");//�ڶ���|�ָ�������Ʒ���Ƶ�����
					string attribute1str = attributestr.substr(flag + 1, flag1 - 1);
					attribute1 = stoi(attribute1str);
					string attribute2str = attributestr.substr(flag1 + 1, s.length() - 1);
					attribute2 = stoi(attribute2str);//�����Ժ�ת��Ϊ����
					
					a1[user][item1].rate = (a1[user][attribute1].rate+a1[user][attribute2].rate) / 2;

				}
			}
	}
	attribute.close();

}

