#include "cnbody/gravity.h"

double fgrav(double m1, double m2, double *pa, double *pb){
    const double G=6.67408e-11;
    double dir[3];
    for(int i=0;i<3;i++){
        dir[i]=pb[i]-pa[i];
    }
    return G*m1*m2/(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
}

/* 
 * a is the pos of the body we are calculating
 * for dir = b-a, vector points towards b
 */
void dgrav(double *dir, double *pa, double *pb){
    for(int i=0;i<3;i++){
        dir[i]=pb[i]-pa[i];
    }
    double mag = sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
    for(int i=0;i<3;i++){
        dir[i]=dir[i]/mag;
    }
}

/* ADDS TO VEC not overwrite */
void vecfgrav(double *vec, double m1, double m2, double *pa, double *pb){
    dgrav(vec,pa,pb);
    double f = fgrav(m1,m2,pa,pb);
    for(int i=0;i<3;i++){
        vec[i] += vec[i]*f;
    }
}

void apply_velverl(body *b, body **bs, int nb, double td){
    double fgrav_init[]={0,0,0};
    double fgrav_fina[]={0,0,0};

    for(int i=0;i<nb;i++){
        vecfgrav(fgrav_init, body_get_mass(*b), body_get_mass(*bs[i]), body_get_pos(*b), body_get_pos(*bs[i]));
    }
    body_set_pos_x(b,body_get_pos(*b)[0]+body_get_vel(*b)[0]*td+0.5*fgrav_init[0]/body_get_mass(*b)*td*td);
    body_set_pos_y(b,body_get_pos(*b)[1]+body_get_vel(*b)[1]*td+0.5*fgrav_init[1]/body_get_mass(*b)*td*td);
    body_set_pos_z(b,body_get_pos(*b)[2]+body_get_vel(*b)[2]*td+0.5*fgrav_init[2]/body_get_mass(*b)*td*td);

    for(int i=0;i<nb;i++){
        vecfgrav(fgrav_fina, body_get_mass(*b), body_get_mass(*bs[i]), body_get_pos(*b), body_get_pos(*bs[i]));
    }
    body_set_vel_x(b,body_get_vel(*b)[0]+0.5*(fgrav_init[0]/body_get_mass(*b)+fgrav_fina[0]/body_get_mass(*b))*td);
    body_set_vel_y(b,body_get_vel(*b)[1]+0.5*(fgrav_init[1]/body_get_mass(*b)+fgrav_fina[1]/body_get_mass(*b))*td);
    body_set_vel_z(b,body_get_vel(*b)[2]+0.5*(fgrav_init[2]/body_get_mass(*b)+fgrav_fina[2]/body_get_mass(*b))*td);
}
