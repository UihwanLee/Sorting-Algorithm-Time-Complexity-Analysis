#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

#define SWAP(x, y, t) ( (t)=(x), (x)=(y), (y)=(t) )
#define BUCKETS 10
void print_list(int list[], int n)
{
	int i = 0;

	for (i = 0; i < n; i++)
	{
		if (list[i] < 0) {
			printf("Error");
		}
		printf("%d->", list[i]);
	}
	printf("\n");

}
//버블정렬
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i>0; i--) {
		for (j = 0; j<i; j++)
			/* 앞뒤의 레코드를 비교한 후 교체 */
			if (list[j]>list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
// 삽입정렬
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i<n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j]>key; j--)
			list[j + 1] = list[j]; /* 레코드의 오른쪽 이동 */
		list[j + 1] = key;
	}
}
//선택정렬
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i<n - 1; i++) {
		least = i;
		for (j = i + 1; j<n; j++) 	// 최소값 탐색
			if (list[j]<list[least]) least = j;
		//if(i!=least)
		SWAP(list[i], list[least], temp);
	}
}
//
//셸정렬
inc_insertion_sort(int list[], int first, int last, int gap)
{
	// gap 만큼 떨어진 요소들을 삽입 정렬
	// 정렬의 범위는 first에서 last
	int i, j, key;
	for (i = first + gap; i <= last; i = i + gap) {
		key = list[i];
		for (j = i - gap; j >= first && key<list[j]; j = j - gap)
			list[j + gap] = list[j];
		list[j + gap] = key;
	}
}
void shell_sort(int list[], int n)   // n = size
{
	int i, gap;
	for (gap = n / 2; gap>0; gap = gap / 2) {
		if ((gap % 2) == 0) gap++;
		for (i = 0; i<gap; i++)		// 부분 리스트의 개수는 gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
//합병정렬
void merge(int list[], int left, int mid, int right, int sorted[])
{

	/* i는 정렬된 왼쪽리스트에 대한 인덱스
	j는 정렬된 오른쪽리스트에 대한 인덱스
	k는 정렬될 리스트에 대한 인덱스 */
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	/* 분할 정렬된 list의 합병 */
	while (i <= mid && j <= right) {

		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];

		}
		else
		{
			sorted[k++] = list[j++];

		}


	}

	if (i > mid)	/* 남아 있는 레코드의 일괄 복사 */
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];

		}
	else	/* 남아 있는 레코드의 일괄 복사 */
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];

		}
	/* 배열 sorted[]의 리스트를 배열 list[]로 재복사 */
	for (l = left; l <= right; l++) {

		list[l] = sorted[l];

	}
}
void merge_sort(int list[], int left, int right, int sorted[])
{

	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* 리스트의 균등 분할 */
		merge_sort(list, left, mid, sorted);    /* 부분 리스트 정렬 */
		merge_sort(list, mid + 1, right, sorted); /* 부분 리스트 정렬 */
		merge(list, left, mid, right, sorted);    /* 합병 */
												  //	printf("정렬 전 출력\n");
												  //	print_list(list, right);
												  //	printf("정렬 후 출력\n");
												  //	print_list(sorted, right);
	}
}
//퀵정렬
/*
int partition(int list[], int left, int right)
{
int pivot, temp;
int low, high;

low = left;
high = right + 1;
pivot = list[left]; 	//* 피벗 설정
do {
do
low++;
//* 왼쪽 리스트에서 피벗보다 큰 레코드 선택
while (low <= right && list[low]<pivot);
do
high--;
//* 오른쪽 리스트에서 피벗보다 작은 레코드 선택
while (high >= left && list[high]>pivot);
if (low<high) SWAP(list[low], list[high], temp);//* 선택된 두 레코드 교환
} while (low<high);	  //* 인덱스 i,j가 엇갈리지 않는 한 반복

SWAP(list[left], list[high], temp); //* 인텍스 j가 가리키는 레코드와 피벗 교환
return high;
}
void quick_sort(int list[], int left, int right)
{
if (left<right) {    //* 리스트에 2개 이상의 레코드가 있을 경우
int q = partition(list, left, right);
quick_sort(list, left, q - 1);         //* 왼쪽 부분리스트를 퀵정렬
quick_sort(list, q + 1, right);       //* 오른쪽 부분리스트를 퀵정렬
}
}
*/
int compare(const void *arg1, const void *arg2)
{
	if (*(int *)arg1 > *(int *)arg2) return 1;
	else if (*(int *)arg1 == *(int *)arg2) return 0;
	else return -1;
}

typedef struct {
	int *heap;
	int heap_size;
} HeapType;

