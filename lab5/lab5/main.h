#ifndef MAIN_H
#define MAIN_H

void CheckPtr(void* ptr);
void CopyFromBuffer(char** buffer, char*** str, int* const length, int* const n);
int ReadStr(char** str);
short Palindrom(char** str, int n);

#endif
