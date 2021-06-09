unsigned long long int hashing(char* key);
void ShowHistory(unsigned long long int account);
double GetPercent(int sum, const char* from, const char* to);
char* toString(unsigned long long int account);
void GetBalance(struct List* list, unsigned long long int accountNumber);
void GetMoney(struct List* list, unsigned long long int accountNumber, int sum);
void transfer(struct List* list, unsigned long long int from, unsigned long long int to, int sum);
void PutMoney(struct List* list, unsigned long long int accountNumber, int sum);