class DllElement{
public:
    DllElement(void *itemPtr, int sortKey);
    DllElement *next;
    DllElement *prev;
    int key;
    void *item;
};

class Dllist{
public:
    Dllist();
    ~Dllist();

    void Prepend(void *item);   //在前面链表头部插入
    void Append(void *item);    //在在链表尾部插入
    void *Remove(int *keyPtr);  //按 优先键 删除

    bool isEmpty();
    void ShowAll();

    void SortedInsert(void *item, int sortKey);     //按 优先键 插入
    void SortedRemove(int sortKey);        // 按 优先键 删除

private:
    DllElement *first;
    DllElement *last;
};
