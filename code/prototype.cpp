#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <cassert>

void sortString(char * s){
    if(s==0)return;
    static unsigned count[0xFF] = {0};
    unsigned i = 0x0, l = 0xFF;
    while(s[i]){count[s[i++]]++;}
    while(i--){
        while(count[l]==0&&l--);
        count[l]--;
        s[i] = l;
    }
}

template<unsigned maxKey, typename sizeT, typename T>
void bufferSort(T * begin, T * end){
    assert(begin <= end && begin != nullptr && end != nullptr);
    static sizeT count[maxKey+1] = {0};

    for(T * i = begin; i < end; i++){
        count[*i]++;
    }
    T * i = begin;
    for(sizeT valueIndex = 0; valueIndex != maxKey+1; valueIndex++ ){
        for(sizeT c = count[valueIndex]; c != 0; c--){
            *i++ = valueIndex;
        }
    }
}

template<typename T>
void bufferSort(T * begin, T * end){
    const T k = ~0;
    bufferSort<k, size_t, T>(begin);
}

int main(){
    //*/
    char * input = (char*) "H3ll0 d4rkn355 my 0ld fr13nd";
    char * str = (char*) malloc(strlen(input) + 1);
    strcpy(str, input);

    sortString(str);

    std::cout << str << std::endl;
    free(str);

    input = (char*) "H3ll0 d4rkn355 my n3wer fr13nd";
    str = (char*) malloc(strlen(input) + 1);

    strcpy(str, input);
    bufferSort<255, size_t, char>(str, str + strlen(input));

    std::cout << str << std::endl;
    free(str);
    //*/
}

// -O3 -fopt-info-vec-all -ftree-vectorize
