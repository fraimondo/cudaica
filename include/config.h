/*
 *	Copyright (C) 2011, Federico Raimondo (fraimondo@dc.uba.ar)
 *
 *	This file is part of Cudaica.
 *
 *  Cudaica is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  Cudaica is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Cudaica.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __CONFIG__
#define __CONFIG__

/*****************************
 * Opciones de configuracion *
 *****************************/
 /*
  * GPU Paramteres
  */
#define MAX_MULTIPROCESSORS 32
#define MAX_CHANNELS 512

/*
 * Prints debugging messages
 * Levels 0 - N
 * 1 - Function calls
 * 2 - Memory information
 * 3 - Function calls inside iterations
 */
//~ #define DEBUG 2

#ifdef DEBUG
	#define PREFIX "DEBUG::%s:%d "
	#define DPRINTF(N, ...) if (N <= DEBUG) { fprintf(stdout, PREFIX ,__FILE__, __LINE__); fprintf(stdout, __VA_ARGS__); }

	#if DEBUG >= 3
		#define printcol 31
		#define printrow 8955
	#endif
#else /* Not DEBUG */
	#define DPRINTF(N, ...)
#endif


/*
 * Double/Single precission magic
 */

#ifdef USESINGLE
typedef float real;
#else
typedef double real;
#endif

typedef unsigned int natural;
typedef int	integer;
typedef int error;


#define JACOBI_TOLERANCE 0.000001f


/*
 * INFOMAX Configuration
 */
#define DEFAULT_BIASING        	1
#define MAX_PDFSIZE            	6000
#define MIN_PDFSIZE            	2000
#define DEFAULT_EXTENDED       	1
#define DEFAULT_EXTBLOCKS       1
#define DEFAULT_BLOCK(length)  	(unsigned int)sqrt((float)length/3.0)
#define DEFAULT_MAXSTESPS	    512
#define DEFAULT_STOP         	0.000001
#define DEFAULT_POSACT		   	1
#define DEFAULT_SPHERING	   	1
#define DEFAULT_PCA			   	0
#define DEFAULT_MOMENTUM       	0.0
#define DEFAULT_EXTMOMENTUM   	0.5
#define MIN_LRATE              	0.000001
#define MAX_LRATE              	0.1
#define DEFAULT_LRATE(chans)   	0.015/log((float)chans)

#define MAX_WEIGHT             	1e8

#define DEFAULT_ANNEALDEG      	60
#define DEFAULT_ANNEALSTEP     	0.90
#define DEFAULT_EXTANNEAL      	0.98

#define DEFAULT_BLOWUP         	1000000000.0
#define DEFAULT_BLOWUP_FAC     	0.8
#define DEFAULT_RESTART_FAC    	0.9

 /* Extended options*/
#define DEFAULT_NSUB           	1
#define DEFAULT_EXTBLOCKS      	1
#define DEFAULT_UREXTBLOCKS    	1
#define SIGNCOUNT_THRESHOLD    	25
#define DEFAULT_SIGNSBIAS      	0.02
#define SIGNCOUNT_STEP         	2
#define DEGCONST               	180.0/ICA_PI
#define ICA_PI                 	3.14159265358979324

#define DEFAULT_VERBOSE			1

#define MAX_MEM_THRESHOLD 64

#define RESERVED_MEM_BYTES (32 * 1024 * 1024)
#define MAX_CUDA_BLOCKS 65535


/*
 * BLAS functions
 */
#ifdef USESINGLE
#define ddot_ sdot_
#define idamax_ isamax_
#define ilaenv_ ilaenv_
#define dscal_ sscal_
#define dcopy_ scopy_
#define dswap_ sswap_
#define daxpy_ saxpy_
#define dgemv_ sgemv_
#define dgemm_ sgemm_
#define dsymm_ ssymm_
#define dsyrk_ ssyrk_
#define dsyev_ ssyev_
#define dgesv_ sgesv_
#define dgetri_ sgetri_
#define dgetrf_ sgetrf_
#endif


