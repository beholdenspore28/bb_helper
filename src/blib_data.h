/*
===============================================================================

				8 oooooooooo.  ooooo        ooooo oooooooooo.  8 
				8 `888'   `Y8b `888'        `888' `888'   `Y8b 8 
				8  888     888  888          888   888     888 8 
				   888oooo888'  888          888   888oooo888'   
				8  888    `88b  888          888   888    `88b 8 
				8  888    .88P  888       o  888   888    .88P 8 
				8 o888bood8P'  o888ooooood8 o888o o888bood8P'  8 


============================== Project Vision =================================

  This project is a general purpose tool library for tasks I believe to be 
common in software development. Blib is written in C89. I realise that no 
one asked for this and there is probably someone out there who has already done 
what I am trying to do here. The main goal for me is to learn the 
inner-workings of the code most people take for granted. This will allow me to 
completely understand all of the code that I use in my projects.

=================================== LEGAL =====================================

MIT License

Copyright (c) 2023 Benjamin Joseph Brooks

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

===============================================================================
*/

#if !defined(BLIB_DATA_H)
#define BLIB_DATA_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

/*=============================== ARRAY_LIST ================================*/

//initial capacity of a list
#define B_ARRAYLIST_INIT_CAP 2
#define B_ARRAYLIST_GROWTH_FACTOR 1.5f
#define BLIB_ARRAYLIST_TYPE int

// typedef struct blib_arrayList {
// 	int* data; 
// 	unsigned long length;
// 	unsigned long capacity;
// }blib_arrayList_t;
//
// blib_arrayList_t* blib_arrayList_alloc();
// void blib_arrayList_free(blib_arrayList_t* list);
// void blib_arrayList_push();
// void blib_arrayList_pop();
// void blib_arrayList_print(blib_arrayList_t* list);

typedef struct blib_arrayList {
	BLIB_ARRAYLIST_TYPE* data; 
	size_t elementSize;
	unsigned long length;
	unsigned long capacity;
}blib_arrayList_t;

blib_arrayList_t* blib_arrayList_alloc(size_t elementSize);
void blib_arrayList_free(blib_arrayList_t* list);
void blib_arrayList_push();
void blib_arrayList_pop();
void blib_arrayList_print(blib_arrayList_t* list);

/*=============================== LINKED_LIST ===============================*/

typedef struct blib_linkedList_node{
	int data;
	struct blib_linkedList_node* next;
}blib_linkedList_node_t;

typedef struct blib_linkedList{
	blib_linkedList_node_t* head;
}blib_linkedList_t;

blib_linkedList_t* blib_linkedList_alloc();
void blib_linkedList_print(blib_linkedList_t* list);
void blib_linkedList_free(blib_linkedList_t* list);
void blib_linkedList_append(blib_linkedList_t* list, int data);
/*===========================================================================*/
#endif /*BLIB_DATA_H*/
