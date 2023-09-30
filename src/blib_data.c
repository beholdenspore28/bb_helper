#include "blib_data.h"

/*=============================== LINKED LIST ===============================*/

blib_linkedList_t* blib_linkedList_alloc(){
	blib_linkedList_t* newList = 
		(blib_linkedList_t*) malloc(sizeof(blib_linkedList_t));
	newList->head = NULL;
	return newList;	
}

//loop through the whole list and print
//all it's elements.
void blib_linkedList_print(blib_linkedList_t* list){
	blib_linkedList_node_t* iter = list->head;
	while(iter != NULL){
		printf("data: %d\n", iter->data);
		iter=iter->next;
	}
}

void blib_linkedList_free(blib_linkedList_t* list){
	if (list == NULL)
		return;

	blib_linkedList_node_t* current = list->head;

	if (current == NULL){
		free(list);
		return;
	}

	blib_linkedList_node_t* next = current->next;
	while(current != NULL){
		free(current);
		current = next;

		if (current != NULL)
			next = current->next;
	}

	free(list);
}

void blib_linkedList_append(blib_linkedList_t* list, int data){
	if (list->head == NULL){ 
		//case 1, list is empty
		//add a new node at the head of the list
		blib_linkedList_node_t* newNode = 
			(blib_linkedList_node_t*) malloc(sizeof(blib_linkedList_node_t));
		newNode->data = data;
		newNode->next = NULL;
		list->head = newNode;
	} else {
		//case 2, list is not empty
		//loop through the whole list
		blib_linkedList_node_t* iter = list->head;
		while(iter->next != NULL)
			iter=iter->next;

		//create a new node at the end of the list
		blib_linkedList_node_t* newNode = 
			(blib_linkedList_node_t*) malloc(sizeof(blib_linkedList_node_t));
		newNode->data = data;
		newNode->next = NULL;
		iter->next = newNode;
	}
}

/*=============================== FILE BUFFER ===============================*/

void blib_fileBuffer_close(blib_fileBuffer_t file){
	free(file.text);
}

blib_fileBuffer_t blib_fileBuffer_read(const char *filename){
	FILE *file = fopen(filename, "r");
	if (file == NULL) {
		blib_fileBuffer_t ret;
		ret.error = true;
		return ret;
	}

	size_t alloc = B_FILE_BUFFER_CHUNK_SIZE * B_FILE_BUFFER_GROWTH;
	char *buf = (char *) malloc(alloc);
	size_t len = 0;
	while (!feof(file)){
		if (alloc - len >= B_FILE_BUFFER_CHUNK_SIZE + 1){
			alloc += B_FILE_BUFFER_CHUNK_SIZE;
			alloc *= B_FILE_BUFFER_GROWTH;
			buf = (char *) realloc((void *) buf, alloc);
		}
		int got = fread((void *) &buf[len], 1, B_FILE_BUFFER_CHUNK_SIZE, file);
		len += got;
		if (got != B_FILE_BUFFER_CHUNK_SIZE){
			break;
		}
	}

	buf[len] = '\0';
	fclose(file);
	blib_fileBuffer_t ret;
	ret.text = buf;
	ret.len = len;
	ret.error = false;
	return ret;
}

/*=============================== ARRAY LIST ================================*/

// void blib_arrayList_print(blib_arrayList_t* list){
// 	for(int i = 0; i < list->length; i++){
// 		printf("data %d %d\n", i, list->data[i]);
// 	}
// }
//
// //Allocate a new list to the heap
// //Returns a pointer to the newly allocated list.
// blib_arrayList_t* blib_arrayList_alloc(){
// 	blib_arrayList_t* newList = 
// 		(blib_arrayList_t*) malloc(sizeof(blib_arrayList_t));
// 	newList->capacity = B_ARRAYLIST_INIT_CAP;
// 	newList->data = (int*) malloc(sizeof(int) * B_ARRAYLIST_INIT_CAP);
// 	return newList;
// }
//
// //Add a new element to the list.
// //List will grow x2 on reallocation
// void blib_arrayList_push(blib_arrayList_t* list, int value){
// //	printf("prealloc len %lu \n prealloc cap %lu\n", list->length, list->capacity);
// 	list->length++;
// 	
// 	if (list->length > list->capacity) { 
// 		/*list cap must be greater than one in order to multiply it by
// 		B_ARRAYLIST_FACTOR*/
// 		assert(list->capacity > 1);
// 		//List is full. Allocate more space
// 		list->capacity *= B_ARRAYLIST_GROWTH_FACTOR;
// 		list->data = realloc(list->data, sizeof(int) * list->capacity);
// //		printf("&data %p @ %x", &list->data, &list->data);
// 	}
//
// //	printf("postalloc len %lu \n postalloc cap %lu\n", list->length, list->capacity);
// 	//add new element to the list
// 	list->data[list->length - 1] = value;
// }
//
// void blib_arrayList_pop(blib_arrayList_t* list){
// 	list->length--;
// }
//
// void blib_arrayList_free(blib_arrayList_t* list){
// 	free(list->data);
// 	free(list);	
// }

//TODO add blib_arrayList_print() again

//Allocate a new list to the heap
//Returns a pointer to the newly allocated list.
blib_arrayList_t* blib_arrayList_alloc(size_t elementSize){
	blib_arrayList_t* newList = 
		(blib_arrayList_t*) malloc(sizeof(blib_arrayList_t));

	newList->capacity = B_ARRAYLIST_INIT_CAP;
	newList->elementSize = elementSize;

	newList->data = 
		(void*) malloc(sizeof(newList->elementSize) * B_ARRAYLIST_INIT_CAP);

	return newList;
}

//Add a new element to the list.
//List will grow x2 on reallocation
void blib_arrayList_push(blib_arrayList_t* list, int value){
	list->length++;
	
	if (list->length > list->capacity) { 
		assert(list->capacity > 1);
		//List is full. Allocate more space
		list->capacity *= B_ARRAYLIST_GROWTH_FACTOR;
		list->data = 
			realloc(list->data, sizeof(list->elementSize) * list->capacity);
	}

	//add new element to the list
	int* data = (int*) list->data;
	data[list->length - 1] = value;
	// list->data[list->length - 1] = value;
}

void blib_arrayList_pop(blib_arrayList_t* list){
	list->length--;
}

void blib_arrayList_free(blib_arrayList_t* list){
	free(list->data);
	free(list);	
}
