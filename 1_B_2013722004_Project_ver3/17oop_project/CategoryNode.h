#pragma once

#include "Node.h"
//Node�� ��ӹ޴´�.
class CategoryNode : public Node
{
private:
	char	mName[64];
	
public:
	//Name�� ���ڷ� �޾Ƽ� ī�װ� �̸��� Set
	void setCategory(char* Name)
	{
		strcpy(mName, Name);
	}
	//ī�װ� �̸��� return �޴´�.
	char* getCategory()
	{
		return mName;
	}
	/*������� ������ instance����� �������� �ȴ�. �̸�, ����, ���ݿ� ���õ� �Լ����� ItemNode���� ���*/
	/*�Ʒ� ��ɵ��� ItemNode���� ���*/
	void setName(char* Name)
	{

	}
	void setCount(int Count)
	{

	}
	void setPrice(int Price)
	{
	
	}

	char* getName()
	{
		return 0;
	}
	int getCount()
	{
		return 0;
	}
	int getPrice()
	{
		return 0;
	}

};