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

	void set(std::ifstream &fout);	//LOAD���� �޸����� ���ڷ� �޾Ƽ� List�� �����.
	Node* Search(char* Category);	//Category�̸��� ���ڷ� �޾Ƽ� Node�� return �Ѵ�.
	char* C_Search(char* Item); //������ �̸��� �޾Ƽ� ī�װ��� ��ġ
	void setUpDown(Node* CNode, Node* INode); //����� Linked List�� ���� �ϴ� �Լ�
	void ADD(char* Category); //Category�̸��� ���ڷ� �޾Ƽ� �߰����ִ� �Լ�
	int ALL_PRINT(); //��� ī�װ��� ��� �������� ���
	int I_PRINT(char* Category); //ī�װ� �̸��� ���ڷι޾Ƽ� �ش� ī�װ��� �������� ��� 
	Node* Delete(char* arg); //��ǰ �̸��� ���ڷ� �޾Ƽ� CategoryNode�� ����
	void CategoryList::SAVE(); //����Ʈ ��ü�� SAVE
};