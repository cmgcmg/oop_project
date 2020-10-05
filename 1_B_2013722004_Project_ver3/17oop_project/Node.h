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

	Node* getNext() { return pNext; }	//���� Node�� return �޴´�
	Node* getUp()	{ return pUp; }		//���� Node�� return �޴´�
	Node* getDown() { return pDown; }	//�Ʒ� Node�� return �޴´�

	void setNext(Node* pN)	{ pNext = pN; }	//���� ��带 ���� �� �� ���
	void setUp(Node* pN)	{ pUp = pN; }	//���� ��带 ���� �� �� ���
	void setDown(Node* pN)	{ pDown = pN; }	//�Ʒ� ��带 ���� �� �� ���

	/*�������� ���*/
	virtual void setName(char* Name) = 0;	//�̸��� set�ϴ� �Լ�
	virtual void setCount(int Count) = 0;	//������ set�ϴ� �Լ�
	virtual void setPrice(int Price) = 0;	//������ set�ϴ� �Լ�

	virtual char* getName() = 0;			//�̸��� ������ �Լ�
	virtual int getCount() = 0;				//������ ������ �Լ�
	virtual int getPrice() = 0;				//������ ������ �Լ�

	//Category
	virtual void setCategory(char* Name) = 0;	//ī�װ��� set�ϴ� �Լ�
	virtual char* getCategory() = 0;			//ī�װ��� ������ �Լ�
};