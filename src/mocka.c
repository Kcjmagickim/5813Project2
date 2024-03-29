#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "memory.h"
#include "conversion.h"
#include "circbuf.h"
#include "mocka.h"

uint8_t length = 4;
uint8_t i;

static void test_memmove1(void **state){	//SRC & DST = NULL
	uint8_t * test;
  	test=my_memmove(NULL,NULL,i);
	assert_true(test==NULL);
}

static void test_memmove2(void **state){	//No overlap
  	uint8_t * set;
  	uint8_t * ptra;
  	uint8_t * ptrb;

	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);

	ptra = &set[0];
	ptrb = &set[8];

	for( i = 0; i < 16; i++){
		set[i] = i;
	}
	
	my_memmove(ptra, ptrb, 8);

	for (i = 0; i < 8; i++){
		assert_int_equal(i, set[i+8]);
	}

	free_words( (uint32_t*)set );
}

static void test_memmove3(void **state){	//SRC in DST
  	uint8_t * set;
  	uint8_t * ptra;
  	uint8_t * ptrb;

	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);

	ptra = &set[0];
	ptrb = &set[4];

	for( i = 0; i < 16; i++){
		set[i] = i;
	}
	
	my_memmove(ptrb, ptra, 10);

	for (i = 0; i < 10; i++){
		assert_int_equal(i+4, set[i]);
	}

	free_words( (uint32_t*)set );
}

static void test_memmove4(void **state){	//DST in SRC
  	uint8_t * set;
  	uint8_t * ptra;
  	uint8_t * ptrb;

	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);

	ptra = &set[0];
	ptrb = &set[4];

	for( i = 0; i < 16; i++){
		set[i] = i;
	}
	
	my_memmove(ptra, ptrb, 10);

	for (i = 0; i < 10; i++){
		assert_int_equal(i, set[i+4]);
	}

	free_words( (uint32_t*)set );
}

static void test_memmove5(void **state){	//DST == SRC
  	uint8_t * set;
  	uint8_t * ptra;

	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);

	ptra = &set[0];

	for( i = 0; i < 16; i++){
		set[i] = i;
	}
	
	my_memmove(ptra, ptra, 8);

	for (i = 0; i < 16; i++){
		assert_int_equal(i, set[i]);
	}

	free_words( (uint32_t*)set );
}

static void test_memset1(void **state){	//SRC = NULL
	uint8_t * test;
  	test=my_memset(NULL,length,length);
	assert_true(test==NULL);
}

static void test_memset2(void **state){	//set check
  	uint8_t * set;
	
	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);
	
	my_memset(set, 16, length);

	for (i = 0; i < 16; i++){
		assert_int_equal(length, set[i]);
	}
	free_words( (uint32_t*)set );
}

static void test_memzero1(void **state){	//SRC = NULL
	uint8_t * test;
  	test=my_memzero(NULL,length);
	assert_true(test==NULL);
}

static void test_memzero2(void **state){	//set check
  	uint8_t * set;
	
	set = (uint8_t*)reserve_words(length);
	assert_true(set!=NULL);
	
	my_memzero(set, 16);

	for (i = 0; i < 16; i++){
		assert_int_equal(0, set[i]);
	}
	free_words( (uint32_t*)set );
}

static void test_reverse1(void **state){	//SRC = NULL
	uint8_t * test;
  	test=my_reverse(NULL,length);
	assert_true(test==NULL);
}

static void test_reverse2(void **state){	//Odd length
  	uint8_t * set;
	
	set = (uint8_t*)reserve_words(15);
	assert_true(set!=NULL);
	for (i = 0; i < 15; i++){
		set[i]=i;
	}
	
	my_reverse(set, 15);

	for (i = 0; i < 15; i++){
		assert_int_equal(14-i, set[i]);
	}
	free_words( (uint32_t*)set );
}

static void test_reverse3(void **state){	//Even length
  	uint8_t * set;
	
	set = (uint8_t*)reserve_words(16);
	assert_true(set!=NULL);
	for (i = 0; i < 16; i++){
		set[i]=i;
	}
	
	my_reverse(set, 16);

	for (i = 0; i < 16; i++){
		assert_int_equal(15-i, set[i]);
	}
	free_words( (uint32_t*)set );
}

static void test_reverse4(void **state){	//String reversal
  	char set[6] = "hello";
	assert_true(set!=NULL);
	
	my_reverse((uint8_t*) set, 5);
	char check[6] = "olleh";
	for (i = 0; i < 6; i++){
		assert_true(set[i]==check[i]);
	}
}

static void test_atoi1(void **state){	//NULL
  	uint8_t test;
  	test = my_atoi(NULL, 1, 10);
  	assert_int_equal((uint8_t) -1, test);
}

static void test_atoi2(void **state){	//zero
  	uint8_t test;
  	test = my_atoi((uint8_t*) "0", 2, 10);
  	assert_int_equal((uint8_t) 0, test);
}

static void test_atoi3(void **state){	//max
  	uint32_t test;
  	test = my_atoi((uint8_t*) "4294967295", 11, 10);
  	assert_int_equal(4294967295, test);
  	assert_int_equal(0, test+1);
}

static void test_itoa1(void **state){	//NULL
  	uint8_t digits;
  	digits = my_itoa(0, NULL, 10);
  	assert_int_equal((uint8_t) -1,digits);
}

static void test_itoa2(void **state){	//zero
  	char test[2];
  	uint8_t digits;
  	digits = my_itoa(0, (uint8_t*) test, 10);
  	assert_int_equal((uint8_t) 2, digits);
  	assert_true(test[0] == '0');
}

