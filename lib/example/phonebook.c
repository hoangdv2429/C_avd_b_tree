#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_SIZE 1
#define INCREMENTAL_SIZE 1

typedef struct _Entry {
	void * key;
	void * value;
} Entry;

typedef struct _SymbolTable{
	Entry *entries;
	int size, total;
	Entry* (*makeNode)(void const *, void const *);
	int (*compare)(void const *, void const *);
} SymbolTable;


SymbolTable *createSymbolTable(
	Entry* (*makeNode)(void const *, void const *),
	int (*compare)(void const *, void const *)
)
{
	SymbolTable *symbolTable = (SymbolTable*)malloc(sizeof(SymbolTable));

	symbolTable->makeNode = makeNode;
	symbolTable->compare = compare;
	symbolTable->total = 0;
	symbolTable->size = INITIAL_SIZE;
	symbolTable->entries = malloc(INITIAL_SIZE*sizeof(Entry));

	return symbolTable;
}

void dropSymbolTable(SymbolTable* tab);

Entry* getEntry(void* key, SymbolTable *book){
	Entry *e;
	int i;
	for(i = 0; i < book->total; i++){
		e = ((book->entries+i));
		if(book->compare(key,e->key) == 0) return e;
	}
	return NULL;
}

void addEntry(void* key, void* value, SymbolTable *book){
	Entry *entry;
	entry = getEntry(key,book);

	if(entry != NULL){
		printf("overwriting.\n");
		memcpy(entry->value, value, sizeof(*value));
	}
	else{
		Entry *tempnode = (book->makeNode(key,value));
		book->total = book->total + 1;
		if(book->total == book->size) {
			book->size += INCREMENTAL_SIZE;
			book->entries = realloc(book->entries, (book->size)*sizeof(Entry));
		}

		*(book->entries+book->total-1) = *tempnode;
	}

}

Entry* makePhone(void const * name, void const * phone) {
	Entry *res = (Entry*)malloc(sizeof(Entry));
	res->key = strdup((char*)name);
	res->value =((long*)phone);
	return res;
}

int comparePhone(void const * key1, void const * key2) {
	if(strcmp((char*)key1, (char*)key2) < 0) return -1;
	else if(strcmp((char*)key1, (char*)key2) > 0) return 1;
	else return 0;
}

void entryPrint(Entry *entry){
	printf("%s\t%ld\n", (char*)entry->key, *(long*)entry->value);
}

int main(){
	SymbolTable *phoneBook = createSymbolTable(makePhone, comparePhone);

	long number = 988599345;
	char name[] = "Nguyen Van A";
	addEntry(name, &number, phoneBook);
	// number = 111111111;
	// addEntry(name, &number, phoneBook);
	

    long number1=966456788;
	char name1[] = "Nguyen Van B";
	addEntry(name1, &number1, phoneBook);

	long number2=985456095;
	char name2[] = "Nguyen Van C";
	addEntry(name2, &number2, phoneBook);

	long number3=933435456;
	char name3[] = "Nguyen Van D";
	addEntry(name3, &number3, phoneBook);

	printf("Size of phonebook %d\n", phoneBook->size);
	printf("Total element of phonebook %d\n", phoneBook->total);
    int i;
	for(i=0; i<phoneBook->total;i++){
		entryPrint(phoneBook->entries+i);
	}

	printf("Value of key 'Nguyen Van F' \n");
	Entry *e = getEntry("Nguyen Van F",phoneBook);
	if(e!=NULL) printf("%ld\n", *(long *)e->value);
    else
        printf("Khong ton tai key nay\n");

	printf("Value of key 'Nguyen Van C' \n");
	Entry *ef = getEntry("Nguyen Van C",phoneBook);
	if(ef!=NULL) printf("%ld\n", *(long *)ef->value);

	return 0;
}
