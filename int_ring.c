
#include <stdio.h>
#include <unistd.h>
#include <mpi.h>

int main(int argc, char **argv){

	if (argc != 2){
		printf("Please specifcy ONE command Line param 'N' = Num Loops about ring\n");
	}
	int rank, tag, origin, destination,comm_size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);

	MPI_Status status;
	char hostname[1024];
 	gethostname(hostname, 1024);

	int message_in;
	int N = atoi(argv[1]);
	int currentLoop=0;
	int message_out=rank;

	if(rank == 0){ // Starter Process
		printf("Running with %d processes\n",comm_size);
		destination = rank+1;
		origin = comm_size-1;
		while (currentLoop < N){
			currentLoop++;
			MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
			MPI_Recv(&message_in,  1, MPI_INT, origin, tag, MPI_COMM_WORLD, &status); // Blocking 
			message_out += message_in;
			printf("Rank %d running on %s recveived MSG: %d from Rank %d now sending %d to %d\n",
				rank,hostname,message_in,origin,message_out,destination);
		}
		
	}else{
		destination = (rank+1)%comm_size;
		origin = rank-1;
		while  ( currentLoop < N){
			MPI_Recv(&message_in,  1, MPI_INT, origin, tag, MPI_COMM_WORLD, &status); // Blocking...
			message_out = message_in + rank;
			printf("Rank %d running on %s recveived MSG: %d from Rank %d now sending %d to %d\n",
				rank,hostname,message_in,origin,message_out,destination);
			MPI_Send(&message_out, 1, MPI_INT, destination, tag, MPI_COMM_WORLD);
			currentLoop++;
		}
	}

	MPI_Finalize();
	return 0;



}