// 초기화 함수
init(HeapType *h)
{
	h->heap_size = 0;
}
// 삽입 함수
void insert_max_heap(HeapType *h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // 새로운 노드를 삽입
}
// 삭제 함수
int delete_max_heap(HeapType *h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// 현재 노드의 자식노드중 더 큰 자식노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// 우선 순위 큐인 히프를 이용한 정렬
void heap_sort(int list[], int n)
{
	int i;
	HeapType h;
	h.heap = (int *)malloc(sizeof(int) * n);//힙정렬
	init(&h);
	for (i = 0; i<n; i++) {
		insert_max_heap(&h, list[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		list[i] = delete_max_heap(&h);
	}
}


typedef int element;	// 요소의 타입
typedef struct QueueNode {	// 큐의 노드의 타입 
	element item;
	struct QueueNode *link;
} QueueNode;
typedef struct {		// 큐 ADT 구현
	QueueNode *front, *rear;
} QueueType;
// 오류 함수
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 초기화 함수
void init2(QueueType *q)
{
	q->front = q->rear = 0;
}
// 공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == NULL);
}
// 포화 상태 검출 함수
int is_full(QueueType *q)
{
	return 0;
}
// 삽입 함수
void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("메모리를 할당할 수 없습니다");
	else {
		temp->item = item; 		// 데이터 저장
		temp->link = NULL; 		// 링크 필드를 NULL
		if (is_empty(q)) { 		// 큐가 공백이면
			q->front = temp;
			q->rear = temp;
		}
		else { 		// 큐가 공백이 아니면
			q->rear->link = temp;  // 순서가 중요
			q->rear = temp;
		}
	}
}
// 삭제 함수
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q))			// 공백상태
		error("큐가 비어 있읍니다");
	else {
		item = temp->item; 		// 데이터를 꺼낸다.
		q->front = q->front->link; // front를 다음노드를 가리키도록 한다.
		if (q->front == NULL) 	// 공백 상태
			q->rear = NULL;
		free(temp); 			// 동적메모리 해제
		return item; 			// 데이터 반환
	}
}
// peek 함수
element peek(QueueType *q)
{
	element item;
	if (is_empty(q))
		error("큐가 비어 있읍니다");
	else {
		item = q->front->item;	// 데이터를 꺼낸다.
		return item; 			// 데이터 반환
	}
}

void radix_sort(int list[], int n, int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b<BUCKETS; b++) init2(&queues[b]);  // 큐들의 초기화

	for (d = 0; d<digit; d++) {
		for (i = 0; i<n; i++)			// 데이터들을 자리수에 따라 큐에 삽입
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b<BUCKETS; b++)  // 버킷에서 꺼내어 list로 합친다.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// 그 다음 자리수로 간다.
	}
}

//함수의 시간을 측정하는 함수
double getTime(void* fuc(), int ls[], int num) {
	clock_t start, end;
	double res;

	start = clock();
	fuc(ls, num);
	end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;

	return res;
}
//3개의 매개변수를 갖는 함수의 시간을 측정하는 함수
double getTime_3(void* fuc(), int ls[], int num, int in) {
	clock_t start, end;
	double res;

	start = clock();
	fuc(ls, in, num);
	end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;

	return res;
}
//파일에 있는 숫자의 수를 반환하는 함수
int getSize(char * fname, char * mod) {
	int size = 0;
	int buf;
	FILE * f = NULL;

	f = fopen(fname, mod);
	if (f == NULL) {
		printf("파일오픈을 실패했습니다.\n");
		return 0;
	}
	while (fscanf(f, "%d", &buf) == 1) {
		size++;
	}
	fclose(f);
	return size;
}
//메뉴출력함수
int printMenu() {
	int n;
	
	printf("정렬 알고리즘 비교 프로그램입니다.\n");
	printf("해당하는 정렬의 번호를 1개씩 입력해주시기 바랍니다.\n");
	printf("\n");

	printf(" 1. 선택정렬\n");
	printf(" 2. 삽입정렬\n");
	printf(" 3. 버블정렬\n");
	printf(" 4. 쉘정렬\n");
	printf(" 5. 히프정렬\n");
	printf(" 6. 합병정렬\n");
	printf(" 7. 퀵  정렬\n");
	printf(" 8. 기수정렬\n");
	printf(" 9. 종료\n");
	printf("\n비교할 정렬의 번호를 입력하세요 :");
	scanf("%d", &n);
	system("cls");
	return n;
}
////메뉴실행함수
//double doMenu(int n, int arr[], int num) {
//	double time;
//	time_t start, finish;
//	int digit = 0;
//
//
//	switch (n)
//	{
//	case 1:
//		printf("선택정렬\t");
//		start = clock();
//		selection_sort(arr, num); // 선택정렬 호출 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 2:
//		printf("삽입정렬\t");
//		start = clock();
//		insertion_sort(arr, num); // 삽입정렬 호출 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 3:
//		printf("버블정렬\t");
//		start = clock();
//		bubble_sort(arr, num); // 버블정렬 호출/
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 4:
//		printf("쉘  정렬\t");
//		start = clock();
//		shell_sort(arr, num); // 쉘정렬 호출/
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 5:
//		printf("히프정렬\t");
//		start = clock();
//		heap_sort(arr, num);	//히프정렬 호출
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 6://
//		printf("합병정렬\t");
//		start = clock();
//		merge_sort(arr, 0, num, sorted_list); // 합병정렬 호출 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 7:
//		printf("퀵  정렬\t");
//		start = clock();
//		//quick_sort(quick_list, 0, n); // 퀵정렬 호출 
//		qsort((void *)arr, (size_t)num, sizeof(int), compare);
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 8:
//		printf("기수정렬\t");
//		start = clock();
//		radix_sort(arr, n, digit);	//기수정렬 호출
//		finish = clock();
//		time = finish - start;
//		return time;
//	default:
//		printf("오류발생\n");
//		break;
//	}
//}


