QUICK-NOTE: The image labeled DataRate.png
-> The units are incorrect (only slightly)
-> The data for MB/sec is too large by a factor of 2!!
-> When running the code, I forgot to account
-> for the fact that I was recording the time taken
-> to send data over and back. Therefore, the max dataRate
-> between crunchy1/3 maxes out around 1GByte/sec

Joe Zuhusky:

HW3 MPI Submission

See data plots attached for Data collected

TripTimeVsMB.ps ->
Shows trip time of sending an array between 2 machines and back

DataRate.png -> Show how bandwidth becomes saturated as the 
number of trips around the loop increases. This is pretty much 
what was expected.

Call 'make' to compile

mpirun {INPUT YOUR OWN FLAGS HERE} ./int_ring.run #loops
mpirun {INPUT YOUR OWN FLAGS HERE} ./int_array.run #loops #sizeOfIntegerArrayToSendAboutTheLoop


Final project pitch:

I'll be experimenting with parallel implementations of the
Multigrid Method for 2D Laplace/Possion eq, possibly 3D (a simple extension).

Todo:
1. Implement Serial Code
2. Explore speedup achieveable using openMP & MPI.
3. Try to map the Kernel (relaxtion loops) to GPU for serial Code and examine speedup.
4. Deploy to stampede for ~4k MPI Procs/tasks.











