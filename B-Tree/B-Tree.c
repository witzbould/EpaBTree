// B-Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h>

btree t = NULL;
node_pointer current_node = NULL;

bool findkey(stdelement e) {
	bool success = false;
	node_pointer p = t->root;
	current_node = NULL;

	while (!success && (p != NULL)) {
		current_node = p;

		for (size_t i = 0; i < p->number_of_elements; i++) {
			if (e == p->elements[i]) {
				success = true;
				break;
			}
			if (e < p->elements[i]) {
				p = p->children[i];
			}
			if (i == p->number_of_elements - 1) {
				p = p->children[i + 1];
			}
		}
	}

	return success;
}

bool insert(stdelement e) {
	bool success = !findkey(e);

	if (success) {
		if (t->root != NULL) {
			// TODO insert_into_node(current_node, e)
		}
		else {
			t->root = (node_pointer)malloc(sizeof(struct node));
			t->root->elements[0] = e;
		}
	}

	return false;
}

void insert_into_node(node_pointer cur, stdelement e) {
}

int main()
{
	return 0;
}
