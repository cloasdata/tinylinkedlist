// test.h compile and run on target

#include <Arduino.h>
#include <assert.h>

#include "linkedlist.h"
#undef NDEBUG

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
    int res{};
    for(int i=0; i<11; i++){
        res = list.iter.loopNext();
    }

    assert(res==0); 
}

void run_tests(){
    printf("\n\n===============\nTest Starting\n===============\n"); 
    unsigned long timeTaken = millis();
    GivenEmptyList_WhenSize_Return0();
    printf("1");
    GivenEmptyListAndString_WhenAppend100_SizeReturn100();
    printf("2");
    GiventListWithElements_WhenGet2_Return2();
    printf("3");
    GiventListWithElements_WhenGet_Return();
    printf("4");
    GiventListWithElements_WhenGetReverse_ReturnReverse();
    printf("5");
    GivenListWith10Elements_WhenPopped_SizeReturn9();
    printf("6");
    GivenListWith10Elements_WhenIter_10elementsCount();
    printf("7");
    GivenList10El_whenIter11El_then0Return();
    printf("...Done\n");
    timeTaken = millis() - timeTaken;
    printf("\n==================\nTest End after: %lu ms\n==================\n", timeTaken);
}