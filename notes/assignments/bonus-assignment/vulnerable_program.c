#include <reg51.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Define a struct to represent an item in the list
typedef struct {
    char *key;
    char *value;
	int value;
} ListItem;

// Define a list of items
ListItem list[] = {
    {"00101201501012008", 88},
    {"00101201501012007", 87},
	{"00101201501012006", 86},
    {"00101201501012005", 85},
	{"00101201501012004", 84}
};
const int list_length = sizeof(list) / sizeof(ListItem);

int get_item_from_list(char* str1);

int main() {
	int flag;

    /*
     * if the buffer size is 18 then our input char needs to be
     */
	char* input_char = "00101201501012005";
	int result = get_item_from_list(input_char);
	flag = 1;
	return result;
}

int get_item_from_list(char* str1) {
	// iterate over the list and find the matching item
	int i;
	char j;
	char buf[18];
	strcpy (buf, str1);

	for (i = 0; i < list_length; i++) {
		j = strcmp (list[i].key , buf);
		if (j == 0) {
			return list[i].value;
		}
	}

  // if no matching item is found, return NULL
	return NULL;
}