/*
 * CUBLAS functions
 */
#ifdef USESINGLE
	#define cublas(X) cublasS##X
#else
	#define cublas(X) cublasD##X
#endif

/*
 * CUBLAS error messages
 */

#define CUBLAS_STATUS_NOT_INITIALIZED_STR "CUBLAS_STATUS_NOT_INITIALIZED"
#define CUBLAS_STATUS_ALLOC_FAILED_STR "CUBLAS_STATUS_ALLOC_FAILED"
#define CUBLAS_STATUS_INVALID_VALUE_STR "CUBLAS_STATUS_INVALID_VALUE"
#define CUBLAS_STATUS_ARCH_MISMATCH_STR "CUBLAS_STATUS_ARCH_MISMATCH"
#define CUBLAS_STATUS_MAPPING_ERROR_STR "CUBLAS_STATUS_MAPPING_ERROR"
#define CUBLAS_STATUS_EXECUTION_FAILED_STR "CUBLAS_STATUS_EXECUTION_FAILED"
#define CUBLAS_STATUS_INTERNAL_ERROR_STR "CUBLAS_STATUS_INTERNAL_ERROR"


#define STR_EXPAND(tok) #tok
#define xstr(tok) STR_EXPAND(tok)

#define GITVERSION xstr(GITHASH)

#if CUDA_VERSION>4
	#define SYMBOL(x) x
#else
	#define SYMBOL(x) xstr(x)
#endif

typedef struct {
	/*
	 * Required
	 */
	char *		datafile;			//Input data file
	natural		nchannels;			//Channels
	natural		nsamples;			//Samples
	char *		weightsoutfile;		//Weights out file
	char *		sphereoutfile;		//Sphere out file

	/*
	 * Listed as required but optional
	 */
	natural		sphering;			//Do sphering
	natural		biasing;			//Do bias
	natural		extblocks;			//Do extended: N of blocks
	natural		pca;				//Do PCA
	/*
	 * Optional
	 */
	char *		weightsinfile;		//Weights in file
	real		lrate;				//Initial learning rate
	natural 	block;				//Block size
	real	 	nochange;  			//Stop
	natural 	maxsteps;			//Max steps
	natural		posact;				//Positive activations
	real		annealstep;			//Anneal step
	real		annealdeg;			//Anneal deg
	real		momentum;			//Momentum

	char*		activationsfile;
	char*		biasfile;
	char*		signfile;

	natural		verbose;

	natural		seed;				//Random permutation seed

	/*
	 * Internal
	 */
	natural 	nsub;
	natural 	pdfsize;
	natural 	urextblocks;
	real 		signsbias;
	int			extended;

} config_t;

typedef struct {
	natural			nchannels;			//Original channels (rows)
	natural			nsamples;			//Original samples (cols)
	void* 			devicePointer;		//Pointer to device mem where loaded
	real* 			sphere;				//sphere matrix
	size_t	 		pitch;				//Datapitch in device
	real* 			data;				//The data
	size_t			spitch;				//Sphering pitch
	real*			weights;			//Weights
	size_t			wpitch;				//Weights pitch
	real* 			h_weights;			//Weights in host, used for weigths in file
	real*			bias;
	integer*		signs;
	config_t 		config;
} eegdataset_t;

extern char * programname; // Fix for NVCC bug 01/11/2016

#ifdef __cplusplus
extern "C" {
#endif


void initDefaultConfig(eegdataset_t *set);

void checkDefaultConfig(eegdataset_t *set);

void printConfig(eegdataset_t *dataset);

void help(void);

char* getParam(char * needle, char* haystack[], int count);

error parseConfig(char* filename, eegdataset_t *dataset);

int isParam(char * needle, char* haystack[], int count);

void printConfig(eegdataset_t *dataset);

#ifdef __cplusplus
}
#endif



#endif //__CONFIG__
