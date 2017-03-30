
#include "util.h"
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){

	if (argc != 3){
		printf("Please specifcy two command Line param 'N' = Num Loops about ring\n");
		printf("and number of integers to send\n");
	}
	int rank, tag, origin, destination,comm_size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	MPI_Status status;
	char hostname[1024];
 	gethostname(hostname, 1024);

	int N = atoi(argv[1]);
	int currentLoop=0;
	int numberOfInts = atoi(argv[2]);
	int *message_out = (int*)malloc(sizeof(int)*atoi(argv[2]));
	int *message_in  = (int*)malloc(sizeof(int)*atoi(argv[2]));

	timestamp_type time1, time2;
	
	double avgRTT = 0.0;

	if(rank == 0){ // Starter Process
        	get_timestamp(&time1);
		destination = rank+1;
		origin = comm_size-1;
		while (currentLoop < N){
			currentLoop++;
			get_timestamp(&time1);
			MPI_Send(message_out, numberOfInts, MPI_INT, destination, tag, MPI_COMM_WORLD);
			MPI_Recv(message_in,  numberOfInts, MPI_INT, origin, tag, MPI_COMM_WORLD, &status); // Blocking 
			get_timestamp(&time2);
			avgRTT += timestamp_diff_in_seconds(time1,time2);
		}
		avgRTT = avgRTT / N / 2.0;
		printf("%f %f %f \n",numberOfInts*sizeof(int)*0.000001,avgRTT, numberOfInts*sizeof(int)*0.000001/avgRTT);
		
	}else{
		destination = (rank+1)%comm_size;
		origin = rank-1;
		while  ( currentLoop < N){
			MPI_Recv(message_in,  numberOfInts, MPI_INT, origin, tag, MPI_COMM_WORLD, &status); // Blocking 
			MPI_Send(message_out, numberOfInts, MPI_INT, destination, tag, MPI_COMM_WORLD);
			currentLoop++;
		}
	}
	free(message_in);
	free(message_out);
	

	MPI_Finalize();
	return 0;



}
