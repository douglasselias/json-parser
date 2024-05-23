#include <criterion/criterion.h>

#include "json_parser.c"

Test(parse, strings) {
  JSON* json = parse_json("{ \"key\": {\"inner\": \"value\"} }");
  // cr_assert(strcmp(json->key, "key") == 0);
  cr_assert(strcmp(json->value[0]->object->key, "inner") == 0);
  cr_assert(strcmp(json->value[0]->object->value[0]->string, "value") == 0);

  // JSON* json = parse_json("{ \"key\": \"value\", }\0");
  // JSON* json = parse_json("{ \"key\": {\"inner\": \"value\"}, }\0");
  // puts("{ \"key\": \"value\", }\0");
  // printf("JSON->value: %s\n", json->value[0]->string);

  // cr_assert(strcmp(json->key, "key") == 0);
  // cr_assert(strcmp(json->value[0]->string, "value") == 0);
  // cr_assert(float_equals(json->value[0]->number, 123.45));
  // cr_assert(json->value[0]->boolean == true);
  // cr_assert(json->value[0]->boolean == false);
  // cr_assert(json->value[0]->nil == NULL);
}