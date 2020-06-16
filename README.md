# List
C 语言通用 List 集合

现提供以下 API:



| 功能描述               | 函数                                                         | 传入参数                                                     | 返回值                    |
| ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------- |
| 初始化链表               | void ListInit(struct List *list);                            | 指向 List 的指针                                             | 空                        |
| 根据下标获取链表节点   | struct Node *ListGet(struct List *list, int index);          | list List 指针，index 链表下标                               | 节点指针                  |
| 向链表头部添加节点     | void ListAddHead(struct List *list, struct Node *newNode);   | list 指向 List 的指针，newNode 新节点指针                    | 空                        |
| 向链表尾部添加节点     | void ListAddTail(struct List *list, struct Node *newNode);   | list 指向 List 的指针，newNode 新节点指针                    | 空                        |
| 向链表指定下标添加节点 | void ListAddAtIndex(struct List *list, struct Node *newNode, int index); | list 指向 List 的指针，newNode 新节点指针，index 链表下标    | 空                        |
| 删除链表指定下标节点   | void ListDeleteAtIndex(struct List *list, int index, void (*freeFunc)(struct Node *)); | list 指向 List 的指针，index 下标，freeFunc 释放实际节点空间的函数指针 | 空                        |
| 释放整个链表           | void ListFree(struct List *list, void (*freeFunc)(struct Node *)); | list 指向 List 的指针，freeFunc 释放实际节点空间的函数指针   | 空                        |
| 判断链表是否为空       | bool ListIsEmpty(struct List *list);                         | list 指向 List 的指针                                        | true 表示为空，false 非空 |
| 链表 Push 操作         | void ListPush(struct List *list, struct Node *newNode);      | list 指向 List 的指针，newNode 新节点指针                    | 空                        |
| 链表 Pop 操作          | void ListPop(struct List *list, void (*freeFunc)(struct Node *)); | list 指向 List 的指针，freeFunc 释放实际节点空间的函数指针   | 空                        |
| 链表 Peek 操作         | struct Node *ListPeek(struct List *list);                    | list 指向 List 的指针                                        | Peek 后得到的节点指针     |
| 链表排序               | void ListSort(struct List *list, int (*compareFunc)(struct Node *, struct Node *)); | list 指向 List 的指针，compareFunc 比较函数                  | 空                        |
| 移除链表头部元素 | void ListRemoveHead(struct List *list, void (*freeFunc)(struct Node *)); | list 指向 List 的指针，freeFunc 释放实际节点空间的函数指针 | 空 |
| 移除链表尾部元素 | void ListRemoveTail(struct List *list, void (*freeFunc)(struct Node *)); | list 指向 List 的指针，freeFunc 释放实际节点空间的函数指针 | 空 |
| 获得链表头部元素 | struct Node *ListGetHead(struct List *list); | list 指向 List 的指针 | 头部节点指针 |
| 获得链表尾部元素 | struct Node *ListGetTail(struct List *list); | list 指向 List 的指针 | 尾部节点指针 |
| 判断链表中是否存在该元素 | bool ListContains(struct List *list, struct Node *node, bool (*equalsFunc)(struct Node *, struct Node *)); | list 指向 List 的指针，node 判断元素，equalsFunc 比较元素是否相等的函数指针 | true 存在，false 不存在 |

# HashTable

C 语言存储键值对 HashTable

现提供以下 API:

| 功能描述                                          | 函数                                                         | 传入参数                                                     | 返回值                        |
| ------------------------------------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ----------------------------- |
| HashTable 初始化                                  | bool HashInit(struct HashTable *hashTable, int bktSize);     | hashTable 指向 HashTable 的指针，bktSize HashTable 中链表个数 | true 表示成功，false 表示失败 |
| 向 HashTable 中添加键值对（若键已存在，则更新值） | bool HashPut(struct HashTable *hashTable, int key, int val); | hashTable 指向 HashTable 的指针，key 键，val 值              | true 表示成功，false 表示失败 |
| 在 HashTable 中根据键获取对应值                   | bool HashGet(struct HashTable *hashTable, int key, int *saveVal); | hashTable 指向 HashTable 的指针，key 键，saveVal 将获取到的值赋于该参数 | true 表示成功，false 表示失败 |
| 删除 HashTable 中对应键值对                       | void HashRemove(struct HashTable *hashTable, int key);       | hashTable 指向 HashTable 的指针，key 键                      | 空                            |
| 释放 HashTable                                    | void HashFree(struct HashTable *hashTable);                  | hashTable 指向 HashTable 的指针                              | 空                            |

