#include "stdio.h"
#include "stdbool.h"
#include "string.h"

#include "json_parser.c"

int main() {
  // printf("JSON Parser\n");

  // JSON j = {
  //   .key = "Hello",
  //   .value.number = 10,
  // };

  // printf("%s, %f\n", j.key, j.value.number);

  JSON* json = parse_json("{ \"key\": {\"inner\": \"value\"} }");
  // printf("Obj: %d\n", json->value[0]->object);
  // cr_assert(strcmp(json->key, "key") == 0);
  // printf(strcmp(json->value[0]->object->value[0]->string, "value") == 0);

  return 0;
}