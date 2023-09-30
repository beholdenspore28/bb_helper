#include "stdio.h"
#include "blib_data.h"

void blib_linkedList_example(){
	printf(
			"\n"
			"========================================\n"
			"           LINKED LIST EXAMPLE          \n"
			"========================================\n"
			"\n"
		  );

	blib_linkedList_t* list = blib_linkedList_alloc();
	blib_linkedList_append(list, 1);
	blib_linkedList_append(list, 2);
	blib_linkedList_append(list, 3);
	blib_linkedList_print(list);
	blib_linkedList_free(list);
}

void blib_fileBuffer_example(){
	printf("\n\nfileBuffer\n\n");
}

//this is a test function. ignore it.
void blib_arrayList_example(){
	printf(
			"\n"
			"========================================\n"
			"            ARRAY LIST EXAMPLE          \n"
			"========================================\n"
			"\n"
		  );

	blib_arrayList_t* myList = blib_arrayList_alloc(sizeof(int));
	blib_arrayList_push(myList, 1);
	blib_arrayList_pop(myList);
	blib_arrayList_push(myList, 2);
	blib_arrayList_push(myList, 3);
	// blib_arrayList_print(myList);
	blib_arrayList_free(myList);
}

int main () {
	blib_linkedList_example();
	blib_fileBuffer_example();
	blib_arrayList_example();
}
