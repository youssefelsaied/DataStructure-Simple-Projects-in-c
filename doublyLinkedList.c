#include <stdio.h>
#include <stdlib.h>
/*
 *
 */
typedef struct Node
{
    int data;
    struct Node* next;
    struct Node* prev;
} Node;
/*
 *
 */
typedef struct
{
    Node* head;
    Node* tail;
} DoublyLinkedList;
/*
 *
 */
const DoublyLinkedList EmptyList = {NULL, NULL};
/*
 * convertArrayToDoublyLinkedList
 */
DoublyLinkedList convertArrayToDoublyLinkedList(int array[], int size)
{

    DoublyLinkedList list = {NULL, NULL};
    Node *p_head = NULL;
    do
    {
        Node *p_current = NULL;
        int i = 0;
        if ( size<= 0) //simple check
        {
            break;
        }
        for(i; i < size; i++)
        {
            Node *p_item =
                ( Node*)malloc(sizeof ( Node));
            if (NULL == p_item) // simple check
            {
                break;
            }

            p_item->data = array[i];
            if (NULL == p_current)
            {
                p_current = p_item;
                p_current->prev = NULL;
                p_current->next = NULL;
                p_head = p_current;
            }
            else
            {
                p_current->next = p_item;
                p_item->prev = p_current;
                p_item-> next = NULL;

                p_current = p_item;
            }
        }
    }
    while(0);

    list.head=p_head;
    return list;
}
/*
 * destroy
 */
void destroy(DoublyLinkedList* list)
{

    Node* current = list->head;
    Node* next;
    while (current != NULL)
    {
        next = current->next;
        current = next;
    }
    list->head = NULL;

}


/*
 * duplicate
 */
DoublyLinkedList Dup(DoublyLinkedList list)
{
    DoublyLinkedList newlist = {NULL, NULL};
    int i=0,count=0;
    Node * a = list.head;
    Node * b=list.head;
    while (a != NULL)
    {
        count++;
        a = a->next;
    }
    int arr[count];
    while(b!=NULL)
    {
        arr[i]=b->data;
        i++;
        b= b->next;
    }
    i=0;
    newlist=convertArrayToDoublyLinkedList (arr,count);

    return newlist;
}
/*
 * concatenate: concatenates the second list to the first one
 */
DoublyLinkedList concatenate(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList newlist = {NULL, NULL};
    if( list1.head == NULL )
        newlist=list2;
    else if (list2.head==NULL)
        newlist=list1;
    else
    {
        newlist=list1;
        Node* head3 = NULL;
        Node* p1 = list1.head;
        Node* p2 = list2.head;
        Node* p3 = NULL;

        while (p1 != NULL || p2 != NULL)
        {
            Node * tmp = NULL;
            if (p1 == NULL)
            {
                tmp = p2;
                p2 = NULL;
            }
            else if (p2 == NULL)
            {
                tmp = p1;
                p1 = NULL;
            }

            if ((p1 != NULL) && (p2 != NULL))
            {
                //if (p1->data < p2->data) {
                tmp = p1;
                p1 = p1->next;
                //} else {
                //  tmp = p2;
                // p2 = p2->next;
                //}
            }

            if (head3 == NULL)
            {
                head3 = tmp;
            }
            else
            {
                p3->next = tmp;
                tmp->prev = p3;
            }
            p3 = tmp;
        }
        head3=newlist.head;
        return newlist;
    }
}

/*
 * length: count the number of items stored in the list
 */
size_t length(DoublyLinkedList list)
{
    size_t count = 0;
    Node *n=list.head;
    while(n!=NULL)
    {
        count++;
        n=n->next;
    }

    return count;
}
/*
 * isPalindrome: returns 1 if list is palindrome
 *               returns 0 if list is not palindrome
 *               a palindrome prints forwards as backwards
 *               e.g., 1 2 3 2 1
 *               e.g., 1 2 3 3 2 1
 */
int isPalindrome(DoublyLinkedList list)
{
    Node *left=list.head;
    if (left == NULL)
        return 0;


    Node *right = left;
    while (right->next != NULL)
        right = right->next;

    while (left != right)
    {
        if (left->data != right->data)
            return 0;

        left = left->next;
        right = right->prev;
    }

    return 1;
}
/*
 * areEqual: returns 1 if both lists contain same elements
 *               returns 0 otherwise
 */
int areEqual(DoublyLinkedList list1, DoublyLinkedList list2)
{
    Node *n=list1.head;
    Node *m=list2.head;
    while(n!=NULL&&m!=NULL)
    {
        if(n->data==m->data)
        {
            n=n->next;
            m=m->next;
        }
        else
            return 0;
    }
    if(n!=NULL || m!=NULL)
        return 0;
    else
        return 1;
}
/*
 * printlnListForward: prints the list {1, 3, 5, 7} as 1 3 5 7
 *                    prints end of line at the end
 */
void printlnListForward(DoublyLinkedList list)
{

    Node *temp=list.head;
    while(temp!=NULL)
    {
        printf("%d\t",temp->data);
        temp=temp->next;
    }

    printf("\n");
}
/*
 * printlnListBackward: prints the list {1, 3, 5, 7} as 7 5 3 1
 *                    prints end of line at the end
 */
void printlnListBackward(DoublyLinkedList list)
{

    Node* temp = list.head;
    if(temp == NULL)
        return;

    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    while(temp != NULL)
    {
        printf("%d\t",temp->data);
        temp = temp->prev;
    }
    printf("\n");

}
/*
 *
 */
