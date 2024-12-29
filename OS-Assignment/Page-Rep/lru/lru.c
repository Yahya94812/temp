#include <stdio.h>
#include <limits.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Structure to store page information
typedef struct {
    int page_number;
    int last_used;  // Timestamp of last usage
} Page;

// LRU page replacement algorithm
void lru_page_replacement(int pages[], int n, int num_frames) {
    Page frames[MAX_FRAMES];
    int page_faults = 0;
    int current_time = 0;

    // Initialize frames
    for (int i = 0; i < num_frames; i++) {
        frames[i].page_number = -1;
        frames[i].last_used = -1;
    }

    printf("\nLRU Page Replacement Simulation:\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("\nReferencing page %d: ", pages[i]);
        
        // Check if page already exists
        bool page_found = false;
        for (int j = 0; j < num_frames; j++) {
            if (frames[j].page_number == pages[i]) {
                frames[j].last_used = current_time;
                page_found = true;
                printf("Page Hit! ");
                break;
            }
        }

        if (!page_found) {
            page_faults++;
            
            // Find the least recently used page
            int lru_index = 0;
            int oldest_time = INT_MAX;
            
            for (int j = 0; j < num_frames; j++) {
                if (frames[j].page_number == -1) {
                    // Found an empty frame
                    lru_index = j;
                    break;
                }
                if (frames[j].last_used < oldest_time) {
                    oldest_time = frames[j].last_used;
                    lru_index = j;
                }
            }
            
            // Replace the page
            frames[lru_index].page_number = pages[i];
            frames[lru_index].last_used = current_time;
            printf("Page Fault! ");
        }
        
        // Print current state of frames
        printf("Frames: ");
        for (int j = 0; j < num_frames; j++) {
            if (frames[j].page_number == -1) {
                printf("[ ] ");
            } else {
                printf("[%d] ", frames[j].page_number);
            }
        }
        
        current_time++;
    }
    
    printf("\n\nTotal page faults: %d\n", page_faults);
    printf("Page fault rate: %.2f%%\n", (float)page_faults/n * 100);
}

int main() {
    // Test case
    int pages[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int n = sizeof(pages)/sizeof(pages[0]);
    int num_frames = 3;

    printf("Page Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\nNumber of frames: %d", num_frames);

    lru_page_replacement(pages, n, num_frames);
    return 0;
}