//메뉴실행함수
double doMenu(int in, int arr[], int data_size) {


	int i, n, size, sel_data, digit = 0;
	double sel_result, ins_result, bub_result, shell_result, merge_result, quick_result, heap_result, radix_result;

	//printf("배열의 크기를 입력하세요 : ");
	//scanf_s("%d", &size);
	//srand(time(NULL));

	int *sel_list = (int *)malloc(sizeof(int) * data_size);  //선택정렬
	int *ins_list = (int *)malloc(sizeof(int) * data_size);  //삽입정렬
	int *bub_list = (int *)malloc(sizeof(int) * data_size);  //버블정렬
	int *shell_list = (int *)malloc(sizeof(int) * data_size);//쉘정렬
	int *merge_list = (int *)malloc(sizeof(int) * data_size);//합병정렬
	int *sorted_list = (int *)malloc(sizeof(int) * data_size);//합병정렬2
	int *quick_list = (int *)malloc(sizeof(int) * data_size);//퀵정렬
	int *heap_list = (int *)malloc(sizeof(int) * data_size);//힙정렬
	int *radix_list = (int *)malloc(sizeof(int) * data_size);//힙정렬

	size = data_size;
	n = size;
	
	//printf("데이터 선택 (1.랜덤 2.정렬된 상태 3.역순으로 정렬된 상태) : ");
	//scanf_s("%d", &sel_data);
	for (i = 0; i < n; i++)
	{
		//if (sel_data == 1) sel_list[i] = n * rand() / (double)RAND_MAX; //랜덤
		//else if (sel_data == 2) sel_list[i] = i; //정렬된 상태
		//else if (sel_data == 3) sel_list[i] = n - i; //역순
		//else break;

		sel_list[i] = arr[i];
		ins_list[i] = arr[i];
		bub_list[i] = arr[i];
		shell_list[i] = arr[i];
		merge_list[i] = arr[i];
		quick_list[i] = arr[i];
		heap_list[i] = arr[i];
		radix_list[i] = arr[i];

	}
	clock_t start, finish;
	
	int MAX = arr[0];
	for (i = 1; i<n; i++)
	{
		if (arr[i] > MAX)
			MAX = arr[i];
	}
	do {
		MAX = MAX / 10;
		digit++;
	} while (MAX > 0);
	
	switch (in)
	{
	case 1:
		printf("선택정렬\t");
		start = clock();
		selection_sort(sel_list, n); // 선택정렬 호출 
		finish = clock();
		sel_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return sel_result;
	case 2:
		printf("삽입정렬\t");
		start = clock();
		insertion_sort(ins_list, n); // 삽입정렬 호출 
		finish = clock();
		ins_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return ins_result;
	case 3:
		printf("버블정렬\t");
		start = clock();
		bubble_sort(bub_list, n); // 버블정렬 호출/
		finish = clock();
		bub_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return bub_result;
	case 4:
		printf("쉘  정렬\t");
		start = clock();
		shell_sort(shell_list, n); // 쉘정렬 호출/
		finish = clock();
		shell_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return shell_result;
	case 5:
		printf("히프정렬\t");
		start = clock();
		heap_sort(heap_list, n);	//히프정렬 호출
		finish = clock();
		heap_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return heap_result;
	case 6://
		printf("합병정렬\t");
		start = clock();
		merge_sort(merge_list, 0, n - 1, sorted_list); // 합병정렬 호출 
		finish = clock();
		merge_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return merge_result;
	case 7:
		printf("퀵  정렬\t");
		start = clock();
		//quick_sort(quick_list, 0, n); // 퀵정렬 호출 
		qsort((void *)quick_list, (size_t)n, sizeof(int), compare);
		finish = clock();
		quick_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return quick_result;
	case 8:
		printf("기수정렬\t");
		start = clock();
		radix_sort(radix_list, n, digit);	//히프정렬 호출
		finish = clock();
		radix_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return radix_result;
	default:
		printf("오류발생\n");
		break;
}
}

