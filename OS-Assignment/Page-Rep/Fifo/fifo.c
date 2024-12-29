#include <stdio.h>
#include <stdbool.h>

#define MAX_FRAMES 10
#define MAX_PAGES 20

// Function to check if a page exists in frames
bool page_exists(int page, int frames[], int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (frames[i] == page) {
            return true;
        }
    }
    return false;
}

// FIFO page replacement algorithm
void fifo_page_replacement(int pages[], int n, int num_frames) {
    int frames[MAX_FRAMES];
    int page_faults = 0;
    int frame_index = 0;  // Points to the frame where next page will be placed

    // Initialize frames with -1 to indicate empty
    for (int i = 0; i < num_frames; i++) {
        frames[i] = -1;
    }

    printf("\nFIFO Page Replacement Simulation:\n");
    printf("--------------------------------\n");
    
    for (int i = 0; i < n; i++) {
        printf("\nReferencing page %d: ", pages[i]);
        
        if (!page_exists(pages[i], frames, num_frames)) {
            // Page fault occurred
            page_faults++;
            
            // Replace page at current frame_index (FIFO)
            frames[frame_index] = pages[i];
            frame_index = (frame_index + 1) % num_frames;
            
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

    fifo_page_replacement(pages, n, num_frames);
    return 0;
}