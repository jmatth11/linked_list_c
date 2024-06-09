#include <stdlib.h>
#include "linked_list.h"

int linked_list_init(struct linked_list *ll) {
  ll->value = NULL;
  ll->next = NULL;
  ll->prev = NULL;
  return 0;
}

static inline struct linked_list* find_pos(struct linked_list *ll, size_t cur_pos, size_t target_pos) {
  if (ll == NULL) return NULL;
  if (cur_pos == target_pos) return ll;
  return find_pos(ll->next, cur_pos + 1, target_pos);
}

static inline struct linked_list* find_end(struct linked_list *ll) {
  if (ll == NULL) return NULL;
  if (ll->next == NULL) return ll;
  return find_end(ll);
}

int linked_list_insert(struct linked_list *ll, size_t pos, void* value) {
  struct linked_list *obj = find_pos(ll, 0, pos);
  if (obj == NULL) return 1;
  struct linked_list *tmp = (struct linked_list*)malloc(sizeof(struct linked_list));
  if (tmp == NULL) return 1;
  linked_list_init(tmp);
  tmp->prev = obj;
  tmp->value = value;
  obj->next = tmp;
  return 0;
}

int linked_list_append(struct linked_list *ll, void* value) {
  struct linked_list *obj = find_end(ll);
  if (obj == NULL) return 1;
  struct linked_list *tmp = (struct linked_list*)malloc(sizeof(struct linked_list));
  if (tmp == NULL) return 1;
  linked_list_init(tmp);
  tmp->prev = obj;
  tmp->value = value;
  obj->next = tmp;
  return 0;
}

struct linked_list* linked_list_get_pos(struct linked_list *ll, size_t pos) {
  return find_pos(ll, 0, pos);
}

int linked_list_delete(struct linked_list *ll, size_t pos, void** out_value) {
  struct linked_list *obj = find_pos(ll, 0, pos);
  if (obj == NULL) return 1;
  obj->prev->next = obj->next;
  obj->next->prev = obj->prev;
  *out_value = obj->value;
  free(obj);
  return 0;
}

void linked_list_free(struct linked_list *ll) {
  linked_list_init(ll);
}

