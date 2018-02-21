//__enable_irq() and __disable_irq(
//following functions as inline functions: BufferFull BufferEmpt
//_attribute__((always_inline)) inline   <normal-function-prototype-here>(<Params>);
//__attribute__((always_inline)) static inline   <normal-function-prototype-here>(<Params
//_INLINE __STATIC_INLIN

typedef struct {
	//base memory ptr
	//HEAD, TAIL
	//Length/size
	//Count
} CB_t;

typedef enum {
	//success
	//null ptr error
	//no length
	//full/empty
} CB_e;

<CB enum type> CB_init(<pointer of buffer type>, <length of buffer>);
//2 arguments: Pointer to the circular buffer, length to be reserved for the buffer
//returns the status of the circular buffer or an error codes
//The circular buffer structure needs to be allocated in heap memory
//The circular buffer memory array pointed to by the base pointer 
//needs to be allocated in heap memory
//allocate length number of items for the buffer memory section
//Two independent dynamic memory allocations should be called
//must check for success/failure from the return of malloc
//After allocating memory, the buffer members should properly initialize the buffer pointer
//head, tail, the length, and the count.

<CB enum type> CB_destroy(<pointer of buffer type>);
//The functions takes in a pointer to the circular buffer to be destroyed
//should deallocate both the structure and buffer memory region of heap memory using free
//returns the status of the circular buffer
//circular buffer pointer should be reset to NULL after all memory is returned to the heap

<CB enum type> CB_buffer_add_item(<buffer to add to>, <data to add>);
//2 arguments: Pointer to the circular buffer to add items	data to be added
//returns an enumeration that specifies the success, failure etc. of the function call
//consider the corner cases possible

<CB enum type> CB_buffer_remove_item(<buffer to remove from>, <variable to store data removed>);
//2 arguments: Pointer to the circular buffer  Variable to store/return the removed item
//returns an enumeration that specifies the success, failure etc. of the function call
//Must take into consideration the corner cases possible

<CB enum type> CB_is_full(<buffer to check>);
//check if it is full
//0 = Buffer is not full 	1 = Buffer is full
//should be implemented as an inline function with a few as operations as possible.

<CB enum type> CB_is_empty(<buffer to check>);
The function will take in the circular buffer pointer to check if it is empty
//0 = Buffer is not empty 	1 = Buffer is empty
should be implemented as an inline function with a few as operations as possible.

//<CB enum type> CB_peek(<buffer to peek into>, <position to peek>, <holder for the peeked value>);
//3 args: Pointer to the circular buffer 	position from the head of the buffer to peek into
//A pointer to hold the data you peeked at
//returns the status of the circular buffer or an error codes
//Must take into consideration the corner cases possible

//Define a two new macro function called that correctly enable/disable interrupts:
#define START_CRITICAL()
#define END_CRITICAL