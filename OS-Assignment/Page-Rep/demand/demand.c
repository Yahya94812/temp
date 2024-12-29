#include <stdio.h>

// Basic configuration
#define FRAMES 3  // Number of frames in physical memory
#define PAGES 5   // Number of pages in reference string

void displayFrames(int frames[], int n) {
    printf("\nFrames: ");
    for(int i = 0; i < n; i++) {
        if(frames[i] == -1)
            printf("[ ] ");
        else
            printf("[%d] ", frames[i]);
    }
    printf("\n");
}

int isPagePresent(int frames[], int n, int page) {
    for(int i = 0; i < n; i++) {
        if(frames[i] == page)
            return 1;
    }
    return 0;
}

void demandPaging(int pages[], int n) {
    // Initialize frames with -1 (empty)
    int frames[FRAMES];
    for(int i = 0; i < FRAMES; i++) {
        frames[i] = -1;
    }
    
    int page_faults = 0;
    int current_position = 0;  // For FIFO replacement
    
    printf("\nDemand Paging Simulation\n");
    printf("------------------------\n");
    
    // Process each page request
    for(int i = 0; i < n; i++) {
        printf("\nRequesting Page %d: ", pages[i]);
        
        // Check if page is already present
        if(!isPagePresent(frames, FRAMES, pages[i])) {
            // Page fault - need to load the page
            frames[current_position] = pages[i];
            current_position = (current_position + 1) % FRAMES;
            page_faults++;
            printf("Page Fault!");
        } else {
            printf("Page Hit!");
        }
        
        // Display current state of frames
        displayFrames(frames, FRAMES);
    }
    
    // Display final statistics
    printf("\nTotal Page Faults: %d\n", page_faults);
    printf("Page Fault Rate: %.2f%%\n", (float)page_faults/n * 100);
}

int main() {
    // Page reference string
    int pages[] = {1, 2, 3, 2, 1, 5, 2, 1, 6, 2, 5, 6, 3, 1, 3};
    int n = sizeof(pages)/sizeof(pages[0]);
    
    printf("Page Reference String: ");
    for(int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    
    demandPaging(pages, n);
    return 0;
}