#include "CategoryList.h"

CategoryList::CategoryList(ofstream* fout) {
	this->fout = fout;
	cRoot = NULL;
}
//카테고리 리스트를 단일 리스트로 연결
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
		//새로운 카테고리 newNode의 데이터를 설정
		newNode->setCategory(CName);
		newNode->setNext(NULL);

		if (cRoot == NULL) cRoot = newNode;

		else
		{
			Node* temp = new CategoryNode;
			temp = cRoot;

			while (temp != NULL)
			{	
				//카테고리의 이름이 같을경우 새로운 리스트를 추가하지 않는다.
				if (strcmp(temp->getCategory(), newNode->getCategory()) == 0) break;
				//두번째 노드 삽입시
				if (temp->getNext() == NULL)
				{
					//헤드보다 새로운 노드가 클 경우
					if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
					{
						//두번째 노드에 삽입
						temp->setNext(newNode);
						break;
					}
					//헤드보다 새로운 노드가 작을 경우
					else
					{
						newNode->setNext(temp);
						cRoot = newNode;
						break;
					}
				}
				//노드가 여러개 존재할 경우
				else
				{	//헤드보다 새로운 노드가 클 경우
					if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
					{	//헤드 다음 노드가 새로운 노드보다 클 경우
						if (strcmp(temp->getNext()->getCategory(), newNode->getCategory()) > 0)
						{
							newNode->setNext(temp->getNext());
							temp->setNext(newNode);
							break;
						}
						temp = temp->getNext();
					}
					//헤드보다 새로운 노드가 작을 경우
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
//카테고리 이름을 인자로 받아서 해당하는 Node를 리턴
Node* CategoryList::Search(char* Category)
{
	Node* temp = new CategoryNode;
	temp = cRoot;

	while (temp != NULL)
	{	//인자로 받은 카테고리 이름과 같은 것을 찾았을 경우 해당 Node를 return
		if (strcmp(temp->getCategory(), Category) == 0) {
			return temp;
		}
		temp = temp->getNext();
	}
}
//카테고리 노드와 아이템 노드를 인자로받아서 Up down Set
void CategoryList::setUpDown(Node* CNode, Node* INode)
{
	Node* temp = new CategoryNode;
	temp = CNode;

	//카테고리 노드에 연결된게 없을 때
	if (temp->getDown() == NULL) {
		temp->setDown(INode);
		temp->getDown()->setUp(CNode);
	}
	//카테고리 노드에 연결된게 있을 때 정렬 삽입
	else
	{	//카테고리를 Down시키면서 탐색
		temp = temp->getDown();

		while (temp != NULL)
		{	
			//두개의 노드
			if (temp->getDown() == NULL) {
				//INode가 맨마지막에 들어가야 할 때
				if (strcmp(temp->getName(), INode->getName()) < 0) {
					temp->setDown(INode);
					temp->getDown()->setUp(temp);
					break;
				}
				//INODE가 카테고리 노드와 원래 존재했던 노드 사이에 들어갈 때
				else {
					INode->setUp(temp->getUp());
					temp->getUp()->setDown(INode);
					INode->setDown(temp);
					temp->setUp(INode);
					break;
				}
			}
			//여러가지 노드가 존재할 경우
			else {
				//INode의 문자열이 뒤로들어가야할 때 temp->getDown()
				if (strcmp(temp->getName(), INode->getName()) < 0) {
					temp = temp->getDown();
				}
				//INode의 위치를 찾았을 때
				else {
					//마지막일 경우
					if (temp->getDown() == NULL) {
						temp->setDown(INode);
						INode->setUp(temp);
						break;
					}
					else { //마지막이 아닌경우
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
//새로운 물품과 카테고리를 ADD할 때 쓰이는 함수
void CategoryList::ADD(char* Category)
{
	Node* newNode = new CategoryNode;
	newNode->setCategory(Category);
	//cRoot가 NULL일 경우 새로운 Node를 삽입
	if (cRoot == NULL) cRoot = newNode;

	else
	{
		Node* temp = new CategoryNode;
		temp = cRoot;

		while (temp != NULL)
		{
			//카테고리의 이름이 같을경우 새로운 리스트를 추가하지 않는다.
			if (strcmp(temp->getCategory(), newNode->getCategory()) == 0) break;
			//두번째 노드 삽입시
			if (temp->getNext() == NULL)
			{
				//헤드보다 새로운 노드가 클 경우
				if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
				{
					//두번째 노드에 삽입
					temp->setNext(newNode);
					break;
				}
				//헤드보다 새로운 노드가 작을 경우
				else
				{
					newNode->setNext(temp);
					cRoot = newNode;
					break;
				}
			}
			//노드가 여러개 존재할 경우
			else
			{	//헤드보다 새로운 노드가 클 경우
				if (strcmp(temp->getCategory(), newNode->getCategory()) < 0)
				{	//헤드 다음 노드가 새로운 노드보다 클 경우
					if (strcmp(temp->getNext()->getCategory(), newNode->getCategory()) > 0)
					{
						newNode->setNext(temp->getNext());
						temp->setNext(newNode);
						break;
					}
					temp = temp->getNext();
				}
				//헤드보다 새로운 노드가 작을 경우
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
//아이템 이름을 받아서 카테고리 이름을 서치해서 return
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
			//해당 Item을 찾아서 getUp()해서 카테고리 이름을 return한다.
			if (strcmp(temp->getName(), Item) == 0) return temp1->getCategory();
			else {
				if (temp->getDown() == NULL) break;
			}
		}
		if(temp1->getNext() != NULL) temp1 = temp1->getNext();
	}
}
//Item이름을 받아서 해당 Node를 리턴한다.
Node* CategoryList::Delete(char* arg) {
	Node* prevC = 0; // 카테고리 이전 노드

	for (Node* category = cRoot; category; category = category->getNext()) {
		// 지우고자 하는 노드가 맨 처음에 있으면
		if (strcmp(category->getDown()->getName(), arg) == 0) {
			Node* delNode = category->getDown();

			// 지우고자 하는 노드의 이전 노드, 즉 카테고리가
			// 지우고자하는 노드의 다음 노드를 가리키도록 함
			category->setDown(delNode->getDown());

			// 만약 지우고자하는 노드의 다음(즉, 아래)이 존재하는 경우
			if (delNode->getDown())
				// 그의 역방향도 설정해줌
				delNode->setUp(category);
			else {
				// 존재하지 않는 경우는 카테고리를 삭제해야하는 경우임
				if (!prevC) {
					prevC = cRoot;
					// 카테고리가 루트인 경우
					cRoot = cRoot->getNext();
					delete prevC;
				}
				else {
					// 아니면 Linked List처럼 연결해주고 삭제
					prevC->setNext(category->getNext());
					delete category;
				}
			}

			return delNode;
		}
		// 지우고자 하는 노드가 두 번째 이상부터 있는 경우
		// 즉, 아이템이 하나 이상 존재하므로 카테고리를 지울 이유가 없음
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
//카테고리와 모든 정보들을 출력
int CategoryList::ALL_PRINT()
{	
	ofstream fout;
	fout.open("log.txt", ios::app);
	Node *temp = cRoot;
	Node *temp1 = cRoot;

	if (cRoot == NULL) {
		fout.close();
		return 1; //정보가 없을 경우
	}
	/*cRoot부터 아래로 내려가면서 아이템 노드를 출력*/
	/*모두 출력했다면 cRoot->getNext() 해서 또 해당 노드의 아래 아이템들을 모두 출력*/
	/*위의 과정들을 반복*/
	while (temp1 != NULL)
	{
		temp = temp1;
		/*카테고리 노드들을 출력*/
		cout << "<" << temp->getCategory() << ">" << endl;
		fout << "<" << temp->getCategory() << ">" << endl;

		while (temp->getDown() != NULL) {
			temp = temp->getDown();
			cout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}
		/*카테고리 노드를 getNext()*/
		temp1 = temp1->getNext();
	}

	fout.close();
	return 0;
}
//카테고리 이름을 인자로 받아서 카테고리에 포함되어있는 아이템을 출력
int CategoryList::I_PRINT(char* Category)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	int Check = 0;
	Node* temp = new CategoryNode;
	temp = cRoot;
	//정보가 존재하지 않을 경우
	if (temp == NULL) return 1;

	while (temp != NULL)
	{
		if (strcmp(temp->getCategory(), Category) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//찾는 카테고리가 없는 경우
	if (Check == 0) {
		fout.close();
		return 1;
	}
	//찾는 카테고리를 찾았을 때
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
	//노드가 아예 존재하지 않는 경우
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
			//메모장에 처음 쓸 떄
			if (temp1 == cRoot && temp->getUp() == cRoot) {
				ItemList << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice();
			}
			//메모장에 쓸 때 처음이 아닐 경우
			else ItemList << "\n" << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice();
			
		}

		temp1 = temp1->getNext();
	}
	
	ItemList.close();
}
