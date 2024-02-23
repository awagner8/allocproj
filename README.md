**Objectives:**
- Gain familiarity with a simulated segregated heap allocator.
- Understand how a heap manager keeps track of its memory.

---

**Format:**

In this project will implement a segregated heap allocator that keeps track of the memory used.

This project has three functions in need of implementation, all of which are in `alloc.c`.
You do not need to (and really shouldn't) modify any other files in the project. Doing so may cause certain tests and compilation commands to break.

Your allocator should function as an interface between someone's program and the heap. Internally, it will use the C standard library's `malloc` function, but the user of your interface will always call `my_malloc` and `my_free` from `alloc.h` instead of using `malloc` and `free`. From the user's perspective, your functions should behave the same way as the default ones.

---

**Understanding Helper/Util Files:**

For every project, we always give you certain files like `.h` header files and `.c` util files to let you inspect the the code elements/data structures you will use in the project. Before working on the project, we strongly recommend reading the explanations below.

**`alloc.h`**

This file contains the function headers and struct definitions for elements in `alloc.c`

The first two function headers tell `alloc_test.c` (which uses functions and variables from `alloc.c` and is also the wrapper program that helps run tests) what functions and variables are accessible/can be called or used.

Also, notice that `NUM_HEAP_BLOCKS` is defined at the bottom as exactly 8. This means that every time the `allocate_slab()` function is called, 8 blocks will be allocated. More on when `allocate_slab()` should be called and what it is supposed to do below.

In addition, please take a good look at the `blk_header_t` struct. One of these will go before each block allocated. This struct stores the size of the block it's in front, and it stores a pointer to the next block header. A diagram of an example set of a 4 allocated blocks in memory, starting at address X, is shown below:

|address|data|
|:-----:|:---:|
|X|blk_header_t: [size = 8, next = X+24]|
|X + 16|block [8 bytes]|
|X + 24|blk_header_t [size = 32, next = X+72]|
|X + 40|block [32 bytes]|
|X + 72|blk_header_t [size = 16, next = X + 104]|
|X + 88|block [16 bytes]|
|X + 104|blk_header_t [size = 64, next = NULL]|
|X + 120|block [64 bytes]|

**NOTE:** The `next` field of a `blk_header_t` points to the next `blk_header_t` in the list, so we need to do some pointer arithmetic. Also be mindful to always cast variables to the proper types. Blocks are `void*` and headers are `blk_header_t*`. Also note that the start of a bin points to the block header. 

Hopefully you noticed that the heap is a `void*` array (aka. an array of `void*`s). The tester will access this array to check the linked list of blocks at each array index (or bin). 

The final thing to note is the function `void count_heap_blks()` will be used in the test, so DO NOT modify this function. The other two functions `print_bin()` and `print_heap()` are there for you to use in `alloc.c` for debugging. ***They must be removed/commented out before running tests or submitting to Gradescope***

---

**What you are implementing:**

**`alloc.c`**

There are three functions you should implement. They are also listed in the code in the order which you should implement them.

Before implementing the functions, please review CS:APP 9.9.14, which describes how simple segregated storage works.

1. `void *allocate_slab(unsigned int size)`
   - This function is called by `my_alloc`  if the free list doesn't have enough free blocks of the appropriate size. It will
   allocate and return a new slab of memory of the
   desired size.
   - The returned slab is just an empty block of memory. It will not have any
   free list data set. Configuring this data
   is the job of the calling function. The calling function should ensure that there is enough space to write the block header in addition to the space that will be given to the user.
   - It will return the malloc'd memory as a void pointer, or NULL if the allocated memory would exceed `max_heap_size`.

2. `void *my_alloc(unsigned int size)`
    - This function will take in a size specified by the test and match the size with the correct bin of the heap array to get the free list. If there are blocks in the free list, it returns the first one. If there are no blocks remaining, it will call `allocate_slab` or to allocate more blocks,
    then return a newly allocated block. 
    - To calculate the slab size for `allocate_slab`, use basic arithmetic with the bin number to get segregated size, add on the blk_header_t size (because every block needs a header allocated), and multiply that computed size with the `NUM_HEAP_BLOCKS` to get total size for the slab.
    - ***Important!*** If the requested allocation (from `allocate_slab()`) exceeds the maximum heap size your code should print `"Malloc failed, out of memory!\n"` and exit with 0 value without doing anything else.

3. `void my_free(void *ptr)`
   - This function will take the pointer to a block (not to its block header!) and insert the block into the front of the appropriate bin. You can tell which bin owns the block by looking at the `blk_header_t` info before the block in memory (Hint: use pointer arithmetic to get the header of that block).
   - You will have to modify `heap[bin]` and insert the given block (`ptr`) into the `heap[bin]`

---

**How to test your code:**

We have included a python tester and a settings.json file as well as all of the test input files. Below are all the ways to test your code.

1. Run `make` to compile your `alloc.c` with a wrapper called `alloc_test.c`

2. The Python Tester runs all of the tests listed in `settings.json` and reports a point value for each test.
    ```bash
    python3 hwtest.py ALL
    ```
3. You can run individual tests by typing each value of a particular test's `args` field of the `settings.json` and pasting them into the terminal after `./alloc_test` and comparing the printed results with the expected file. Always remember that you can use `gdb` if you want to debug the behavior
of your functions while running the C tester.
Below are examples for tests 0 and 2 from the test kit.
   
    `-f <filename>` sets the file to read. The provided files are t1.txt through t6.txt.
    A file consists of lines of allocs and frees. Here's some example file contents with
    an explanation:
    ```
    a 32 0
    c 0 0
    f 2 0
    ```
    The first line allocates a 32-byte block and gives it an id of 0. The second
    line prints out the number of heap blocks in each free list. The third
    line frees the block with id 0 (the second token "2" is ignored).
    
    `-s <max_heap_size>` sets the max heap size
    ```bash
    ./alloc_test -f t1.txt
    ./alloc_test -f t3.txt -s 2048
    ```
    
---

**Submission:**

- Submit your project on Gradescope using the GitLab submission process.

- ***Team specific instructions*** 
  - Teams should only do one submission via group submission.
  - Teams must also edit the file called reflection.txt and include a detailed description of each team member's contributions to the project.
