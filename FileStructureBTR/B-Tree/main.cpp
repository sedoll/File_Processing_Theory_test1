#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>

#define MAX_TEST_COUNT 10 
#define MAX_KEY_RANGE 1000

int main(void)
{
	BTNode* root = NULL; 
	int i, rand_key;

	for (i = 0; i < MAX_TEST_COUNT; i++) {
		KeyPair kp = { rand() % MAX_KEY_RANGE , rand() };
		BT_insert_key(&root, kp);
		printf("%d, %d\n", kp.key, kp.offset);
	}

	return 0;
}