# List
C 语言通用 List 集合

现提供以下 API:

创建链表
void ListInit(struct List *list);

根据下标获取链表节点
struct Node *ListGet(struct List *list, int index);

向链表头部添加节点
void ListAddHead(struct List *list, struct Node *newNode);

向链表尾部添加节点
void ListAddTail(struct List *list, struct Node *newNode);

向链表指定下标添加节点
void ListAddAtIndex(struct List *list, struct Node *newNode, int index);

删除链表指定下标节点
void ListDeleteAtIndex(struct List *list, int index, void (*freeFunc)(struct Node *));

释放整个链表
void ListFree(struct List *list, void (*freeFunc)(struct Node *));

判断链表是否为空
bool ListIsEmpty(struct List *list);

链表 Push 操作
void ListPush(struct List *list, struct Node *newNode);

链表 Pop 操作 
void ListPop(struct List *list, void (*freeFunc)(struct Node *));

链表 Peek 操作
struct Node *ListPeek(struct List *list);

链表排序
void ListSort(struct List *list, int (*compareFunc)(struct Node *, struct Node *));
