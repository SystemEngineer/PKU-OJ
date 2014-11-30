/*
1004:487-3279
Description
Businesses like to have memorable telephone numbers. One way to make a telephone number memorable is to have it spell a memorable word or phrase. For example, you can call the University of Waterloo by dialing the memorable TUT-GLOP. Sometimes only part of the number is used to spell a word. When you get back to your hotel tonight you can order a pizza from Gino's by dialing 310-GINO. Another way to make a telephone number memorable is to group the digits in a memorable way. You could order your pizza from Pizza Hut by calling their ``three tens'' number 3-10-10-10. 

The standard form of a telephone number is seven decimal digits with a hyphen between the third and fourth digits (e.g. 888-1200). The keypad of a phone supplies the mapping of letters to numbers, as follows: 

A, B, and C map to 2 
D, E, and F map to 3 
G, H, and I map to 4 
J, K, and L map to 5 
M, N, and O map to 6 
P, R, and S map to 7 
T, U, and V map to 8 
W, X, and Y map to 9 

There is no mapping for Q or Z. Hyphens are not dialed, and can be added and removed as necessary. The standard form of TUT-GLOP is 888-4567, the standard form of 310-GINO is 310-4466, and the standard form of 3-10-10-10 is 310-1010. 

Two telephone numbers are equivalent if they have the same standard form. (They dial the same number.) 

Your company is compiling a directory of telephone numbers from local businesses. As part of the quality control process you want to check that no two (or more) businesses in the directory have the same telephone number. 

Input
The input will consist of one case. The first line of the input specifies the number of telephone numbers in the directory (up to 100,000) as a positive integer alone on the line. The remaining lines list the telephone numbers in the directory, with each number alone on a line. Each telephone number consists of a string composed of decimal digits, uppercase letters (excluding Q and Z) and hyphens. Exactly seven of the characters in the string will be digits or letters. 
Output
Generate a line of output for each telephone number that appears more than once in any form. The line should give the telephone number in standard form, followed by a space, followed by the number of times the telephone number appears in the directory. Arrange the output lines by telephone number in ascending lexicographical order. If there are no duplicates in the input print the line: 

No duplicates. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define A_SHIFT 65
#define MAX_INPUT_LEN 100

typedef struct InputChainItem{
    struct InputChainItem* next;
    char content[MAX_INPUT_LEN];
}stInputChainItem;

typedef struct OutputItem{
    int num_digit;
    int repeat_times;
}stOutputItem;

char g_char_table[26] = {'2','2','2','3','3','3','4','4','4','5','5','5',
                       '6','6','6','7','\0','7','7','8','8','8','9','9','9','\0'};

void removeDash(char* str)
{
    int i,j,tmp;
    for(i = 0,j = 0;(i < strlen(str))&&(i < MAX_INPUT_LEN);i++){
        if(((str[i] >= '0')&&(str[i] <= '9'))||((str[i] >= 'A')&&(str[i] <= 'Z')
            &&(str[i] != 'Q')&&(str[i]!= 'Z'))) {
            str[j] = str[i];
            if((str[j] >= 'A')&&(str[j] <= 'Z')){
                tmp = str[j] - 'A';
                str[j] = g_char_table[tmp];
            }
            j++;
        }
    }
    str[j] = '\0';
    //printf("str is %s\n",str);
}

int main()
{
    int input_count = 0;
    char input_str[MAX_INPUT_LEN] = {0};
    int *number_map;
    int *output_item_indexes;
    
    number_map = malloc(10000000*sizeof(int));
    memset(number_map,0,10000000);

    scanf("%d",&input_count);
    //printf("input count is %d\n",input_count);
    int i = 0;
    int content_digit = 0;
    while(input_count > 0){
        scanf("%s",input_str);
        removeDash(input_str);
        content_digit = atoi(input_str);
        //printf("--%d\n",content_digit);
        number_map[content_digit]++;
        input_count--;
    }
    //printf("finished.\n");
    int is_repeat = 0;
    for(i = 0; i < 10000000; i++){
        if(number_map[i] > 1){
            printf("%03d-%04d %d\n",i/10000,i%10000,number_map[i]);
            is_repeat = 1;
        }
    }
    if(is_repeat == 0)
        printf("No duplicates.\n");
    return 0;
}
