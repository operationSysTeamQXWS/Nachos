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

    void Prepend(void *item);   //在表头 插入
    void Append(void *item);    //在表尾 插入
    void *Remove(int *keyPtr);  //从表头 删除
    //重载 for thread test
    void *Remove(int *keyPtr, int test_id, int thread_id, int No_id);  

    bool isEmpty();
    void ShowAll();

    void SortedInsert(void *item, int sortKey);     //按 优先键 插入
    void SortedRemove(int sortKey);        // 按 优先键 删除

private:
    DllElement *first;
    DllElement *last;
};
