#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main ()
{
pid_t i, pid1, pid2;

pid1 = fork(); // First fork will create child_1 from parent

if (pid1 <0) // fork unsuccessful
 {
	printf("fork unsuccessful");
	exit(1);
 }

if (pid1 > 0) // If pid1 is greater than 0, we are in the top parent process
 {
	i = getpid();
	printf("\n parent process (PID %d) created child_1 (PID %d)\n", i, pid1);
	printf("\n parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", i, pid1);
	wait(NULL); // Wait for child_1 process to complete
	pid2 = fork(); // Second fork and create child_2
	if(pid1 > 0 && pid2 > 0){ // If pid1 and pid2 is greater than 0 we know that we have successfuly created 2 children and are continuing the parent process
		printf("\n parent (PID %d) created child_2 (PID %d)\n", i, pid2);
	}
	if(pid2 == 0){ // Child_2 process
		i = getpid();
		printf("\n child_2 (PID %d) is calling an external program external_program.out and leaving child_2...\n\n", i);
		execl("external_program.out", "external_program.out", NULL);
		printf("\n");
	}
 }

if (pid1 == 0) // child_1 process
  {	
	i = getpid();
	pid2 = fork(); // Creates child_1.1 process
		if(pid1 == 0 && pid2 > 0){ // Child_1 process
			printf("\n child_1 (PID %d) created child_1.1 (PID %d)\n", i, pid2);
			printf("\n child_1 (PID %d) is now complete\n", i);
		}
	}  
}
