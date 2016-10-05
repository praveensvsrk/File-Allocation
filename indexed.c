#include<stdio.h>
#define maxsize 100

struct fileEntry{
	char *name;
	int start;
	int length;
	int *blocks;
}fileEntry;

int disk[maxsize] = { 0 };
int freeSpace = maxsize;
struct fileEntry files[30];

void init(){
	int i;
	for (i = 0; i < 30; i++){
		files[i].name = NULL;
		files[i].blocks = NULL;
	}
}
int getEmptySlot(){
	int i;
	for (i = 0; i < 30; i++){
		if (files[i].name == NULL)
			return i;
	}
	return -1;
}
void insertFile(char *name, int blocks){
	if (blocks > freeSpace){
		printf("\nFile size too big\n");
		return;
	}
	if (searchFile(name) != -1){
		printf("\nCannot insert the file\n");
		return;
	}
	int i, j, allocated = 0;
	int start = -1;
	int slot = getEmptySlot();
	files[slot].blocks = malloc(blocks*sizeof(int));
	files[slot].name = malloc(0);
	strcpy(files[slot].name, name);
	files[slot].length = blocks;

	for (i = 0; i<maxsize; i++){
		if (disk[i] == 0){
			disk[i] = 1;
			files[slot].blocks[allocated] = i;
			if (start == -1)
				start = i;
			allocated++;
		}
		if (allocated == blocks){
			break;
		}
	}
	files[slot].start = start;
	freeSpace -= blocks;
	printf("Inserted\n");
}
void deleteFile(char *name){
	int pos;
	if ((pos = searchFile(name)) == -1){
		printf("\nFile not found\n");
		return;
	}
	int i;
	for (i = 0; i<files[pos].length; i++){
		disk[files[pos].blocks[i]] = 0;
	}
	freeSpace += files[pos].length;
	files[pos].name = NULL;
	printf("Deleted\n");

}
int searchFile(char *name){
	int i;
	for (i = 0; i<30; i++){
		if (files[i].name != NULL && strcmp(files[i].name, name) == 0)
			return i;
	}
	return -1;
}
void displaySize(){
	printf("Free space in disk = %d", freeSpace);
}
void displayDisk(){
	int i;
	printf("\nDISK:\n\n\t0\t1\t2\t3\t4\t5\t6\t7\t8\t9\n");
	for (i = 0; i<maxsize; i++){
		if (i % 10 == 0)
			printf("\n%d\t", i);
		if (disk[i] == 0)
			printf("%d\t", 0);
		else
			printf("%d\t", 1);
	}
	printf("\n");

}
void displayFiles(){
	int i, j;
	printf("Files in disk:\n");
	printf("Name\tStart\tLength\n");
	for (i = 0; i < 30; i++){
		if (files[i].name != NULL){
			printf("%s\t%4d\t%3d\n", files[i].name, files[i].start, files[i].length);
			printf("Blocks: ");
			for (j = 0; j < files[i].length; j++){
				printf("%d -> ", files[i].blocks[j]);
			}
			printf("NULL\n");
		}
	}
	printf("\n");
}
int main(){
	int option;
	char* name = (char*)malloc(20 * sizeof(char));
	int blocks, start;
	init();
	printf("Sequential File allocation technique\n\n");
	printf("\n1. Insert a File");
	printf("\n2. Delete a File");
	printf("\n3. Display the disk");
	printf("\n4. Display all files");
	printf("\n5. Exit\n");
	while (1){
		displaySize();
		printf("\nEnter option: ");
		scanf_s("%d", &option);
		switch (option){
		case 1:
			printf("Enter file name: ");
			getchar();
			gets_s(name, 20);
			printf("Enter number of blocks: ");
			scanf_s("%d", &blocks);
			insertFile(name, blocks);
			break;
		case 2:
			printf("Enter file name to delete: ");
			getchar();
			gets_s(name, 20);
			deleteFile(name);
			break;
		case 3:
			displayDisk();
			break;
		case 4:
			displayFiles();
			break;
		case 5:
			exit(1);
		default:
			exit(1);
		}
	}
}
