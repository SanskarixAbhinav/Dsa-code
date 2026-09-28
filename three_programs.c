#ifdef PROGRAM1

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;

Node *head = NULL;

Node *newNode(int d) {
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) {
        printf("Memory allocation failed!\n");
        exit(1);
    }
    n->data = d;
    n->prev = n->next = NULL;
    return n;
}

int readInt(const char *msg) {
    int x;
    printf("%s", msg);
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", msg);
    }
    return x;
}

int countNodes(void) {
    int c = 0;
    for (Node *t = head; t; t = t->next) c++;
    return c;
}

void freeList(void) {
    Node *t;
    while (head) {
        t = head;
        head = head->next;
        free(t);
    }
}

void insertLast(int d);

void createList(void) {
    freeList();
    int n = readInt("How many nodes? ");
    for (int i = 1; i <= n; i++) {
        char msg[40];
        sprintf(msg, "Enter data %d: ", i);
        insertLast(readInt(msg));
    }
    printf("List created.\n");
}

void printList(void) {
    if (!head) { printf("List is empty.\n"); return; }
    printf("List: NULL <-> ");
    for (Node *t = head; t; t = t->next) printf("%d <-> ", t->data);
    printf("NULL\n");
}

void insertFirst(int d) {
    Node *n = newNode(d);
    n->next = head;
    if (head) head->prev = n;
    head = n;
}

void insertLast(int d) {
    Node *n = newNode(d);
    if (!head) { head = n; return; }
    Node *t = head;
    while (t->next) t = t->next;
    t->next = n;
    n->prev = t;
}

void insertAtPos(int pos, int d) {
    int len = countNodes();
    if (pos < 1 || pos > len + 1) {
        printf("Invalid position! Valid range: 1 to %d\n", len + 1);
        return;
    }
    if (pos == 1) { insertFirst(d); return; }
    Node *t = head;
    for (int i = 1; i < pos - 1; i++) t = t->next;
    Node *n = newNode(d);
    n->next = t->next;
    n->prev = t;
    if (t->next) t->next->prev = n;
    t->next = n;
}

void insertAfterData(int key, int d) {
    Node *t = head;
    while (t && t->data != key) t = t->next;
    if (!t) { printf("%d not found in list.\n", key); return; }
    Node *n = newNode(d);
    n->next = t->next;
    n->prev = t;
    if (t->next) t->next->prev = n;
    t->next = n;
}

void unlinkNode(Node *t) {
    if (t->prev) t->prev->next = t->next;
    else head = t->next;
    if (t->next) t->next->prev = t->prev;
    printf("Deleted %d\n", t->data);
    free(t);
}

void deleteFirst(void) {
    if (!head) { printf("List is empty.\n"); return; }
    unlinkNode(head);
}

void deleteLast(void) {
    if (!head) { printf("List is empty.\n"); return; }
    Node *t = head;
    while (t->next) t = t->next;
    unlinkNode(t);
}

void deleteAtPos(int pos) {
    int len = countNodes();
    if (pos < 1 || pos > len) {
        printf("Invalid position! Valid range: 1 to %d\n", len);
        return;
    }
    Node *t = head;
    for (int i = 1; i < pos; i++) t = t->next;
    unlinkNode(t);
}

void deleteData(int key) {
    Node *t = head;
    while (t && t->data != key) t = t->next;
    if (!t) { printf("%d not found in list.\n", key); return; }
    unlinkNode(t);
}

int searchPosition(int key) {
    int pos = 1;
    for (Node *t = head; t; t = t->next, pos++)
        if (t->data == key) return pos;
    return 0;
}

int searchFrequency(int key) {
    int c = 0;
    for (Node *t = head; t; t = t->next)
        if (t->data == key) c++;
    return c;
}

void sortList(void) {
    if (!head || !head->next) { printf("Nothing to sort.\n"); return; }
    int swapped;
    Node *end = NULL;
    do {
        swapped = 0;
        Node *t = head;
        while (t->next != end) {
            if (t->data > t->next->data) {
                int tmp = t->data;
                t->data = t->next->data;
                t->next->data = tmp;
                swapped = 1;
            }
            t = t->next;
        }
        end = t;
    } while (swapped);
    printf("List sorted in ascending order.\n");
}

void reverseList(void) {
    Node *cur = head, *tmp = NULL;
    while (cur) {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }
    if (tmp) head = tmp->prev;
    printf("List reversed.\n");
}

void insertMenu(void) {
    printf("\n a) Insert at first node\n b) Insert at last node\n"
           " c) Insert at given position\n d) Insert after given data\n");
    printf("Choice: ");
    char c;
    scanf(" %c", &c);
    int d, p;
    switch (c) {
    case 'a': case 'A':
        insertFirst(readInt("Enter data: "));
        break;
    case 'b': case 'B':
        insertLast(readInt("Enter data: "));
        break;
    case 'c': case 'C':
        p = readInt("Enter position (1-based): ");
        d = readInt("Enter data: ");
        insertAtPos(p, d);
        break;
    case 'd': case 'D':
        p = readInt("Insert after which data? ");
        d = readInt("Enter new data: ");
        insertAfterData(p, d);
        break;
    default: printf("Invalid choice.\n");
    }
}

