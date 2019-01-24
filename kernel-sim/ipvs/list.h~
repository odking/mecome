#ifndef __TOOLS_LINUX_LIST_H
#define __TOOLS_LINUX_LIST_H


#define NULL 0

struct list_head {
        struct list_head *next, *prev;
};
#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) \
        struct list_head name = LIST_HEAD_INIT(name)

#ifndef offsetof
#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
#endif

#ifndef container_of
/**
 *  * container_of - cast a member of a structure out to the containing structure
 *   * @ptr:    the pointer to the member.
 *    * @type:  the type of the container struct this is embedded in.
 *     * @member:   the name of the member within the struct.
 *      *
 *       */
#define container_of(ptr, type, member) ({          \
        const typeof(((type *)0)->member) * __mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); })
#endif

/**
 *  * list_entry - get the struct for this entry
 *   * @ptr:    the &struct list_head pointer.
 *    * @type:  the type of the struct this is embedded in.
 *     * @member:   the name of the list_head within the struct.
 *      */
#define list_entry(ptr, type, member) \
        container_of(ptr, type, member)

/**
 *  * list_first_entry - get the first element from a list
 *   * @ptr:    the list head to take the element from.
 *    * @type:  the type of the struct this is embedded in.
 *     * @member:   the name of the list_head within the struct.
 *      *
 *       * Note, that list is expected to be not empty.
 *        */
#define list_first_entry(ptr, type, member) \
    list_entry((ptr)->next, type, member)

/**
 *  * list_next_entry - get the next element in list
 *   * @pos:    the type * to cursor
 *    * @member:    the name of the list_head within the struct.
 *     */
#define list_next_entry(pos, member) \
    list_entry((pos)->member.next, typeof(*(pos)), member)

/**
 *  * list_for_each_entry   -   iterate over list of given type
 *   * @pos:    the type * to use as a loop cursor.
 *    * @head:  the head for your list.
 *     * @member:   the name of the list_head within the struct.
 *      */
#define list_for_each_entry(pos, head, member)              \
    for (pos = list_first_entry(head, typeof(*pos), member);    \
            &pos->member != (head);                    \
            pos = list_next_entry(pos, member))

#define list_for_each_entry_safe(pos, n, head, member)          \
    for (pos = list_first_entry(head, typeof(*pos), member),    \
            n = list_next_entry(pos, member);           \
            &pos->member != (head);                    \
            pos = n, n = list_next_entry(n, member))

static inline void __list_add(struct list_head *new,
        struct list_head *prev,
        struct list_head *next)
{
    next->prev = new;
    new->next = next;
    new->prev = prev;
    prev->next = new;
}
static inline void list_add(struct list_head *new, struct list_head *head)
{
    __list_add(new, head, head->next);
}

static inline void __list_del(struct list_head * prev, struct list_head * next)
{
    next->prev = prev;
    prev->next = next;
}
static inline void list_del(struct list_head *entry)
{
    __list_del(entry->prev, entry->next);
}

static inline void INIT_LIST_HEAD(struct list_head *list)
{
    list->next = list;
    list->prev = list;
}

struct hlist_head {
        struct hlist_node *first;
};

struct hlist_node {
        struct hlist_node *next, **pprev;
};

#define HLIST_HEAD_INIT { .first = NULL }
#define HLIST_HEAD(name) struct hlist_head name = {  .first = NULL }
#define INIT_HLIST_HEAD(ptr) ((ptr)->first = NULL)
static inline void INIT_HLIST_NODE(struct hlist_node *h)
{
    h->next = NULL;
    h->pprev = NULL;
}

#define list_for_each_entry_continue(pos, head, member)         \
    for (pos = list_next_entry(pos, member);            \
            &pos->member != (head);                    \
            pos = list_next_entry(pos, member))

#endif