void Investigate(char* title, DoublyLinkedList list)
{
    printf("%s\n", title);
    printf("List =         ");
    printlnListForward(list);
    printf("Reverse List = ");
    printlnListBackward(list);
    printf("List Length = %u\n", length(list));
    printf("List isPalindrome = %d\n", isPalindrome(list));
    printf("...................................................\n");
}
/*
 *
 */
void testConcatenate1(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;

    list3 = Dup(list1);
    Investigate("List3 = dup(List1)\n==================", list3);
    emptyList1 = Dup(EmptyList);
    Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList list5 = concatenate(list3, emptyList1);
    Investigate("List5 = List3<->EmptyList1\n==========================", list5);
    destroy(&list5);
    Investigate("List5 (after destroy)\n=====================", list5);
    //destroy(&list3);            //already destroyed when list5 got destroyed
    //destroy(&emptyList1);        //already destroyed when list5 got destroyed
}
/*
 *
 */
void testConcatenate2(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;
    list3 = Dup(list1);
    emptyList1 = Dup(EmptyList);
    DoublyLinkedList list6 = concatenate(emptyList1, list3);
    Investigate("List6 = EmptyList1<->List3\n==========================", list6);
    destroy(&list6);
    Investigate("List6 (after destroy)\n=====================", list6);
    //destroy(&list3);            //already destroyed when list6 got destroyed
    //destroy(&emptyList1);        //already destroyed when list6 got destroyed
}
/*
 *
 */
void testConcatenate3(DoublyLinkedList list1, DoublyLinkedList list2)
{
    DoublyLinkedList list3, list4, emptyList1;

    list3 = Dup(list1);
    list4 = Dup(list2);
    DoublyLinkedList list7 = concatenate(list3, list4);
    Investigate("List7 = List3<->List4\n=====================", list7);
    destroy(&list7);
    Investigate("List7 (after destroy)\n=====================", list7);
    //destroy(&list3);            //already destroyed when list7 got destroyed
    //destroy(&list4);            //already destroyed when list7 got destroyed
}
/*
 *
 */
void testConcatenate()
{
    int array1[] = {0, 1, 2, 3, 4, 5, 6};
    int array2[] = {7, 8, 9};

    DoublyLinkedList list1 = convertArrayToDoublyLinkedList(array1, sizeof(array1)/sizeof(*array1));
    Investigate("List1\n=====", list1);
    DoublyLinkedList list2 = convertArrayToDoublyLinkedList(array2, sizeof(array2)/sizeof(*array2));
    Investigate("List2\n=====", list2);

    testConcatenate1(list1, list2);
    testConcatenate2(list1, list2);
    testConcatenate3(list1, list2);

    destroy(&list1);
    destroy(&list2);
}
/*
 *
 */
void testPalindrome()
{
    int array3[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array4[] = {7, 8, 9, 9, 8, 7};

    DoublyLinkedList list8 = convertArrayToDoublyLinkedList(array3, sizeof(array3)/sizeof(*array3));
    Investigate("List8\n=====", list8);
    DoublyLinkedList list9 = convertArrayToDoublyLinkedList(array4, sizeof(array4)/sizeof(*array4));
    Investigate("List9\n=====", list9);

    destroy(&list8);
    destroy(&list9);
}
/*
 *
 */
void testAreEqual()
{
    int array5[] = {0, 1, 2, 3, 4, 5, 6, 5, 4, 3, 2, 1, 0};
    int array6[] = {7, 8, 9, 9, 8, 7};
    int array7[] = {0, 1, 2, 3, 4, 5};

    DoublyLinkedList list10 = convertArrayToDoublyLinkedList(array5, sizeof(array5)/sizeof(*array5));
    Investigate("List10\n=====", list10);
    DoublyLinkedList list11 = convertArrayToDoublyLinkedList(array6, sizeof(array6)/sizeof(*array6));
    Investigate("List11\n=====", list11);
    DoublyLinkedList list12 = convertArrayToDoublyLinkedList(array7, sizeof(array7)/sizeof(*array7));
    Investigate("List12\n=====", list12);
    DoublyLinkedList emptyList1 = Dup(EmptyList);
    Investigate("EmptyList1 = dup(EmptyList)\n===========================", emptyList1);
    DoublyLinkedList emptyList2 = Dup(EmptyList);
    Investigate("EmptyList2 = dup(EmptyList)\n===========================", emptyList2);

    printf("areEqual(List10, List10) = %d\n", areEqual(list10, list10));
    printf("areEqual(List10, List11) = %d\n", areEqual(list10, list11));
    printf("areEqual(List10, List12) = %d\n", areEqual(list10, list12));
    printf("areEqual(List11, List10) = %d\n", areEqual(list11, list10));
    printf("areEqual(List10, EmptyList1) = %d\n", areEqual(list10, emptyList1));
    printf("areEqual(EmptyList1, List10) = %d\n", areEqual(emptyList1, list10));
    printf("areEqual(EmptyList1, EmptyList2) = %d\n", areEqual(emptyList1, emptyList2));

    destroy(&list10);
    destroy(&list11);
    destroy(&list12);

}
/*
 *
 */
main()
{
    testConcatenate();
    testPalindrome();
    testAreEqual();
    return 0;
}
