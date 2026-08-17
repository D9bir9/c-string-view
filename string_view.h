//
// Created by dabira on 8/17/26.
//

#ifndef STRINGVIEW_STRING_VIEW_H
#define STRINGVIEW_STRING_VIEW_H
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>


#ifdef __cplusplus
extern "C" {
#endif
typedef struct {
  const char* data;
  size_t start_index;
  size_t end_index;
} stringView;

/* Multi-evaluation safe literal initialization macro */
#define SV(literal) string_view_from_data(literal, sizeof(literal) - 1)

/* Safe macro for standard runtime null-terminated char strings */
#define SV_STR(runtime_str) string_view_from_data(runtime_str, strlen(runtime_str))

static inline stringView string_view_from_data(const char* data, const size_t length) {
  return (stringView){.data = data, .start_index = 0, .end_index = length};
}

static inline void strip_left(stringView *s){
  /* Remove one character from the left of the view */
  if (s->start_index < s->end_index){
    s->start_index++;
  }
}

static inline void strip_right(stringView *s){
  /* Remove one character from the right of the view */
  if (s->end_index > s->start_index){
    s->end_index--;
  }
}

static inline void print_sv(const stringView *s){
  /* A function to print out the string view */
  for (size_t i = s->start_index; i < s->end_index; ++i){
    printf("%c", s->data[i]);
  }
}

static inline bool sv_equals(const stringView *a, const stringView *b){
  /* Check if two stringViews are equal */
  const size_t a_length = a->end_index - a->start_index;
  const size_t b_length = b->end_index - b->start_index;
  if (a_length != b_length) return false;

  return memcmp(a->data + a->start_index,
      b->data + b->start_index, a_length) == 0;
}

static inline bool sv_start_with(const stringView *s, const stringView *prefix){
  /* Check if a string view starts with a prefix */
  const size_t s_length = s->end_index - s->start_index;
  const size_t p_length = prefix->end_index - prefix->start_index;
  if (s_length < p_length) return false;

  return memcmp(s->data + s->start_index,
      prefix->data + prefix->start_index, p_length) == 0;
}

static inline bool sv_end_with(const stringView *s, const stringView *suffix){
  /* Check if a stringView ends with a suffix */
  const size_t s_length = s->end_index - s->start_index;
  const size_t suf_length = suffix->end_index - suffix->start_index;
  if (s_length < suf_length) return false;

  const size_t offset = s->end_index - suf_length;
  return memcmp(s->data + offset,
      suffix->data + suffix->start_index, suf_length) == 0;
}

static inline void trim_left_sv(stringView *s){
  /* Remove white spaces from the left of a stringView */
  size_t count = 0;
  while (s->start_index + count < s->end_index && isspace((unsigned char)s->data[s->start_index + count])){
    count++;
  }
  s->start_index += count;
}
static inline void trim_right_sv(stringView *s){
  /* Remove white spaces from the right of a stringView */
  size_t count = 0;
  while (s->start_index < s->end_index -count && isspace((unsigned char)s->data[s->end_index - count - 1])){
    count++;
  }
  s->end_index -= count;
}

static inline stringView split_by_delim(stringView *s, const char delim) {
  /* Split string view by delimiter */
  if (s->start_index >= s->end_index) {
    return (stringView){.data = s->data, .start_index = s->start_index, .end_index = s->end_index};
  }
  size_t count = 0;
  while (s->start_index + count < s->end_index && *(s->data + s->start_index + count) != delim) {
    count++;
  }
  const stringView token = (stringView){
    .data = s->data,
    .start_index = s->start_index,
    .end_index = s->start_index + count
  };
  if (s->start_index + count < s->end_index) {
    s->start_index += count + 1;
  }
  else {
    s->start_index = s->end_index;
  }
  return token;
}
#ifdef __CPlusPlus
}
#endif
#endif //STRINGVIEW_STRING_VIEW_H
