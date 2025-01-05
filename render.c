#include "render.h"

struct vector
{
    int x;
    int y;
};
struct renderTable {
    int x_size;
    int y_size;
    int *contents;
};

const struct vector VEC_ZERO = {0,0};
const struct vector VEC_UP = {0,1};
const struct vector VEC_DOWN = {0,-1};
const struct vector VEC_LEFT = {-1,0};
const struct vector VEC_RIGHT = {1,0};

const struct renderTable ERRORTABLE = {-1, -1, NULL};

struct vector mul_vec(struct vector vec1, struct vector vec2)
{  
    return (struct vector) {vec1.x*vec2.x, vec1.y*vec2.y};
};
struct vector div_vec(struct vector vec1, struct vector vec2)
{  
    return (struct vector) {vec1.x/vec2.x, vec1.y/vec2.y};
};
struct vector add_vec(struct vector vec1, struct vector vec2)
{  
    return (struct vector) {vec1.x+vec2.x, vec1.y+vec2.y};
};
struct vector sub_vec(struct vector vec1, struct vector vec2)
{  
    return (struct vector) {vec1.x-vec2.x, vec1.y-vec2.y};
};
int print_vec(struct vector vec1)
{
    printf("{ %d ; %d }", vec1.x, vec1.y);
    return 0;
}

struct renderTable new_table(int x_size,int  y_size, int init_val)
{
    struct renderTable renTable;
    
    renTable.x_size = x_size;
    renTable.y_size = y_size;

    int *cont = malloc(x_size * y_size * sizeof(int));
    if (cont == NULL)
    {
        return ERRORTABLE;
    }
    for (int y = 0; y < y_size; y++)
    {
        for (int x = 0; x < x_size; x++)
        {
            cont[y*x_size+x] = init_val;
        }
    }
    renTable.contents = cont;
    return renTable;
}

int getval_table(struct renderTable table, int x, int y)
{
    if (table.contents == NULL) {return -1;}

    int val = table.contents[table.x_size*y+x];
    return val;     //If NULL error
};
int modval_table(struct renderTable *table, int x, int y, int val)
{
    if (table->contents == NULL) {return 1;}                                         //Err
    if (x < 0 || x >= table->x_size || y < 0 || y >= table->y_size ) {return 2;}      //Err
    
    table->contents[table->x_size*y+x] = val;
    return 0;
};
int getmat_table(struct renderTable table1, struct renderTable *table2, int offset_x, int offset_y)
{
    if (table1.contents == NULL || table2->contents == NULL)
    {
        return -1;
    }
    
    int sxa, sxb, sya, syb;
    int limxa, limxb, limya, limyb;
    int start_iter_x, start_iter_y;

    sxa = 0; sya = 0;
    limxa = sxa + table1.x_size;
    limya = sya + table1.y_size;

    sxb = offset_x; syb = offset_y;
    limxb = sxb + table2->x_size;
    limyb = syb + table2->y_size;

    for (int y = syb; y < limyb; ++y)
    {
        for (int x = sxb; x < limxb; ++x)
        {
            if (y >= limya || y < sya || x >= limxa || x < sxa)
            {
                table2->contents[(syb-y)*table2->x_size+x] = 0;
            }else{
                table2->contents[(syb-y)*table2->x_size+x] = table1.contents[y*table1.x_size+x];
            }
        }
    } 
    return 0;
};
int modmat_table(struct renderTable *table1, struct renderTable table2, int offset_x, int offset_y){
    getmat_table(table2, table1, offset_x, offset_y);
    return 0;
};

int free_table(struct renderTable *table){
    free(table->contents);
    table->contents = NULL;
    return 0;
};

void render(struct renderTable *table, int destr)
{
    if (table->contents != NULL)
    {
        for (int y = 0; y < table->y_size; ++y)
        {
            for (int x = 0; x < table->x_size; ++x)
            {
                printf("%d ", table->contents[y*table->x_size+x]);
            }
            printf("\n");        
        }
        if (destr == 1) free_table(table);
    }
}; 

int main()
{   
    RENTABLE a = new_table(10, 10, 1);
    RENTABLE b = new_table(5,5,0);
    RENTABLE c = new_table(6,6,0);

    render(&a, 0);
    render(&b, 0);
    render(&c, 0);

    getmat_table(a, &c, 3, 5);
    modmat_table(&a, b, 0,0);

    render(&a, 1);
    render(&b, 1);
    render(&c, 1);

    return 0;
}