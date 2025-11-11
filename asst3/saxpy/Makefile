EXECUTABLE := cudaSaxpy

CU_FILES   := saxpy.cu
CC_FILES   := main.cpp

ARCH := $(shell uname -m)

HOSTCXX   := /usr/bin/g++-10      # 确保已安装：sudo apt install g++-10
CXX       := g++-10 
NVCC      := nvcc

OBJDIR    := objs

CXXFLAGS  := -O3 -Wall -std=c++14 -m64
NVCCFLAGS := -O3 -m64 -std=c++14 -ccbin g++-10 -Xcompiler -std=c++14

ifeq ($(ARCH),aarch64)
  # ARM 不加 -m64
else
  CXXFLAGS  += -m64
  NVCCFLAGS += -m64
endif

LDFLAGS :=
ifeq ($(ARCH),Darwin)
  LDFLAGS += -L/usr/local/depot/cuda-8.0/lib/ -lcudart
else
  LDFLAGS += -L/usr/local/cuda/lib64/ -lcudart
endif

OBJS := $(OBJDIR)/main.o $(OBJDIR)/saxpy.o

.PHONY: dirs clean default
default: $(EXECUTABLE)

dirs:
	@mkdir -p $(OBJDIR)

clean:
	@rm -rf $(OBJDIR) *.ppm *~ $(EXECUTABLE)

$(EXECUTABLE): dirs $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/%.o: %.cu
	$(NVCC) $(NVCCFLAGS) -c $< -o $@
