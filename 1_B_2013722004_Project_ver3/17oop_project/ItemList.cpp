#include "ItemList.h"

ItemList::ItemList(ofstream* fout) {
	this->fout = fout;
	iRoot = NULL;
}
//item.txt파일을 읽어서 물품들을 단일리스트로 연결
int ItemList::set(std::ifstream &fout)
{	
	char data[256] = { 0 };
	char *ItemName;
	int ItemCount;
	int ItemPrice;
	
	while (!fout.eof())
	{	
		fout.getline(data, sizeof(data));
		if (strcmp(data, "") == 0) return 1; // 메모장에 아무것도 존재하지 않을 때, return 1
		Node* newNode = new ItemNode;

		ItemName = strtok(data, " ");
		strtok(NULL, " ");
		ItemPrice = atoi(strtok(NULL, " "));
		ItemCount = atoi(strtok(NULL, " "));
		//새로운 Node의 데이터를 설정
		newNode->setName(ItemName);
		newNode->setPrice(ItemCount);
		newNode->setCount(ItemPrice);
		newNode->setNext(NULL);
		//iRoot가 비어있을 경우 iRoot는 새로운 node이다.
		if (iRoot == NULL) iRoot = newNode;
		//iRoot가 비어있지 않을 경우 정렬하고 삽입한다.
		else
		{
			Node* temp = new ItemNode;
			temp = iRoot;
			
			while (temp != NULL)
			{	
				//두번째 노드 삽입시
				if (temp->getNext() == NULL) 
				{
					//헤드보다 새로운 노드가 클 경우
					if (strcmp(temp->getName(), newNode->getName()) < 0)
					{
						//두번째 노드에 삽입
						temp->setNext(newNode);
						break;
					}
					//헤드보다 새로운 노드가 작을 경우
					else 
					{
						newNode->setNext(temp);
						iRoot = newNode;
						break;
					}
				}
				//노드가 여러개 존재할 경우
				else
				{	//헤드보다 새로운 노드가 클 경우
					if (strcmp(temp->getName(), newNode->getName()) < 0)
					{	//헤드 다음 노드가 새로운 노드보다 클 경우
						if (strcmp(temp->getNext()->getName(), newNode->getName()) > 0)
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
						iRoot = newNode;
						break;
					}
				}
			}	
		}
	}

	return 0; // 정상적으로 종료
}
//아이템 이름을 인자로 받아서 해당하는 Node를 리턴
Node* ItemList::Search(char* Item)
{	
	
	Node* temp = new ItemNode;
	temp = iRoot;
	//아이템 이름이 같으면 Node를 return
	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) {
			return temp;
		}
		temp = temp->getNext();
	}
	//없을 경우 temp Node를 return
	return temp;
}
//벡터에 넣어줄 ItemNode를 리턴한다
ItemNode* ItemList::V_Search(char* Item,int Count)
{
	ItemNode* Vtemp = new ItemNode;
	Node* temp = new ItemNode;
	temp = iRoot;//temp는 iRoot를 가리킨다.
	
	while (temp != NULL)
	{	//해당 Node를 찾은 경우
		if (strcmp(temp->getName(), Item) == 0) {
			if ((temp->getCount() - Count) < 0) return NULL; //수량이 0미만이 될 경우 NULL을 return
			//그렇지 않을 경우
			else {
				Vtemp->setName(temp->getName());
				Vtemp->setPrice(temp->getPrice());
				Vtemp->setCount(0);
				return Vtemp; //해당 Node의 데이터 정보를 저장해주고 return한다.
			}
		}

		temp = temp->getNext();
	}

	return NULL;
}
//ItemList에 새로운 Node를 ADD
int ItemList::I_ADD(char *Item, int Count, int Price)
{
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) { //똑같은 이름이 존재한다면 return1, error
			return 1;
		}
		temp = temp->getNext();
	}

	temp = iRoot;
	Node* newNode = new ItemNode;
	newNode->setName(Item);
	newNode->setCount(Count);
	newNode->setPrice(Price);
	//만약 iRoot가 NULL일 경우
	if (temp == NULL) {

			iRoot = newNode;
	}
	//iRoot가 NULL이 아니고 다른 정보가 존재할 경우
	else {

		while (temp != NULL)
		{
			//두번째 노드 삽입시
			if (temp->getNext() == NULL)
			{
				//헤드보다 새로운 노드가 클 경우
				if (strcmp(temp->getName(), newNode->getName()) < 0)
				{
					//두번째 노드에 삽입
					temp->setNext(newNode);
					break;
				}
				//헤드보다 새로운 노드가 작을 경우
				else
				{
					newNode->setNext(temp);
					iRoot = newNode;
					break;
				}
			}
			//노드가 여러개 존재할 경우
			else
			{	//헤드보다 새로운 노드가 클 경우
				if (strcmp(temp->getName(), newNode->getName()) < 0)
				{	//헤드 다음 노드가 새로운 노드보다 클 경우
					if (strcmp(temp->getNext()->getName(), newNode->getName()) > 0)
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
					iRoot = newNode;
					break;
				}
			}
		}
	}

	return 0;
}
//물품의 수량을 ADD
int ItemList::CountADD(char *Item, int Count)
{	
	int Check = 0;
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{
		if (strcmp(temp->getName(), Item) == 0) { //Item이름을 탐색
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//인자로 받은 Item을 탐색하지 못했을 경우 return 1
	if (Check == 0) return 1; // 물품이 존재하지 않는 경우
	//인자로 받은 Item을 탐색했을 경우 수량을 설정
	else if (Check == 1)
	{
		temp->setCount(Count + temp->getCount());
	}

	return 0;
}
//물품의 가격을 수정
int ItemList::P_MODIFY(char* Item, int Price)
{
	Node* temp = new ItemNode;
	temp = iRoot;
	int Check = 0;

	while (temp != NULL)
	{	//Item이름을 가지는 Node를 탐색한다.
		if (strcmp(temp->getName(), Item) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}
	//Node를 탐색하지 못한 경우 return 1, error
	if (Check == 0) return 1;
	//Node를 탐색했을 경우 가격을 설정
	else if (Check == 1) {
		
		temp->setPrice(Price);
	}

	return 0;
}
//물품 판매
int ItemList::I_SELL(char* Item, int Count)
{
	Node* temp = new ItemNode;
	temp = iRoot;
	int Check = 0;

	while (temp != NULL)
	{	//Item이름을 갖는 Node를 탐색한다.
		if (strcmp(temp->getName(), Item) == 0) {
			Check = 1;
			break;
		}
		temp = temp->getNext();
	}		
	//정상적으로 판매 된 경우
	temp->setCount(temp->getCount() - Count);

	return 0;
}
//판매된 물품의 가격을 얻어 오는 함수
int ItemList::g_Price(char* Item)
{
	Node* temp = new ItemNode;
	temp = iRoot;

	while (temp != NULL)
	{	//인자로 받은 Item이름을 갖는 Node를 탐색
		if (strcmp(temp->getName(), Item) == 0) {
			break;
		}
		temp = temp->getNext();
	}
	//가격을 return
	return temp->getPrice();
}
//물품을 탐색하는 함수
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
	//한개 문자를 비교할 경우
	if (StrCount == 1) {
		while (temp1 != NULL)
		{
			temp = temp1;
			I_Name = temp->getName();	//Item List에 저장된 Item이름
			
			if (I_Name[0] == Item[0]) { //맨처음 문자만 비교한다.
				OverLap = 1;
				ItemCount = temp->getCount();
				SellCount = temp->getPrice();

				while (1)
				{	//Category 이름을 찾기 위한 While문
					temp = temp->getUp();
					if (temp->getUp() == NULL) break;
				}
				cout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
				//로그에 기록
				fout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
			}

			temp1 = temp1->getNext();
		}
	}
	///문자열을 비교할 경우
	else {
		while (temp1 != NULL)
		{
			temp = temp1;
			I_Name = temp->getName();	//Item List에 저장된 Item이름
			len = strlen(I_Name);		//
			Count = 0;

			for (i = 0; i < len; i++) {
				//첫번 째 문자열을 찾은경우
				if (I_Name[i] == Item[0]) {
					Count = 0;	//첫번째 문자열을 찾은경우 인자의 길이만큼 비교해 준다. 다음 문자열이 같은지
					for (k = 0; k < StrCount; k++) {
						if (I_Name[i + k] == Item[k]) Count++;
					}
				}
			}
			//만약 비교했을 때 있다면
			if (StrCount == Count) {
				OverLap++;
				ItemCount = temp->getCount();
				SellCount = temp->getPrice();
				while (1)
				{	//Category 이름을 얻어오기 위해서
					temp = temp->getUp();
					if (temp->getUp() == NULL) break;
				}//해당 정보들을 출력
				cout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
				//해당 정보들을 Log에 기록
				fout << I_Name << " " << temp->getCategory() << " " << ItemCount << " " << SellCount << endl;
			}

			temp1 = temp1->getNext();
		}
	}

	fout.close();

	if (OverLap == 0)  return 1;

	return 0;
}
//물품 수량은 인자로 받아서 인자로 받은 수량 이하면 출력
int ItemList::C_MANAGE(int Count)
{	
	ofstream fout;
	fout.open("log.txt", ios::app);

	Node* temp = new ItemNode;
	Node* temp1 = new ItemNode;
	temp = iRoot;
	int Check = 0;
	//iRoot가 NULL일 경우
	if (iRoot == NULL) {
		fout.close();
		return 1; //물품이 존재하지 않을 때
	}

	while (temp != NULL)
	{	//인자로 들어온 수량 이하인것을 탐색한다.
		if (temp->getCount() <= Count) {
			temp1 = temp;
			Check++;
			//카테고리 노드를 찾는다.
			while (temp1->getUp() != NULL) {
				temp1 = temp1->getUp();
			}
			cout << temp->getName() << " " << temp1->getCategory() << " " << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp1->getCategory() << " " << temp->getName() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}

		temp = temp->getNext();
	}
	//탐색했을 때 해당하는게 없을 경우
	if (Check == 0) {
		fout.close();
		return 1;
	}

	fout.close();
	return 0;
}
//물품 수량과 바꿀 수량을 인자로 받아서 바꾸고 출력
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
		return 1; //물품이 존재하지 않을 때
	}

	while (temp != NULL)
	{	//수량 이하인 것을 탐색한다
		if (temp->getCount() <= Count) {
			temp1 = temp;
			Check++;
			//카테고리 노드를 찾는다.
			while (temp1->getUp() != NULL) {
				temp1 = temp1->getUp();
			}
			temp->setCount(temp->getCount() + ChangeCount); //실제 수량에 추가할 수량을 더해준다
			cout << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice() << endl;
			fout << temp->getName() << " " << temp1->getCategory() << " " << temp->getCount() << " " << temp->getPrice() << endl;
		}

		temp = temp->getNext();
	}
	//탐색하지 못한 경우
	if (Check == 0) {
		fout.close();
		return 1;
	}
	fout.close();
	return 0;
}
//Item이름을 인자로 받아서 해당 Node를 리턴한다.
Node* ItemList::Delete(char* item) {
	// 지우는 노드가 루트인 경우
	if (strcmp(iRoot->getName(), item) == 0) {
		Node* delNode = iRoot;

		// 루트를 다음 노드로 지정
		iRoot = iRoot->getNext();

		return delNode;
	}

	for (Node* temp = iRoot; temp->getNext(); temp = temp->getNext()) {
		// 지울 노드 발견하면
		if (!strcmp(temp->getNext()->getName(), item)) {
			Node* delNode = temp->getNext();

			// 지울 노드 전에 있는 노드가
			// 지울 노드 다음에 있는 노드를 가리키게 함
			// [.A.]->[.B.]->[.C.] ========>>> [.A.]->[.C.]
			temp->setNext(delNode->getNext());
			return delNode;
		}
	}

	return NULL;
}