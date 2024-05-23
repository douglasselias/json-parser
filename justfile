just:
  mkdir -p build && clang -std=c99 main.c -g3 -o build/main && build/main

test:
  mkdir -p build && clang -lcriterion main.test.c -o build/test && build/test

debug:
  clang -std=c99 main.c -g3 -o build/main && gf2 build/main