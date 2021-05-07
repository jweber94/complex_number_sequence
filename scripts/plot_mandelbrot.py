#!/usr/bin/python3

import matplotlib.pyplot as plt
from matplotlib import transforms
import numpy as np
import csv
import argparse

parser = argparse.ArgumentParser(description="Pass path to the data storage location")
parser.add_argument("-p", "--path", type=str, help="Path to the result data of run_mandelbrot that should be plotted.")
parser.add_argument("-r", "--result", type=str, help="(Path and) Name of the resulting image.")


def main(): 
    print("Plotting the mandelbrot set started")

    # parse path and load the data to numpy
    input_args = parser.parse_args()
    path_to_data = input_args.path
    result_img_name = str(input_args.result)

    # loaded and divide data
    my_data = np.genfromtxt(path_to_data, delimiter=' ')
    re_list = my_data[:, 0]
    im_list = my_data[:, 1]
    conv_radius_list = my_data[:, 2]

    # reshape the convergency radius list
    n_re = int(re_list[-1]) + 1
    n_im = int(im_list[-1]) + 1
    conv_radius_list = conv_radius_list.reshape((n_re, n_im))
    
    # plot and save
    fig, ax = plt.subplots()
    ax.imshow(conv_radius_list)
    ax.set_axis_off()
    ax.set_xlabel("Real Part")
    ax.set_ylabel("Imaginary Part")
    fig.savefig(result_img_name, bbox_inches='tight')

    print("Plotting finished. You can find the result in " + str(result_img_name))

if __name__ == "__main__":
    main()

