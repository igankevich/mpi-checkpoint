CC = mpicc

mpi_checkpoint.so: mpi_checkpoint.c mpi_checkpoint.h mpi_checkpoint_weak.c
	$(CC) -D_GNU_SOURCE mpi_checkpoint.c -shared -fpic -o mpi_checkpoint.so

mpi_checkpoint_weak.o: mpi_checkpoint_weak.c
	$(CC) mpi_checkpoint_weak.c -o mpi_checkpoint_weak.o

mpi_checkpoint_weak.c: mpi_checkpoint_gen.c mpi_checkpoint_gen
	./mpi_checkpoint_gen > mpi_checkpoint_weak.c

mpi_checkpoint_gen: mpi_checkpoint_gen.c
	$(CC) mpi_checkpoint_gen.c -o mpi_checkpoint_gen
