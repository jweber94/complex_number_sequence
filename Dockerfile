FROM ubuntu:18.04
ENV name="manedelbrot_example"

RUN apt-get update && \
    apt-get install -y vim \
    git cmake build-essential \
    python3-pip gnuplot tmux \
    clang-tidy eog

WORKDIR /mandelbrot_project

# install yaml-cpp
RUN git clone https://github.com/jbeder/yaml-cpp.git
WORKDIR /mandelbrot_project/yaml-cpp/build
RUN cmake -DYAML_BUILD_SHARED_LIBS=ON ..
RUN make -j12
RUN make install

#  copy the code from the repo into the container
WORKDIR /mandelbrot_project/my_code
COPY . /mandelbrot_project/my_code/
RUN rm -rf results && mkdir results
WORKDIR /mandelbrot_project/my_code/build
RUN rm -rf *
RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
RUN make -j12

# install the neccessary python packages
RUN pip3 install numpy && pip3 install matplotlib

# make the python plot script executable without calling python explicitly
WORKDIR /mandelbrot_project/my_code/scripts
RUN chmod u+x plot_mandelbrot.py

# go to the repo-folder in the container
WORKDIR /mandelbrot_project/my_code
