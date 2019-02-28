#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "cnbody/body.h"
#include "cnbody/gravity.h"

double get_rand_between(double a, double b) {
    assert(a<b);
    return a+((double)rand() / (double)RAND_MAX)*(b-a);
}

int main(int argc, char* argv[]){
    srand(time(NULL));
    body *sun = body_create();
    body_set_mass(sun,1.989e30);
    body_set_pos(sun,(double[]) {0,0,0} );
    body_set_vel(sun,(double[]) {0,0,0} );

    body *earth = body_create();
    body_set_mass(earth,5.972e24);
    body_set_pos(earth,(double[]){1.496e11,0,0});
    body_set_vel(earth,(double[]){0,2.98e4,0});

    body_print(*earth);
    body_print(*sun);

    body *bs[1];
    bs[0]=sun;
    int niter=10000;
    FILE *f;
    char* outf="out.txt";
    f = fopen(outf,"w");
    fclose(f);

    for(int i=0;i<niter;i++){
            body_write(*earth,outf);
            apply_velverl(earth, bs, 1, 1e4);
    }
    
    body_destroy(earth);
    body_destroy(sun);

    printf("success!\n");
    return 0;
}
