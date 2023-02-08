#include <stdlib.h>
#include <stdio.h>

/*
This function takes advantage of the fact that
every recurisve function call is placed right
after it's caller in the stack (up or down).
First time through we make space for an int
and pass it's address onto the next call,
where we create another int, this time further
along in the call stack. By comparing the address
locations of those two ints, we know if the 
stack grows upwards or downwards.
*/

void stackTest(int *p) {
    int q;
    if (!p) {
        stackTest(&q);
    }
    else if (p < &q) {
        printf("Stack grows upward!");
    }
    else {
        printf("Stack grows downward!");
    }
}

int main(int argc, char const *argv[]) {
    stackTest(NULL);
    return 0;
}

