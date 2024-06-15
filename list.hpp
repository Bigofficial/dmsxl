

// x + y
// x + y + n(y + z)
// 2(x + y) = x + y + n(y + z)
// x + y = n(y + z)
// x = z
// 相交以后， 走x另一个走z就到了入圈
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
// 203 移除链表元素
ListNode *removeElement(ListNode *head, int val)
{

    // 1 2 6 3 4 5 6
    //  dp
    ListNode dummy(0, head);
    ListNode *prev = &dummy;
    while (prev->next != nullptr)
    {
        if (prev->next->val == val)
        {
            ListNode *temp = prev->next;
            prev->next = prev->next->next;
            delete temp;
        }
        else
        {
            prev = prev->next;
        }
    }
    return dummy.next;
}

// 707设计链表
class MyLinkedList
{
public:
    struct LinkedNode
    {
        int val;
        LinkedNode *next;
        LinkedNode(int val) : val(val), next(nullptr) {}
    };

    MyLinkedList()
    {
        _size = 0;
        _dummy = new LinkedNode(0);
    }

    int get(int index)
    {
        if (index > (_size - 1) || index < 0)
        {
            return -1;
        }
        LinkedNode *cur = _dummy->next;
        while (index--)
        {
            cur = cur->next;
        }
        return cur->val;
    }

    void addAtHead(int val)
    {
        LinkedNode *newNode = new LinkedNode(val);
        newNode->next = _dummy->next;
        _dummy->next = newNode;
        _size++;
    }

    void addAtTail(int val)
    {
        LinkedNode *newNode = new LinkedNode(val);
        LinkedNode *cur = _dummy;
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = newNode;
        _size++;
    }

    void addAtIndex(int index, int val)
    {
        if (index > _size)
            return;
        if (index < 0)
            index = 0;
        LinkedNode *cur = _dummy;
        LinkedNode *newNode = new LinkedNode(val);
        // 循环直至cur为index前一个
        while (index--)
        {
            cur = cur->next;
        }
        newNode->next = cur->next;
        cur->next = newNode;
        _size++;
    }

    void deleteAtIndex(int index)
    {
        if (index >= _size || index < 0)
        {
            return;
        }
        // 找到前一个
        LinkedNode *cur = _dummy;
        // 循环直至cur为index前一个
        while (index--)
        {
            cur = cur->next;
        }
        LinkedNode *temp = cur->next;
        cur->next = cur->next->next;
        delete temp;
        temp = nullptr;
        _size--;
    }

private:
    int _size;
    LinkedNode *_dummy;
};

// 206反转链表
ListNode *reverseList(ListNode *head)
{
    if (head == nullptr)
        return nullptr;
    ListNode *prev = nullptr;
    ListNode *cur = head;
    while (cur != nullptr)
    {
        ListNode *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    return prev;
}

// 24 两两交换链表中的节点
ListNode *swapPairs(ListNode *head)
{
    // cur first second third
    //     second      first   third
    ListNode *dummy = new ListNode(0);
    dummy->next = head;
    ListNode *cur = dummy;
    while (cur->next != nullptr && cur->next->next != nullptr)
    {
        ListNode *temp = cur->next;              // first
        ListNode *temp1 = cur->next->next->next; // third;
        cur->next = cur->next->next;
        cur->next->next = temp;
        cur->next->next->next = temp1;
        cur = cur->next->next;
    }
    ListNode *result = dummy->next;
    delete dummy;
    return result;
}

// 19删除链表中的倒数第N个节点
ListNode *removeNthFromEnd(ListNode *head, int n)
{
    //  1 2 3 4 5
    //      s   f
    //  1
    // s f
    ListNode *dummy = new ListNode(0);
    ListNode *slow = dummy;
    ListNode *fast = dummy;
    dummy->next = head;
    while (n-- > 0)
    {
        fast = fast->next;
    }
    while (fast->next != nullptr)
    {
        slow = slow->next;
        fast = fast->next;
    }
    // slow是前一个了
    ListNode *temp = slow->next;
    slow->next = slow->next->next;
    delete temp;
    return dummy->next;
}

// 02.07. 链表相交
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
{
    int lengthA = 0, lengthB = 0;
    ListNode *curA = headA;
    ListNode *curB = headB;
    while (curA != nullptr)
    {
        curA = curA->next;
        lengthA++;
    }
    while (curB != nullptr)
    {
        curB = curB->next;
        lengthB++;
    }

    // 永远都是A长B短
    if (lengthA < lengthB)
    {
        ListNode *temp = headA;
        headA = headB;
        headB = temp;

        int tempint = lengthA;
        lengthA = lengthB;
        lengthB = tempint;
    }
    int gap = lengthA - lengthB;

    while (gap--)
    {
        headA = headA->next;
    }
    while (headA != headB)
    {
        headA = headA->next;
        headB = headB->next;
    }
    if (headA == nullptr)
        return nullptr;
    return headA;
}

// 142环形链表
ListNode *detectCycle(ListNode *head)
{
    //x + y
    //x + y + n(y + z)
    // x + y = n(y + z)
    //x = n(y + z) - y
    //x = z
    ListNode* slow = head;
    ListNode* fast = head;
    while(fast != nullptr && fast->next != nullptr){
        slow=  slow->next;
        fast = fast->next->next;
        if(slow == fast){
            ListNode* s1 = head;
            ListNode* f1 = fast;
            while(f1 != s1){
                s1 = s1->next;
                f1= f1->next;
            }
            return f1;
        }
    }

    return nullptr;

}