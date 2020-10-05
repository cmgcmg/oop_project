#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

class Node
{
private:
	Node*	pNext;
	Node*	pDown;
	Node*	pUp;

public:
	Node() {
		pNext = NULL;
		pDown = NULL;
		pUp = NULL;
	};
	~Node() {};

	Node* getNext() { return pNext; }	//다음 Node를 return 받는다
	Node* getUp()	{ return pUp; }		//위에 Node를 return 받는다
	Node* getDown() { return pDown; }	//아래 Node를 return 받는다

	void setNext(Node* pN)	{ pNext = pN; }	//다음 노드를 연결 할 때 사용
	void setUp(Node* pN)	{ pUp = pN; }	//위에 노드를 연결 할 때 사용
	void setDown(Node* pN)	{ pDown = pN; }	//아래 노드를 연결 할 때 사용

	/*다형성을 사용*/
	virtual void setName(char* Name) = 0;	//이름을 set하는 함수
	virtual void setCount(int Count) = 0;	//수량을 set하는 함수
	virtual void setPrice(int Price) = 0;	//가격을 set하는 함수

	virtual char* getName() = 0;			//이름을 얻어오는 함수
	virtual int getCount() = 0;				//수량을 얻어오는 함수
	virtual int getPrice() = 0;				//가격을 얻어오는 함수

	//Category
	virtual void setCategory(char* Name) = 0;	//카테고리를 set하는 함수
	virtual char* getCategory() = 0;			//카테고리를 얻어오는 함수
};