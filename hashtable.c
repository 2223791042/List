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
 * @brief HashTable 模板定义的 HashTable 类型
 */
struct HashTable {
    int bktSize;
    int size;
    struct List *bkts;
};

/**
 * @brief HashTable 内部节点类型（键/值）
 */
struct HashNode {
    int key;
    int val;
    struct Node node;
};

/**
 * @brief 初始化链表
 * @param list 指向 List 的指针
 */
void ListInit(struct List *list);

/**
 * @brief 向链表尾部添加节点
 * @param list 指向 List 的指针
 * @param newNode 新节点指针
 */ 
void ListAddTail(struct List *list, struct Node *newNode);

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
 * @brief HashTable 内部节点释放函数
 * @param node 指向 Node 的指针
 */ 
void HashNodeFreeFunc(struct Node *node);

/**
 * @brief 获取所给 key 在 HashTable 中具体链表下标
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @return 所给 key 在 HashTable 中具体链表下标
 */ 
int HashPositionFunc(struct HashTable *hashTable, int key);

/**
 * @brief HashTable 初始化
 * @param hashTable 指向 HashTable 的指针
 * @param bktSize HashTable 中链表个数
 * @return true 表示成功，false 表示失败
 */ 
bool HashInit(struct HashTable *hashTable, int bktSize);

/**
 * @brief 向 HashTable 中添加键值对（若键已存在，则更新值）
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @param val 值
 * @return true 表示成功，false 表示失败
 */ 
bool HashPut(struct HashTable *hashTable, int key, int val);

/**
 * @brief 在 HashTable 中根据键获取对应值
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @param saveVal 将获取到的值赋于该参数
 * @return true 表示成功，false 表示失败
 */ 
bool HashGet(struct HashTable *hashTable, int key, int *saveVal);

/**
 * @brief 删除 HashTable 中对应键值对
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 */ 
void HashRemove(struct HashTable *hashTable, int key);

/**
 * @brief 释放 HashTable
 * @param hashTable 指向 HashTable 的指针
 */ 
void HashFree(struct HashTable *hashTable);

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
 * @brief HashTable 内部节点释放函数
 * @param node 指向 Node 的指针
 */ 
void HashNodeFreeFunc(struct Node *node)
{
    free(NODE_ENTRY(node, struct HashNode, node));
}

/**
 * @brief 获取所给 key 在 HashTable 中具体链表下标
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @return 所给 key 在 HashTable 中具体链表下标
 */ 
int HashPositionFunc(struct HashTable *hashTable, int key)
{
    return key % hashTable->bktSize;
}

/**
 * @brief HashTable 初始化
 * @param hashTable 指向 HashTable 的指针
 * @param bktSize HashTable 中链表个数
 * @return true 表示成功，false 表示失败
 */ 
bool HashInit(struct HashTable *hashTable, int bktSize)
{
    int i = 0;
    if (hashTable == NULL || bktSize <= 0) {
        return false;
    }

    hashTable->bkts = (struct List *)malloc(sizeof(struct List) * bktSize);
    if (hashTable->bkts == NULL) {
        return false;
    }

    for (i = 0; i < bktSize; i++) {
        ListInit(&hashTable->bkts[i]);
    }

    hashTable->bktSize = bktSize;

    return true;
}

/**
 * @brief 向 HashTable 中添加键值对（若键已存在，则更新值）
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @param val 值
 * @return true 表示成功，false 表示失败
 */ 
bool HashPut(struct HashTable *hashTable, int key, int val)
{
    int position = 0;
    struct HashNode *hashNode = NULL;
    if (hashTable == NULL || hashTable->bkts == NULL) {
        return false;
    }

    position = HashPositionFunc(hashTable, key);
    LIST_FOR_EACH_ENTRY(hashNode, &hashTable->bkts[position], struct HashNode, node) {
        if (hashNode->key == key) {
            hashNode->val = val;
            return true;
        }
    }

    hashNode = (struct HashNode *)malloc(sizeof(struct HashNode));
    if (hashNode == NULL) {
        return false;
    }
    hashNode->key = key;
    hashNode->val = val;

    ListAddTail(&hashTable->bkts[position], &hashNode->node);

    return true;
}

/**
 * @brief 在 HashTable 中根据键获取对应值
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 * @param saveVal 将获取到的值赋于该参数
 * @return true 表示成功，false 表示失败
 */ 
bool HashGet(struct HashTable *hashTable, int key, int *saveVal)
{
    int position = 0;
    struct HashNode *hashNode = NULL;
    if (hashTable == NULL || hashTable->bkts == NULL) {
        return false;
    }

    position = HashPositionFunc(hashTable, key);
    if (ListIsEmpty(&hashTable->bkts[position])) {
        return false;
    }

    LIST_FOR_EACH_ENTRY(hashNode, &hashTable->bkts[position], struct HashNode, node) {
        if (hashNode->key == key) {
            *saveVal = hashNode->val;
            return true;
        }
    }

    return false;
}

/**
 * @brief 删除 HashTable 中对应键值对
 * @param hashTable 指向 HashTable 的指针
 * @param key 键
 */ 
void HashRemove(struct HashTable *hashTable, int key)
{
    int position = 0;
    struct HashNode *hashNode = NULL;
    struct Node *prev = NULL;
    struct Node *next = NULL;
    if (hashTable == NULL || hashTable->bkts == NULL) {
        return;
    }

    position = HashPositionFunc(hashTable, key);
    if (ListIsEmpty(&hashTable->bkts[position])) {
        return;
    }

    LIST_FOR_EACH_ENTRY(hashNode, &hashTable->bkts[position], struct HashNode, node) {
        if (hashNode->key == key) {
            prev = hashNode->node.prev;
            next = hashNode->node.next;
            prev->next = next;
            next->prev = prev;
            free(hashNode);
            return;
        }
    }
}

/**
 * @brief 释放 HashTable
 * @param hashTable 指向 HashTable 的指针
 */ 
void HashFree(struct HashTable *hashTable)
{
    int i = 0;
    if (hashTable == NULL || hashTable->bkts == NULL) {
        return;
    }

    for (i = 0; i < hashTable->bktSize; i++) {
        ListFree(&hashTable->bkts[i], HashNodeFreeFunc);
    }

    free(hashTable->bkts);
}