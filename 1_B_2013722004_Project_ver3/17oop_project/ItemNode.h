#pragma once

#include "Node.h"

//Node�� ��ӹ޴´�
class ItemNode : public Node
{
private:
	char	mName[64];
	int		mCount;
	int		mPrice;

public:
	/*�̸��� ���ڷ� �޾Ƽ� ��ǰ �̸��� Set�ϴ� �Լ�*/
	void setName(char* Name)
	{
		strcpy(mName, Name);
	}
	/*������ ���ڷ� �޾Ƽ� ��ǰ ������ Set�ϴ� �Լ�*/
	void setCount(int Count)
	{
		mCount = Count;
	}
	/*������ ���ڷ� �޾Ƽ� ��ǰ ������ Set�ϴ� �Լ�*/
	void setPrice(int Price)
	{
		mPrice = Price;
	}
	/*��ǰ�� �̸��� Return �޴� �Լ�*/
	char* getName()
	{
		return mName;
	}
	/*��ǰ�� ������ Return �޴� �Լ�*/
	int getCount()
	{
		return mCount;
	}
	/*��ǰ�� ������ Return �޴� �Լ�*/
	int getPrice()
	{
		return mPrice;
	}
	/*������� ������ instance����� �������� �ȴ�. �̸�, ����, ���ݿ� ���õ� �Լ����� CategoryNode���� ���*/
	/*�Ʒ� ��ɵ��� CategoryNode���� ���*/
	void setCategory(char* Name)
	{

	}
	char* getCategory()
	{
		return 0;
	}
};