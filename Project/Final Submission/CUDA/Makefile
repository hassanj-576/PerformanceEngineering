
debug		:= 0
include		Makefile.inc

all: cuda

cuda: mainCuda mainCuda.cpp
	$(LINKER) -o cuda mainCuda.cpp mainCuda.o ./src/Timer.cpp $(INCLUDES) $(CUDA_LIBS) $(CFLAGS) $(CUDA_LDFLAGS) 

mainCuda: mainCuda.cu
	$(NVCC) -c mainCuda.cu $(NVCCFLAGS) $(INCLUDES)