void deleteMenu(void) {
    printf("\n a) Delete first node\n b) Delete last node\n"
           " c) Delete from given position\n d) Delete a given data\n");
    printf("Choice: ");
    char c;
    scanf(" %c", &c);
    switch (c) {
    case 'a': case 'A': deleteFirst(); break;
    case 'b': case 'B': deleteLast(); break;
    case 'c': case 'C': deleteAtPos(readInt("Enter position (1-based): ")); break;
    case 'd': case 'D': deleteData(readInt("Enter data to delete: ")); break;
    default: printf("Invalid choice.\n");
    }
}

void searchMenu(void) {
    printf("\n a) Detect presence\n b) Find position\n c) Count occurrences\n");
    printf("Choice: ");
    char c;
    scanf(" %c", &c);
    int key, p;
    switch (c) {
    case 'a': case 'A':
        key = readInt("Enter data to search: ");
        printf(searchPosition(key) ? "%d is present.\n" : "%d is NOT present.\n", key);
        break;
    case 'b': case 'B':
        key = readInt("Enter data to search: ");
        p = searchPosition(key);
        if (p) printf("%d found at position %d (first occurrence).\n", key, p);
        else   printf("%d is NOT present.\n", key);
        break;
    case 'c': case 'C':
        key = readInt("Enter data to search: ");
        printf("%d occurs %d time(s).\n", key, searchFrequency(key));
        break;
    default: printf("Invalid choice.\n");
    }
}

