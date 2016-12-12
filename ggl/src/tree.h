#pragma once

struct tree *ggl_tree_make(const char *key, void *value);
struct tree *ggl_tree_insert(struct tree *node, const char *key, void *value);
void *ggl_tree_lookup(struct tree *node, const char *key);
void ggl_tree_free(struct tree *node);
