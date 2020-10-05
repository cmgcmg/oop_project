#pragma once

#include "Node.h"
//Node를 상속받는다.
class CategoryNode : public Node
{
private:
	char	mName[64];
	
public:
	//Name을 인자로 받아서 카테고리 이름을 Set
	void setCategory(char* Name)
	{
		strcpy(mName, Name);
	}
	//카테고리 이름을 return 받는다.
	char* getCategory()
	{
		return mName;
	}
	/*사용하지 않지만 instance해줘야 컴파일이 된다. 이름, 수량, 가격에 관련된 함수들은 ItemNode에서 사용*/
	/*아래 기능들은 ItemNode에서 사용*/
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