#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100
#define MAX_RESOURCES 100

// Function to check if the requested resources can be allocated
bool isSafe(int processes[], int available[], int max[][MAX_RESOURCES],
            int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES],
            int num_processes, int num_resources) {
    bool finish[MAX_PROCESSES] = {false};
    int work[MAX_RESOURCES];
    int safe_sequence[MAX_PROCESSES];
    int count = 0;

    // Initialize work array with available resources
    for (int i = 0; i < num_resources; i++) {
        work[i] = available[i];
    }

    // Find a process that can be allocated resources
    while (count < num_processes) {
        bool found = false;

        for (int p = 0; p < num_processes; p++) {
            if (!finish[p]) {
                bool possible = true;

                // Check if all resources for this process can be allocated
                for (int r = 0; r < num_resources; r++) {
                    if (need[p][r] > work[r]) {
                        possible = false;
                        break;
                    }
                }

                // If allocation is possible
                if (possible) {
                    // Add allocated resources back to work
                    for (int r = 0; r < num_resources; r++) {
                        work[r] += allocation[p][r];
                    }

                    safe_sequence[count] = p;
                    finish[p] = true;
                    count++;
                    found = true;
                }
            }
        }

        // If no process can be allocated resources, system is not in safe state
        if (!found) {
            printf("\nSystem is not in safe state\n");
            return false;
        }
    }

    printf("\nSystem is in safe state.\nSafe sequence: ");
    for (int i = 0; i < num_processes; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");

    return true;
}

// Function to request resources
bool requestResources(int process_id, int request[], int processes[], 
                     int available[], int max[][MAX_RESOURCES],
                     int allocation[][MAX_RESOURCES], int need[][MAX_RESOURCES],
                     int num_processes, int num_resources) {
    // Check if request is valid
    for (int r = 0; r < num_resources; r++) {
        if (request[r] > need[process_id][r]) {
            printf("\nError: Requested resources exceed maximum claim\n");
            return false;
        }
        if (request[r] > available[r]) {
            printf("\nError: Resources not available\n");
            return false;
        }
    }

    // Try to allocate resources
    for (int r = 0; r < num_resources; r++) {
        available[r] -= request[r];
        allocation[process_id][r] += request[r];
        need[process_id][r] -= request[r];
    }

    // Check if system remains in safe state
    if (isSafe(processes, available, max, allocation, need, 
               num_processes, num_resources)) {
        return true;
    }

    // If not safe, rollback changes
    for (int r = 0; r < num_resources; r++) {
        available[r] += request[r];
        allocation[process_id][r] -= request[r];
        need[process_id][r] += request[r];
    }

    printf("\nRequest denied: Would lead to unsafe state\n");
    return false;
}

int main() {
    int num_processes, num_resources;
    
    // Get number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &num_processes);
    printf("Enter number of resources: ");
    scanf("%d", &num_resources);

    if (num_processes > MAX_PROCESSES || num_resources > MAX_RESOURCES) {
        printf("Error: Number of processes or resources exceeds maximum limit\n");
        return 1;
    }

    int processes[MAX_PROCESSES];
    int available[MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];

    // Initialize process IDs
    for (int i = 0; i < num_processes; i++) {
        processes[i] = i;
    }

    // Get available resources
    printf("\nEnter number of available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        printf("Resource %d: ", i);
        scanf("%d", &available[i]);
    }

    // Get maximum resource claims for each process
    printf("\nEnter maximum resource claims for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < num_resources; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &max[i][j]);
        }
    }

    // Get current resource allocation for each process
    printf("\nEnter current resource allocation for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d:\n", i);
        for (int j = 0; j < num_resources; j++) {
            printf("Resource %d: ", j);
            scanf("%d", &allocation[i][j]);
            
            // Validate allocation doesn't exceed maximum claim
            if (allocation[i][j] > max[i][j]) {
                printf("Error: Allocation exceeds maximum claim\n");
                return 1;
            }
            
            // Calculate need matrix
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Check initial state
    printf("\nChecking if system is in safe state:");
    if (!isSafe(processes, available, max, allocation, need, 
                num_processes, num_resources)) {
        printf("Initial state is unsafe. Exiting.\n");
        return 1;
    }

    // Resource request loop
    while (1) {
        int choice;
        printf("\nOptions:\n");
        printf("1. Request resources\n");
        printf("2. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 2) {
            break;
        }
        else if (choice == 1) {
            int process_id;
            int request[MAX_RESOURCES];

            printf("Enter process ID (0 to %d): ", num_processes - 1);
            scanf("%d", &process_id);

            if (process_id < 0 || process_id >= num_processes) {
                printf("Invalid process ID\n");
                continue;
            }

            printf("Enter resource request for process %d:\n", process_id);
            for (int i = 0; i < num_resources; i++) {
                printf("Resource %d: ", i);
                scanf("%d", &request[i]);
            }

            if (requestResources(process_id, request, processes, available, 
                               max, allocation, need, num_processes, num_resources)) {
                printf("Request granted\n");
                
                // Display current state
                printf("\nCurrent resource allocation:\n");
                for (int i = 0; i < num_processes; i++) {
                    printf("Process %d:", i);
                    for (int j = 0; j < num_resources; j++) {
                        printf(" %d", allocation[i][j]);
                    }
                    printf("\n");
                }
                
                printf("\nAvailable resources:");
                for (int i = 0; i < num_resources; i++) {
                    printf(" %d", available[i]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}