FROM ubuntu:18.04
ENV name="complex_sequence"

RUN apt-get update && \
    apt-get install -y vim \
    git cmake build-essential \
    python3-pip tmux \
    clang-tidy eog \
    libboost-all-dev

WORKDIR /complex_number_sequence

# install yaml-cpp
RUN git clone https://github.com/jbeder/yaml-cpp.git
WORKDIR /complex_number_sequence/yaml-cpp/build
RUN cmake -DYAML_BUILD_SHARED_LIBS=ON ..
RUN make -j12
RUN make install

#  copy the code from the repo into the container
WORKDIR /complex_number_sequence/my_code
COPY . /complex_number_sequence/my_code/
RUN rm -rf results && mkdir results
WORKDIR /complex_number_sequence/my_code/build
RUN rm -rf *
RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
RUN make -j12

# install the neccessary python packages
RUN pip3 install numpy && pip3 install matplotlib && pip3 install pep8

# make the python plot script executable without calling python explicitly
WORKDIR /complex_number_sequence/my_code/scripts
RUN chmod a+x plot_cplx_seq.py

# go to the repo-folder in the container
WORKDIR /complex_number_sequence/my_code
