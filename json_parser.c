#include "stdio.h"
#include "stdbool.h"
#include "stdlib.h"
#include "math.h"

typedef struct JSON JSON;
typedef union JSON_Values JSON_Values;

struct JSON {
  char* key;
  JSON_Values** value;
};

union JSON_Values {
  float number;
  bool boolean;
  void* nil;
  char* string;
  JSON* object;
  JSON** array;
};

// https://github.com/raysan5/raylib/blob/d9c5066382615644137b4f65479c65c44820027a/src/raymath.h#L218
bool float_equals(float x, float y) {
  #define EPSILON 0.000001f
  int result = (fabsf(x - y)) <= (EPSILON*fmaxf(1.0f, fmaxf(fabsf(x), fabsf(y))));
  return result == 1;
}

char* parse_string(char** current_char) {
  char* start = *current_char;
  while(**current_char != '"') {
    (*current_char)++;
  }
  char* end = *current_char;
  int length = end - start;
  char* result = malloc(length + 1);
  strncpy(result, start, length);
  result[length] = '\0';
  /// @note: eat "
  (*current_char)++;
  return result;
}

JSON* parse_json(char* text) {
//  FILE* file = fopen("files/verysmall.json", "r");

//   char c;
//   while((c = fgetc(file)) != EOF) {
//     printf("%c", c);
//   }
  JSON* root = NULL;

  char* current_char = text;
  static bool is_key_next = false;
  int index = 0;

  while(*current_char != '\0') {
    switch(*current_char) {
      case ':': {
        current_char++;
        is_key_next = false;
        break;
      }
      case '}': {
        current_char++;
        is_key_next = false;
        return root;
      }
      case ',': {
        current_char++;
        is_key_next = false;
        break;
      }
      case '{': {
        if(root == NULL) {
          current_char++;
          root = malloc(sizeof(JSON));
          root->value = (JSON_Values**)malloc(sizeof(JSON_Values)*100);
          is_key_next = true;
        } else {
          is_key_next = true;
          JSON* child = parse_json(current_char);
          root->value[index] = (JSON_Values*)malloc(sizeof(JSON_Values));
          root->value[index]->object = child;
          index++;
          current_char++;
        }
        break;
      }
      case '"': {
        current_char++;
        char* result = parse_string(&current_char);
        if(is_key_next) {
          root->key = result;
          is_key_next = false;
        } else {
          root->value[index] = malloc(sizeof(char)*(strlen(result)+1));
          root->value[index]->string = result;
          index++;
        }
        break;
      }
      case '[': {
        current_char++;
        int i = 0;
        while(current_char != ']') {
          // is_key_next = true;
          JSON* child = parse_json(current_char);
          root->value[index] = (JSON_Values*)malloc(sizeof(JSON_Values));
          root->value[index]->array[i++] = child;
          index++;
        }
        break;
      }
      case 'n': {
        current_char += 4;
        root->value[index] = malloc(sizeof(void));
        root->value[index]->nil = NULL;
        index++;
        break;
      }
      case 't': {
        current_char += 4;
        root->value[index] = malloc(sizeof(bool));
        root->value[index]->boolean = true;
        index++;
        break;
      }
      case 'f': {
        current_char += 5;
        root->value[index] = malloc(sizeof(bool));
        root->value[index]->boolean = false;
        index++;
        break;
      }
      case ' ':
      case '\n': {
        current_char++;
        break;
      }
      default: {
        if('1' <= *current_char && *current_char <= '9') {
          char* start = current_char;
          while(('0' <= *current_char && *current_char <= '9')
                || *current_char == '.') {
            current_char++;
          }
          char* end = current_char;
          int length = end - start;
          char* number_str = malloc(length + 1);
          strncpy(number_str, start, length);
          number_str[length] = '\0';

          root->value[index] = malloc(sizeof(float));
          root->value[index]->number = atof(number_str);
          index++;
        }
      }
    }
  }

  return root;
}