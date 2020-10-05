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

	int set(std::ifstream &fout);	//�޸����� ���ڷ� �޾Ƽ� �о List�� ����� �Լ�
	Node* Search(char* Item);		//Item�̸��� �޾Ƽ� Node�� return �ϴ� �Լ�
	int I_ADD(char *Item, int Count, int Price);	//ADD��ɾ� ���ڰ� 4���� ��� List�� �߰��ϴ� �Լ�
	int CountADD(char *Item, int Count);	//ADD��ɾ ���ڰ� 2���� ��� ������ ADD�ϴ� �Լ�
	int P_MODIFY(char* Item, int Price);	//��ǰ��� ������ ���ڷ� �޾Ƽ� ã�Ƽ� �����ϴ� �Լ�
	int I_SELL(char* Item, int Count);	//SELL�Լ����� ��ǰ�� ã���� ��� ������ ����
	int g_Price(char* Item); //Item�� ���ڷ� �޾Ƽ� ������ �����Ѵ�.
	Node* Delete(char* item);	//item �̸��� ���ڷ� �޾Ƽ� ������ Node�� return �޴´�.
	int I_SEARCH(char* Item); //Item�� ���ڷ� �޾Ƽ� Search
	int C_MANAGE(int Count); //��ǰ ������ ���ڷ� �޾Ƽ� ��ǰ ������ ���� ������ ��� ���
	int I_MANAGE(int Count, int ChangeCount);  //��ǰ ������ �ٲ� ������ ���ڷ� �޾Ƽ� �ٲٰ� ���
	ItemNode* V_Search(char* Item, int Count); //���Ϳ� �־��� ItemNode�� �����Ѵ�
};