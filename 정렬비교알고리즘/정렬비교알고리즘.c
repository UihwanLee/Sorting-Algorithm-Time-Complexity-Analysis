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
//��������
void bubble_sort(int list[], int n)
{
	int i, j, temp;
	for (i = n - 1; i>0; i--) {
		for (j = 0; j<i; j++)
			/* �յ��� ���ڵ带 ���� �� ��ü */
			if (list[j]>list[j + 1])
				SWAP(list[j], list[j + 1], temp);
	}
}
// ��������
void insertion_sort(int list[], int n)
{
	int i, j, key;
	for (i = 1; i<n; i++) {
		key = list[i];
		for (j = i - 1; j >= 0 && list[j]>key; j--)
			list[j + 1] = list[j]; /* ���ڵ��� ������ �̵� */
		list[j + 1] = key;
	}
}
//��������
void selection_sort(int list[], int n)
{
	int i, j, least, temp;
	for (i = 0; i<n - 1; i++) {
		least = i;
		for (j = i + 1; j<n; j++) 	// �ּҰ� Ž��
			if (list[j]<list[least]) least = j;
		//if(i!=least)
		SWAP(list[i], list[least], temp);
	}
}
//
//������
inc_insertion_sort(int list[], int first, int last, int gap)
{
	// gap ��ŭ ������ ��ҵ��� ���� ����
	// ������ ������ first���� last
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
		for (i = 0; i<gap; i++)		// �κ� ����Ʈ�� ������ gap
			inc_insertion_sort(list, i, n - 1, gap);
	}
}
//�պ�����
void merge(int list[], int left, int mid, int right, int sorted[])
{

	/* i�� ���ĵ� ���ʸ���Ʈ�� ���� �ε���
	j�� ���ĵ� �����ʸ���Ʈ�� ���� �ε���
	k�� ���ĵ� ����Ʈ�� ���� �ε��� */
	int i, j, k, l;
	i = left;  j = mid + 1;  k = left;

	/* ���� ���ĵ� list�� �պ� */
	while (i <= mid && j <= right) {

		if (list[i] <= list[j]) {
			sorted[k++] = list[i++];

		}
		else
		{
			sorted[k++] = list[j++];

		}


	}

	if (i > mid)	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = j; l <= right; l++) {
			sorted[k++] = list[l];

		}
	else	/* ���� �ִ� ���ڵ��� �ϰ� ���� */
		for (l = i; l <= mid; l++) {
			sorted[k++] = list[l];

		}
	/* �迭 sorted[]�� ����Ʈ�� �迭 list[]�� �纹�� */
	for (l = left; l <= right; l++) {

		list[l] = sorted[l];

	}
}
void merge_sort(int list[], int left, int right, int sorted[])
{

	int mid;
	if (left < right) {
		mid = (left + right) / 2;     /* ����Ʈ�� �յ� ���� */
		merge_sort(list, left, mid, sorted);    /* �κ� ����Ʈ ���� */
		merge_sort(list, mid + 1, right, sorted); /* �κ� ����Ʈ ���� */
		merge(list, left, mid, right, sorted);    /* �պ� */
												  //	printf("���� �� ���\n");
												  //	print_list(list, right);
												  //	printf("���� �� ���\n");
												  //	print_list(sorted, right);
	}
}
//������
/*
int partition(int list[], int left, int right)
{
int pivot, temp;
int low, high;

low = left;
high = right + 1;
pivot = list[left]; 	//* �ǹ� ����
do {
do
low++;
//* ���� ����Ʈ���� �ǹ����� ū ���ڵ� ����
while (low <= right && list[low]<pivot);
do
high--;
//* ������ ����Ʈ���� �ǹ����� ���� ���ڵ� ����
while (high >= left && list[high]>pivot);
if (low<high) SWAP(list[low], list[high], temp);//* ���õ� �� ���ڵ� ��ȯ
} while (low<high);	  //* �ε��� i,j�� �������� �ʴ� �� �ݺ�

SWAP(list[left], list[high], temp); //* ���ؽ� j�� ����Ű�� ���ڵ�� �ǹ� ��ȯ
return high;
}
void quick_sort(int list[], int left, int right)
{
if (left<right) {    //* ����Ʈ�� 2�� �̻��� ���ڵ尡 ���� ���
int q = partition(list, left, right);
quick_sort(list, left, q - 1);         //* ���� �κи���Ʈ�� ������
quick_sort(list, q + 1, right);       //* ������ �κи���Ʈ�� ������
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

// �ʱ�ȭ �Լ�
init(HeapType *h)
{
	h->heap_size = 0;
}
// ���� �Լ�
void insert_max_heap(HeapType *h, int item)
{
	int i;
	i = ++(h->heap_size);

	//  Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item > h->heap[i / 2])) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;     // ���ο� ��带 ����
}
// ���� �Լ�
int delete_max_heap(HeapType *h)
{
	int parent, child;
	int item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		// ���� ����� �ڽĳ���� �� ū �ڽĳ�带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child]) < h->heap[child + 1])
			child++;
		if (temp >= h->heap[child]) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

// �켱 ���� ť�� ������ �̿��� ����
void heap_sort(int list[], int n)
{
	int i;
	HeapType h;
	h.heap = (int *)malloc(sizeof(int) * n);//������
	init(&h);
	for (i = 0; i<n; i++) {
		insert_max_heap(&h, list[i]);
	}
	for (i = (n - 1); i >= 0; i--) {
		list[i] = delete_max_heap(&h);
	}
}


typedef int element;	// ����� Ÿ��
typedef struct QueueNode {	// ť�� ����� Ÿ�� 
	element item;
	struct QueueNode *link;
} QueueNode;
typedef struct {		// ť ADT ����
	QueueNode *front, *rear;
} QueueType;
// ���� �Լ�
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// �ʱ�ȭ �Լ�
void init2(QueueType *q)
{
	q->front = q->rear = 0;
}
// ���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == NULL);
}
// ��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return 0;
}
// ���� �Լ�
void enqueue(QueueType *q, element item)
{
	QueueNode *temp = (QueueNode *)malloc(sizeof(QueueNode));
	if (temp == NULL)
		error("�޸𸮸� �Ҵ��� �� �����ϴ�");
	else {
		temp->item = item; 		// ������ ����
		temp->link = NULL; 		// ��ũ �ʵ带 NULL
		if (is_empty(q)) { 		// ť�� �����̸�
			q->front = temp;
			q->rear = temp;
		}
		else { 		// ť�� ������ �ƴϸ�
			q->rear->link = temp;  // ������ �߿�
			q->rear = temp;
		}
	}
}
// ���� �Լ�
element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;
	if (is_empty(q))			// �������
		error("ť�� ��� �����ϴ�");
	else {
		item = temp->item; 		// �����͸� ������.
		q->front = q->front->link; // front�� ������带 ����Ű���� �Ѵ�.
		if (q->front == NULL) 	// ���� ����
			q->rear = NULL;
		free(temp); 			// �����޸� ����
		return item; 			// ������ ��ȯ
	}
}
// peek �Լ�
element peek(QueueType *q)
{
	element item;
	if (is_empty(q))
		error("ť�� ��� �����ϴ�");
	else {
		item = q->front->item;	// �����͸� ������.
		return item; 			// ������ ��ȯ
	}
}

void radix_sort(int list[], int n, int digit)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b<BUCKETS; b++) init2(&queues[b]);  // ť���� �ʱ�ȭ

	for (d = 0; d<digit; d++) {
		for (i = 0; i<n; i++)			// �����͵��� �ڸ����� ���� ť�� ����
			enqueue(&queues[(list[i] / factor) % 10], list[i]);

		for (b = i = 0; b<BUCKETS; b++)  // ��Ŷ���� ������ list�� ��ģ��.
			while (!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		factor *= 10;					// �� ���� �ڸ����� ����.
	}
}

//�Լ��� �ð��� �����ϴ� �Լ�
double getTime(void* fuc(), int ls[], int num) {
	clock_t start, end;
	double res;

	start = clock();
	fuc(ls, num);
	end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;

	return res;
}
//3���� �Ű������� ���� �Լ��� �ð��� �����ϴ� �Լ�
double getTime_3(void* fuc(), int ls[], int num, int in) {
	clock_t start, end;
	double res;

	start = clock();
	fuc(ls, in, num);
	end = clock();
	res = (double)(end - start) / CLOCKS_PER_SEC;

	return res;
}
//���Ͽ� �ִ� ������ ���� ��ȯ�ϴ� �Լ�
int getSize(char * fname, char * mod) {
	int size = 0;
	int buf;
	FILE * f = NULL;

	f = fopen(fname, mod);
	if (f == NULL) {
		printf("���Ͽ����� �����߽��ϴ�.\n");
		return 0;
	}
	while (fscanf(f, "%d", &buf) == 1) {
		size++;
	}
	fclose(f);
	return size;
}
//�޴�����Լ�
int printMenu() {
	int n;
	
	printf("���� �˰��� �� ���α׷��Դϴ�.\n");
	printf("�ش��ϴ� ������ ��ȣ�� 1���� �Է����ֽñ� �ٶ��ϴ�.\n");
	printf("\n");

	printf(" 1. ��������\n");
	printf(" 2. ��������\n");
	printf(" 3. ��������\n");
	printf(" 4. ������\n");
	printf(" 5. ��������\n");
	printf(" 6. �պ�����\n");
	printf(" 7. ��  ����\n");
	printf(" 8. �������\n");
	printf(" 9. ����\n");
	printf("\n���� ������ ��ȣ�� �Է��ϼ��� :");
	scanf("%d", &n);
	system("cls");
	return n;
}
////�޴������Լ�
//double doMenu(int n, int arr[], int num) {
//	double time;
//	time_t start, finish;
//	int digit = 0;
//
//
//	switch (n)
//	{
//	case 1:
//		printf("��������\t");
//		start = clock();
//		selection_sort(arr, num); // �������� ȣ�� 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 2:
//		printf("��������\t");
//		start = clock();
//		insertion_sort(arr, num); // �������� ȣ�� 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 3:
//		printf("��������\t");
//		start = clock();
//		bubble_sort(arr, num); // �������� ȣ��/
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 4:
//		printf("��  ����\t");
//		start = clock();
//		shell_sort(arr, num); // ������ ȣ��/
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 5:
//		printf("��������\t");
//		start = clock();
//		heap_sort(arr, num);	//�������� ȣ��
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 6://
//		printf("�պ�����\t");
//		start = clock();
//		merge_sort(arr, 0, num, sorted_list); // �պ����� ȣ�� 
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 7:
//		printf("��  ����\t");
//		start = clock();
//		//quick_sort(quick_list, 0, n); // ������ ȣ�� 
//		qsort((void *)arr, (size_t)num, sizeof(int), compare);
//		finish = clock();
//		time = finish - start;
//		return time;
//	case 8:
//		printf("�������\t");
//		start = clock();
//		radix_sort(arr, n, digit);	//������� ȣ��
//		finish = clock();
//		time = finish - start;
//		return time;
//	default:
//		printf("�����߻�\n");
//		break;
//	}
//}


//�޴������Լ�
double doMenu(int in, int arr[], int data_size) {


	int i, n, size, sel_data, digit = 0;
	double sel_result, ins_result, bub_result, shell_result, merge_result, quick_result, heap_result, radix_result;

	//printf("�迭�� ũ�⸦ �Է��ϼ��� : ");
	//scanf_s("%d", &size);
	//srand(time(NULL));

	int *sel_list = (int *)malloc(sizeof(int) * data_size);  //��������
	int *ins_list = (int *)malloc(sizeof(int) * data_size);  //��������
	int *bub_list = (int *)malloc(sizeof(int) * data_size);  //��������
	int *shell_list = (int *)malloc(sizeof(int) * data_size);//������
	int *merge_list = (int *)malloc(sizeof(int) * data_size);//�պ�����
	int *sorted_list = (int *)malloc(sizeof(int) * data_size);//�պ�����2
	int *quick_list = (int *)malloc(sizeof(int) * data_size);//������
	int *heap_list = (int *)malloc(sizeof(int) * data_size);//������
	int *radix_list = (int *)malloc(sizeof(int) * data_size);//������

	size = data_size;
	n = size;
	
	//printf("������ ���� (1.���� 2.���ĵ� ���� 3.�������� ���ĵ� ����) : ");
	//scanf_s("%d", &sel_data);
	for (i = 0; i < n; i++)
	{
		//if (sel_data == 1) sel_list[i] = n * rand() / (double)RAND_MAX; //����
		//else if (sel_data == 2) sel_list[i] = i; //���ĵ� ����
		//else if (sel_data == 3) sel_list[i] = n - i; //����
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
		printf("��������\t");
		start = clock();
		selection_sort(sel_list, n); // �������� ȣ�� 
		finish = clock();
		sel_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return sel_result;
	case 2:
		printf("��������\t");
		start = clock();
		insertion_sort(ins_list, n); // �������� ȣ�� 
		finish = clock();
		ins_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return ins_result;
	case 3:
		printf("��������\t");
		start = clock();
		bubble_sort(bub_list, n); // �������� ȣ��/
		finish = clock();
		bub_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return bub_result;
	case 4:
		printf("��  ����\t");
		start = clock();
		shell_sort(shell_list, n); // ������ ȣ��/
		finish = clock();
		shell_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return shell_result;
	case 5:
		printf("��������\t");
		start = clock();
		heap_sort(heap_list, n);	//�������� ȣ��
		finish = clock();
		heap_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return heap_result;
	case 6://
		printf("�պ�����\t");
		start = clock();
		merge_sort(merge_list, 0, n - 1, sorted_list); // �պ����� ȣ�� 
		finish = clock();
		merge_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return merge_result;
	case 7:
		printf("��  ����\t");
		start = clock();
		//quick_sort(quick_list, 0, n); // ������ ȣ�� 
		qsort((void *)quick_list, (size_t)n, sizeof(int), compare);
		finish = clock();
		quick_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return quick_result;
	case 8:
		printf("�������\t");
		start = clock();
		radix_sort(radix_list, n, digit);	//�������� ȣ��
		finish = clock();
		radix_result = (double)(finish - start) / CLOCKS_PER_SEC;
		return radix_result;
	default:
		printf("�����߻�\n");
		break;
}
}

int main() {
	int data1_size, data2_size, data3_size;	//�� ������ ���� ����
	int buf;	//�ӽ� ����
	int * arr1, *arr2, *arr3;	//�⺻ �迭
	int *xcp1, *xcp2, *xcp3;	//ī���� �迭
	int *ycp1, *ycp2, *ycp3;	//ī���� �迭
	FILE *file = NULL;
	int x, y; //2���� ���� ����
	double xtime1, xtime2, xtime3;	//����x������ �ð�
	double ytime1, ytime2, ytime3;	//����y������ �ð�

									//�� ���Ͽ� ����Ǿ��ִ� ���� ���� ����
	data1_size = getSize("Data1.txt", "r");
	data2_size = getSize("Data2.txt", "r");
	data3_size = getSize("Data3.txt", "r");

	//���Ĺ迭 arr1
	file = fopen("Data1.txt", "r");
	arr1 = (int*)malloc(sizeof(int)*data1_size);

	int i;
	for (i = 0; i < data1_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr1[i] = buf;
	}
	fclose(file);

	//�����Ĺ迭 arr2
	file = fopen("Data2.txt", "r");
	arr2 = (int*)malloc(sizeof(int)*data2_size);

	for (i = 0; i < data2_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr2[i] = buf;
	}
	fclose(file);

	//�����迭 arr3
	file = fopen("Data3.txt", "r");
	arr3 = (int*)malloc(sizeof(int)*data3_size);

	for (i = 0; i < data3_size; i++) {
		int n = fscanf(file, "%d", &buf);
		arr3[i] = buf;
	}
	fclose(file);

	//���� �˰��� ����� �迭 �����Ҵ�
	xcp1 = (int*)malloc(sizeof(int)*data1_size);
	xcp2 = (int*)malloc(sizeof(int)*data2_size);
	xcp3 = (int*)malloc(sizeof(int)*data3_size);
	ycp1 = (int*)malloc(sizeof(int)*data1_size);
	ycp2 = (int*)malloc(sizeof(int)*data2_size);
	ycp3 = (int*)malloc(sizeof(int)*data3_size);

	//�޴�
	while (1) {
		printf("1��° ����\n");
		x = printMenu();
		printf("2��° ����\n");
		y = printMenu();
		if (x == 9 || y == 9) { break; }

		//�迭 �ʱ�ȭ
		for (i = 0; i < data1_size; i++) {
			xcp1[i] = ycp1[i] = arr1[i];
		}
		for (i = 0; i < data2_size; i++) {
			xcp2[i] = ycp2[i] = arr2[i];
		}
		for (i = 0; i < data3_size; i++) {
			xcp3[i] = ycp3[i] = arr3[i];
		}

		//printf("���ĵǱ� ��\n");	//���ĵǱ� ���� �迭���� ��� ���
		//printf("Data1\t\tData2\t\tData3\n");
		//for (i = 0; i < data1_size; i++) {
		//	printf("%d\t\t%d\t\t%d\n", xcp1[i], xcp2[i], xcp3[i]);
		//}
		
		printf("\n");
		printf("���ĵ� ����\n");	//arr1
		xtime1 = doMenu(x, xcp1, data1_size);
		ytime1 = doMenu(y, ycp1, data1_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime1, ytime1);

		printf("\n");
		printf("�����ĵ� ����\n");	//arr2
		xtime2 = doMenu(x, xcp2, data2_size);
		ytime2 = doMenu(y, ycp2, data2_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime2, ytime2);

		printf("\n");
		printf("��������\n");		//arr3
		xtime3 = doMenu(x, xcp3, data3_size);
		ytime3 = doMenu(y, ycp3, data3_size);
		printf("\n");
		printf("%.4lf\t\t%.4lf\n", xtime3, ytime3);
		system("pause");

		//printf("\n");
		//printf("���ĵ� ��\n");	//���ĵ� ���� �迭��� ���
		//printf("Data1\t\tData2\t\tData3\n");
		//for (i = 0; i < data1_size; i++) {
		//	printf("%d\t\t%d\t\t%d\n", xcp1[i], xcp2[i], xcp3[i]);
		//}
		//system("pause");
		system("cls");

	}
	printf("�����մϴ�.\n");
	free(arr1); free(arr2); free(arr3);
	free(xcp1); free(xcp2); free(xcp3);
	free(ycp1); free(ycp2); free(ycp3);
	return 0;
}
