// Hospital Emergency Triage System Using Priority Queue



#include <stdio.h>

#define MAX 50

struct Patient {
    int patient_id;
    char name[30];
    int severity;
    int arrival_no;
};

struct Patient heap[MAX];
int size = 0;

// Swap two patients
void swap(struct Patient *a, struct Patient *b) {
    struct Patient temp = *a;
    *a = *b;
    *b = temp;
}

// Check priority
int higher(struct Patient a, struct Patient b) {
    if (a.severity != b.severity)
        return a.severity > b.severity;

    return a.arrival_no < b.arrival_no;
}

// Insert patient
void insert() {
    if (size == MAX) {
        printf("Queue is full!\n");
        return;
    }

    struct Patient p;

    printf("Enter Patient ID: ");
    scanf("%d", &p.patient_id);

    printf("Enter Name: ");
    scanf("%29s", p.name);

    printf("Enter Severity (1-10): ");
    scanf("%d", &p.severity);

    if (p.severity < 1 || p.severity > 10) {
        printf("Invalid severity score!\n");
        return;
    }

    p.arrival_no = size + 1;

    int i = size;
    heap[size++] = p;

    // Heapify up
    while (i > 0 && higher(heap[i], heap[(i - 1) / 2])) {
        swap(&heap[i], &heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    printf("Patient added successfully!\n");
}

// Treat highest priority patient
void treatPatient() {
    if (size == 0) {
        printf("No patients in queue!\n");
        return;
    }

    printf("\nPatient Being Treated:\n");
    printf("ID: %d\n", heap[0].patient_id);
    printf("Name: %s\n", heap[0].name);
    printf("Severity: %d\n", heap[0].severity);

    heap[0] = heap[--size];

    // Heapify down
    int i = 0;

    while (1) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largest = i;

        if (left < size && higher(heap[left], heap[largest]))
            largest = left;

        if (right < size && higher(heap[right], heap[largest]))
            largest = right;

        if (largest == i)
            break;

        swap(&heap[i], &heap[largest]);
        i = largest;
    }
}

// Display patients
void display() {
    if (size == 0) {
        printf("Queue is empty!\n");
        return;
    }

    printf("\nID\tName\tSeverity\tArrival\n");

    for (int i = 0; i < size; i++) {
        printf("%d\t%s\t%d\t\t%d\n",
               heap[i].patient_id,
               heap[i].name,
               heap[i].severity,
               heap[i].arrival_no);
    }
}

// Main function
int main() {
    int choice;

    do {
        printf("\n--- HOSPITAL TRIAGE SYSTEM ---\n");
        printf("1. Add Patient\n");
        printf("2. Treat Highest Priority Patient\n");
        printf("3. Display Patients\n");
        printf("4. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insert();
                break;

            case 2:
                treatPatient();
                break;

            case 3:
                display();
                break;

            case 4:
                printf("Exiting System...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
