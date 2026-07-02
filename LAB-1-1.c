#include <stdio.h>
#include <string.h>

int main(void) {
    char text[] = "ก";
    char text_2[] = "A";

    printf("text = %s\n", text);
    printf("strlen(text) = %zu bytes\n", strlen(text));

    for (size_t i = 0; i < strlen(text); i++) {
        printf("byte %zu = 0x%02X\n", i, (unsigned char)text[i]);
    }
  printf("\n------------------------------------\n");
  printf("text = %s\n", text_2);
    printf("strlen(text) = %zu bytes\n", strlen(text_2));

    for (size_t i = 0; i < strlen(text_2); i++) {
        printf("byte %zu = 0x%02X\n", i, (unsigned char)text_2[i]);
    }
    return 0;
}
