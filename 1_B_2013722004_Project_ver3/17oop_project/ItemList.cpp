#include "ItemList.h"

ItemList::ItemList(ofstream* fout) {
	this->fout = fout;
	iRoot = NULL;
}
//item.txt������ �о ��ǰ���� ���ϸ���Ʈ�� ����
int ItemList::set(std::ifstream &fout)
{	
	char data[256] = { 0 };
	char *ItemName;
	int ItemCount;
	int ItemPrice;
	
	while (!fout.eof())
	{	
		fout.getline(data, sizeof(data));
		if (strcmp(data, "") == 0) return 1; // �޸��忡 �ƹ��͵� �������� ���� ��, return 1
		Node* newNode = new ItemNode;

		ItemName = strtok(data, " ");
		strtok(NULL, " ");
		ItemPrice = atoi(strtok(NULL, " "));
		ItemCount = atoi(strtok(NULL, " "));
		//���ο� Node�� �����͸� ����
		newNode->setName(ItemName);
		newNode->setPrice(ItemCount);
		newNode->setCount(ItemPrice);
		newNode->setNext(NULL);
		//iRoot�� ������� ��� iRoot�� ���ο� node�̴�.
		if (iRoot == NULL) iRoot = newNode;
		//iRoot�� ������� ���� ��� �����ϰ� �����Ѵ�.
		else
		{
			Node* temp = new ItemNode;
			temp = iRoot;
			
			while (temp != NULL)
			{	
				//�ι�° ��� ���Խ�
				if (temp->getNext() == NULL) 
				{
					//��庸�� ���ο� ��尡 Ŭ ���
					if (strcmp(temp->getName(), newNode->getName()) < 0)
					{
						//�ι�° ��忡 ����
						temp->setNext(newNode);
						break;
					}
					//��庸�� ���ο� ��尡 ���� ���
					else 
					{
						newNode->setNext(temp);
						iRoot = newNode;
						break;
					}
				}
				//��尡 ������ ������ ���
				else
				{	//��庸�� ���ο� ��尡 Ŭ ���
					if (strcmp(temp->getName(), newNode->getName()) < 0)
					{	//��� ���� ��尡 ���ο� ��庸�� Ŭ ���
						if (strcmp(temp->getNext()->getName(), newNode->getName()) > 0)
						{
							newNode->setNext(temp->getNext());
							temp->setNext(newNode);
							break;
						}
						temp = temp->getNext();
					}
					//��庸�� ���ο� ��尡 ���� ���
					else
					{
						newNode->setNext(temp);
						iRoot = newNode;
						break;
					}
				}
			}	
		}
	}

	return 0; // ���������� ����
}
//������ �̸��� ���ڷ� �޾Ƽ� �ش��ϴ� Node�� ����
Node* ItemList::Search(char* Item)
{	
	
	Node* temp = new ItemNode;
	temp = iRoot;
	//������ �̸��� ������ Node�� return
	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) {
			return temp;
		}
		temp = temp->getNext();
	}
	//���� ��� temp Node�� return
	return temp;
}
//���Ϳ� �־��� ItemNode�� �����Ѵ�
ItemNode* ItemList::V_Search(char* Item,int Count)
{
	ItemNode* Vtemp = new ItemNode;
	Node* temp = new ItemNode;
	temp = iRoot;//temp�� iRoot�� ����Ų��.
	
	while (temp != NULL)
	{	//�ش� Node�� ã�� ���
		if (strcmp(temp->getName(), Item) == 0) {
			if ((temp->getCount() - Count) < 0) return NULL; //������ 0�̸��� �� ��� NULL�� return
			//�׷��� ���� ���
			else {
				Vtemp->setName(temp->getName());
				Vtemp->setPrice(temp->getPrice());
				Vtemp->setCount(0);
				return Vtemp; //�ش� Node�� ������ ������ �������ְ� return�Ѵ�.
			}
		}

		temp = temp->getNext();
	}

	return NULL;
}
//ItemList�� ���ο� Node�� ADD
int ItemList::I_ADD(char *Item, int Count, int Price)
{
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) { //�Ȱ��� �̸��� �����Ѵٸ� return1, error
			return 1;
		}
		temp = temp->getNext();
	}

	temp = iRoot;
	Node* newNode = new ItemNode;
	newNode->setName(Item);
	newNode->setCount(Count);
	newNode->setPrice(Price);
	//���� iRoot�� NULL�� ���
	if (temp == NULL) {

			iRoot = newNode;
	}
	//iRoot�� NULL�� �ƴϰ� �ٸ� ������ ������ ���
	else {

		while (temp != NULL)
		{
			//�ι�° ��� ���Խ�
			if (temp->getNext() == NULL)
			{
				//��庸�� ���ο� ��尡 Ŭ ���
				if (strcmp(temp->getName(), newNode->getName()) < 0)
				{
					//�ι�° ��忡 ����
					temp->setNext(newNode);
					break;
				}
				//��庸�� ���ο� ��尡 ���� ���
				else
				{
					newNode->setNext(temp);
					iRoot = newNode;
					break;
				}
			}
			//��尡 ������ ������ ���
			else
			{	//��庸�� ���ο� ��尡 Ŭ ���
				if (strcmp(temp->getName(), newNode->getName()) < 0)
				{	//��� ���� ��尡 ���ο� ��庸�� Ŭ ���
					if (strcmp(temp->getNext()->getName(), newNode->getName()) > 0)
					{
						newNode->setNext(temp->getNext());
						temp->setNext(newNode);
						break;
					}
					temp = temp->getNext();
				}
				//��庸�� ���ο� ��尡 ���� ���
				else
				{
					newNode->setNext(temp);
					iRoot = newNode;
					break;
				}
			}
		}
	}

	return 0;
}
//��ǰ�� ������ ADD
int ItemList::CountADD(char *Item, int Count)
{	
	int Check = 0;
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) { //Item�̸��� Ž��
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//���ڷ� ���� Item�� Ž������ ������ ��� return 1
	if (Check == 0) return 1; // ��ǰ�� �������� �ʴ� ���
	//���ڷ� ���� Item�� Ž������ ��� ������ ����
	else if (Check == 1)
	{
		temp->setCount(Count + temp->getCount());
	}

	return 0;
}
//��ǰ�� ������ ����
int ItemList::P_MODIFY(char* Item, int Price)
{
	Node* temp = new ItemNode;
	temp = iRoot;
	int Check = 0;

	while (temp != NULL)
	{	//Item�̸��� ������ Node�� Ž���Ѵ�.
		if (strcmp(temp->getName(), Item) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//Node�� Ž������ ���� ��� return 1, error
	if (Check == 0) return 1;
	//Node�� Ž������ ��� ������ ����
	else if (Check == 1) {
		
		temp->setPrice(Price);
	}

	return 0;
}
//��ǰ �Ǹ�
int ItemList::I_SELL(char* Item, int Count)
{
	Node* temp = new ItemNode;
	temp = iRoot;
	int Check = 0;

	while (temp != NULL)
	{	//Item�̸��� ���� Node�� Ž���Ѵ�.
		if (strcmp(temp->getName(), Item) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}		
	//���������� �Ǹ� �� ���
	temp->setCount(temp->getCount() - Count);

	return 0;
}
//�Ǹŵ� ��ǰ�� ������ ��� ���� �Լ�
int ItemList::g_Price(char* Item)
{
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{	//���ڷ� ���� Item�̸��� ���� Node�� Ž��
		if (strcmp(temp->getName(), Item) == 0) {
			break;
		}
		temp = temp->getNext();
	}
	//������ return
	return temp->getPrice();
}
//��ǰ�� Ž���ϴ� �Լ�
int ItemList::I_SEARCH(char* Item)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	int StrCount = 0;
	int i = 0;
	int k = 0;
	int len = 0;
	int Count = 0;
	int ItemCount = 0;
	int SellCount = 0;
	int OverLap = 0;
	char* I_Name = NULL;

	StrCount = strlen(Item);
	Node* temp = new ItemNode;
	Node* temp1 = new ItemNode;
	temp = iRoot;
	temp1 = iRoot;
	//�Ѱ� ���ڸ� ���� ���
	if (StrCount == 1) {
		while (temp1 != NULL)
		{
			temp = temp1;
			I_Name = temp->getName();	//Item List�� ����� Item�̸�
			
			if (I_Name[0] == Item[0]) { //��ó�� ���ڸ� ���Ѵ�.
				OverLap = 1;
				ItemCount = temp->getCount();
				SellCount = temp->getPrice();

				while (1)
				{	//Category �̸��� ã�� ���� While��
					temp = temp->getUp();
					if (temp->getUp() == NULL) break;
				}
				cout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
				//�α׿� ���
				fout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
			}

			temp1 = temp1->getNext();
		}
	}
	///���ڿ��� ���� ���
	else {
		while (temp1 != NULL)
		{
			temp = temp1;
			I_Name = temp->getName();	//Item List�� ����� Item�̸�
			len = strlen(I_Name);		//
			Count = 0;

			for (i = 0; i < len; i++) {
				//ù�� ° ���ڿ��� ã�����
				if (I_Name[i] == Item[0]) {
					Count = 0;	//ù��° ���ڿ��� ã����� ������ ���̸�ŭ ���� �ش�. ���� ���ڿ��� ������
					for (k = 0; k < StrCount; k++) {
						if (I_Name[i + k] == Item[k]) Count++;
					}
				}
			}
			//���� ������ �� �ִٸ�
			if (StrCount == Count) {
				OverLap++;
				ItemCount = temp->getCount();
				SellCount = temp->getPrice();
				while (1)
				{	//Category �̸��� ������ ���ؼ�
					temp = temp->getUp();
					if (temp->getUp() == NULL) break;
				}//�ش� �������� ���
				cout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
				//�ش� �������� Log�� ���
				fout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
			}

			temp1 = temp1->getNext();
		}
	}

	fout.close();

	if (OverLap == 0)  return 1;

	return 0;
}
//��ǰ ������ ���ڷ� �޾Ƽ� ���ڷ� ���� ���� ���ϸ� ���
int ItemList::C_MANAGE(int Count)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	Node* temp = new ItemNode;
	Node* temp1 = new ItemNode;
	temp = iRoot;
	int Check = 0;
	//iRoot�� NULL�� ���
	if (iRoot == NULL) {
		fout.close();
		return 1; //��ǰ�� �������� ���� ��
	}

	while (temp != NULL)
	{	//���ڷ� ���� ���� �����ΰ��� Ž���Ѵ�.
		if (temp->getCount() <= Count) {
			temp1 = temp;
			Check++;
			//ī�װ� ��带 ã�´�.
			while (temp1->getUp() != NULL) {
				temp1 = temp1->getUp();
			}
			cout << temp->getName() << " " << temp1->getCategory() << " " << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp1->getCategory() << " " << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}

		temp = temp->getNext();
	}
	//Ž������ �� �ش��ϴ°� ���� ���
	if (Check == 0) {
		fout.close();
		return 1;
	}

	fout.close();
	return 0;
}
//��ǰ ������ �ٲ� ������ ���ڷ� �޾Ƽ� �ٲٰ� ���
int ItemList::I_MANAGE(int Count, int ChangeCount)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	Node* temp = new ItemNode;
	Node* temp1 = new ItemNode;
	temp = iRoot;
	int Check = 0;

	if (iRoot == NULL) {
		fout.close();
		return 1; //��ǰ�� �������� ���� ��
	}

	while (temp != NULL)
	{	//���� ������ ���� Ž���Ѵ�
		if (temp->getCount() <= Count) {
			temp1 = temp;
			Check++;
			//ī�װ� ��带 ã�´�.
			while (temp1->getUp() != NULL) {
				temp1 = temp1->getUp();
			}
			temp->setCount(temp->getCount() + ChangeCount); //���� ������ �߰��� ������ �����ش�
			cout << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}

		temp = temp->getNext();
	}
	//Ž������ ���� ���
	if (Check == 0) {
		fout.close();
		return 1;
	}
	fout.close();
	return 0;
}
//Item�̸��� ���ڷ� �޾Ƽ� �ش� Node�� �����Ѵ�.
Node* ItemList::Delete(char* item) {
	// ����� ��尡 ��Ʈ�� ���
	if (strcmp(iRoot->getName(), item) == 0) {
		Node* delNode = iRoot;

		// ��Ʈ�� ���� ���� ����
		iRoot = iRoot->getNext();

		return delNode;
	}

	for (Node* temp = iRoot; temp->getNext(); temp = temp->getNext()) {
		// ���� ��� �߰��ϸ�
		if (!strcmp(temp->getNext()->getName(), item)) {
			Node* delNode = temp->getNext();

			// ���� ��� ���� �ִ� ��尡
			// ���� ��� ������ �ִ� ��带 ����Ű�� ��
			// [.A.]->[.B.]->[.C.] ========>>> [.A.]->[.C.]
			temp->setNext(delNode->getNext());
			return delNode;
		}
	}

	return NULL;
}