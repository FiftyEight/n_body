#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
double G = 6.673;
//sequential n-body simulation with gravitational potential
//accepts a text file with vector of masses, vector of positions, vector of velocities
//2 Dimensions

typedef struct {
	double mass;
	double pos_x, pos_y;
	double vel_x, vel_y;
} body;


int main(int argc, char **argv){
	char *filename = argv[1];
	int no_bodies = atoi(argv[2]); //pass in a filename and the number of lines in that file
	FILE *myfile;
	myfile = fopen(filename, "r");

	//read data from text file (double mass, double position, double vel)
	
	double mass[100];
	double vel_x[100];
	double vel_y[100];
	double pos_x[100];
        double pos_y[100];

	char buffer[1024] = {0,};
	int i = 0;
	while(i < no_bodies){
		double mass_i, vel_x_i, vel_y_i, pos_x_i, pos_y_i;
		fgets(buffer, sizeof(buffer), myfile);
		sscanf(buffer, "%lf %lf %lf %lf %lf", &mass_i, &pos_x_i, &pos_y_i, &vel_x_i, &vel_y_i);
		mass[i] = mass_i;
		pos_x[i] = pos_x_i;
		pos_y[i] = pos_y_i;
		vel_x[i] = vel_x_i;
		vel_y[i] = vel_y_i;
	        i++;
	}

	//quick check: did we load them in correctly?
	/*for(int j  = 0; j < no_bodies; j++){
		printf("%lf %lf %lf\n", mass[j], pos[j], vel[j]);
	}*/

	G = 6.673*pow(10,-11); //define gravitational constant



}

void update_bodies(double *mass, double *pos, double *vel, int size){
	//update values for bodies
}

double magnitude(double *vec, int size){
	double magnitude = 0.0;
	for(int i = 0; i < size; i++){
		magnitude += pow(vec[i],2);
	}
	return sqrt(magnitude);
}

void get_force_vector(double* result, double *mass, double *pos_x, double *pos_y, double *vel_x, double *vel_y, int size, int b1, int b2){
	//calculate force vector between two bodies
	//must have preallocated memory for result
	double relative_position[2] = {pos_x[b1] - pos_x[b2], pos_y[b1] - pos_y[b2]};
	double dist = magnitude(relative_position, 2);
	
	double diff = (G*(mass[b1]*mass[b2]))/pow(dist,3); 
	result[0] = diff*relative_position[0]; 
	result[1] = diff*relative_position[1];
}

void get_force_on_body(double* result, double *mass, double *pos_x, double *pos_y, double *vel_x, double *vel_y, int size, int body){
	//functions much the same way, need to allocate space for result
	//calculate total force on a single body so that its position can be updates
	for(int i = 0; i < size; i++){
		//iterate through array
		if(i != body){
			//for all bodies except the one me want to calculate for
			get_force_vector(result, mapp, pos_x, pos_y, vel_x, vel_y, size, body, i);
			//should be able to do this without defining a struct...
		}
	}
}

