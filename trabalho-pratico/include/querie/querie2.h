#ifndef QUERIE2_H
#define QUERIE2_H
#include <glib.h>


guint get_garray_length(GArray *array);

char* seconds_to_hhmmss(int total_seconds);

gint compare_discography(gconstpointer a, gconstpointer b);

GArray* filter_and_sort_hash_table_by_discography(GHashTable *Artist_Table, char *country);

void querie2(GHashTable* Artist_Original, int n, int i, char* country);

#endif

