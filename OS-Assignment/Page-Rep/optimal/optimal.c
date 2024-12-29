#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function to find the next occurrence of a page in the future
int find_next_occurrence(int page, int pages[], int current_pos, int n) {
    for (int i = current_pos + 1; i < n; i++) {
        if (pages[i] == page) {
            return i;
        }
    }
    return INT_MAX;  // Page won't be used again
}

// Function to check if a page exists in frames
bool page_exists(int page, int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// Optimal page replacement algorithm
void optimal_page_replacement(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;

    // Initialize frames with -1 to indicate empty
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nOptimal (Belady's) Page Replacement Simulation:\n");
    printf("--------------------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("\nReferencing page %d: ", pages[i]);
        
        if (!page_exists(pages[i], frames, num_frames)) {
            page_faults++;
            
            // Find if there's any empty frame
            int empty_frame = -1;
            for (int j = 0; j < num_frames; j++) {
                if (frames[j] == -1) {
                    empty_frame = j;
                    break;
                }
            }
            
            if (empty_frame != -1) {
                // If empty frame exists, use it
                frames[empty_frame] = pages[i];
            } else {
                // Find the page that will not be used for the longest time
                int farthest = -1;
                int replace_index = 0;
                
                for (int j = 0; j < num_frames; j++) {
                    int next = find_next_occurrence(frames[j], pages, i, n);
                    if (next > farthest) {
                        farthest = next;
                        replace_index = j;
                    }
                }
                
                frames[replace_index] = pages[i];
            }
            printf("Page Fault! ");
        } else {
            printf("Page Hit! ");
        }
        
        // Print current state of frames
        printf("Frames: ");
        for (int j = 0; j < num_frames; j++) {
            if (frames[j] == -1) {
                printf("[ ] ");
            } else {
                printf("[%d] ", frames[j]);
            }
        }
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

    optimal_page_replacement(pages, n, num_frames);
    return 0;
}