#ifndef QUERIE2_H
#define QUERIE2_H
#include <glib.h>


guint get_garray_length(GArray *array);

char* seconds_to_hhmmss(int total_seconds);

void print_info_array(GArray *array);

gint compare_discography(gconstpointer a, gconstpointer b);

GArray* filter_and_sort_hash_table_by_discography(GHashTable *D_Info_original, char *country);

void querie2(GHashTable* dinfo_Original, GHashTable* Artist_Original, int n, int i, char* country);

#endif

