# Virtual-Memory-Allocator
The implemented virtual memory allocator has the following functionality (or API):

-a hidden buffer, on which direct operations are prohibited, called the kernel buffer or arena; this is a generic vector, which holds the information allocated by you

-a doubly linked list holding the allocated areas in the arena; it also stores adjacent allocated areas, represented in turn as doubly linked lists
