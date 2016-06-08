#include<stdio.h>

typedef int GG_CODING_RESULT_T;

typedef struct {
    GG_CODING_RESULT_T
    (*query)(
        int     id
    );
} GG_CODING_PROF_IF_T;

GG_CODING_RESULT_T coding_prof_query(int id)
{
    printf("Number = %d\n",id);
    
}

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
