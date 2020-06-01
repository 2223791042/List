# List
C 语言通用 List 集合

现提供以下 API:
/**
 * @brief 创建链表
 * @return 指向 List 的指针
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
