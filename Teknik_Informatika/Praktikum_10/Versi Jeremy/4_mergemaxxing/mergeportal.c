#include "mergeportal.h"

Address findMax(List L){
    Address temp = (L).first;
    Address ret;
    int maxim = -1e9;
    while(temp->next != (L).first){
        if(temp->info > maxim){
                maxim = temp->info;
                ret = temp;
        }
        temp = temp->next;
    }
    if(temp->info > maxim){
        maxim = temp->info;
        ret = temp;
    }
    return ret;
}

Address findMin(List L){
    Address temp = (L).first;
    Address ret;
    int minim = 1e9;
    while(temp->next != (L).first){
        if(temp->info < minim){
                minim = temp->info;
                ret = temp;
        }
        temp = temp->next;
    }
    if(temp->info < minim){
        minim = temp->info;
        ret = temp;
    }
    return ret;
}

int sumList(List L){
        if(isEmpty(L)) return 0;
        int sum = 0;
        Address temp = (L).first;
    while(temp->next != (L).first){
        sum += temp->info;
        temp = temp->next;
    }
    sum += temp->info;
    return sum;
}

List concatCircular(List A, List B){
        Address pivotA = findMax(A);
        Address pivotB = findMin(B);
        Address temp = pivotB;
        while(temp->next != pivotB) temp = temp->next;
        Address connectB = temp;
        int val = sumList(A) + sumList(B);
        Address add = allocate(val);
        connectB->next = add;
        add->next = pivotA->next;
        pivotA->next = pivotB;
        return A;
}