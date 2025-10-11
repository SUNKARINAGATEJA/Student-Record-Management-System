#include <stdio.h>
#include <string.h>

#define MAX 100

struct Student {
    int rollNo;
    char name[50];
    float marks;
};

struct Student students[MAX];
int count = 0;

// --- Basic Operations ---

void insertStudent() {
    if (count >= MAX) {
        printf("Record full!\n");
        return;
    }
    printf("Enter Roll No: ");
    scanf("%d", &students[count].rollNo);
    printf("Enter Name: ");
    scanf("%s", students[count].name);
    printf("Enter Marks: ");
    scanf("%f", &students[count].marks);
    count++;
    printf("✅ Student added successfully.\n");
}

void displayStudents() {
    if (count == 0) {
        printf("No student records.\n");
        return;
    }
    printf("\n--- Student Records ---\n");
    for (int i = 0; i < count; i++) {
        printf("Roll No: %d, Name: %s, Marks: %.2f\n", 
               students[i].rollNo, students[i].name, students[i].marks);
    }
}

void deleteStudent() {
    int roll;
    printf("Enter Roll No to delete: ");
    scanf("%d", &roll);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == roll) {
            for (int j = i; j < count - 1; j++) {
                students[j] = students[j + 1];
            }
            count--;
            found = 1;
            printf("🗑️ Student deleted successfully.\n");
            break;
        }
    }
    if (!found)
        printf("❌ Student not found.\n");
}

void updateStudent() {
    int roll;
    printf("Enter Roll No to update: ");
    scanf("%d", &roll);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == roll) {
            printf("Enter new name: ");
            scanf("%s", students[i].name);
            printf("Enter new marks: ");
            scanf("%f", &students[i].marks);
            found = 1;
            printf("✏️ Student updated successfully.\n");
            break;
        }
    }
    if (!found)
        printf("❌ Student not found.\n");
}

// --- Searching Algorithms ---

int linearSearch(int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].rollNo == roll)
            return i;
    }
    return -1;
}

int binarySearch(int roll) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (students[mid].rollNo == roll)
            return mid;
        else if (students[mid].rollNo < roll)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

int interpolationSearch(int roll) {
    int low = 0, high = count - 1;
    while (low <= high && roll >= students[low].rollNo && roll <= students[high].rollNo) {
        if (students[low].rollNo == students[high].rollNo)
            break;
        int pos = low + ((roll - students[low].rollNo) * (high - low)) /
                        (students[high].rollNo - students[low].rollNo);
        if (pos < 0 || pos >= count) break;
        if (students[pos].rollNo == roll)
            return pos;
        if (students[pos].rollNo < roll)
            low = pos + 1;
        else
            high = pos - 1;
    }
    return -1;
}

// --- Sorting Algorithms ---

void bubbleSortByMarks() {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (students[j].marks < students[j + 1].marks) {
                struct Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
    printf("✅ Bubble Sort done (by marks).\n");
}

void selectionSortByMarks() {
    for (int i = 0; i < count - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < count; j++) {
            if (students[j].marks > students[maxIdx].marks)
                maxIdx = j;
        }
        struct Student temp = students[i];
        students[i] = students[maxIdx];
        students[maxIdx] = temp;
    }
    printf("✅ Selection Sort done (by marks).\n");
}

void insertionSortByMarks() {
    for (int i = 1; i < count; i++) {
        struct Student key = students[i];
        int j = i - 1;
        while (j >= 0 && students[j].marks < key.marks) {
            students[j + 1] = students[j];
            j--;
        }
        students[j + 1] = key;
    }
    printf("✅ Insertion Sort done (by marks).\n");
}

void quickSort(int low, int high) {
    if (low < high) {
        float pivot = students[high].marks;
        int i = low - 1;
        for (int j = low; j < high; j++) {
            if (students[j].marks >= pivot) {
                i++;
                struct Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
        struct Student temp = students[i + 1];
        students[i + 1] = students[high];
        students[high] = temp;

        int pi = i + 1;
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void merge(struct Student arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    struct Student L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].marks >= R[j].marks)
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(struct Student arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// --- Filtering ---
void filterByMarks() {
    float threshold;
    printf("Enter mark threshold: ");
    scanf("%f", &threshold);
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (students[i].marks >= threshold) {
            printf("Roll No: %d, Name: %s, Marks: %.2f\n", 
                   students[i].rollNo, students[i].name, students[i].marks);
            found = 1;
        }
    }
    if (!found)
        printf("No students above threshold.\n");
}

// --- Main Menu ---

int main() {
    int choice;
    while (1) {
        printf("\n=== Student Record Manager ===\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Display All Students\n");
        printf("5. Search Student\n");
        printf("6. Sort Students\n");
        printf("7. Filter by Marks\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: insertStudent(); break;
            case 2: deleteStudent(); break;
            case 3: updateStudent(); break;
            case 4: displayStudents(); break;
            case 5: {
                int roll, index;
                char type[20];
                printf("Enter Roll No to search: ");
                scanf("%d", &roll);
                printf("Search method (linear/binary/interpolation): ");
                scanf("%s", type);

                if (strcmp(type, "linear") == 0)
                    index = linearSearch(roll);
                else if (strcmp(type, "binary") == 0)
                    index = binarySearch(roll);
                else if (strcmp(type, "interpolation") == 0)
                    index = interpolationSearch(roll);
                else {
                    printf("Invalid search type!\n");
                    break;
                }

                if (index != -1)
                    printf("Found: Roll No: %d, Name: %s, Marks: %.2f\n",
                           students[index].rollNo, students[index].name, students[index].marks);
                else
                    printf("Student not found.\n");
                break;
            }
            case 6: {
                char type[20];
                printf("Sort method (bubble/selection/insertion/quick/merge): ");
                scanf("%s", type);
                if (strcmp(type, "bubble") == 0)
                    bubbleSortByMarks();
                else if (strcmp(type, "selection") == 0)
                    selectionSortByMarks();
                else if (strcmp(type, "insertion") == 0)
                    insertionSortByMarks();
                else if (strcmp(type, "quick") == 0)
                    quickSort(0, count - 1);
                else if (strcmp(type, "merge") == 0)
                    mergeSort(students, 0, count - 1);
                else
                    printf("Invalid sorting method.\n");
                printf("✅ Students sorted successfully.\n");
                break;
            }
            case 7: filterByMarks(); break;
            case 8: 
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }
    }
}
