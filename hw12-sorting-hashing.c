/*
 * hw12-sorting-hashing.c
 *
 *  Created on: May 22, 2021
 *
 *  Homework 12: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	printf("2020039071 JoJunHwa");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a) //int형 array의 주소가 파라메터로 들어온다
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a; //a가 생성되었으면 tmep가 a를 가리키게한다

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) 
		temp[i] = rand() % MAX_ARRAY_SIZE; //0~MAX_ARRAY_SIZE-1까지의 숫자로 초기화한다

	return 0;
}

int freeArray(int *a) //배열을 차례로 초기화해준다
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 index를 프린트한다
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 값을 프린트한다
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //선택정렬 알고리즘, 가장 첫 번째 원소부터 가장 작은값으로 대치하는 식으로 진행된다
	{
		minindex = i; 
		min = a[i];
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			if (min > a[j]) //현재 까지의 min보다 작은 값이 나타나면 그 값과 바꾼다
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i]; 
		a[i] = min; //i까지의 정렬이 완료되었다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) 
	//삽입정렬 알고리즘 배열의 첫 번째 요소부터 그 다음의 요소와 비교하여 삽입할 자리를 비워 끼워넣는다
	{
		t = a[i]; //t는 i번째 값을 저장하고 있는다
		j = i; 
		while (a[j-1] > t && j > 0) 
		{ //j-1부터 즉 i-1부터 a[i]가 삽입될 곳을 찾는다 
			a[j] = a[j-1];
			j--;
		} //while문을 나왔다면 j의 위치에 a[i]에 있던 요소를 삽입하면 된다
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //버블정렬 알고리즘, 가장 큰 값을 가장 뒤로 보내면서 정렬한다
	{
		for (j = 1; j < MAX_ARRAY_SIZE+1; j++)
		{
			if (a[j-1] > a[j]) //j전의 값이 더 크다면 j와 j-1을 바꾼다
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //쉘 정렬 알고리즘
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; //v는 a[j]를 임시 저장
				k = j; //k도 j를 임시 저장
				while (k > h-1 && a[k-h] > v) 
				//i에서 h만큼 떨어진 값을 앞뒤로(+-h만큼) 비교하여 더 큰값을 뒤로 보낸다 h를 2로 나누면서 비교할 레코드를 줄이면서 진행한다 
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	//처음 n값은 MAX_ARRAY_SIZE
	int v, t;
	int i, j;

	if (n > 1) //순환구조의 무한루프 탈출 조건
	{
		v = a[n-1]; //n-1을 pivot으로 사용
		i = -1; //i가 left
		j = n - 1; //j가 right

		while(1)
		{
			while(a[++i] < v); //left에서 pivot보다 큰 값이 나오면 그 값을 i로 하고 중단 
			while(a[--j] > v); //right에서 pivot보다 작은 값이 나오면 그 값을 j로하고 중단

			if (i >= j) break; //i >= j이면 quick sort의 한 단계 끝
			//i와 j의 값을 스왑
			t = a[i]; 
			a[i] = a[j];
			a[j] = t;
		}
		//반복문을 나오면 pivot과 i를 스왑
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;
		//pivot을 i-1로 하는 QucickSort 진행
		quickSort(a, i);
		//pivot을 n-i-2로 하는 QuickSort 진행
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; //모들러 연산을 이용하여 해시코드를 구하는 함수
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //-1로 초기화
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1) //넣어야 하는 곳의 테이블이 비어있다면 바로 넣는다
		{
			hashtable[hashcode] = key;
		} else 	{

			index = hashcode;

			while(hashtable[index] != -1) //비어있지 않다면 비어 있는 곳을 index를 하나씩 늘려가면서 찾아서 넣는다
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); //key에 대한 index를 찾는다

	if(ht[index] == key)
		return index; //해시테이블의 index에 key가 있다면 index 리턴

	while(ht[++index] != key) 
	//해시테이블에서 index에 없다면 밀려서 저장되있으므로 key가 있는 index를 찾아서 리턴 0번째 index를 검사하지 않는 오류가 생겨서 수정했습니다
	{
		if(index == MAX_HASH_TABLE_SIZE)
			index = -1;		
	}
	return index;
}



