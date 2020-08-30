#include <stdio.h>

typedef struct PERSON
{
    char name[64];
    int age;
    int score;
} Person;

int main() {
    printf("%ld\n",sizeof(Person));
    return 0;
}
