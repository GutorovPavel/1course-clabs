struct List
{
	int size;
	struct Node* head;
};

struct Node
{
	struct Node* next;
	struct Node* prev;
	unsigned long long int accountNumber;
	char* name;
	char* surname;
	char* issuingAuthority;
	char* timeIn;
	char* timeExpired;
	char* passortSeries;
	struct Deposit* depHead;
	int depSize;
};

struct Deposit
{
	int balance;
	char* depositCategory;
	int isLock;
	struct Deposit* depNext;
};

struct Stack
{
	int level;
	struct Deposit* dep;
};

void push_back(char* depositCategory, char* name, char* surname, char* issuingAuthority, char* timeInn, char* timeExpired, char* passportSeries, int balance, struct List* list);
struct Node* FindAccount(struct Node* node, unsigned long long int accountNumber);
struct Deposit* findDeposit(struct Node* node, const int index);
int GetSize(struct List* list);
void ShowDeposit(struct Node* node);
void showNode(struct List* list);
void FindSurname(struct Node* node, const char* surname);
struct Node* GetNode(struct List* list, const int index);
void freeList(struct List* list);
void sort(struct Node* node);
void print(struct Node* node);
struct Node* AddDeposit(struct Node* node, char* passportSeries, char* depositCategory, int balance);
int pop(struct List* list, const char* passportSeries, const int index);

