#pragma once

#include "ItemNode.h"

class ItemList 
{
private:
	Node*		iRoot;
	ofstream*	fout;

public:
	ItemList() { };
	~ItemList() { };
	ItemList(ofstream* fout);

	int set(std::ifstream &fout);	//메모장을 인자로 받아서 읽어서 List를 만드는 함수
	Node* Search(char* Item);		//Item이름을 받아서 Node를 return 하는 함수
	int I_ADD(char *Item, int Count, int Price);	//ADD명령어 인자가 4개일 경우 List에 추가하는 함수
	int CountADD(char *Item, int Count);	//ADD명령어에 인자가 2개일 경우 수량을 ADD하는 함수
	int P_MODIFY(char* Item, int Price);	//물품명과 가격을 인자로 받아서 찾아서 수정하는 함수
	int I_SELL(char* Item, int Count);	//SELL함수에서 물품을 찾았을 경우 수량을 수정
	int g_Price(char* Item); //Item을 인자로 받아서 가격을 리턴한다.
	Node* Delete(char* item);	//item 이름을 인자로 받아서 삭제할 Node를 return 받는다.
	int I_SEARCH(char* Item); //Item을 인자로 받아서 Search
	int C_MANAGE(int Count); //물품 수량을 인자로 받아서 물품 수량이 인자 이하인 경우 출력
	int I_MANAGE(int Count, int ChangeCount);  //물품 수량과 바꿀 수량을 인자로 받아서 바꾸고 출력
	ItemNode* V_Search(char* Item, int Count); //벡터에 넣어줄 ItemNode를 리턴한다
};