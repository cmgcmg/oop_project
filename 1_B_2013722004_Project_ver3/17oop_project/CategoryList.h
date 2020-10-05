#pragma once

#include "CategoryNode.h"

class CategoryList
{
private:
	Node*		cRoot;
	ofstream*	fout;

public:
	CategoryList(ofstream* fout);

	/* write your code */
	CategoryList() {};
	~CategoryList() {};

	void set(std::ifstream &fout);	//LOAD에서 메모장을 인자로 받아서 List를 만든다.
	Node* Search(char* Category);	//Category이름을 인자로 받아서 Node를 return 한다.
	char* C_Search(char* Item); //아이템 이름을 받아서 카테고리를 써치
	void setUpDown(Node* CNode, Node* INode); //양방향 Linked List를 연결 하는 함수
	void ADD(char* Category); //Category이름을 인자로 받아서 추가해주는 함수
	int ALL_PRINT(); //모든 카테고리와 모든 아이템을 출력
	int I_PRINT(char* Category); //카테고리 이름을 인자로받아서 해당 카테고리의 아이템을 출력 
	Node* Delete(char* arg); //물품 이름을 인자로 받아서 CategoryNode를 삭제
	void CategoryList::SAVE(); //리스트 전체를 SAVE
};