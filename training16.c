#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 배열 요소 교환
void swap(int* a, int* b, int* moveCount) {
    int temp = *a;
    *a = *b;
    *b = temp;
    (*moveCount)++;
}

// 분할 함수
int partition(int arr[], int low, int high, int* compareCount, int* moveCount) {
    int pivot_index = arr[high]; // 피벗을 배열의 끝에서 선택
    int i = (low - 1); // 작은 요소들을 위한 인덱스

    for (int j = low; j <= high - 1; j++) {
        // 비교 횟수 증가
        (*compareCount)++;

        // 현재 요소가 피벗보다 작으면 교환
        if (arr[j] < pivot_index) {
            i++;
            swap(&arr[i], &arr[j], moveCount);
        }
    }
    // 피벗 위치 교환
    swap(&arr[i + 1], &arr[high], moveCount);
    return (i + 1);
}

// 퀵 정렬 함수 (반복적 방법)
void QuickSort(int arr[], int low, int high, int* compareCount, int* moveCount) {
    // 스택을 사용하여 반복적 퀵 정렬 구현
    int stack[high - low + 1];
    // -1로 초기화
    int top = -1;

    // 초기화
    stack[++top] = low; // 작은값
    stack[++top] = high; // 큰값

    while (top >= 0) {
        // 스택에서 low, high를 뽑아낸다
        high = stack[top--];
        low = stack[top--];

        // 분할 인덱스 찾기
        int pivot_index = partition(arr, low, high, compareCount, moveCount);

        // 왼쪽 부분 정렬
        if (pivot_index - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivot_index - 1;
        }

        // 오른쪽 부분 정렬
        if (pivot_index + 1 < high) {
            stack[++top] = pivot_index + 1;
            stack[++top] = high;
        }

        // 정렬 후 전체 배열 출력
        for (int i = 0; i < 20; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }
}

int main() {
    int n = 20; // 배열의 크기
    int arr[n];

    // 0부터 99까지의 난수로 배열 초기화
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    printf("Original List: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    int compareCount = 0; // 비교 횟수
    int moveCount = 0;    // 이동 횟수

    QuickSort(arr, 0, n - 1, &compareCount, &moveCount);

    // 평균 비교 횟수와 이동 횟수 출력
    printf("Average Move Count: %.2f\n", (float)compareCount / n);
    printf("Average Comp Count: %.2f\n", (float)moveCount / n);

    return 0;
}