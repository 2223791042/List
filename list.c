#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * @brief 根据 Node 指针，获取自定义 Type 指针
 * @param node 链表节点指针
 * @param type 自定义的结构体类型
 * @param member 自定义 Type 中 Node 的名称
 * @return 自定义 Type 指针
 */
#define NODE_ENTRY(node, type, member) \
    ((type *)((char *)(node) - (size_t)&((type *)0)->member))

/**
 * @brief 遍历循环链表
 * @param entry 自定义 Type 指针，用来存放数据
 * @param list List 指针
 * @param type 自定义的结构体类型
 * @param member 自定义 Type 中 Node 的名称
 */ 
#define LIST_FOR_EACH_ENTRY(entry, list, type, member) \
    for (entry = NODE_ENTRY((list)->base->next, type, member); \
         &(entry)->member != (list)->base; \
         entry = NODE_ENTRY((entry)->member.next, type, member))


/**
 * @brief 链表模板定义的 Node 类型
 */ 
struct Node
{
    struct Node *next, *prev;
};

/**
 * @brief 链表模板定义的 List 类型
 */ 
struct List
{
    struct Node *base;
    int size;
};

/**
 * @brief 初始化链表
 * @param list 指向 List 的指针
 */
void ListInit(struct List *list);

/**
 * @brief 根据下标获取链表节点
 * @param list List 指针
 * @param index 链表下标
 * @return 节点指针
 */
struct Node *ListGet(struct List *list, int index);

/**
 * @brief 向链表头部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddHead(struct List *list, struct Node *newNode);


/**
 * @brief 向链表尾部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddTail(struct List *list, struct Node *newNode);

/**
 * @brief 向链表指定下标添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 * @param index 链表下标
 */ 
void ListAddAtIndex(struct List *list, struct Node *newNode, int index);

/**
 * @brief 删除链表指定下标节点
 * @param list 指向 List 的指针
 * @param index 下标
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListDeleteAtIndex(struct List *list, int index, void (*freeFunc)(struct Node *));

/**
 * @brief 释放整个链表
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListFree(struct List *list, void (*freeFunc)(struct Node *));

/**
 * @brief 判断链表是否为空
 * @param list 指向 List 的指针
 * @return true 表示为空，false 非空
 */ 
bool ListIsEmpty(struct List *list);

/**
 * @brief 链表 Push 操作
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListPush(struct List *list, struct Node *newNode);

/**
 * @brief 链表 Pop 操作
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListPop(struct List *list, void (*freeFunc)(struct Node *));

/**
 * @brief 链表 Peek 操作
 * @param list 指向 List 的指针
 * @return Peek 后得到的节点指针
 */ 
struct Node *ListPeek(struct List *list);

/**
 * @brief 链表排序
 * @param list 指向 List 的指针
 * @param compareFunc 比较函数
 */ 
void ListSort(struct List *list, int (*compareFunc)(struct Node *, struct Node *));

/**
 * @brief 初始化链表
 * @param list 指向 List 的指针
 */
void ListInit(struct List *list)
{
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    if (node == NULL) {
        return;
    }

    node->next = node;
    node->prev = node;
    list->base = node;
    list->size = 0;
}

/**
 * @brief 根据下标获取链表节点
 * @param list List 指针
 * @param index 链表下标
 * @return 节点指针
 */
struct Node *ListGet(struct List *list, int index)
{
    if (index < 0 || index >= list->size) {
        return NULL;
    }

    struct Node *node = list->base->next;
    while (index > 0) {
        node = node->next;
        index--;
    }

    return node;
}

/**
 * @brief 向链表指定下标添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 * @param index 链表下标
 */ 
void ListAddAtIndex(struct List *list, struct Node *newNode, int index)
{
    if (index > list->size) {
        return;
    }

    if (index == list->size) {
        return ListAddTail(list, newNode);
    }

    struct Node *node = list->base->next;
    while (index > 0) {
        node = node->next;
        index--;
    }

    struct Node *prev = node->prev;
    prev->next = newNode;
    newNode->prev = prev;
    newNode->next = node;
    node->prev = newNode;
    list->size++;
}

/**
 * @brief 向链表头部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddHead(struct List *list, struct Node *newNode)
{
    newNode->prev = list->base;
    newNode->next = list->base->next;
    newNode->next->prev = newNode;
    list->base->next = newNode;
    list->size++;
}

/**
 * @brief 向链表尾部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddTail(struct List *list, struct Node *newNode)
{
    newNode->prev = list->base->prev;
    newNode->next = list->base;
    newNode->prev->next = newNode;
    list->base->prev = newNode;
    list->size++;
}

/**
 * @brief 删除链表指定下标节点
 * @param list 指向 List 的指针
 * @param index 下标
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListDeleteAtIndex(struct List *list, int index, void (*freeFunc)(struct Node *))
{
    if (index < 0 || index >= list->size) {
        return;
    }

    struct Node *node = list->base->next;
    while (index > 0) {
        node = node->next;
        index--;
    }

    struct Node *prev = node->prev;
    prev->next = node->next;
    node->next->prev = prev;
    freeFunc(node);
    list->size--;
}

/**
 * @brief 释放整个链表
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListFree(struct List *list, void (*freeFunc)(struct Node *))
{
    struct Node *node = list->base->next;
    while (node != list->base) {
        list->base->next = node->next;
        node->next->prev = list->base;
        freeFunc(node);
        node = list->base->next;
    }
    free(list->base);
}

/**
 * @brief 判断链表是否为空
 * @param list 指向 List 的指针
 * @return true 表示为空，false 非空
 */ 
bool ListIsEmpty(struct List *list)
{
    return list->size == 0;
}

/**
 * @brief 链表 Push 操作
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListPush(struct List *list, struct Node *newNode)
{
    ListAddTail(list, newNode);
}

/**
 * @brief 链表 Pop 操作
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListPop(struct List *list, void (*freeFunc)(struct Node *))
{
    if (ListIsEmpty(list)) {
        return;
    }
    struct Node *node = list->base->prev;
    list->base->prev = node->prev;
    node->prev->next = list->base;
    freeFunc(node);
    list->size--;
}

/**
 * @brief 链表 Peek 操作
 * @param list 指向 List 的指针
 * @return Peek 后得到的节点指针
 */ 
struct Node *ListPeek(struct List *list)
{
    if (ListIsEmpty(list)) {
        return NULL;
    }
    return list->base->prev;
}

/**
 * @brief 链表排序
 * @param list 指向 List 的指针
 * @param compareFunc 比较函数
 */ 
void ListSort(struct List *list, int (*compareFunc)(struct Node *, struct Node *))
{
    if (list->size == 0 || list->size == 1) {
        return;
    }
    // 插入排序
    struct Node *ptr = list->base->next->next;
    struct Node *ptrNext = NULL;
    struct Node *node = NULL;
    while (ptr != list->base) {
        ptrNext = ptr->next;
        if (compareFunc(ptr->prev, ptr) <= 0) {
            ptr = ptrNext;
            continue;
        }
        // 节点摘出
        node = ptr;
        node->prev->next = ptr->next;
        node->next->prev = ptr->prev; 
        // 节点插入
        ptr = list->base->next;
        while (ptr != ptrNext) {
            if (compareFunc(node, ptr) < 0) {
                ptr->prev->next = node;
                node->prev = ptr->prev;
                node->next = ptr;
                ptr->prev = node;
                break;
            }
            ptr = ptr->next;
        }
        ptr = ptrNext;
    }
}