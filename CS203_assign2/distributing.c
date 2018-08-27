#include<stdio.h>
#include<stdlib.h>

#define MAX_ITERATIONS 200000
#define NUM_SERVERS 10000000

int main()
{
  //Z can be a maximum of NUM_SERVERS , beginning from 1,however very high values of Z practically never appears
  int* dist_count=(int*)calloc(NUM_SERVERS/100,sizeof(int));
  int num_exceed=0;
  for(int i=0;i<MAX_ITERATIONS;i++)
  {
    srandom(i);
    if(i%100==0)
    {
      printf("%d iterations have finished.\n",i);
    }
    if(i%1000==0)//Backup every 1000 iterations
    {
      FILE* dist_data=fopen("Distributed_Data.txt","w");
      for(int i=0;i<NUM_SERVERS/100;i++)
      {
        fprintf(dist_data,"%d\n",*(dist_count+i));
      }
      fprintf(dist_data,"%d times the max job was greater than 1/100 the number of servers\n",num_exceed);
      fclose(dist_data);
    }
    int max_job=0;
    int* server_job_count=(int*)calloc(NUM_SERVERS,sizeof(int));
    //for each client assign its job randomly to any server
    //increment the job count of server by one
    //Also keeps track of the maximum number of jobs any server has
    for(int client=0;client<NUM_SERVERS;client++)//number of client is equal to number of servers
    {
      int server_number=random()%NUM_SERVERS;
      *(server_job_count+server_number)=*(server_job_count+server_number)+1;
      if(*(server_job_count+server_number) > max_job)
      {
        max_job=*(server_job_count+server_number);
      }
    }
    //we have the maximum number of job any client has
    free(server_job_count);
    if(max_job<NUM_SERVERS/100)
    {
      *(dist_count+max_job-1)=*(dist_count+max_job-1)+1;
    }
    else
    {
      num_exceed=num_exceed+1;
    }
  }
  free(dist_count);
  return 0;
}
