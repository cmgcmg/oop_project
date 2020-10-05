#pragma once

#include "Node.h"

//Node를 상속받는다
class ItemNode : public Node
{
private:
	char	mName[64];
	int		mCount;
	int		mPrice;

public:
	/*이름을 인자로 받아서 물품 이름을 Set하는 함수*/
	void setName(char* Name)
	{
		strcpy(mName, Name);
	}
	/*수량을 인자로 받아서 물품 수량을 Set하는 함수*/
	void setCount(int Count)
	{
		mCount = Count;
	}
	/*가격을 인자로 받아서 물품 가격을 Set하는 함수*/
	void setPrice(int Price)
	{
		mPrice = Price;
	}
	/*물품의 이름을 Return 받는 함수*/
	char* getName()
	{
		return mName;
	}
	/*물품의 수량을 Return 받는 함수*/
	int getCount()
	{
		return mCount;
	}
	/*물품의 가격을 Return 받는 함수*/
	int getPrice()
	{
		return mPrice;
	}
	/*사용하지 않지만 instance해줘야 컴파일이 된다. 이름, 수량, 가격에 관련된 함수들은 CategoryNode에서 사용*/
	/*아래 기능들은 CategoryNode에서 사용*/
	void setCategory(char* Name)
	{

	}
	char* getCategory()
	{
		return 0;
	}
};