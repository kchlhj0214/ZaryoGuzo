#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#include<malloc.h>

int rec_count = 0; //재귀적 함수 호출 횟수를 저장하기 위한 함수
#define PROB 6 // 각각의 문제를 구현하고 해당 문제 번호를 변경하여 테스트
//---------------------------------------------------------------------------------------------------//
#if PROB == 1
/* Compute power(x, n) for int x, n */
// 1번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현
int itr_power(int x, int n) {
	int result = 1;
	for (int i = 0; i < n; ++i)
		result *= x;
	return(result);
}

int rec_power(int x, int n) {
	++rec_count;
	if (n == 0) 
		return 1;
	else if (n % 2 == 0) 
		return rec_power(x * x, n / 2);
	else 
		return x * rec_power(x * x, (n - 1) / 2);
}
void main(void)
{
	int x, n;
	double result;
	clock_t start, end;
	printf("문제 1 \n");
	printf("x, n 입력(x^n) :");
	scanf("%d %d", &x, &n);
	start = clock();
	result = itr_power(x, n);
	end = clock();
	printf("ITR : %d^%d = %f, 수행시간 :%f\n",
		x, n, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_power(x, n);
	end = clock();
	printf("REC : %d^%d = %f, 수행시간 :%f, 함수호출횟수 : %d\n",
		x, n, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#elif PROB == 2
/* Binomial Coef */
// 2번 문제에 대한 반복, 재귀적 방법으로 구현하기 위한 각각의 함수 구현
// main 함수에서 데이터를 입력받아 호출하는 코드와 결과 출력 구현
int itr_binoC(int n, int k) {
	long long result = 1;
	for(int i = n; i > 0; --i)
		result *= i;
	for (int i = k; i > 0; --i)
		result /= i;
	for (int i = (n - k); i > 0; --i)
		result /= i;
	return(result);
}

int rec_binoC(int n, int k) {
	++rec_count;
	if (k == 0 || n == k) 
		return 1;
	else if (k > 0 && n > k) 
		return rec_binoC(n - 1, k - 1) + rec_binoC(n - 1, k);
}
void main(void)
{
	int x, n;
	int result;
	clock_t start, end;
	printf("문제 2 \n");
	printf("n, k 입력(n >= k) :");
	scanf("%d %d", &x, &n);
	start = clock();
	result = itr_binoC(x, n);
	end = clock();
	printf("ITR : %dC%d = %d, 수행시간 :%f\n",
		x, n, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_binoC(x, n);
	end = clock();
	printf("REC : %dC%d = %d, 수행시간 :%f, 함수호출횟수 : %d\n",
		x, n, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#elif PROB == 3
/* Ackerman function */ 
// (반복문은 인터넷 검색 및 이해 후 재작성)
int itr_Ackerman(int m, int n) {		// 맨 뒤 2개 배열을 각각 현재의 m, n으로 만들고 조건 연산 > 현재의 m이 0이 되면 esp 앞으로 이동/m, n이 0이 아니면 배열 추가 및 esp 뒤로 이동 
										// > 이 과정을 반복하여 A(m, n)을 전부 배열로 펼치고 끝에서부터 한 칸씩 값을 더하면서 당겨옴 > 최종적으로 m이 모두 사라지면(맨 앞 m이 0이 되어 함수가 정수가 되면) esp가 0번항이 되고 그때의 0번항 값 리턴
	int ary[100000];
	int esp = 0;			// 현재 n의 위치 추적

	ary[esp] = m;
	++esp;
	ary[esp] = n;

	while (1) {
		if (esp == 0)
			return ary[esp];
		else if (ary[esp - 1] == 0) {
			ary[esp - 1] = ary[esp] + 1;
			--esp;
		}
		else if (ary[esp] == 0) {
			--ary[esp - 1];
			ary[esp] = 1;
		}
		else {
			ary[esp + 1] = ary[esp] - 1;
			ary[esp] = ary[esp - 1];
			ary[esp - 1] = ary[esp - 1] - 1;
			++esp;
		}
	}
}

int rec_Ackerman(int m, int n) {
	++rec_count;
	if (m == 0)
		return n + 1;
	else if (n == 0)
		return rec_Ackerman(m - 1, 1);
	else
		return rec_Ackerman(m - 1, rec_Ackerman(m, n - 1));
}
void main(void)
{
	int m, n;
	int result;
	clock_t start, end;
	printf("문제 3 \n");
	printf("m, n 입력(m, n >= 0) :");
	scanf("%d %d", &m, &n);
	start = clock();
	result = itr_Ackerman(m, n);
	end = clock();
	printf("ITR : A(%d,%d) = %d, 수행시간 :%f\n",
		m, n, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_Ackerman(m, n);
	end = clock();
	printf("REC : A(%d,%d) = %d, 수행시간 :%f, 함수호출횟수 : %d\n",
		m, n, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#elif PROB == 4
/* 피보나치 수열 */
int itr_fib(int n) {
	int result = 0;
	int first = 0;
	int second = 1;
	
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else {
		for (int i = 2; i <= n; ++i) {
			result = first + second;
			first = second;
			second = result;
		}
		return result;
	}

	return(result);
}

int rec_fib(int n) {
	++rec_count;
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	else
		return (rec_fib(n - 1) + rec_fib(n - 2));
}
void main(void)
{
	int n;
	int result;
	clock_t start, end;
	printf("문제 4 \n");
	printf("Input 피보나치 항 :");
	scanf("%d", &n);
	start = clock();
	result = itr_fib(n);
	end = clock();
	printf("ITR : %d번째 항의 값 : %d, 수행시간 :%f\n",
		n, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_fib(n);
	end = clock();
	printf("REC : %d번째 항의 값 : %d, 수행시간 :%f, 함수호출횟수 : %d\n",
		n, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#elif PROB == 5
/* Binary Search */
#define SIZE 100


int itr_binS(int data[], int x, int low, int high) {
	int mid = low + (high - low) / 2;
	for (int i = mid; i != x;) {
		if (i > x)
			high = mid - 1;
		else
			low = mid + 1;
		mid = low + (high - low) / 2;
		i = mid;
	}
	return mid;
}

int rec_binS(int data[], int x, int low, int high) {
	if (low > high)
		return -1;

	++rec_count;

	int mid = low + (high - low) / 2;
	if (x == data[mid])
		return mid;
	else if (x < data[mid])
		return rec_binS(data, x, low, mid - 1);
	else
		return rec_binS(data, x, mid + 1, high);

}
void main(void)
{
	int data[SIZE];
	for (int idx = 0; idx < SIZE; idx++) 
		data[idx] = idx;
	int x;
	int result;
	clock_t start, end;
	printf("문제 5 \n");
	printf("찾으려는 idx 값 :");
	scanf("%d", &x);
	start = clock();
	result = itr_binS(data, x, 0 ,SIZE - 1);
	end = clock();
	printf("ITR : %d값의 idx 위치 : %d, 수행시간 :%f\n",
		x, result, (double)(end - start) / CLOCKS_PER_SEC);
	start = clock();
	result = rec_binS(data, x, 0, SIZE - 1);
	end = clock();
	printf("REC : %d값의 idx 위치 : %d, 수행시간 :%f, 함수호출횟수 : %d\n",
		x, result, (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#elif PROB == 6
/* Hanoi Tower */
void itr_hanoi_tower(int n, char from, char tmp, char to) {
	
}

void rec_hanoi_tower(int n, char from, char tmp, char to) {
	++rec_count;
	if (n == 1)
		printf("원판 1을 %c 에서 %c으로 옮긴다.\n", from, to);
	else {
		rec_hanoi_tower(n-1, from, to, tmp);
		printf("원판 %d을 %c 에서 %c으로 옮긴다.\n", n, from, to);
		rec_hanoi_tower(n - 1, tmp, from, to);
	}
}
void main(void)
{
	int n;
	int result;
	clock_t start, end;
	printf("문제 6 \n");
	printf("원판 개수 입력:");
	scanf("%d", &n);
	/*printf("반복적 기법\n");
	start = clock();
	itr_hanoi_tower(n, 'A', 'B', 'C');
	end = clock();
	printf("ITR : , 수행시간 :%f\n", (double)(end - start) / CLOCKS_PER_SEC);*/
	printf("재귀적 기법\n");
	start = clock();
	rec_hanoi_tower(n, 'A', 'B', 'C');
	end = clock();
	printf("REC : , 수행시간 :%f, 함수호출횟수 : %d\n", (double)(end - start) / CLOCKS_PER_SEC, rec_count);
	return;
}
//---------------------------------------------------------------------------------------------------//
#endif