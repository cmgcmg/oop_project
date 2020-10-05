#include "Manager.h"

Manager::Manager()
{
	fout.open("log.txt", ios::app);
	cList = new CategoryList(&fout);
	iList = new ItemList(&fout);
}

Manager::~Manager()
{
	/* write your code */
	//delete cList;
	//delete iList;
}

void Manager::run(const char* fileName)
{
	ifstream fin;
	fin.open(fileName);

	if (!fin) {
		cout << "[OPEN]" << endl << "error" << endl;
		return;
	}

	char cmd[64] = { 0 };
	char arg[64] = { 0 };

	bool isWork = true;	

	while (!fin.eof())
	{
		fin >> cmd;
		fin.getline(arg, 64);

		if		(!strcmp(cmd, "LOAD"))		{	isWork = LOAD();		}
		else if (!strcmp(cmd, "ADD"))		{	isWork = ADD(arg);		}
		else if (!strcmp(cmd, "MODIFY"))	{	isWork = MODIFY(arg);	}
		else if (!strcmp(cmd, "SELL"))		{	isWork = SELL(arg);		}
		else if (!strcmp(cmd, "DELETE"))	{	isWork = DELETE(arg);	}
		else if (!strcmp(cmd, "SEARCH"))	{	isWork = SEARCH(arg);	}
		else if (!strcmp(cmd, "PRINT"))		{	isWork = PRINT(arg);	}
		else if (!strcmp(cmd, "MANAGE"))	{	isWork = MANAGE(arg);	}
		else if (!strcmp(cmd, "SALES"))		{	isWork = SALES(arg);	}
		else if (!strcmp(cmd, "SAVE"))		{	isWork = SAVE();		}
		else								{	isWork = false;			}

		cout << "[" << cmd << "]" << endl;

		if (isWork == false) {
			cout << "error" << endl << endl;
		}		
	}	
	
	fin.close();
}
/*LOAD*/
/*메모장에서 정보를 불러와서 리스트를 생성한다*/
bool Manager::LOAD()
{
	fout << "[LOAD]" << endl;

	char data[256] = { 0 };
	char* C_Name;
	char* I_Name;
	Node* CNode;
	Node* INode;

	//item.txt파일을 읽는다.
	ifstream ItemInfo;
	ItemInfo.open("item.txt");

	if (ItemInfo.fail()) {
		fout << "success" << endl << endl;
		return true;
	}
	//item.txt에 정보가 있다면
	if (iList->set(ItemInfo) == 0)
	{
		//ItemList와 Category List를 단일리스트로 먼저 연결시켜준다.
		ItemInfo.close();
		ItemInfo.open("item.txt");
		cList->set(ItemInfo);
		ItemInfo.close();

		//ItemList와 Category List를 양방향 연결리스트로 Up, Donw 연결
		ItemInfo.open("item.txt");
		while (!ItemInfo.eof())
		{
			ItemInfo.getline(data, sizeof(data));
			I_Name = strtok(data, " ");
			C_Name = strtok(NULL, " ");
			strtok(NULL, " ");
			strtok(NULL, " ");

			CNode = cList->Search(C_Name); // Category Node를 받았다.
			INode = iList->Search(I_Name); // Item Node를 받았다.
			cList->setUpDown(CNode, INode);// 카테고리 노드와 아이템노드를 연결
		}
		ItemInfo.close();

	}
	else {
		fout << "success" << endl << endl;
		return true;
	}

	fout << "success" << endl << endl;
	return true;
}
/*ADD*/
/*인자가 4개 들어올 경우 새로 추가*/
/*인자가 2개 들어올 경우 물품명을 찾아서 수량을 더해준다.*/
bool Manager::ADD(char * arg)
{	
	fout << "[ADD]" << endl;
	char *IName;
	char *CName;
	int Price = 0;
	int Count = 0;
	char cpy_arg[256] = { 0 };
	int Argc_count = 0;
	Node* CNode;
	Node* INode;

	//ADD 명령어에 인자들을 Copy한다.
	strcpy(cpy_arg, arg);
	//ADD 명령어에 들어온 인자의 개수를 센다.
	strtok(arg, " ");
	Argc_count = 1;
	while (1)
	{
		if (strtok(NULL, " ") == NULL) break;
		Argc_count++;
	}
	
	//ADD에 인자가 4개 들어올 경우, 새로 추가한다.
	if (Argc_count == 4) {
		IName = strtok(cpy_arg, " ");
		CName = strtok(NULL, " ");
		Count = atoi(strtok(NULL, " "));
		Price = atoi(strtok(NULL, " '"));
		if (iList->I_ADD(IName, Count, Price) == 1) { //return 값이 1이면 이미 존재하는 것, error
			fout << "error" << endl << endl;
			return false;
		}
		else {//물품이 존재하지 않는 경우
			cList->ADD(CName);
			CNode = cList->Search(CName); // Category Node를 받았다.
			INode = iList->Search(IName); // Item Node를 받았다.
			cList->setUpDown(CNode, INode);// 카테고리 노드와 양방향 리스트로 아이템노드를 연결
		}
	}
	//ADD에 인자가 2개(물품명과 수량이 들어올 경우)
	else if (Argc_count == 2) {
		IName = strtok(cpy_arg, " ");
		Count = atoi(strtok(NULL, " "));
		if (iList->CountADD(IName, Count) == 1) { //return 값이 1이면 물품명을 찾지 못한 경우, error
			fout << "error" << endl << endl;
			return false;
		}
	}
	
	fout << "success" << endl << endl;

	return true;
}
/*MODIFY*/
/*인자로 물품명과 가격이 들어온다 찾는 물품명을 찾아서 가격을 수정한다.*/
bool Manager::MODIFY(char * arg)
{	
	fout << "[MODIFY]" << endl;
	char* IName;
	int Price = 0;
	char cpy_arg[256] = { 0 };
	strcpy(cpy_arg, arg);

	IName = strtok(cpy_arg, " ");
	Price = atoi(strtok(NULL, " "));
	if (iList->P_MODIFY(IName, Price) == 1) { //return 값이 1이면 찾는 물품명이 없는 경우, error
		fout << "error" << endl << endl;
		return false;
	}
	//성공시 로그 기록
	fout << "success" << endl << endl;
	return true;
}
/*SELL*/
/*물품을 판매하는 명령어*/
/*물품을 찾아서 판매하고 수량을 수정하고 sell.txt에 저장*/
bool Manager::SELL(char * arg)
{	
	fout << "[SELL]" << endl;
	char* IName;
	char* CName;
	int Count = 0;
	int Price = 0;
	char cpy_arg[256] = { 0 };
	char Data[256] = { 0 };
	ItemNode* temp = new ItemNode;
	strcpy(cpy_arg, arg);

	IName = strtok(cpy_arg, " ");
	Count = atoi(strtok(NULL, " "));
	//원래 물품수량에 판매수량을 빼서 음수가 되었을 경우 return false, error
	if ((temp = iList->V_Search(IName, Count)) == NULL) {
		fout << "error" << endl << endl;
		return false;
	}
	//판매수량 설정 ( 수량만큼 빼서 데이터를 수정 )
	temp->setCount(Count);
	//ItemNode를 Vector에 삽입, 벡터에 아무것도 존재하지 않을 경우
	if (vItem.size() == 0) vItem.push_back(temp);
	//벡터에 삽입할 때 가격순으로 정렬하면서 삽입, 만약 가격이 같다면 이름순으로 삽입
	else {
		vector<ItemNode*>::iterator iter;
		//벡터 내에 Item이름과 비교하면서 정렬하면서 삽입
		for (iter = vItem.begin(); iter != vItem.end(); iter++) {
			//iter가 가리키는 Node의 판매수량보다 새로 들어올 벡터에 판매수량이 더 클 경우
			if (((*iter)->getPrice() * (*iter)->getCount()) < (temp->getPrice() * temp->getCount())) {
				vItem.insert(iter, temp);
				break;
			}
			else if (((*iter)->getPrice() * (*iter)->getCount()) > (temp->getPrice() * temp->getCount())) {
				if (iter + 1 == vItem.end()) {
					vItem.push_back(temp);
					break;
				}
			}
			//판매 수량이 같을 경우
			else if (((*iter)->getPrice() * (*iter)->getCount()) == (temp->getPrice() * temp->getCount())) {
				//이름을 비교, 새로 들어오는 Vector의 이름 크기가 더 큰경우
				if (strcmp((*iter)->getName(), temp->getName()) < 0) {
					if (iter + 1 == vItem.end()) {
						vItem.push_back(temp);
						break;
					}
				}
				//이름을 비교, 새로 들어오는 Vector의 이름 크기가 더 작은 경우
				else {
					vItem.insert(iter, temp);
					break;
				}
			}
		}
	}
	vector<ItemNode*>::iterator iter;
	for (iter = vItem.begin(); iter != vItem.end(); iter++) {
		cout << (*iter)->getName() << endl;
	}


	//sell.txt에 쓰는 과정
	ifstream SellInfo;
	SellInfo.open("sell.txt");
	SellInfo.getline(Data, sizeof(Data));

	CName = cList->C_Search(IName); // Category 이름을 받았다.
	Price = iList->g_Price(IName); //가격을 받아온다.
	iList->I_SELL(IName, Count); //물품 수량을 수정한다.
	//메모장에 첫줄에 쓸때
	if (strcmp(Data, "") == 0) {
		SellInfo.close();
		ofstream SellInfo;
		SellInfo.open("sell.txt", ios::app);
		SellInfo << IName << " " << CName << " " << Count * Price;
		SellInfo.close();
	}
	else { //메모장에 첫줄이 있을 때 개행문자와 함께 쓴다.
		SellInfo.close();
		ofstream SellInfo;
		SellInfo.open("sell.txt", ios::app);
		SellInfo << "\n" << IName << " " << CName << " " << Count * Price;
		SellInfo.close();
	}
	//성공시 로그 기록
	fout << "success" << endl << endl;
	return true;
}
/*DELETE*/
/*물품명을 찾아서 해당 Node를 삭제하는 명령어*/
/*카테고리에 한개의 아이템만 존재한다면 카테고리도 삭제*/
bool Manager::DELETE(char * arg)
{	
	fout << "[DELETE]" << endl;

	char* IName;
	char cpy_arg[256] = { 0 };

	strcpy(cpy_arg, arg);
	IName = strtok(cpy_arg, " ");

	 if (iList->Delete(IName)) { //Item 물품을 탐색했을 때 존재하는 경우
      delete cList->Delete(IName);//메모리 해제 및 Node삭제
	  fout << "success" << endl << endl; //삭제된 경우 return true, 로그 기록
      return true;
   }

	 fout << "error" << endl << endl;
	//물품을 탐색하지 못한 경우 false를 반환, error
   return false;
}
/*SEARCH*/
/*인자로 들어온 문자열을 SEARCH해서 해당하는 ITEM들을 모두 찾아서 출력*/
bool Manager::SEARCH(char * arg)
{
	fout << "[SEARCH]" << endl;
	char cpy_arg[256] = { 0 };
	char* IName;

	strcpy(cpy_arg, arg);
	IName = strtok(cpy_arg, " ");

	if (iList->I_SEARCH(IName) == 1) {
		//return 값이 1이면 물품명을 찾지 못한 경우, no result 기록
		cout << "no result" << endl;
		fout << "no result" << endl << endl;
		return false;
	}
	fout << endl;
	return true;
}
/*PRINT*/
/*인자가 없다면 카테고리와 해당 카테고리의 아이템들을 출력*/
/*인자가 있다면 해당하는 카테고리에 아이템들을 출력*/
bool Manager::PRINT(char* arg)
{
	fout << "[PRINT]" << endl;
	//인자가 없는 경우 모든 카테고리 및 아이템 출력
	if (strcmp(arg, "\0") == 0) {
		if (cList->ALL_PRINT() == 1) {
			fout << "no result" << endl << endl;
			return false;
		}
	}
	//인자가 있는 경우(카테고리를 인자로 받는다)
	else {
		char cpy_arg[256] = { 0 };
		char* CName;

		strcpy(cpy_arg, arg);
		CName = strtok(cpy_arg, " ");

		if (cList->I_PRINT(CName) == 1) {//return값이 1이면 해당 카테고리를 찾지 못한 경우이다. no result 기록
			fout << "no result" << endl << endl;
			return false;
		}
	}
	fout << endl;
	return true;
}
/*MANAGE*/
/*인자가 한개일 경우 인자 수량 이하들을 출력*/
/*인자가 두개일 경우 인자 수량 이하들을 인자 수량만큼 추가*/
bool Manager::MANAGE(char * arg)
{
	fout << "[MANAGE]" << endl;
	char cpy_arg[256] = { 0 };
	int Argc_count = 0;
	int Count = 0; // 물품 수량
	int ChangeCount = 0; //물품 수량을 바꿀 변수

	strcpy(cpy_arg, arg);
	strtok(arg, " ");
	Argc_count = 1;

	//인자 개수를 체크
	while (1)
	{
		if (strtok(NULL, " ") == NULL) break;
		Argc_count++;
	}
	//인자개수가 하나일 경우
	if (Argc_count == 1) {
		
		Count = atoi(strtok(cpy_arg, " "));
		if (iList->C_MANAGE(Count) == 1) { //return 값이 1이면 물품명을 찾지 못한 경우, no result
			cout << "no result" << endl;
			fout << "no result" << endl << endl;
			return false;
		}

	}
	//인자개수가 두개일 경우
	else if (Argc_count == 2) {

		Count = atoi(strtok(cpy_arg, " "));
		ChangeCount = atoi(strtok(NULL, " "));
		if (iList->I_MANAGE(Count, ChangeCount) == 1) { //return 값이 1이면 물품명을 찾지 못한 경우, no result
			cout << "no result" << endl;
			fout << "no result" << endl << endl;
			return false;
		}
	}
	fout << endl;
	return true;
}
/*SALES*/
/*판매액 순위를 출력하는 명령어*/
/*인자로 Rank를 받는다. Rank가 음수일 경우 error, 0일 경우 no result*/
bool Manager::SALES(char * arg)
{	
	fout << "[SALES]" << endl;

	int rank = 0;
	int total = 0;
	//Rank값
	rank = atoi(arg);
	/*rank가 0이하 인경우 error*/
	if (rank <= 0) {
		fout << "error" << endl << endl;
		return false;
	}

	//벡터에 정보가 없을 경우, no result
	if (vItem.size() == 0) {
		fout << "no result" << endl << endl;
		return false;
	}
	//벡터 사이즈가 Rank보다 작을경우 존재하는 벡터에 정보들을 모두 출력하면 된다.
	if (rank > vItem.size()) {
		vector<ItemNode*>::iterator iter;
		for (iter = vItem.begin(); iter != vItem.end(); iter++) {
			cout << (*iter)->getName() << " " << cList->C_Search((*iter)->getName()) << " " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			total = total + (*iter)->getCount() * (*iter)->getPrice();
			//로그파일에 기록
			fout << (*iter)->getName() << " - " << (*iter)->getCount() * (*iter)->getPrice() << endl;
		}
		cout << "Total - " << total << endl;
		fout << "Total - " << total << endl;
	}
	//Rank가 벡터 사이즈 보다 작은 경우
	else {
		vector<ItemNode*>::iterator iter;
		iter = vItem.begin();
		while (rank) {
			cout << (*iter)->getName() << " " << cList->C_Search((*iter)->getName()) << " " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			//로그 파일에 기록
			fout << (*iter)->getName() << " - " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			total = total + (*iter)->getCount() * (*iter)->getPrice();
			rank--;
			iter = iter + 1;
		}
		//Total 판매가격 출력 및 기록
		cout << "Total - " << total << endl;
		fout << "Total - " << total << endl;
	}
	fout << endl;
	return true;
}
/*SAVE*/
/*리스트를 저장*/
bool Manager::SAVE()
{	//Save후 무조건 success기록
	cList->SAVE();
	fout << "[SAVE]" << endl;
	fout << "success" << endl << endl;
	return true;
}