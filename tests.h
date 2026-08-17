//
// Created by dabira on 8/17/26.
//

#ifndef STRINGVIEW_TESTS_H
#define STRINGVIEW_TESTS_H
#include "string_view.h"

static inline void test1() {
   stringView s = SV("Hello World");
  stringView s1 = s;
  printf("s : ");
  print_sv(&s);
  printf("\ns1 : ");
  print_sv(&s1);

  // remove one character from the left of the stringView s
  printf("\n\nRemove one character from the left of s1\n");
  strip_left(&s1);
  printf("\ns : ");
  print_sv(&s);
  printf("\ns1 : ");
  print_sv(&s1);

  // remove one character from the right of stringView s
  printf("\n\nRemove one character from the right of s1\n");
  strip_right(&s1);
  printf("s : ");
  print_sv(&s);
  printf("\ns1 : ");
  print_sv(&s1);

  stringView s2 = SV("Hello World");
  printf("\n\ns2: ");
  print_sv(&s2);

  // Check if s ,s1 and s2 are equal
  printf("\n\ncompare s , s1 and s2\n\n");
  printf("Is s equals s1 ? %s\n", sv_equals(&s,&s1) ? "true" : "false");
  printf("Is s equals s2 ? %s\n", sv_equals(&s,&s2) ? "true" : "false");
  printf("Is s1 equals s2 ? %s\n", sv_equals(&s1,&s2) ? "true" : "false");

  stringView url = SV("https://www.google.com");
  printf("\nUrl : ");
  print_sv(&url);
  printf("\n\n");
  printf("Check if url starts with https://\n");
  const stringView prefix = SV("https://");
  const stringView prefix2 = SV("http://");
  const stringView suffix = SV(".com");
  const stringView suffix2 = SV(".org");
  printf("Url start with https:// ? %s\n",sv_start_with(&url, &prefix)? "true" : "false");
  printf("Url start with http:// ? %s\n",sv_start_with(&url, &prefix2)? "true" : "false");
  printf("Url end with .com ? %s\n", sv_end_with(&url, &suffix)? "true" : "false");
  printf("Url end with .org ? %s\n", sv_end_with(&url, &suffix2)? "true" : "false");

  // trimming
  stringView frontSpace_s = SV("     Hello there|");
  printf("\nFrontSpace_s : |");
  print_sv(&frontSpace_s);
  printf("\n");
  // trim front Spaces
  printf("trimming the front spaces \n");
  trim_left_sv(&frontSpace_s);
  printf("FrontSpace_s : |");
  print_sv(&frontSpace_s);
  printf("\n\n");

  // trim back spaces
  stringView backSpace_s = SV("Hello there       ");
  printf("BackSpace_s : |");
  print_sv(&backSpace_s);
  printf("|\n");
  printf("Trimming the back spaces \n");
  trim_right_sv(&backSpace_s);
  printf("BackSpace_s : |");
  print_sv(&backSpace_s);
  printf("|\n");

  // splitting by a delimiter

  stringView info = SV("Red, Bag");
  printf("\nInfo : ");
  print_sv(&info);
  printf("\n");
  const stringView slice = split_by_delim(&info, ',');
  printf("\nslice: ");
  print_sv(&slice);
  printf("\n");
  printf("\nInfo : ");
  print_sv(&info);
  printf("\n");
}

static inline void test2() {
  // Advanced Test: Sequential CSV Parsing Loop
  stringView csv_data = SV("Apple,Banana,Orange,Mango");
  printf("\nParsing CSV Items:\n");

  // This loop terminates perfectly now because of the guard clause fix!
  while (csv_data.start_index < csv_data.end_index) {
    stringView fruit = split_by_delim(&csv_data, ',');
    printf(" -> Item: ");
    print_sv(&fruit);
    printf("\n");
  }
}

static inline void test3() {
  stringView config = SV("  timeout = 30 \n     host = localhost   \n port = 8080 ");

  printf("--- Parsing Config File Data ---\n");

  while (config.start_index < config.end_index) {
    // Step 1: Extract individual lines cleanly using the newline delimiter
    stringView line = split_by_delim(&config, '\n');

    // Step 2: Strip out any formatting whitespace from outer ends
    trim_left_sv(&line);
    trim_right_sv(&line);

    // Skip blank formatting lines
    if (line.start_index == line.end_index) continue;

    // Step 3: Isolate assignment values using the equality token
    stringView key = split_by_delim(&line, '=');
    stringView value = line; // The remainder of the line is the data block

    // Step 4: Perform cleanup on keys/values to clear space around the delimiter
    trim_right_sv(&key);
    trim_left_sv(&value);

    // Step 5: Render processed strings safely via stack memory
    printf("Key: [");
    print_sv(&key);
    printf("] -> Value: [");
    print_sv(&value);
    printf("]\n");
  }
}
#endif //STRINGVIEW_TESTS_H
