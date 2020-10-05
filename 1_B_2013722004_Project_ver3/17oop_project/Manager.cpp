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
/*�޸��忡�� ������ �ҷ��ͼ� ����Ʈ�� �����Ѵ�*/
bool Manager::LOAD()
{
	fout << "[LOAD]" << endl;

	char data[256] = { 0 };
	char* C_Name;
	char* I_Name;
	Node* CNode;
	Node* INode;

	//item.txt������ �д´�.
	ifstream ItemInfo;
	ItemInfo.open("item.txt");

	if (ItemInfo.fail()) {
		fout << "success" << endl << endl;
		return true;
	}
	//item.txt�� ������ �ִٸ�
	if (iList->set(ItemInfo) == 0)
	{
		//ItemList�� Category List�� ���ϸ���Ʈ�� ���� ��������ش�.
		ItemInfo.close();
		ItemInfo.open("item.txt");
		cList->set(ItemInfo);
		ItemInfo.close();

		//ItemList�� Category List�� ����� ���Ḯ��Ʈ�� Up, Donw ����
		ItemInfo.open("item.txt");
		while (!ItemInfo.eof())
		{
			ItemInfo.getline(data, sizeof(data));
			I_Name = strtok(data, " ");
			C_Name = strtok(NULL, " ");
			strtok(NULL, " ");
			strtok(NULL, " ");

			CNode = cList->Search(C_Name); // Category Node�� �޾Ҵ�.
			INode = iList->Search(I_Name); // Item Node�� �޾Ҵ�.
			cList->setUpDown(CNode, INode);// ī�װ� ���� �����۳�带 ����
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
/*���ڰ� 4�� ���� ��� ���� �߰�*/
/*���ڰ� 2�� ���� ��� ��ǰ���� ã�Ƽ� ������ �����ش�.*/
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

	//ADD ��ɾ ���ڵ��� Copy�Ѵ�.
	strcpy(cpy_arg, arg);
	//ADD ��ɾ ���� ������ ������ ����.
	strtok(arg, " ");
	Argc_count = 1;
	while (1)
	{
		if (strtok(NULL, " ") == NULL) break;
		Argc_count++;
	}
	
	//ADD�� ���ڰ� 4�� ���� ���, ���� �߰��Ѵ�.
	if (Argc_count == 4) {
		IName = strtok(cpy_arg, " ");
		CName = strtok(NULL, " ");
		Count = atoi(strtok(NULL, " "));
		Price = atoi(strtok(NULL, " '"));
		if (iList->I_ADD(IName, Count, Price) == 1) { //return ���� 1�̸� �̹� �����ϴ� ��, error
			fout << "error" << endl << endl;
			return false;
		}
		else {//��ǰ�� �������� �ʴ� ���
			cList->ADD(CName);
			CNode = cList->Search(CName); // Category Node�� �޾Ҵ�.
			INode = iList->Search(IName); // Item Node�� �޾Ҵ�.
			cList->setUpDown(CNode, INode);// ī�װ� ���� ����� ����Ʈ�� �����۳�带 ����
		}
	}
	//ADD�� ���ڰ� 2��(��ǰ��� ������ ���� ���)
	else if (Argc_count == 2) {
		IName = strtok(cpy_arg, " ");
		Count = atoi(strtok(NULL, " "));
		if (iList->CountADD(IName, Count) == 1) { //return ���� 1�̸� ��ǰ���� ã�� ���� ���, error
			fout << "error" << endl << endl;
			return false;
		}
	}
	
	fout << "success" << endl << endl;

	return true;
}
/*MODIFY*/
/*���ڷ� ��ǰ��� ������ ���´� ã�� ��ǰ���� ã�Ƽ� ������ �����Ѵ�.*/
bool Manager::MODIFY(char * arg)
{	
	fout << "[MODIFY]" << endl;
	char* IName;
	int Price = 0;
	char cpy_arg[256] = { 0 };
	strcpy(cpy_arg, arg);

	IName = strtok(cpy_arg, " ");
	Price = atoi(strtok(NULL, " "));
	if (iList->P_MODIFY(IName, Price) == 1) { //return ���� 1�̸� ã�� ��ǰ���� ���� ���, error
		fout << "error" << endl << endl;
		return false;
	}
	//������ �α� ���
	fout << "success" << endl << endl;
	return true;
}
/*SELL*/
/*��ǰ�� �Ǹ��ϴ� ��ɾ�*/
/*��ǰ�� ã�Ƽ� �Ǹ��ϰ� ������ �����ϰ� sell.txt�� ����*/
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
	//���� ��ǰ������ �Ǹż����� ���� ������ �Ǿ��� ��� return false, error
	if ((temp = iList->V_Search(IName, Count)) == NULL) {
		fout << "error" << endl << endl;
		return false;
	}
	//�Ǹż��� ���� ( ������ŭ ���� �����͸� ���� )
	temp->setCount(Count);
	//ItemNode�� Vector�� ����, ���Ϳ� �ƹ��͵� �������� ���� ���
	if (vItem.size() == 0) vItem.push_back(temp);
	//���Ϳ� ������ �� ���ݼ����� �����ϸ鼭 ����, ���� ������ ���ٸ� �̸������� ����
	else {
		vector<ItemNode*>::iterator iter;
		//���� ���� Item�̸��� ���ϸ鼭 �����ϸ鼭 ����
		for (iter = vItem.begin(); iter != vItem.end(); iter++) {
			//iter�� ����Ű�� Node�� �Ǹż������� ���� ���� ���Ϳ� �Ǹż����� �� Ŭ ���
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
			//�Ǹ� ������ ���� ���
			else if (((*iter)->getPrice() * (*iter)->getCount()) == (temp->getPrice() * temp->getCount())) {
				//�̸��� ��, ���� ������ Vector�� �̸� ũ�Ⱑ �� ū���
				if (strcmp((*iter)->getName(), temp->getName()) < 0) {
					if (iter + 1 == vItem.end()) {
						vItem.push_back(temp);
						break;
					}
				}
				//�̸��� ��, ���� ������ Vector�� �̸� ũ�Ⱑ �� ���� ���
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


	//sell.txt�� ���� ����
	ifstream SellInfo;
	SellInfo.open("sell.txt");
	SellInfo.getline(Data, sizeof(Data));

	CName = cList->C_Search(IName); // Category �̸��� �޾Ҵ�.
	Price = iList->g_Price(IName); //������ �޾ƿ´�.
	iList->I_SELL(IName, Count); //��ǰ ������ �����Ѵ�.
	//�޸��忡 ù�ٿ� ����
	if (strcmp(Data, "") == 0) {
		SellInfo.close();
		ofstream SellInfo;
		SellInfo.open("sell.txt", ios::app);
		SellInfo << IName << " " << CName << " " << Count * Price;
		SellInfo.close();
	}
	else { //�޸��忡 ù���� ���� �� ���๮�ڿ� �Բ� ����.
		SellInfo.close();
		ofstream SellInfo;
		SellInfo.open("sell.txt", ios::app);
		SellInfo << "\n" << IName << " " << CName << " " << Count * Price;
		SellInfo.close();
	}
	//������ �α� ���
	fout << "success" << endl << endl;
	return true;
}
/*DELETE*/
/*��ǰ���� ã�Ƽ� �ش� Node�� �����ϴ� ��ɾ�*/
/*ī�װ��� �Ѱ��� �����۸� �����Ѵٸ� ī�װ��� ����*/
bool Manager::DELETE(char * arg)
{	
	fout << "[DELETE]" << endl;

	char* IName;
	char cpy_arg[256] = { 0 };

	strcpy(cpy_arg, arg);
	IName = strtok(cpy_arg, " ");

	 if (iList->Delete(IName)) { //Item ��ǰ�� Ž������ �� �����ϴ� ���
      delete cList->Delete(IName);//�޸� ���� �� Node����
	  fout << "success" << endl << endl; //������ ��� return true, �α� ���
      return true;
   }

	 fout << "error" << endl << endl;
	//��ǰ�� Ž������ ���� ��� false�� ��ȯ, error
   return false;
}
/*SEARCH*/
/*���ڷ� ���� ���ڿ��� SEARCH�ؼ� �ش��ϴ� ITEM���� ��� ã�Ƽ� ���*/
bool Manager::SEARCH(char * arg)
{
	fout << "[SEARCH]" << endl;
	char cpy_arg[256] = { 0 };
	char* IName;

	strcpy(cpy_arg, arg);
	IName = strtok(cpy_arg, " ");

	if (iList->I_SEARCH(IName) == 1) {
		//return ���� 1�̸� ��ǰ���� ã�� ���� ���, no result ���
		cout << "no result" << endl;
		fout << "no result" << endl << endl;
		return false;
	}
	fout << endl;
	return true;
}
/*PRINT*/
/*���ڰ� ���ٸ� ī�װ��� �ش� ī�װ��� �����۵��� ���*/
/*���ڰ� �ִٸ� �ش��ϴ� ī�װ��� �����۵��� ���*/
bool Manager::PRINT(char* arg)
{
	fout << "[PRINT]" << endl;
	//���ڰ� ���� ��� ��� ī�װ� �� ������ ���
	if (strcmp(arg, "\0") == 0) {
		if (cList->ALL_PRINT() == 1) {
			fout << "no result" << endl << endl;
			return false;
		}
	}
	//���ڰ� �ִ� ���(ī�װ��� ���ڷ� �޴´�)
	else {
		char cpy_arg[256] = { 0 };
		char* CName;

		strcpy(cpy_arg, arg);
		CName = strtok(cpy_arg, " ");

		if (cList->I_PRINT(CName) == 1) {//return���� 1�̸� �ش� ī�װ��� ã�� ���� ����̴�. no result ���
			fout << "no result" << endl << endl;
			return false;
		}
	}
	fout << endl;
	return true;
}
/*MANAGE*/
/*���ڰ� �Ѱ��� ��� ���� ���� ���ϵ��� ���*/
/*���ڰ� �ΰ��� ��� ���� ���� ���ϵ��� ���� ������ŭ �߰�*/
bool Manager::MANAGE(char * arg)
{
	fout << "[MANAGE]" << endl;
	char cpy_arg[256] = { 0 };
	int Argc_count = 0;
	int Count = 0; // ��ǰ ����
	int ChangeCount = 0; //��ǰ ������ �ٲ� ����

	strcpy(cpy_arg, arg);
	strtok(arg, " ");
	Argc_count = 1;

	//���� ������ üũ
	while (1)
	{
		if (strtok(NULL, " ") == NULL) break;
		Argc_count++;
	}
	//���ڰ����� �ϳ��� ���
	if (Argc_count == 1) {
		
		Count = atoi(strtok(cpy_arg, " "));
		if (iList->C_MANAGE(Count) == 1) { //return ���� 1�̸� ��ǰ���� ã�� ���� ���, no result
			cout << "no result" << endl;
			fout << "no result" << endl << endl;
			return false;
		}

	}
	//���ڰ����� �ΰ��� ���
	else if (Argc_count == 2) {

		Count = atoi(strtok(cpy_arg, " "));
		ChangeCount = atoi(strtok(NULL, " "));
		if (iList->I_MANAGE(Count, ChangeCount) == 1) { //return ���� 1�̸� ��ǰ���� ã�� ���� ���, no result
			cout << "no result" << endl;
			fout << "no result" << endl << endl;
			return false;
		}
	}
	fout << endl;
	return true;
}
/*SALES*/
/*�Ǹž� ������ ����ϴ� ��ɾ�*/
/*���ڷ� Rank�� �޴´�. Rank�� ������ ��� error, 0�� ��� no result*/
bool Manager::SALES(char * arg)
{	
	fout << "[SALES]" << endl;

	int rank = 0;
	int total = 0;
	//Rank��
	rank = atoi(arg);
	/*rank�� 0���� �ΰ�� error*/
	if (rank <= 0) {
		fout << "error" << endl << endl;
		return false;
	}

	//���Ϳ� ������ ���� ���, no result
	if (vItem.size() == 0) {
		fout << "no result" << endl << endl;
		return false;
	}
	//���� ����� Rank���� ������� �����ϴ� ���Ϳ� �������� ��� ����ϸ� �ȴ�.
	if (rank > vItem.size()) {
		vector<ItemNode*>::iterator iter;
		for (iter = vItem.begin(); iter != vItem.end(); iter++) {
			cout << (*iter)->getName() << " " << cList->C_Search((*iter)->getName()) << " " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			total = total + (*iter)->getCount() * (*iter)->getPrice();
			//�α����Ͽ� ���
			fout << (*iter)->getName() << " - " << (*iter)->getCount() * (*iter)->getPrice() << endl;
		}
		cout << "Total - " << total << endl;
		fout << "Total - " << total << endl;
	}
	//Rank�� ���� ������ ���� ���� ���
	else {
		vector<ItemNode*>::iterator iter;
		iter = vItem.begin();
		while (rank) {
			cout << (*iter)->getName() << " " << cList->C_Search((*iter)->getName()) << " " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			//�α� ���Ͽ� ���
			fout << (*iter)->getName() << " - " << (*iter)->getCount() * (*iter)->getPrice() << endl;
			total = total + (*iter)->getCount() * (*iter)->getPrice();
			rank--;
			iter = iter + 1;
		}
		//Total �ǸŰ��� ��� �� ���
		cout << "Total - " << total << endl;
		fout << "Total - " << total << endl;
	}
	fout << endl;
	return true;
}
/*SAVE*/
/*����Ʈ�� ����*/
bool Manager::SAVE()
{	//Save�� ������ success���
	cList->SAVE();
	fout << "[SAVE]" << endl;
	fout << "success" << endl << endl;
	return true;
}