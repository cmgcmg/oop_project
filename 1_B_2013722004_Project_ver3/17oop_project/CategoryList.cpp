#include "CategoryList.h"

CategoryList::CategoryList(ofstream* fout) {
	this->fout = fout;
	cRoot = NULL;
}
//ī�װ� ����Ʈ�� ���� ����Ʈ�� ����
void CategoryList::set(std::ifstream &fout)
{
	char data[256] = { 0 };
	char *CName;

	while (!fout.eof())
	{
		fout.getline(data, sizeof(data));
		Node* newNode = new CategoryNode;
		
		strtok(data, " ");
		CName = strtok(NULL, " ");
		strtok(NULL, " ");
		strtok(NULL, " ");
		//���ο� ī�װ� newNode�� �����͸� ����
		newNode->setCategory(CName);
		newNode->setNext(NULL);

		if (cRoot == NULL) cRoot = newNode;

		else
		{
			Node* temp = new CategoryNode;
			temp = cRoot;

			while (temp != NULL)
			{	
				//ī�װ��� �̸��� ������� ���ο� ����Ʈ�� �߰����� �ʴ´�.
				if (strcmp(temp->getCategory(), newNode->getCategory()) == 0) break;
				//�ι�° ��� ���Խ�
				if (temp->getNext() == NULL)
				{
					//��庸�� ���ο� ��尡 Ŭ ���
					if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
					{
						//�ι�° ��忡 ����
						temp->setNext(newNode);
						break;
					}
					//��庸�� ���ο� ��尡 ���� ���
					else
					{
						newNode->setNext(temp);
						cRoot = newNode;
						break;
					}
				}
				//��尡 ������ ������ ���
				else
				{	//��庸�� ���ο� ��尡 Ŭ ���
					if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
					{	//��� ���� ��尡 ���ο� ��庸�� Ŭ ���
						if (strcmp(temp->getNext()->getCategory(), newNode->getCategory()) > 0)
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
						cRoot = newNode;
						break;
					}
				}

			}
		}
	}
}
//ī�װ� �̸��� ���ڷ� �޾Ƽ� �ش��ϴ� Node�� ����
Node* CategoryList::Search(char* Category)
{
	Node* temp = new CategoryNode;
	temp = cRoot;

	while (temp != NULL)
	{	//���ڷ� ���� ī�װ� �̸��� ���� ���� ã���� ��� �ش� Node�� return
		if (strcmp(temp->getCategory(), Category) == 0) {
			return temp;
		}
		temp = temp->getNext();
	}
}
//ī�װ� ���� ������ ��带 ���ڷι޾Ƽ� Up down Set
void CategoryList::setUpDown(Node* CNode, Node* INode)
{
	Node* temp = new CategoryNode;
	temp = CNode;

	//ī�װ� ��忡 ����Ȱ� ���� ��
	if (temp->getDown() == NULL) {
		temp->setDown(INode);
		temp->getDown()->setUp(CNode);
	}
	//ī�װ� ��忡 ����Ȱ� ���� �� ���� ����
	else
	{	//ī�װ��� Down��Ű�鼭 Ž��
		temp = temp->getDown();

		while (temp != NULL)
		{	
			//�ΰ��� ���
			if (temp->getDown() == NULL) {
				//INode�� �Ǹ������� ���� �� ��
				if (strcmp(temp->getName(), INode->getName()) < 0) {
					temp->setDown(INode);
					temp->getDown()->setUp(temp);
					break;
				}
				//INODE�� ī�װ� ���� ���� �����ߴ� ��� ���̿� �� ��
				else {
					INode->setUp(temp->getUp());
					temp->getUp()->setDown(INode);
					INode->setDown(temp);
					temp->setUp(INode);
					break;
				}
			}
			//�������� ��尡 ������ ���
			else {
				//INode�� ���ڿ��� �ڷε����� �� temp->getDown()
				if (strcmp(temp->getName(), INode->getName()) < 0) {
					temp = temp->getDown();
				}
				//INode�� ��ġ�� ã���� ��
				else {
					//�������� ���
					if (temp->getDown() == NULL) {
						temp->setDown(INode);
						INode->setUp(temp);
						break;
					}
					else { //�������� �ƴѰ��
						INode->setUp(temp->getUp());
						temp->getUp()->setDown(INode);
						INode->setDown(temp);
						temp->setUp(INode);
						break;
					}
				}
			}
		}
	}
	
}
//���ο� ��ǰ�� ī�װ��� ADD�� �� ���̴� �Լ�
void CategoryList::ADD(char* Category)
{
	Node* newNode = new CategoryNode;
	newNode->setCategory(Category);
	//cRoot�� NULL�� ��� ���ο� Node�� ����
	if (cRoot == NULL) cRoot = newNode;

	else
	{
		Node* temp = new CategoryNode;
		temp = cRoot;

		while (temp != NULL)
		{
			//ī�װ��� �̸��� ������� ���ο� ����Ʈ�� �߰����� �ʴ´�.
			if (strcmp(temp->getCategory(), newNode->getCategory()) == 0) break;
			//�ι�° ��� ���Խ�
			if (temp->getNext() == NULL)
			{
				//��庸�� ���ο� ��尡 Ŭ ���
				if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
				{
					//�ι�° ��忡 ����
					temp->setNext(newNode);
					break;
				}
				//��庸�� ���ο� ��尡 ���� ���
				else
				{
					newNode->setNext(temp);
					cRoot = newNode;
					break;
				}
			}
			//��尡 ������ ������ ���
			else
			{	//��庸�� ���ο� ��尡 Ŭ ���
				if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
				{	//��� ���� ��尡 ���ο� ��庸�� Ŭ ���
					if (strcmp(temp->getNext()->getCategory(), newNode->getCategory()) > 0)
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
					cRoot = newNode;
					break;
				}
			}

		}
	}
}
//������ �̸��� �޾Ƽ� ī�װ� �̸��� ��ġ�ؼ� return
char* CategoryList::C_Search(char* Item)
{
	Node* temp = new CategoryNode;
	Node* temp1 = new CategoryNode;
	temp = cRoot;
	temp1 = cRoot;

	while (1)
	{
		temp = temp1;
		while (1) {
			temp = temp->getDown();
			//�ش� Item�� ã�Ƽ� getUp()�ؼ� ī�װ� �̸��� return�Ѵ�.
			if (strcmp(temp->getName(), Item) == 0) return temp1->getCategory();
			else {
				if (temp->getDown() == NULL) break;
			}
		}
		if(temp1->getNext() != NULL) temp1 = temp1->getNext();
	}
}
//Item�̸��� �޾Ƽ� �ش� Node�� �����Ѵ�.
Node* CategoryList::Delete(char* arg) {
	Node* prevC = 0; // ī�װ� ���� ���

	for (Node* category = cRoot; category; category = category->getNext()) {
		// ������� �ϴ� ��尡 �� ó���� ������
		if (strcmp(category->getDown()->getName(), arg) == 0) {
			Node* delNode = category->getDown();

			// ������� �ϴ� ����� ���� ���, �� ī�װ���
			// ��������ϴ� ����� ���� ��带 ����Ű���� ��
			category->setDown(delNode->getDown());

			// ���� ��������ϴ� ����� ����(��, �Ʒ�)�� �����ϴ� ���
			if (delNode->getDown())
				// ���� �����⵵ ��������
				delNode->setUp(category);
			else {
				// �������� �ʴ� ���� ī�װ��� �����ؾ��ϴ� �����
				if (!prevC) {
					prevC = cRoot;
					// ī�װ��� ��Ʈ�� ���
					cRoot = cRoot->getNext();
					delete prevC;
				}
				else {
					// �ƴϸ� Linked Listó�� �������ְ� ����
					prevC->setNext(category->getNext());
					delete category;
				}
			}

			return delNode;
		}
		// ������� �ϴ� ��尡 �� ��° �̻���� �ִ� ���
		// ��, �������� �ϳ� �̻� �����ϹǷ� ī�װ��� ���� ������ ����
		for (Node* item = category->getDown(); item->getDown(); item = item->getDown()) {
			if (strcmp(item->getDown()->getName(), arg) == 0) {
				Node* delNode = item->getDown();

				item->setDown(delNode->getDown());
				if (delNode->getDown())
					delNode->setUp(category);

				return delNode;
			}
		}

		prevC = category;
	}

	return NULL;
}
//ī�װ��� ��� �������� ���
int CategoryList::ALL_PRINT()
{	
	ofstream fout;
	fout.open("log.txt", ios::app);
	Node *temp = cRoot;
	Node *temp1 = cRoot;

	if (cRoot == NULL) {
		fout.close();
		return 1; //������ ���� ���
	}
	/*cRoot���� �Ʒ��� �������鼭 ������ ��带 ���*/
	/*��� ����ߴٸ� cRoot->getNext() �ؼ� �� �ش� ����� �Ʒ� �����۵��� ��� ���*/
	/*���� �������� �ݺ�*/
	while (temp1 != NULL)
	{
		temp = temp1;
		/*ī�װ� ������ ���*/
		cout << "<" << temp->getCategory() << ">" << endl;
		fout << "<" << temp->getCategory() << ">" << endl;

		while (temp->getDown() != NULL) {
			temp = temp->getDown();
			cout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}
		/*ī�װ� ��带 getNext()*/
		temp1 = temp1->getNext();
	}

	fout.close();
	return 0;
}
//ī�װ� �̸��� ���ڷ� �޾Ƽ� ī�װ��� ���ԵǾ��ִ� �������� ���
int CategoryList::I_PRINT(char* Category)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	int Check = 0;
	Node* temp = new CategoryNode;
	temp = cRoot;
	//������ �������� ���� ���
	if (temp == NULL) return 1;

	while (temp != NULL)
	{
		if (strcmp(temp->getCategory(), Category) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//ã�� ī�װ��� ���� ���
	if (Check == 0) {
		fout.close();
		return 1;
	}
	//ã�� ī�װ��� ã���� ��
	else {
		cout << "<" << temp->getCategory() << ">" << endl;
		fout << "<" << temp->getCategory() << ">" << endl;

		while (temp->getDown() != NULL)
		{	
			temp = temp->getDown();
			cout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}
	}
	fout.close();
	return 0;
}
//SAVE
void CategoryList::SAVE()
{	
	ofstream ItemList;
	ItemList.open("item.txt", ios::trunc);

	Node* temp = new CategoryNode;
	Node* temp1 = new CategoryNode;
	temp = cRoot;
	temp1 = cRoot;
	//��尡 �ƿ� �������� �ʴ� ���
	if (cRoot == NULL) {
		ItemList.close();
		return;
	}

	while (temp1 != NULL)
	{	
		temp = temp1;

		while (temp->getDown() != NULL)
		{
			temp = temp->getDown();
			//�޸��忡 ó�� �� ��
			if (temp1 == cRoot && temp->getUp() == cRoot) {
				ItemList << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice();
			}
			//�޸��忡 �� �� ó���� �ƴ� ���
			else ItemList << "\n" << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice();
			
		}

		temp1 = temp1->getNext();
	}
	
	ItemList.close();
}
