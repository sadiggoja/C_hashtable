#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LLNode
{
    char *fName;
    int nmb;
    struct LLNode *pNext;
};

struct HashTable
{
    int size;
    struct LLNode **table;
};

struct LLNode *LL_new(char *name)
{
	//char temp[50];
	//char *temp=(char *)malloc(sizeof(char));
	//strcpy(temp, name);
    struct LLNode *newNode = (struct LLNode *)
        malloc(sizeof(struct LLNode));
    //temp=name;
	//printf("%s\n",temp );     
	//printf("%s\n", name );   
    newNode->fName = name;
    newNode->pNext = NULL;
    newNode->nmb = 1;
    return newNode;
}

void LL_add(struct LLNode **ppHead, char *name)
{
	//char b[100];
	//strcpy(b, name);	
	//printf("%s is in add\n",name);	
    struct LLNode * temp = (*ppHead);
    int c = 0;
    while(temp != NULL) {
        if(strcmp(temp->fName, name) == 0) {
            temp->nmb++;
            c++;
            break;
        }
        temp = temp->pNext;
    }
    if(c == 0) {
        struct LLNode *newNode = LL_new(name);
        newNode->pNext = *ppHead;
        *ppHead = newNode;
    }
    //printf("%s is head\n",(*ppHead)->fName );
    //printf("%s IS IN NODE\n",name );
}

void LL_print(struct LLNode *pHead)
{
    if (pHead == NULL)
    {
        puts("");
        return;
    }

    while (pHead != NULL)
    {
        printf("[%s] => ",
               pHead->fName);
        pHead = pHead->pNext;
    }
    puts("");
}

void LL_print_hist(struct LLNode *pHead)
{
    if (pHead == NULL)
    {
        puts("");
        return;
    }

    while (pHead != NULL)
    {
        printf("* ");
        pHead = pHead->pNext;
    }
}

void LL_remove(struct LLNode **ppHead, char *name)
{
    if (*ppHead == NULL)
    {
        return;
    }

    if (strcmp((*ppHead)->fName, name) == 0)
    {
        *ppHead = (*ppHead)->pNext;
        return;
    }

    //complete
    while ((*ppHead)->pNext != NULL)
    {
        if (strcmp((*ppHead)->pNext->fName, name) == 0)
        {
            (*ppHead)->pNext = (*ppHead)->pNext->pNext;
            break;
        }
    }
}

struct HashTable *HASH_new(int size)
{
    struct HashTable *hashTable =
        (struct HashTable *)
            malloc(sizeof(struct HashTable));

    hashTable->size = size;
    hashTable->table =
        (struct LLNode **)
            malloc(size * sizeof(struct LLNode *));

    int i;
    for (i = 0; i < size; i++)
    {
        hashTable->table[i] = NULL;
    }

    return hashTable;
}

int HASH_hash(struct HashTable *hT, char *fName)
{
    if (hT == NULL || hT->size <= 0)
        return -1;
    int index;
    for (index = 0; *fName != '\0'; fName++)
    {
        index = (index * 256 + (int)(*fName)) % hT->size;
    }
    //added!!!
    // for (; *lName != '\0'; lName++)
    // {
    //     index = (index * 256 + (int)(*lName)) % hT->size;
    // }

    return index;
}

void HASH_add(struct HashTable *hT, char *fName)
{
	//printf("%s is added\n", fName );
    if (hT == NULL || hT->size <= 0)
        return;

    int index = HASH_hash(hT, fName);
    //printf("%d\n",index );
    LL_add(&(hT->table[index]), fName);
}

void HASH_print(struct HashTable *hT)
{
    int i;
    for (i = 0; i < hT->size; i++)
    {
        printf("[%d]:", i);
        LL_print(hT->table[i]);
    }
}

struct LLNode *HASH_search(struct HashTable *hT, char *name)
{
    int index = HASH_hash(hT,name); //incomplete


//    hT->table[index] Linked List
}

char *extrasymbols(char *name){
	int count=0;
	int c=0;
	char *newstr=(char *)malloc(50*sizeof(char));
	while(name[count]!='\0'){
		if (name[count]<='Z' && name[count]>='A' || name[count]>='a' && name[count]<='z')
		{
			newstr[c]=name[count];
			c++;
		}
		count++;
	}
	newstr[c]='\0';
	//printf("%s\n", newstr);
	return newstr;
}
void HT_mostFrequent(struct HashTable * hT) {
    char * word  = (char*)calloc(hT->size*2, sizeof(char));
    int frequency=0;
    for(int i = 0; i < hT->size; i++) {
        struct LLNode * ppNode = hT->table[i];
        while( ppNode != NULL) {
            if(ppNode->nmb  > frequency) {
                frequency = ppNode->nmb;
                word = ppNode->fName;
            }
            ppNode = ppNode->pNext;
        } 
    }
    printf("%s is most used word %d times\n", word, frequency);
}


int nbOfDistinct(struct HashTable * hT) {
    int counter = 0;

    for(int i = 0; i < hT->size; i++) {
        struct LLNode * ppNode = hT->table[i];
        while( ppNode != NULL) {
            counter++;
            ppNode = ppNode->pNext;
        } 
    }

    return counter;
}

void HT_10mostFreq(struct HashTable * hT, int count) {
    int size = 10;

    for(; count > 0; count--) {
        for(int i = 0; i < hT->size; i++) {
            struct LLNode * ppNode = hT->table[i];
            while( ppNode != NULL) {
                if(ppNode->nmb == count) {
                    printf("[%d most frequent]%s is used %d times\n",11 - size,ppNode->fName,ppNode->nmb );
                    size--;
                    if(size == 0) return;
                }
                ppNode = ppNode->pNext;
            }
        }   
    }
} 
void HT_10leastFreq(struct HashTable * hT, int count) {
    int size = 10;

    for(int cnt = 1; cnt  < count; cnt++) {
        for(int i = 0; i < hT->size; i++) {
            struct LLNode * ppNode = hT->table[i];
            while( ppNode != NULL) {
                if(ppNode->nmb == cnt) {
                    printf("[%d least frequent]%s is used %d times\n",size,ppNode->fName,ppNode->nmb );
                    size--;
                    if(size == 0) return;
                }
                ppNode = ppNode->pNext;
            }
        }
    }
}

int main(){
	struct HashTable *hT = HASH_new(1000);
	FILE *fp = fopen("text2.txt", "r");
	
    char buf[100];
    int count = 0;
    while( fscanf(fp, "%s", buf) != EOF ){
    	//printf("%s\n",a );
    	//*a=buf;
    	//strcpy(a,buf);
    	//printf("%s\n",a );
    	HASH_add(hT, extrasymbols(buf));
        //printf("%d: ",count );
        //printf("%s\n", buf);
        count++;

    }
    //printf("%d\n", count);
    HT_10mostFreq(hT, count);
    printf("------------\n");
    HT_10leastFreq(hT, count);
    printf("------------\n");
    HT_mostFrequent(hT);
    printf("------------\n");
    printf("nbOfDistinct: %d\n", nbOfDistinct(hT));
    //printf("%s\n",hT->table[31]->fName );
    // HASH_add(hT, "hello");
    // HASH_add(hT, "hallo");
    // HASH_add(hT, "hrllo");
    // HASH_add(hT, "htllo");
    // HASH_add(hT, "hyllo");
    //HASH_print(hT);
    //printf("COUNT: %d\n", count);

}
