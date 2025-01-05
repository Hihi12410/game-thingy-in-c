#define WIN32_LEAN_AND_MEAN

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

struct vector;
struct renderTable;

typedef struct vector VECTOR;
typedef struct renderTable RENTABLE;

struct vector mul_vec(struct vector vec1, struct vector vec2);
struct vector div_vec(struct vector vec1, struct vector vec2);
struct vector add_vec(struct vector vec1, struct vector vec2);
struct vector sub_vec(struct vector vec1, struct vector vec2);
int print_vec(struct vector vec1);

struct renderTable new_table(int x_size, int y_size, int init_val);

int getval_table(struct renderTable table, int x, int y);
int modval_table(struct renderTable *table, int x, int y, int val);

int getmat_table(struct renderTable table1, struct renderTable *table2, int offset_x, int offset_y);
int modmat_table(struct renderTable *table1, struct renderTable table2, int offset_x, int offset_y);
int free_table(struct renderTable *table);
void render(struct renderTable *toRender, int destroy);
