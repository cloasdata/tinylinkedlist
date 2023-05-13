// test.h compile and run on target

#include <Arduino.h>
#include <assert.h>

#include "../linkedlist.h"

struct testData{
    char test[10] = "123456789";
    int i=42;
};

void GivenEmptyList_WhenSize_Return0(){
    TinyLinkedList<int> list;
    
    assert(list.size() == 0);
}

void GivenEmptyListAndString_WhenAppend100_SizeReturn100(){
    testData data;
    TinyLinkedList<testData> list;
    
    for (int i = 0; i<100; i++) list.append(data);
    assert(list.size()==100);
}

void GivenListWithLargeData_WhenDestroyed_HeapDoesNotIncrease(){
    uint16_t heapSize = ESP.getFreeHeap();
    testData data;
    TinyLinkedList<testData> list;
    for (int i = 0; i<100; i++) list.append(data);
    list.~TinyLinkedList();
    assert(heapSize - ESP.getFreeHeap() == 0);
}


void GiventListWithElements_WhenGet2_Return2(){
    TinyLinkedList<int> list;
    for (int i = 0; i<100; i++) list.append(i);
    
    int res = list.get(2);
    
    assert(res==2);
};

void GiventListWithElements_WhenGet_Return(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    
    for (int i = 0; i<10; i++){
        int res = list.get(i);
        assert(res==i);
    }
    
};

void GiventListWithElements_WhenGetReverse_ReturnReverse(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    
    for (int i = 9; i>=0; i--){
        int res = list.get(i);
        assert(res==i);
    }
    
    
};


void GivenListWith10Elements_WhenPopped_SizeReturn9(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    
    for (int c = 9; c>=0; c--){
        int i = list.pop();
        assert(i==c);
    }

    assert(list.size()==0);
};


void GivenListWith10Elements_WhenIter_10elementsCount(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(1);
    
    int sum = 0;
    while(list.iter()){
        sum+=list.iter.next();
    }
    assert(sum==10);
}

void GivenList10El_whenIter12El_then0Return(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    int res{};
    for(int i=0; i<12; i++){
        if (list.iter())
            res = list.iter.next();
    }

    assert(res==0); 
}

void GivenList10El_whenIter11El_then0Return(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    int res{1};
    for(int i=0; i<11; i++){
        res = list.iter.loopNext();
    }

    assert(res==0); 
}

void GivenList10El_WhenIter28times_Then8Return(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    int res{1};
    for(int i=0; i<29; i++){
        res = list.iter.loopNext();
    }
    assert(res==8); 
}

void GivenEmptyList_whenLoopNext_thenNoError(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++){
        list.iter.loopNext();
    }
}

void GivenList10El_whenIndex0_return0(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    signed int res = list.index(0);
    
    assert(res == 0);
}

void GivenList10El_whenIndex5_return5(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    signed int res = list.index(5);
    assert(res == 5);
}

void GivenList10El_whenRemove9_return9(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    int res = list.remove(9);
    assert(res == 9);
}

void GivenEmptyList_WhenIter_ReturnSafe(){
    TinyLinkedList<int> list;
    while(list.iter()){
        list.iter.next();
        assert(false);
    }
    assert(list.size()==0);
}

void GivenListWith2El_WhenIterAndReset_ReturnFirstEl(){
    TinyLinkedList<int> list;
    list.append(42);
    list.append(13);
    
    list.iter.next();
    list.iter.reset();
    auto el = list.iter.next();
    assert(el==42);
}

void GivenList10El_whenRemove10andIter_ReturnSafe(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    for (int i = 0; i<10; i++) list.pop();
    while(list.iter()){
        list.iter.next();
        assert(list.size()==0);
        assert(false);
    }
    assert(list.size()==0);
}

void GivenList10El_whenPopLeft_ReturnEl0(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    int res = list.popLeft();
    assert(res == 0);
    assert(list.get(9)==9);
}

void GivenList10El_whenPopLeft10_ReturnSafe(){
    TinyLinkedList<int> list;
    for (int i = 0; i<10; i++) list.append(i);
    for (int i = 0; i<10; i++) list.popLeft();
    while(list.iter()){
        list.iter.next();
        assert(list.size()==0);
        assert(false);
    }
    assert(list.size()==0);
}




void run_tinylinkedlist_tests(){
    printf("\n\n===============\nTest Starting\n===============\n"); 
    unsigned long timeTaken = millis();
    GivenEmptyList_WhenSize_Return0();
    printf(".");
    GivenEmptyListAndString_WhenAppend100_SizeReturn100();
    printf(".");
    GivenListWithLargeData_WhenDestroyed_HeapDoesNotIncrease();
    printf(".");
    GiventListWithElements_WhenGet2_Return2();
    printf(".");
    GiventListWithElements_WhenGet_Return();
    printf(".");
    GiventListWithElements_WhenGetReverse_ReturnReverse();
    printf(".");
    GivenListWith10Elements_WhenPopped_SizeReturn9();
    printf(".");
    GivenListWith10Elements_WhenIter_10elementsCount();
    printf(".");
    GivenList10El_whenIndex0_return0();
    printf(".");
    GivenList10El_whenIter11El_then0Return();
    printf(".");
    GivenList10El_whenIndex5_return5();
    printf(".");
    GivenList10El_whenRemove9_return9();
    printf(".");
    GivenEmptyList_WhenIter_ReturnSafe();
    printf(".");
    GivenListWith2El_WhenIterAndReset_ReturnFirstEl();
    printf(".");
    GivenList10El_whenRemove10andIter_ReturnSafe();
    printf(".");
    GivenEmptyList_whenLoopNext_thenNoError();
    printf(".");
    GivenList10El_WhenIter28times_Then8Return();
    printf(".");
    GivenList10El_whenPopLeft_ReturnEl0();
    printf(".");
    GivenList10El_whenPopLeft10_ReturnSafe();
    printf(".");
    printf("\nDone\n");
    timeTaken = millis() - timeTaken;
    printf("\n==================\nTest End after: %lu ms\n==================\n", timeTaken);
}