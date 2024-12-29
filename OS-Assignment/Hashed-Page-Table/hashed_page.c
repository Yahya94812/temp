#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define TABLE_SIZE 16
#define MAX_CHAIN 4
#define PAGE_SIZE 4096
#define INVALID_PAGE -1

// Structure for page table entry
typedef struct PageTableEntry {
    int virtual_page;
    int physical_frame;
    bool valid;
    struct PageTableEntry* next;
} PageTableEntry;

// Structure for hash table
typedef struct {
    PageTableEntry* entries[TABLE_SIZE];
    int num_pages;
    int num_frames;
    int collisions;
} HashPageTable;

// Hash function
int hash_function(int virtual_page) {
    return virtual_page % TABLE_SIZE;
}

// Initialize hash page table
HashPageTable* init_page_table(int num_pages, int num_frames) {
    HashPageTable* table = (HashPageTable*)malloc(sizeof(HashPageTable));
    table->num_pages = num_pages;
    table->num_frames = num_frames;
    table->collisions = 0;
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        table->entries[i] = NULL;
    }
    
    return table;
}

// Insert a page into the hash table
bool insert_page(HashPageTable* table, int virtual_page, int physical_frame) {
    int index = hash_function(virtual_page);
    
    // Create new entry
    PageTableEntry* new_entry = (PageTableEntry*)malloc(sizeof(PageTableEntry));
    new_entry->virtual_page = virtual_page;
    new_entry->physical_frame = physical_frame;
    new_entry->valid = true;
    new_entry->next = NULL;
    
    // If slot is empty
    if (table->entries[index] == NULL) {
        table->entries[index] = new_entry;
        return true;
    }
    
    // Handle collision through chaining
    PageTableEntry* current = table->entries[index];
    int chain_length = 1;
    
    while (current->next != NULL) {
        // Update existing entry if virtual page already exists
        if (current->virtual_page == virtual_page) {
            current->physical_frame = physical_frame;
            current->valid = true;
            free(new_entry);
            return true;
        }
        current = current->next;
        chain_length++;
    }
    
    // Check if chain length exceeds maximum
    if (chain_length >= MAX_CHAIN) {
        printf("Warning: Maximum chain length exceeded at index %d\n", index);
        free(new_entry);
        return false;
    }
    
    table->collisions++;
    current->next = new_entry;
    return true;
}

// Look up a page in the hash table
int lookup_page(HashPageTable* table, int virtual_page) {
    int index = hash_function(virtual_page);
    PageTableEntry* current = table->entries[index];
    
    while (current != NULL) {
        if (current->virtual_page == virtual_page && current->valid) {
            return current->physical_frame;
        }
        current = current->next;
    }
    
    return INVALID_PAGE;
}

// Print the current state of the page table
void print_page_table(HashPageTable* table) {
    printf("\nHash Page Table Status:\n");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Index %2d: ", i);
        PageTableEntry* current = table->entries[i];
        
        if (current == NULL) {
            printf("Empty\n");
            continue;
        }
        
        while (current != NULL) {
            printf("(VP: %d, PF: %d) -> ", 
                   current->virtual_page, 
                   current->physical_frame);
            current = current->next;
        }
        printf("NULL\n");
    }
    
    printf("----------------------------------------\n");
    printf("Total collisions: %d\n", table->collisions);
}

// Free the page table memory
void free_page_table(HashPageTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        PageTableEntry* current = table->entries[i];
        while (current != NULL) {
            PageTableEntry* next = current->next;
            free(current);
            current = next;
        }
    }
    free(table);
}

// Main function to demonstrate the hash page table
int main() {
    // Initialize page table with 32 virtual pages and 16 physical frames
    HashPageTable* table = init_page_table(32, 16);
    
    // Insert some pages
    printf("Inserting pages into the hash table...\n");
    for (int i = 0; i < 20; i++) {
        int virtual_page = i;
        int physical_frame = i % table->num_frames;
        
        if (insert_page(table, virtual_page, physical_frame)) {
            printf("Inserted: Virtual Page %d -> Physical Frame %d\n", 
                   virtual_page, physical_frame);
        } else {
            printf("Failed to insert Virtual Page %d\n", virtual_page);
        }
    }
    
    // Print the current state of the page table
    print_page_table(table);
    
    // Perform some lookups
    printf("\nPerforming page lookups:\n");
    int test_pages[] = {0, 5, 10, 15, 31};
    for (int i = 0; i < 5; i++) {
        int virtual_page = test_pages[i];
        int physical_frame = lookup_page(table, virtual_page);
        
        if (physical_frame != INVALID_PAGE) {
            printf("Found: Virtual Page %d -> Physical Frame %d\n", 
                   virtual_page, physical_frame);
        } else {
            printf("Virtual Page %d not found\n", virtual_page);
        }
    }
    
    // Clean up
    free_page_table(table);
    return 0;
}