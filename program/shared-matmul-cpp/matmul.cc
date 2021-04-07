/*
 Copyright (C) 2000-2010 by Grigori G.Fursin

 http://fursin.net/research

 UNIDAPT Group
 http://unidapt.org
*/

#ifdef OPENME
 #include <openme.h>
#endif

#include <iostream>
#include <fstream>

//#include <stdio.h>
#include <stdlib.h>

#define Q 16

class matmul
{
 public: 
  void calc(float* A, float* B, float* C, int N);
};

void matmul::calc(float* A, float* B, float* C, int N)
{
  int i,j,k;

  for (i=0; i<N; i++)
  {
/* Grigori remarked this line to enable cross-function data reuse just for testing
    A[i*N+j]=0; */
    for (j=0; j<N; j++)
    {
      for (k=0; k<N; k++)
      {
        A[i*N+j]=A[i*N+j]+B[i*N+k]*C[k*N+j];
      }
    }
  }
}

int main(int argc, char* argv[])
{
  FILE* fgg=NULL;
  int N=0;
  float QQ[Q];
  int i=0;
  int j=0;
  int k=0;

  float* A;
  float* B;
  float* C;

  long ct_repeat=0;
  long ct_repeat_max=1;
  int ct_return=0;

  char* fn;

#ifdef OPENME
  openme_init(NULL,NULL,NULL,0);
  openme_callback("PROGRAM_START", NULL);
#endif

  fn=argv[1];

  if ((getenv("CT_REPEAT_MAIN")!=NULL) && (getenv("CT_MATRIX_DIMENSION")!=NULL))
  {
    ct_repeat_max=atol(getenv("CT_REPEAT_MAIN"));
    N=atol(getenv("CT_MATRIX_DIMENSION"));
  } 
  else
  {
    if (argc<3)
    {
       std::cout << "Usage:\n";
       std::cout << "  matmul <data file> <matrix dimension> <repetitions>\n";
       return 1;
    }

    N=atoi(argv[2]);
    ct_repeat_max=atol(argv[3]);
  }

  std::cout << "matrix dimension:" << N;

  if ((fgg=fopen(fn,"rt"))==NULL)
  {
    std::cerr << "\nError: Can't find data!\n";
    return 1;
  }

  for (i=0; i<Q; i++)
  {
    fscanf(fgg, "%f", &QQ[i]);
  }

  fclose(fgg);

  A=(float*) malloc(N*N*sizeof(float));
  B=(float*) malloc(N*N*sizeof(float));
  C=(float*) malloc(N*N*sizeof(float));

  k=0;
  for (i=0; i<N; i++)
  {
    for (j=0; j<N; j++)
    {
      A[j+i*N]=QQ[k++]*rand()/RAND_MAX;
      if (k>=Q) k=0;
      B[j+i*N]=QQ[k++]*rand()/RAND_MAX;
      if (k>=Q) k=0;
      C[j+i*N]=QQ[k++]*rand()/RAND_MAX;
      if (k>=Q) k=0;
    }
  }

  matmul mm;

#ifdef OPENME
  openme_callback("KERNEL_START", NULL);
#endif
  for (ct_repeat=0; ct_repeat<ct_repeat_max; ct_repeat++)
  {
    mm.calc(A,B,C,N);
  }
#ifdef OPENME
  openme_callback("KERNEL_END", NULL);
#endif

  for (i=0; i<N; i++)
  {
    std::cout << i << ") " << A[i*N+i] << " " << B[i*N+i] << " " << C[i*N+i] << "\n";
  }

  free(C);
  free(B);
  free(A);

#ifdef OPENME
  openme_callback("PROGRAM_END", NULL);
#endif

  return 0;
}
