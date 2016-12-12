#include <stdlib.h> /* malloc, free */
#include <string.h> /* strcmp, strdup */
#include <stdio.h>

#include "tree.h"

/* This is an AA-tree implementation. */

struct tree
{
	char *key;
	void *value;
	struct tree *left, *right;
	int level;
};

static struct tree sentinel = { "", NULL, &sentinel, &sentinel, 0 };

struct tree *ggl_tree_make(const char *key, void *value)
{
	struct tree *node = malloc(sizeof(struct tree));
	node->key = strdup(key);
	node->value = value;
	node->left = node->right = &sentinel;
	node->level = 1;
	return node;
}

void *ggl_tree_lookup(struct tree *node, const char *key)
{
	if (node) {
		while (node != &sentinel) {
			int c = strcmp(key, node->key);
			if (c == 0)
				return node->value;
			else if (c < 0)
				node = node->left;
			else
				node = node->right;
		}
	}
	return NULL;
}

static struct tree *ggl_tree_skew(struct tree *node)
{
	if (node->left->level == node->level) {
		struct tree *save = node;
		node = node->left;
		save->left = node->right;
		node->right = save;
	}
	return node;
}

static struct tree *ggl_tree_split(struct tree *node)
{
	if (node->right->right->level == node->level) {
		struct tree *save = node;
		node = node->right;
		save->right = node->left;
		node->left = save;
		node->level++;
	}
	return node;
}

struct tree *ggl_tree_insert(struct tree *node, const char *key, void *value)
{
	if (node && node != &sentinel) {
		int c = strcmp(key, node->key);
		if (c < 0)
			node->left = ggl_tree_insert(node->left, key, value);
		else
			node->right = ggl_tree_insert(node->right, key, value);
		node = ggl_tree_skew(node);
		node = ggl_tree_split(node);
		return node;
	}
	return ggl_tree_make(key, value);
}

void ggl_tree_free(struct tree *node)
{
	if (node && node != &sentinel) {
		ggl_tree_free(node->left);
		ggl_tree_free(node->right);
		free(node->key);
		free(node);
	}
}

void ggl_tree_print(struct tree *node, int level)
{
	int i;
	if (node->left != &sentinel)
		ggl_tree_print(node->left, level + 1);
	for (i = 0; i < level; ++i)
		putchar(' ');
	printf("%s = %s (%d)\n", node->key, (char*)node->value, node->level);
	if (node->right != &sentinel)
		ggl_tree_print(node->right, level + 1);
}
