#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double G = 1.0;
//sequential n-body simulation with gravitational potential
//accepts a text file with vector of masses, vector of positions, vector of velocities
//2 Dimensions

typedef struct Bodies{
  double mass;
  double pos_x, pos_y;
  double vel_x, vel_y;
} Body;




double magnitude(double *vec, int size){
  double magnitude = 0.0;
  for(int i = 0; i < size; i++){
    magnitude += pow(vec[i],2);
  }
  return sqrt(magnitude);
}

void get_force_vector(double* result,Body* bodies, int size, int b1, int b2){
  //calculate force vector between two bodies
  //must have preallocated memory for result
  double relative_position[2] = {bodies[b1].pos_x - bodies[b2].pos_x, bodies[b1].pos_y - bodies[b2].pos_y};
  double dist = magnitude(relative_position, 2);
  
  double diff = (G*(bodies[b1].mass*bodies[b2].mass))/pow(dist,3); 
  result[0] = diff*relative_position[0]; 
  result[1] = diff*relative_position[1];
}

void get_force_on_body(double* result, Body* bodies, int size, int body){
  //read from bodies and write to new_bodies
  //functions much the same way, need to allocate space for result
  //calculate total force on a single body so that its position can be updates
  result[0] = 0.0; //init force to 0
  result[1] = 0.0;
  for(int i = 0; i < size; i++){
    //iterate through array
    if(i != body){
      //for all bodies except the one me want to calculate for
      //allocate another result
      double force_result[2];
      get_force_vector(force_result, bodies, size, body, i);
          printf("Force in loop method: %lf %lf\n",force_result[0],force_result[1]);

      //update original force
      result[0] += force_result[0]; //x
      result[1] += force_result[1]; //y
    }
  }
    printf("Force in method: %lf %lf\n",result[0],result[1]);

}

void calculate_update_on_b(Body* bodies, Body* new_bodies, int size, int body, double delta_t){
  double force[2];
  get_force_on_body(force, bodies, size, body);
  printf("Force: %lf %lf\n",force[0],force[1]);
  new_bodies[body].pos_x = bodies[body].pos_x + delta_t*bodies[body].vel_x;
  new_bodies[body].pos_y = bodies[body].pos_y + delta_t*bodies[body].vel_y; //incremet position based on velocity
  
  new_bodies[body].vel_x = bodies[body].vel_x + delta_t*force[0]/bodies[body].mass;
  new_bodies[body].vel_y = bodies[body].vel_y + delta_t*force[1]/bodies[body].mass; //increment velocity based on force
  
  new_bodies[body].mass = bodies[body].mass;
}

void update_bodies(Body* bodies, Body* new_bodies, int size, double delta_t){
  for(int i = 0; i < size; i++){
    calculate_update_on_b(bodies, new_bodies, size, i, delta_t);
  }
}


int main(int argc, char **argv){
  char *filename = argv[1];
  int no_bodies = atoi(argv[2]); //pass in a filename and the number of lines in that file
  FILE *myfile;
  myfile = fopen(filename, "r");
  
  //read data from text file (double mass, double position, double vel)
  
  Body bodies[100];
  Body new_bodies[100];
  
  char buffer[1024] = {0,};
  int i = 0;
  while(i < no_bodies){
    double mass_i, vel_x_i, vel_y_i, pos_x_i, pos_y_i;
    fgets(buffer, sizeof(buffer), myfile);
    sscanf(buffer, "%lf %lf %lf %lf %lf", &mass_i, &pos_x_i, &pos_y_i, &vel_x_i, &vel_y_i);
    bodies[i].mass = mass_i;
    bodies[i].pos_x = pos_x_i;
    bodies[i].pos_y = pos_y_i;
    bodies[i].vel_x = vel_x_i;
    bodies[i].vel_y = vel_y_i;
    i++;
  }
  
  //G = 6.673*pow(10,-11); //define gravitational constant
  
  
  for(int step = 0; step < 4; step++){
    update_bodies(bodies,new_bodies, no_bodies,1.0);
    
    for(int i = 0; i < no_bodies; i++){
      printf("A: %lf %lf %lf %lf\n", bodies[i].pos_x, bodies[i].pos_y, bodies[i].vel_x, bodies[i].vel_y);
    }
     for(int i = 0; i < no_bodies; i++){
      printf("A1: %lf %lf %lf %lf\n", new_bodies[i].pos_x, new_bodies[i].pos_y, new_bodies[i].vel_x, new_bodies[i].vel_y);
    }
   
    memcpy(bodies,new_bodies,sizeof(new_bodies));
    
    for(int i = 0; i < no_bodies; i++){
      printf("B: %lf %lf %lf %lf\n", bodies[i].pos_x, bodies[i].pos_y, bodies[i].vel_x, bodies[i].vel_y);
    }
    
  }
  
  for(int i = 0; i < no_bodies; i++){
    printf("Mass: %lf, Veloc: %lf %lf, Posit: %lf %lf\n", bodies[i].mass, bodies[i].vel_x, bodies[i].vel_y,bodies[i].pos_x, bodies[i].pos_y);
  }
  
  
}
