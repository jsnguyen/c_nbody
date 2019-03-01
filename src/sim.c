#include "stdio.h"
#include "stdlib.h"
#include "assert.h"
#include "time.h"
#include "cnbody/body.h"
#include "cnbody/gravity.h"
#define SOL_MASS 1.989e30
#define EAR_MASS 5.972e24
#define AU 1.396e11
static inline double get_rand_between(double a, double b) {
    assert(a<b);
    return a+((double)rand() / (double)RAND_MAX)*(b-a);
}

static inline void random_bodies(body *bs, int nb){
    for(int i=0;i<nb;i++){
        body_set_id(&bs[i],i);
        body_set_mass(&bs[i],get_rand_between(1e3*SOL_MASS,1e5*SOL_MASS));
        double pos[3];
        double vel[]={0,0,0};
        for(int j=0;j<2;j++){
            pos[j]=get_rand_between(-1e1*AU,1e1*AU);
            //vel[j]=get_rand_between(0,1e3);
        }
        pos[2]=0;
        vel[2]=0;
        body_set_pos(&bs[i],pos);
        body_set_vel(&bs[i],vel);
    }
}

int main(int argc, char* argv[]){
    srand((unsigned)time(NULL));
    /* rand is weird */
    rand(); rand(); rand();

    const int nb = 1e2;
    body bs[nb];
    for(int i=0;i<nb;i++){
        body_init(&bs[i]);
    }

    random_bodies(bs,nb);
    
    for(int i=0;i<nb;i++){
        body_print(bs[i]);
    }

    int niter=1000;
    FILE *f;
    char* outf="out.txt";
    f = fopen(outf,"w");
    fprintf(f,"%i\n",niter);
    fprintf(f,"%i\n",nb);
    fclose(f);

    register posvel nprop[nb];
    for(int i=0;i<niter;i++){
        for(int j=0;j<nb;j++){
            body_write(bs[j],outf);
            nprop[j] = apply_velverl(&bs[j], bs, nb, 1e4);
        }
        for(int j=0;j<nb;j++){
            body_set_pos(&bs[j],nprop[j].pos);
            body_set_vel(&bs[j],nprop[j].vel);
        }
        printf("%.2f%%\n",(double) 100*i/niter);
    }
    printf("100.00%%\n");
    
    for(int i=0;i<nb;i++){
        body_delete(&bs[i]);
    }

    printf("success!\n");
    return 0;
}
