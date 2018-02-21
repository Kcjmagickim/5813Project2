#include <stdint.h>
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdio.h>

#include "memory.h"
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
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
