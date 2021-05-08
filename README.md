# Project: Calculate the convergence radius of complex number sequences
This project is based on the homework of the KIT lecture "Wissenschaftliches Programmieren für Ingenieure" in the WS 18/19. The aim of the homework was to show of object oriented programming, especially the operator overloading principle. Therefore, an own implementation of a complex number datatype _MyComplex_ was implemented. (If I need to use a complex number in a real world project, of course I would use math library like cmath or eigen.)
After implementing a proper complex number class, the calculation of the a complex number set (called "mandelbrot set" (https://de.wikipedia.org/wiki/Mandelbrot-Menge)) is implemented in the main with the help of the classes and functions in ```complex_seq_utils.hpp```.
To make the calculation a little more interesting, we analyze three different complex number sets. These are the following:

+ ![\Large z_{i+1} = z_i^2 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^2%20+c) , with ![\Large c = const](https://latex.codecogs.com/svg.latex?c%3Dconst)

+ ![\Large z_{i+1} = z_i^2 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^2%20+c) , with ![\Large c = n_x*\delta_x + i*n_y*\delta_y](https://latex.codecogs.com/svg.latex?c%3Dn_x\delta_x%20+%20i%20n_y\delta_y)

+ ![\Large z_{i+1} = z_i^4 + c](https://latex.codecogs.com/svg.latex?z_{i+1}%3Dz_i^4%20+c) , with ![\Large c = n_x*\delta_x + i*n_y*\delta_y](https://latex.codecogs.com/svg.latex?c%3Dn_x\delta_x%20+%20i%20n_y\delta_y)

# Usage
To make the code run on all machines and OS, I created a _Dockerfile_ to create a Docker Image/Container to run the code within a Ubuntu 18.04 emulation.
In order to make it run, you have to build the docker (this might take a while):

    $ docker build -t "proj:complex_image" .

Then you can start the docker continer with a terminal:

    $ docker run -it --name cplx_seq_container -v /path/to/your/local/ipoque_wipro/results:/complex_number_sequence/my_code/results proj:complex_image /bin/bash

To go in the container with a second terminal

    $ docker exec -it cplx_seq_container /bin/bash

Now you are in the docker within the repository folder. You forwarded the folder ```/path/to/your/desired/results/dir``` from your local OS installation to the docker so that you write the result files to you local machine if the use the ```-v (--volume)``` flag.

Now you are able to run the code. In ```/complex_number_sequence/my_code/build``` you can find the _run_cplx_seq_ executable. If you execute it, you will get asked to provide a config file. You can find a reference for the structure and three examples of config-files in the folder ```/etc```. You can choose one of by giving them the relative path.(eg. ```../etc/complex_config_case_1A.yml```) After the execution, there will be result-files in the ```/build``` folder. These will read in to the python plot scripts.

To run the python plot-scripts, go to the folder ```/scripts```. With the execution of

    # ./plot_cplx_seq.py --file /path/to/result.dat --result /path/to/save/image.jpeg

a plot of the complex convergency will be saved in ```/path/to/save/image.jpeg```. 
Example: 

    # ./plot_cplx_seq.py --path ../build/ergebnis1A.dat --result ../results/erg1A.jpeg

To know more about the plot script, type

    # ./plot_cplx_seq.py --help

Example:

    # ./plot_cplx_seq.py --path ../build/ergebnis1A.dat --result ../results/ergebnis1A.jpeg

To access the result images from outside the docker container, you have to copy the _nameImage.jpeg_ data within the docker container to the directory _results_ (which is at the beginning an empty folder).  

# Requirements
The project is meant to be docker based. You can see the requirements to run it on you local machine in the Dockerfile. 

# Possible next steps for the project
These are possible next steps for the mini-project. There was not enough time to do this in Order to hand you a little code project in. I would like to do/rework the followning things:
+ Include Unit-Testing for the operators of MyComplex to make the code more trustworthy if you change basic functionallitiys
+ Create a gitlab CI/CD or Github-Actions Pipeline for Unit-Testing, Linting and create the documentation automatically
+ Think about parallelizing the calculation with threads or openMP
+ Extend the python plot script to scrape all *.dat files in a folder and save them as images