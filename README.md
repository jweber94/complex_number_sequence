# Project: Calculate the convergence radius of complex number sequences
This project is based on the homework of the KIT lecture "Wissenschaftliches Programmieren für Ingenieure" in the WS 18/19. The aim of the homework was to show off object oriented programming, especially the operator overloading principle. Therefore, a self-created implementation of a complex number datatype _MyComplex_ was implemented. (If I need to use a complex number in a real world project, of course I would use a math library like std::complex.)
After implementing a proper complex number class, the calculation of the convergency radius for different complex number sets are implemented.

# Mathematical explanation:
Three different complex number sets can be calculated. The convergency radius gets evaluated within a given range of the real part und the imaginary part of the complex numbers with a given number of evaluation points (![\Large N_xmax](https://latex.codecogs.com/svg.latex?N_{xmax}) & ![\Large N_ymax](https://latex.codecogs.com/svg.latex?N_{ymax})) between two complex numbers (![\Large z_{lower}](https://latex.codecogs.com/svg.latex?z_{lower}) & ![\Large z_{upper}](https://latex.codecogs.com/svg.latex?z_{upper})). The complex number sequence is considered converged if ![\Large \left\|z_i\right\|%3CR_c](https://latex.codecogs.com/svg.latex?\left\|z_i\right\|%3CR_c), where ![\Large R_c](https://latex.codecogs.com/svg.latex?R_c) could be set as a threshold value.  
The following complex number sets are available for the calculation:

+ ![\Large z_{i+1} = z_i^2 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^2%20+c) , with ![\Large c = const](https://latex.codecogs.com/svg.latex?c%3Dconst) and ![\Large z_{0} = n_{x} \delta_{x} + i n_{y} \delta_{x}](https://latex.codecogs.com/svg.latex?z_{0}%20=%20n_{x}%20\delta_{x}%20+%20i%20n_{y}%20\delta_{x}). (I)

+ ![\Large z_{i+1} = z_i^2 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^2%20+c) , with ![\Large c = n_x*\delta_x + i*n_y*\delta_y](https://latex.codecogs.com/svg.latex?c%3Dn_x\delta_x%20+%20i%20n_y\delta_y) and ![\Large z_0 = 0 + i 0](https://latex.codecogs.com/svg.latex?z_{0}%3D0%20+%20i%200). (II)

+ ![\Large z_{i+1} = z_i^4 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^4%20+c) , with ![\Large c = n_x*\delta_x + i*n_y*\delta_y](https://latex.codecogs.com/svg.latex?c%3Dn_x\delta_x%20+%20i%20n_y\delta_y) and ![\Large z_0 = 0 + i 0](https://latex.codecogs.com/svg.latex?z_{0}%3D0%20+%20i%200). (III)

Thereby is ![\Large \delta_{x}=\frac{Re(z_{upper}) - Re(z_{lower})}{N_{xmax}}](https://latex.codecogs.com/svg.latex?\delta_{x}=\frac{Re(z_{upper})%20-%20Re(z_{lower})}{N_{xmax}}) and ![\Large \delta_{y}=\frac{Im(z_{upper}) - Im(z_{lower})}{N_{ymax}}](https://latex.codecogs.com/svg.latex?\delta_{y}=\frac{Im(z_{upper})%20-%20Im(z_{lower})}{N_{ymax}}).  

The described formulas are inspired by the recursive calculation of the mandelbrot set (https://de.wikipedia.org/wiki/Mandelbrot-Menge).

# Usage
The following instructions are described for Linux/MacOS. They can also be transferred to Windows with a few adjustments.

Open up a terminal and clone the code to your local machine  

    $ git clone https://github.com/jweber94/complex_number_sequence.git

Then, go into the cloned folder

    $ cd complex_number_sequence

To make the code run on all machines/OS, I created a _Dockerfile_ for building a Docker Image/Container to run the code within an Ubuntu 18.04 emulation.
In order to make it run, you have to build the docker (this might take a while, depending on your internet connection and hardware):

    $ docker build -t "proj:complex_image" .

Then you can start the docker container with a terminal:

    $ docker run -it --name cplx_seq_container -v /path/to/your/local/complex_number_sequence/results:/complex_number_sequence/my_code/results proj:complex_image /bin/bash

To go into the container with a second terminal, you can use:

    $ docker exec -it cplx_seq_container /bin/bash

Now you are in the docker within the repository folder. You forwarded the folder ```/path/to/your/desired/results/dir``` from your local OS installation to the docker in order to write the result files to your local machine if you use the ```-v (--volume)``` flag.

Now you are able to run the code. In ```/complex_number_sequence/my_code/build``` you can find the _run_cplx_seq_ executable. 
Go into the folder and start the executable with 

    # cd ./build
    # ./run_cplx_seq

If you execute it, you will get asked to provide a configuration file. You can find a reference for the structure and five examples of config-files in the folder ```/etc```. You can choose one of them by giving them the relative path. (eg. ```../etc/complex_config_case_1A.yml```) After the execution, there will be a result file (<NameFromConfig>.dat) in the ```/build``` folder. This file is readable for the python plot script.

To run the python plot-script, go to the folder ```/scripts```, with 

    # cd ../scripts

and start the execution of plot script with

    # ./plot_cplx_seq.py --path /path/to/result.dat --result /path/to/save/image.jpeg

Then, a plot of the convergency will be saved in ```/path/to/save/image.jpeg```.
Example usage:

    # ./plot_cplx_seq.py --path ../build/ergebnis1A.dat --result ../results/nameImage.jpeg

Example:

    # ./plot_cplx_seq.py --path ../build/ergebnis1A.dat --result ../results/ergebnis1A.jpeg

To know more about the plot script, you can type

    # ./plot_cplx_seq.py --help

To access the result images from outside the docker container, you have to copy the _nameImage.jpeg_ within the docker container to the directory ```/results``` or write the results from the plot-script directly to this folder, like in the given example.  

CAUTION: If you write files to ```results```, they will be owned by root. Please change the owner rights before exiting the container with

    # cd ../results
    # chown -R <UserID>:<GroupID> <filename>

If you don't do this, you won't be able to delete the created files on your host system without root or sudo access. Check your user-ID and group-ID ***on your local machine*** with

    # cat /etc/passwd | grep <YourUsername>

The colon separated number couples after the ```x:``` is what you are looking for.

You can exit the docker container with ```strg+d```. 

# Explanation of the configuration setup in ```/etc```:
+ ```case```: Calculation case (I, II or III from "Mathmatical explaination")
+ ```x_lower```: ![\Large Re(z_{lower})](https://latex.codecogs.com/svg.latex?Re(z_{lower}))
+ ```y_lower```: ![\Large Im(z_{lower})](https://latex.codecogs.com/svg.latex?Im(z_{lower}))
+ ```x_upper```: ![\Large Re(z_{upper})](https://latex.codecogs.com/svg.latex?Re(z_{upper}))
+ ```y_upper```: ![\Large Im(z_{upper})](https://latex.codecogs.com/svg.latex?Im(z_{upper}))
+ ```N_xmax```: ![\Large N_{N_max}](https://latex.codecogs.com/svg.latex?N_{xmax})
+ ```N_ymax```: ![\Large N_{ymax}](https://latex.codecogs.com/svg.latex?N_{ymax})
+ ```R_c```: Convergency Threshold
+ ```c_0_real```: Real part of the complex constant ![\Large c](https://latex.codecogs.com/svg.latex?c)
+ ```c_0_imag```: Imaginary part of the complex constant ![\Large c](https://latex.codecogs.com/svg.latex?c)
+ ```name_result```: Name of the calculation result file
+ ```max_iter```: Maximum of iterations per complex number sequence, if the convergency radius could not be reached

# Requirements
The project is meant to be docker based. You can see the requirements to run it on your local machine in the Dockerfile.

# Possible next steps for the project
The following next steps are possible for the mini-project.
+ Include Unit-Testing for the operators of MyComplex to make the code more trustworthy to changes
+ Create a gitlab CI/CD or Github-Actions Pipeline for Unit-Testing, Linting and create the documentation automatically
+ Think about parallelizing the calculation with pthreads or OpenMP, use preallocation and write out the results with one function call at the end 
+ Extend the python plot script to scrape all *.dat files in a folder and save them as images
+ Add an exception class to get better diagnosing functionalities