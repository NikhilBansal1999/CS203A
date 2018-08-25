#include<stdio.h>
#include<stdlib.h>

#define MAX_ITERATIONS 1000
#define NUM_PEOPLE 1000000

int main()
{
  //Probability of X being greater than 10*NUM_PEOPLE is very small
  int* day_count=(int*)calloc(10*NUM_PEOPLE,sizeof(int));
  int num_exceed=0;
  for(int i=0;i<MAX_ITERATIONS;i++)
  {
    srandom(i);
    if(i%100==0)
    {
      printf("%d iterations have finished.\n",i);
    }
    if(i%1000==0)
    {
      FILE* day_data=fopen("News_Data.txt","w");
      for(int i=0;i<10*NUM_PEOPLE;i++)
      {
        fprintf(day_data,"%d\n",*(day_count+i));
      }
      fprintf(day_data,"%d days exceed 10 times the number of people\n",num_exceed);
      fclose(day_data);
    }
    int* known_people=(int*)calloc(NUM_PEOPLE,sizeof(int));
    *known_people=1;
    int num_known=1;
    int days=0;
    while(num_known<NUM_PEOPLE)
    {
      int* set_in_this_iter=(int*)calloc(NUM_PEOPLE,sizeof(int));
      for(int j=0;j<NUM_PEOPLE;j++)
      {
        if((*(known_people+j)==1)&&(*(set_in_this_iter+j)==0))//if j'th person knew the news the previous day
        {
          int random_person;
          do//choose a random person not equal to j
          {
            random_person=random()%NUM_PEOPLE;
          } while(random_person==j);
          if(*(known_people+random_person)==0)
          {
            num_known=num_known+1;
            *(known_people+random_person)=*(known_people+random_person)+1;
            *(set_in_this_iter+random_person)=*(set_in_this_iter+random_person)+1;
          }
        }
      }
      free(set_in_this_iter);
      days=days+1;
    }
    if(days>=(10*NUM_PEOPLE))
    {
      num_exceed=num_exceed+1;
    }
    else
    {
      *(day_count+days)=*(day_count+days)+1;
    }
    free(known_people);
  }
  free(day_count);
  return 0;
}