int main() {
	int data1_size, data2_size, data3_size;	//각 파일의 숫자 개수
	int buf;	//임시 저장
	int * arr1, *arr2, *arr3;	//기본 배열
	int *xcp1, *xcp2, *xcp3;	//카피한 배열
	int *ycp1, *ycp2, *ycp3;	//카피한 배열
	FILE *file = NULL;
	int x, y; //2개의 정렬 선택
	double xtime1, xtime2, xtime3;	//정렬x에대한 시간
	double ytime1, ytime2, ytime3;	//정렬y에대한 시간

									//각 파일에 저장되어있는 숫자 갯수 저장
	data1_size = getSize("Data1.txt", "r");
	data2_size = getSize("Data2.txt", "r");
	data3_size = getSize("Data3.txt", "r");

	//정렬배열 arr1
	file = fopen("Data1.txt", "r");
	arr1 = (int*)malloc(sizeof(int)*data1_size);

	int i;
	for (i = 0; i < data1_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr1[i] = buf;
	}
	fclose(file);

	//역정렬배열 arr2
	file = fopen("Data2.txt", "r");
	arr2 = (int*)malloc(sizeof(int)*data2_size);

	for (i = 0; i < data2_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr2[i] = buf;
	}
	fclose(file);

	//랜덤배열 arr3
	file = fopen("Data3.txt", "r");
	arr3 = (int*)malloc(sizeof(int)*data3_size);

	for (i = 0; i < data3_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr3[i] = buf;
	}
	fclose(file);

	//정렬 알고리즘에 사용할 배열 동적할당
	xcp1 = (int*)malloc(sizeof(int)*data1_size);
	xcp2 = (int*)malloc(sizeof(int)*data2_size);
	xcp3 = (int*)malloc(sizeof(int)*data3_size);
	ycp1 = (int*)malloc(sizeof(int)*data1_size);
	ycp2 = (int*)malloc(sizeof(int)*data2_size);
	ycp3 = (int*)malloc(sizeof(int)*data3_size);

	//메뉴
	while (1) {
		printf("1번째 선택\n");
		x = printMenu();
		printf("2번째 선택\n");
		y = printMenu();
		if (x == 9 || y == 9) { break; }

		//배열 초기화
		for (i = 0; i < data1_size; i++) {
			xcp1[i] = ycp1[i] = arr1[i];
		}
		for (i = 0; i < data2_size; i++) {
			xcp2[i] = ycp2[i] = arr2[i];
		}
		for (i = 0; i < data3_size; i++) {
			xcp3[i] = ycp3[i] = arr3[i];
		}

		//printf("정렬되기 전\n");	//정렬되기 전의 배열안의 요소 출력
		//printf("Data1\t\tData2\t\tData3\n");
		//for (i = 0; i < data1_size; i++) {
		//	printf("%d\t\t%d\t\t%d\n", xcp1[i], xcp2[i], xcp3[i]);
		//}
		
		printf("\n");
		printf("정렬된 상태\n");	//arr1
		xtime1 = doMenu(x, xcp1, data1_size);
		ytime1 = doMenu(y, ycp1, data1_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime1, ytime1);

		printf("\n");
		printf("역정렬된 상태\n");	//arr2
		xtime2 = doMenu(x, xcp2, data2_size);
		ytime2 = doMenu(y, ycp2, data2_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime2, ytime2);

		printf("\n");
		printf("랜덤상태\n");		//arr3
		xtime3 = doMenu(x, xcp3, data3_size);
		ytime3 = doMenu(y, ycp3, data3_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime3, ytime3);
		system("pause");

		//printf("\n");
		//printf("정렬된 후\n");	//정렬된 후의 배열요소 출력
		//printf("Data1\t\tData2\t\tData3\n");
		//for (i = 0; i < data1_size; i++) {
		//	printf("%d\t\t%d\t\t%d\n", xcp1[i], xcp2[i], xcp3[i]);
		//}
		//system("pause");
		system("cls");

	}
	printf("종료합니다.\n");
	free(arr1); free(arr2); free(arr3);
	free(xcp1); free(xcp2); free(xcp3);
	free(ycp1); free(ycp2); free(ycp3);
	return 0;
}
