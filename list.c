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
    for (entry = NODE_ENTRY((list)->base.next, type, member); \
         &(entry)->member != &(list)->base; \
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
    struct Node base;
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
 * @brief 移除链表头部元素
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListRemoveHead(struct List *list, void (*freeFunc)(struct Node *));

/**
 * @brief 移除链表尾部元素
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListRemoveTail(struct List *list, void (*freeFunc)(struct Node *));

/**
 * @brief 获得链表头部元素
 * @param list 指向 List 的指针
 * @return 头部节点指针
 */
struct Node *ListGetHead(struct List *list);

/**
 * @brief 获得链表尾部元素
 * @param list 指向 List 的指针
 * @return 尾部节点指针
 */
struct Node *ListGetTail(struct List *list);

/**
 * @brief 初始化链表
 * @param list 指向 List 的指针
 */
void ListInit(struct List *list)
{
    if (list == NULL) {
        return;
    }

    list->base.next = &list->base;
    list->base.prev = &list->base;
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
    struct Node *node = NULL;
    int pos = 0;

    if (list == NULL || index < 0 || index >= list->size) {
        return NULL;
    }

    node = list->base.next;
    
    if (index < list->size / 2) {
        while (index > 0) {
            node = node->next;
            index--;
        }
    } else {
        pos = list->size - 1;
        node = list->base.prev;
        while (pos > index) {
            node = node->prev;
            pos--;
        }
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
    struct Node *node = NULL;
    struct Node *prev = NULL;

    if (list == NULL || newNode == NULL || index > list->size) {
        return;
    }

    if (index == list->size) {
        return ListAddTail(list, newNode);
    }

    node = list->base.next;
    while (index > 0) {
        node = node->next;
        index--;
    }

    prev = node->prev;
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
    if (list == NULL || newNode == NULL) {
        return;
    }

    newNode->prev = &list->base;
    newNode->next = list->base.next;
    newNode->next->prev = newNode;
    list->base.next = newNode;
    list->size++;
}

/**
 * @brief 向链表尾部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddTail(struct List *list, struct Node *newNode)
{
    if (list == NULL || newNode == NULL) {
        return;
    }

    newNode->prev = list->base.prev;
    newNode->next = &list->base;
    newNode->prev->next = newNode;
    list->base.prev = newNode;
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
    struct Node *node = NULL;
    struct Node *prev = NULL;

    if (list == NULL || freeFunc == NULL || index < 0 || index >= list->size) {
        return;
    }

    node = list->base.next;
    while (index > 0) {
        node = node->next;
        index--;
    }

    prev = node->prev;
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
    struct Node *node = NULL;

    if (list == NULL || freeFunc == NULL) {
        return;
    }

    node = list->base.next;
    while (node != &list->base) {
        list->base.next = node->next;
        node->next->prev = &list->base;
        freeFunc(node);
        node = list->base.next;
    }

    list->size = 0;
}

/**
 * @brief 判断链表是否为空
 * @param list 指向 List 的指针
 * @return true 表示为空，false 非空
 */ 
bool ListIsEmpty(struct List *list)
{
    if (list == NULL || list->size == 0) {
        return true;
    }

    return false;
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
    ListRemoveTail(list, freeFunc);
}

/**
 * @brief 链表 Peek 操作
 * @param list 指向 List 的指针
 * @return Peek 后得到的节点指针
 */ 
struct Node *ListPeek(struct List *list)
{
    return ListGetTail(list);
}

/**
 * @brief 链表排序
 * @param list 指向 List 的指针
 * @param compareFunc 比较函数
 */ 
void ListSort(struct List *list, int (*compareFunc)(struct Node *, struct Node *))
{
    struct Node *ptr = NULL;
    struct Node *ptrNext = NULL;
    struct Node *node = NULL;

    if (list == NULL || compareFunc == NULL || list->size == 0 || list->size == 1) {
        return;
    }

    ptr = list->base.next->next;
    ptrNext = NULL;
    node = NULL;
    while (ptr != &list->base) {
        ptrNext = ptr->next;

        if (compareFunc(ptr->prev, ptr) <= 0) {
            ptr = ptrNext;
            continue;
        }

        node = ptr;
        node->prev->next = ptr->next;
        node->next->prev = ptr->prev; 
        ptr = list->base.next;
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

/**
 * @brief 移除链表头部元素
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListRemoveHead(struct List *list, void (*freeFunc)(struct Node *))
{
    struct Node *node = NULL;

    if (list == NULL || freeFunc == NULL || list->size == 0) {
        return;
    }

    node = list->base.next;
    list->base.next = list->base.next->next;
    list->base.next->prev = &list->base;
    freeFunc(node);
    list->size--;
}

/**
 * @brief 移除链表尾部元素
 * @param list 指向 List 的指针
 * @param freeFunc 释放实际节点空间的函数指针
 */ 
void ListRemoveTail(struct List *list, void (*freeFunc)(struct Node *))
{
    struct Node *node = NULL;

    if (list == NULL || freeFunc == NULL || ListIsEmpty(list)) {
        return;
    }

    node = list->base.prev;
    list->base.prev = list->base.prev->prev;
    list->base.prev->next = &list->base;
    freeFunc(node);
    list->size--;
}

/**
 * @brief 获得链表头部元素
 * @param list 指向 List 的指针
 * @return 头部节点指针
 */
struct Node *ListGetHead(struct List *list)
{
    if (list == NULL || ListIsEmpty(list)) {
        return NULL;
    }

    return list->base.next;
}

/**
 * @brief 获得链表尾部元素
 * @param list 指向 List 的指针
 * @return 尾部节点指针
 */
struct Node *ListGetTail(struct List *list)
{
    if (list == NULL || ListIsEmpty(list)) {
        return NULL;
    }

    return list->base.prev;
}