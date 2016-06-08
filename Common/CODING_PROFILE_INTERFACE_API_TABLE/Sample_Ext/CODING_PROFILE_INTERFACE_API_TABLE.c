#include<stdio.h>

int coding_prof_query(int id)
{
    printf("Number = %d\n",id);
    
}

typedef struct {
    int (*query)(int     id);
} GG_CODING_PROF_IF_T;

/****************************************************************************
 * CODING PROFILE INTERFACE API TABLE
 ****************************************************************************/
GG_CODING_PROF_IF_T  coding_prof_mgr_if = {
    coding_prof_query
};

void main()
{
    coding_prof_mgr_if.query(2);
}