int main(void) {
    int ch;
    do {
        printf("\n===== DOUBLY LINKED LIST MENU =====\n"
               " 1. Create a new list\n"
               " 2. Print the list\n"
               " 3. Insert new data\n"
               " 4. Delete a data\n"
               " 5. Count elements\n"
               " 6. Search for a data\n"
               " 7. Sort the list\n"
               " 8. Reverse the list\n"
               " 0. Exit\n");
        ch = readInt("Enter your choice: ");
        switch (ch) {
        case 1: createList(); break;
        case 2: printList(); break;
        case 3: insertMenu(); break;
        case 4: deleteMenu(); break;
        case 5: printf("Number of elements: %d\n", countNodes()); break;
        case 6: searchMenu(); break;
        case 7: sortList(); break;
        case 8: reverseList(); break;
        case 0: printf("Exiting...\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (ch != 0);
    freeList();
    return 0;
}

#endif

#ifdef PROGRAM2

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX + 1];
int orig[MAX + 1];
int n = 0;

int readInt(const char *msg) {
    int x;
    printf("%s", msg);
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", msg);
    }
    return x;
}

void display(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    printf("Array: ");
    for (int i = 1; i <= n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void inputArray(void) {
    n = readInt("Enter number of elements: ");
    while (n < 1 || n > MAX) {
        n = readInt("Size must be between 1 and 100. Try again: ");
    }
    for (int i = 1; i <= n; i++) {
        char msg[40];
        sprintf(msg, "Enter element %d: ", i);
        arr[i] = orig[i] = readInt(msg);
    }
    printf("Array stored.\n");
}

void resetArray(void) {
    for (int i = 1; i <= n; i++) arr[i] = orig[i];
    printf("Array reset to original order.\n");
}

int isSorted(void) {
    for (int i = 1; i < n; i++)
        if (arr[i] > arr[i + 1]) return 0;
    return 1;
}

void binarySearch(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    if (!isSorted()) {
        printf("Array is not sorted! Sort it first (options 3-5).\n");
        return;
    }
    int key = readInt("Enter element to search: ");
    int low = 1, high = n, step = 0, found = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        printf("Step %d: low=%d high=%d mid=%d (arr[mid]=%d)\n",
               ++step, low, high, mid, arr[mid]);
        if (arr[mid] == key) {
            printf("%d found at position %d.\n", key, mid);
            found = 1;
            break;
        } else if (key < arr[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if (!found) printf("%d not found.\n", key);
}

void modifiedBubbleSort(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    int last = n, pass = 0;
    while (last > 1) {
        int newLast = 0;
        for (int j = 1; j < last; j++) {
            if (arr[j] > arr[j + 1]) {
                int t = arr[j]; arr[j] = arr[j + 1]; arr[j + 1] = t;
                newLast = j;
            }
        }
        pass++;
        printf("Pass %d: ", pass);
        for (int i = 1; i <= n; i++) printf("%d ", arr[i]);
        printf("\n");
        if (newLast == 0) break;
        last = newLast;
    }
    printf("Sorted using Modified Bubble Sort.\n");
}

void insertionSortSentinel(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    for (int i = 2; i <= n; i++) {
        arr[0] = arr[i];
        int j = i - 1;
        while (arr[j] > arr[0]) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = arr[0];
        printf("Pass %d: ", i - 1);
        for (int k = 1; k <= n; k++) printf("%d ", arr[k]);
        printf("\n");
    }
    printf("Sorted using Insertion Sort with Sentinel.\n");
}

void shellSort(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    for (int gap = n / 2; gap >= 1; gap /= 2) {
        for (int i = gap + 1; i <= n; i++) {
            int temp = arr[i], j = i;
            while (j > gap && arr[j - gap] > temp) {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = temp;
        }
        printf("Gap %d: ", gap);
        for (int k = 1; k <= n; k++) printf("%d ", arr[k]);
        printf("\n");
    }
    printf("Sorted using Shell Sort.\n");
}

int main(void) {
    int ch;
    do {
        printf("\n===== SEARCHING & SORTING MENU =====\n"
               " 1. Enter array\n"
               " 2. Binary Search\n"
               " 3. Modified Bubble Sort\n"
               " 4. Insertion Sort using Sentinel\n"
               " 5. Shell Sort\n"
               " 6. Display array\n"
               " 7. Reset to original array\n"
               " 0. Exit\n");
        ch = readInt("Enter your choice: ");
        switch (ch) {
        case 1: inputArray(); break;
        case 2: binarySearch(); break;
        case 3: modifiedBubbleSort(); break;
        case 4: insertionSortSentinel(); break;
        case 5: shellSort(); break;
        case 6: display(); break;
        case 7: resetArray(); break;
        case 0: printf("Exiting...\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (ch != 0);
    return 0;
}

#endif

#ifdef PROGRAM3

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int arr[MAX];
int orig[MAX];
int n = 0;

int readInt(const char *msg) {
    int x;
    printf("%s", msg);
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Invalid input. %s", msg);
    }
    return x;
}

void printRange(int a[], int lo, int hi) {
    for (int i = lo; i <= hi; i++) printf("%d ", a[i]);
    printf("\n");
}

void display(void) {
    if (n == 0) { printf("Array is empty.\n"); return; }
    printf("Array: ");
    printRange(arr, 0, n - 1);
}

void inputArray(void) {
    n = readInt("Enter number of elements: ");
    while (n < 1 || n > MAX)
        n = readInt("Size must be between 1 and 100. Try again: ");
    for (int i = 0; i < n; i++) {
        char msg[40];
        sprintf(msg, "Enter element %d: ", i + 1);
        arr[i] = orig[i] = readInt(msg);
    }
    printf("Array stored.\n");
}

void resetArray(void) {
    for (int i = 0; i < n; i++) arr[i] = orig[i];
    printf("Array reset to original order.\n");
}

int partition(int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
        }
    }
    int t = arr[i + 1]; arr[i + 1] = arr[high]; arr[high] = t;
    return i + 1;
}

void quickSort(int low, int high) {
    if (low < high) {
        int p = partition(low, high);
        printf("Pivot %d placed at index %d: ", arr[p], p);
        printRange(arr, 0, n - 1);
        quickSort(low, p - 1);
        quickSort(p + 1, high);
    }
}

void merge(int low, int mid, int high) {
    int n1 = mid - low + 1, n2 = high - mid;
    int L[MAX], R[MAX];
    for (int i = 0; i < n1; i++) L[i] = arr[low + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    printf("Merged [%d..%d]: ", low, high);
    printRange(arr, low, high);
}

void mergeSort(int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
    }
}

void radixSort(void) {
    int min = arr[0], max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }
    long range = (long)max - min;
    int out[MAX];
    for (long exp = 1; range / exp > 0; exp *= 10) {
        int count[10] = {0};
        for (int i = 0; i < n; i++)
            count[(int)((((long)arr[i] - min) / exp) % 10)]++;
        for (int d = 1; d < 10; d++)
            count[d] += count[d - 1];
        for (int i = n - 1; i >= 0; i--) {
            int d = (int)((((long)arr[i] - min) / exp) % 10);
            out[--count[d]] = arr[i];
        }
        for (int i = 0; i < n; i++) arr[i] = out[i];
        printf("After digit place %ld: ", exp);
        printRange(arr, 0, n - 1);
    }
}

int main(void) {
    int ch;
    do {
        printf("\n===== SORTING MENU =====\n"
               " 1. Enter array\n"
               " 2. Quick Sort\n"
               " 3. Merge Sort\n"
               " 4. Radix Sort\n"
               " 5. Display array\n"
               " 6. Reset to original array\n"
               " 0. Exit\n");
        ch = readInt("Enter your choice: ");
        if (ch >= 2 && ch <= 4 && n == 0) {
            printf("Array is empty. Enter the array first.\n");
            continue;
        }
        switch (ch) {
        case 1: inputArray(); break;
        case 2:
            quickSort(0, n - 1);
            printf("Sorted using Quick Sort.\n");
            break;
        case 3:
            mergeSort(0, n - 1);
            printf("Sorted using Merge Sort.\n");
            break;
        case 4:
            radixSort();
            printf("Sorted using Radix Sort.\n");
            break;
        case 5: display(); break;
        case 6: resetArray(); break;
        case 0: printf("Exiting...\n"); break;
        default: printf("Invalid choice. Try again.\n");
        }
    } while (ch != 0);
    return 0;
}

#endif
