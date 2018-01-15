// B-Tree.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdbool.h>

btree t = NULL;
node_pointer current_node = NULL;

node_pointer addElementToNode(node_pointer n, stdelement e) {
	//n->number_of_elements++;
	//n->elements[n->number_of_elements - 1] = e;

	int i = 0, k = n->number_of_elements;
	while (e > n->elements[i])
	{
		i++;
	}
	while (k > i)
	{
		n->elements[k] = n->elements[k - 1];
		k--;
	}
	n->elements[k] = e;
	n->number_of_elements++;

	return n;
}

node_pointer delElementFromNode(node_pointer n, stdelement e) {
	return n;
}

node_pointer createNode(void) {
	int i = 0;
	node_pointer tmp = (node_pointer)malloc(sizeof(struct node));
	assert(tmp);

	tmp->number_of_elements = 0;
	while (i < MAXNODE)
	{
		tmp->elements[i] = 0;
		i++;
	}
	while (i > -1)
	{
		tmp->children[i] = NULL;
		i--;
	}

	return tmp;
}

node_pointer findElementInTree(btree t, stdelement e, bool * success) {
	*success = false;
	node_pointer p = t->root;
	node_pointer curr = NULL;

	while (!*success && (p != NULL)) {
		curr = p;

		for (int i = 0; i < p->number_of_elements; i++) {
			if (e == p->elements[i]) {
				*success = true;
				break;
			}
			if (e < p->elements[i]) {
				p = p->children[i];
				break;
			}
			if (i == p->number_of_elements - 1) {
				p = p->children[i + 1];
				break;
			}
		}
	}

	return curr;
}

node_pointer splitNode(node_pointer n) {
	//stdelement tmpElems[MAXNODE + 1] = calloc(MAXNODE + 1, sizeof(stdelement));
	//assert(tmpElems);
	node_pointer z = createNode();
	int i = ORDER;
	while (i < MAXNODE)
	{
		addElementToNode(z, n->elements[i]);
		z->children[i - ORDER] = n->children[i];// i + 1 - ORDER maybe??
		n->elements[i] = 0;// not really nessesarry
		n->number_of_elements--;
		i++;
	}

	return z;
}

int searchPos(int n, stdelement * arr, stdelement e) {
	int low = -1, high = n, mid;
	/* invariant: a[lo] < key <= a[hi] */

	while (low + 1 < high)
	{
		mid = (low + high) / 2;
		if (arr[mid] == e) {
			return mid;
		}
		else {
			if (arr[mid] < e) {
				low = mid;
			}
			else {
				high = mid;
			}
		}
	}

	return high;
}

btree insertElementIntoTree(btree t, stdelement e) {
	bool success = false;
	node_pointer tmp = findElementInTree(t, e, &success);

	if (success) {
		// element allready in tree;
		return t;
	}

	if (tmp == NULL) {
		t->root = addElementToNode(createNode(), e);
	}
	else {
		if (tmp->number_of_elements < MAXNODE) {
			addElementToNode(tmp, e);
		}
		else {
			// TODO
			// splitNode
			int pos = searchPos(tmp->number_of_elements, tmp->elements, e);

			if (pos == ORDER) {
				if (tmp->parent == NULL) {
					node_pointer x = addElementToNode(createNode(), e);
					x->children[1] = splitNode(tmp);
					x->children[0] = tmp;
					t->root = x;
				}
				else {
					addElementToNode(tmp->parent, e);
					int pos = searchPos(tmp->parent->number_of_elements, tmp->parent->elements, e);
					tmp->parent->children[pos + 1] = splitNode(tmp);
					tmp->parent->children[pos] = tmp;
				}
			}
		}
	}

	return t;
}

btree createBTree(stdelement e) {
	btree tmp = (btree)calloc(1, sizeof(btree));
	assert(tmp);

	tmp->root = addElementToNode(createNode(), e);

	return tmp;
}

//bool findElementInTree(stdelement e) {
//	bool success = false;
//	node_pointer p = t->root;
//	current_node = NULL;
//
//	while (!success && (p != NULL)) {
//		current_node = p;
//
//		for (int i = 0; i < p->number_of_elements; i++) {
//			if (e == p->elements[i]) {
//				success = true;
//				break;
//			}
//			if (e < p->elements[i]) {
//				p = p->children[i];
//			}
//			if (i == p->number_of_elements - 1) {
//				p = p->children[i + 1];
//			}
//		}
//	}
//
//	return success;
//}

//bool insert(stdelement e) {
//	bool success = !findkey(e);
//
//	if (success) {
//		if (t->root != NULL) {
//			insert_into_node(current_node, e);
//		}
//		else {
//			t->root = (node_pointer)malloc(sizeof(struct node));
//			t->root->elements[0] = e;
//		}
//	}
//
//	return false;
//}
//
//void insert_into_node(node_pointer cur, stdelement e) {
//	node_pointer mid = NULL;
//
//	if (cur->number_of_elements == MAXNODE) {
//		mid = cur->elements[ORDER];
//
//		node_pointer new_node = (node_pointer)malloc(sizeof(struct node));
//
//		for (size_t i = ORDER + 1; i < cur->number_of_elements; i++) {
//			new_node->elements[i] = cur->elements[i];
//		}
//
//		if (cur == t->root) {
//			// mid == new root
//		}
//		else {
//			insert_into_node(cur->parent, mid);
//		}
//	}
//}

int main()
{
	//t = create_btree();
	//t->root = createNode(30);

	t = insertElementIntoTree(
		insertElementIntoTree(
			insertElementIntoTree(
				createBTree(30)
				, 38)
			, 42)
		, 10);

	insertElementIntoTree(t, 35);

	save_btree("D:\\Projects\\EPA\\B-Tree\\svg\\test.svg", t);

	return 0;
}
