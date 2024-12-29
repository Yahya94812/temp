class HashPageTable:
    def __init__(self, table_size=64, page_size=4096):
        self.table_size = table_size
        self.page_size = page_size
        self.page_table = [[] for _ in range(table_size)]  # Using chaining for collision resolution
        self.stats = {
            'lookups': 0,
            'hits': 0,
            'misses': 0,
            'collisions': 0
        }
    
    def _hash_function(self, virtual_address):
        """Simple hash function that maps virtual address to page table index"""
        return (virtual_address // self.page_size) % self.table_size
    
    def add_page_entry(self, virtual_address, frame_number):
        """Add a new page table entry"""
        page_number = virtual_address // self.page_size
        hash_index = self._hash_function(virtual_address)
        
        # Check for existing entry
        for entry in self.page_table[hash_index]:
            if entry[0] == page_number:
                entry[1] = frame_number
                return
        
        # Add new entry, noting collision if bucket is not empty
        if self.page_table[hash_index]:
            self.stats['collisions'] += 1
        
        self.page_table[hash_index].append([page_number, frame_number])
    
    def lookup_page(self, virtual_address):
        """Look up a page table entry and return frame number"""
        self.stats['lookups'] += 1
        page_number = virtual_address // self.page_size
        hash_index = self._hash_function(virtual_address)
        
        # Search in the bucket
        for entry in self.page_table[hash_index]:
            if entry[0] == page_number:
                self.stats['hits'] += 1
                return {
                    'frame_number': entry[1],
                    'offset': virtual_address % self.page_size,
                    'physical_address': (entry[1] * self.page_size) + (virtual_address % self.page_size)
                }
        
        self.stats['misses'] += 1
        return None
    
    def print_statistics(self):
        """Print current statistics of the hash page table"""
        print("\nHash Page Table Statistics:")
        print(f"Table Size: {self.table_size} entries")
        print(f"Page Size: {self.page_size} bytes")
        print(f"Total Lookups: {self.stats['lookups']}")
        print(f"Hits: {self.stats['hits']}")
        print(f"Misses: {self.stats['misses']}")
        print(f"Collisions: {self.stats['collisions']}")
        if self.stats['lookups'] > 0:
            hit_rate = (self.stats['hits'] / self.stats['lookups']) * 100
            print(f"Hit Rate: {hit_rate:.2f}%")
    
    def print_table(self):
        """Print the current state of the page table"""
        print("\nHash Page Table Contents:")
        for i, bucket in enumerate(self.page_table):
            if bucket:  # Only print non-empty buckets
                print(f"Index {i}: {bucket}")

# Example usage and demonstration
def demonstrate_hash_page_table():
    # Create a hash page table
    hpt = HashPageTable(table_size=8, page_size=4096)
    
    # Add some page entries
    test_entries = [
        (0, 100),          # Should hash to 0
        (4096, 101),       # Should hash to 1
        (8192, 102),       # Should hash to 2
        (12288, 103),      # Should hash to 3
        (32768, 104),      # Should create collision
    ]
    
    print("Adding page entries...")
    for virtual_addr, frame in test_entries:
        hpt.add_page_entry(virtual_addr, frame)
        print(f"Added mapping: Virtual Address {virtual_addr} -> Frame {frame}")
    
    # Demonstrate lookups
    print("\nPerforming lookups...")
    test_lookups = [0, 4096, 8192, 12288, 32768, 16384]
    
    for addr in test_lookups:
        result = hpt.lookup_page(addr)
        if result:
            print(f"Lookup for {addr}:")
            print(f"  Frame Number: {result['frame_number']}")
            print(f"  Offset: {result['offset']}")
            print(f"  Physical Address: {result['physical_address']}")
        else:
            print(f"Page fault: No mapping found for address {addr}")
    
    # Print statistics and table contents
    hpt.print_statistics()
    hpt.print_table()

if __name__ == "__main__":
    demonstrate_hash_page_table()