static void test_itoa3(void **state){	//Max
  	char test[11];
  	char * tester = &test[0];
  	char * ans = "2147483647";
  	uint8_t digits;
  	digits = my_itoa(2147483647, (uint8_t*) test, 10);
  	assert_int_equal((uint8_t) 11, digits);
  	for(i=0; i<11; i++){
  	  	assert_true(*tester == *ans);
  	  	tester+=sizeof(uint8_t); ans+=sizeof(uint8_t);
  	  }
}

static void test_endian1(void **state){	//NULL input
	int8_t ret;
	ret = swap_data_endianness(NULL, sizeof(ret) );
   	assert_true(ret == SWAP_ERROR);
}

static void test_endian2(void **state){	//check swap works
	int8_t ret;
	uint32_t data = 0x1234567;
	ret = swap_data_endianness( (uint8_t*)&data, sizeof(data) );
   	assert_true(ret == SWAP_NO_ERROR);
   	assert_true(data == 0x67452301);
}

static void test_endian3(void **state){	//check double swap restores
	int8_t ret;
	uint32_t data = 0x1234567;
	ret = swap_data_endianness( (uint8_t*)&data, sizeof(data) );
	assert_true(ret == SWAP_NO_ERROR);
	ret = swap_data_endianness( (uint8_t*)&data, sizeof(data) );
   	assert_true(ret == SWAP_NO_ERROR);
   	assert_true(data == 0x1234567);
}

static void test_circbuf1(void **state){ //check allocation
	CB_t * buffer = malloc(sizeof(CB_t));
	assert_non_null(buffer);
	CB_e ret = CB_init(buffer, 10);
	assert_true(ret == SUCCESS);
	ret = CB_destroy(buffer);
	assert_true(ret == SUCCESS);
	free(buffer);
}

static void test_circbuf2(void **state){ //check NULL PTR
	CB_t * buffer = malloc(sizeof(CB_t));
	assert_non_null(buffer);
	CB_e ret = CB_init(NULL, 10);
	assert_true(ret == NULL_PTR);
	ret = CB_destroy(NULL);
	assert_true(ret == NULL_PTR);
	free(buffer);
}

static void test_circbuf3(void **state){ //check Add/Remove
	CB_t * buffer = malloc(sizeof(CB_t));
	assert_non_null(buffer);
	CB_e ret = CB_init(buffer, 3);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_add_item(buffer, 1);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_add_item(buffer, 2);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_add_item(buffer, 3);
	assert_true(ret==SUCCESS);
	uint8_t out;
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==1);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==2);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==3);
	ret = CB_destroy(buffer);
	free(buffer);
}

static void test_circbuf4(void **state){ //check is_full, is_empty
	CB_t * buffer = malloc(sizeof(CB_t));
	CB_e ret = CB_init(buffer, 3);
	ret = CB_buffer_add_item(buffer, 1);
	ret = CB_buffer_add_item(buffer, 2);
	ret = CB_buffer_add_item(buffer, 3);
	uint8_t out;
	ret = CB_is_full(buffer);
	assert_true(ret==FULL);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_is_empty(buffer);
	assert_true(ret==EMPTY);
	ret = CB_destroy(buffer);
	free(buffer);
}

static void test_circbuf5(void **state){ //check wrap around
	uint8_t out;
	CB_t * buffer = malloc(sizeof(CB_t));
	CB_e ret = CB_init(buffer, 3);
	ret = CB_buffer_add_item(buffer, 1);
	ret = CB_buffer_add_item(buffer, 2);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);

	ret = CB_buffer_add_item(buffer, 3);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_add_item(buffer, 4);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_add_item(buffer, 5);
	assert_true(ret==SUCCESS);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==3);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==4);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==SUCCESS);
	assert_true(out==5);
	ret = CB_destroy(buffer);
	free(buffer);
}


static void test_circbuf6(void **state){ //check failure on empty and full
	CB_t * buffer = malloc(sizeof(CB_t));
	CB_e ret = CB_init(buffer, 3);
	ret = CB_buffer_add_item(buffer, 1);
	ret = CB_buffer_add_item(buffer, 2);
	ret = CB_buffer_add_item(buffer, 3);

	uint8_t out;
	ret = CB_buffer_add_item(buffer, 3);
	assert_true(ret==FULL);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);
	ret = CB_buffer_remove_item(buffer, &out);
	assert_true(ret==EMPTY);
	ret = CB_destroy(buffer);
	free(buffer);
}


int main(void){
	const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_memmove1),
        cmocka_unit_test(test_memmove2),
        cmocka_unit_test(test_memmove3),
        cmocka_unit_test(test_memmove4),
        cmocka_unit_test(test_memmove5),
        cmocka_unit_test(test_memset1),
        cmocka_unit_test(test_memset2),
        cmocka_unit_test(test_memzero1),
        cmocka_unit_test(test_memzero2),
        cmocka_unit_test(test_reverse1),
        cmocka_unit_test(test_reverse2),
        cmocka_unit_test(test_reverse3),
        cmocka_unit_test(test_reverse4),
        cmocka_unit_test(test_atoi1),
        cmocka_unit_test(test_atoi2),
        cmocka_unit_test(test_atoi3),
        cmocka_unit_test(test_itoa1),
        cmocka_unit_test(test_itoa2),
        cmocka_unit_test(test_itoa3),
        cmocka_unit_test(test_endian1),
        cmocka_unit_test(test_endian2),
        cmocka_unit_test(test_endian3),
        cmocka_unit_test(test_circbuf1),
        cmocka_unit_test(test_circbuf2),
        cmocka_unit_test(test_circbuf3),
        cmocka_unit_test(test_circbuf4),
        cmocka_unit_test(test_circbuf5),
        cmocka_unit_test(test_circbuf6),

    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
