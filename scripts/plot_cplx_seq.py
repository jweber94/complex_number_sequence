#!/usr/bin/python3

import matplotlib.pyplot as plt
import numpy as np
import argparse

parser = argparse.ArgumentParser(
    description="Pass path to the data storage location")
parser.add_argument(
    "-p",
    "--path",
    type=str,
    help="Path to the result data of run_mandelbrot that should be plotted.")
parser.add_argument(
    "-r",
    "--result",
    type=str,
    help="(Path and) Name of the resulting image.")


def load_data(path_to_data):
    my_data = np.genfromtxt(path_to_data, delimiter=' ')
    re_list = my_data[:, 0]
    im_list = my_data[:, 1]
    conv_radius_list = my_data[:, 2]
    return re_list, im_list, conv_radius_list


def reshape_conv_list_to_image(re_list, im_list, conv_rad_list):
    n_re = int(re_list[-1]) + 1
    n_im = int(im_list[-1]) + 1
    conv_radius_list = conv_rad_list.reshape((n_re, n_im))
    return conv_radius_list


def plt_and_save(conv_rad_map, output_name):
    fig, ax = plt.subplots()
    ax.imshow(conv_rad_map)
    ax.set_axis_off()
    ax.set_xlabel("Real Part")
    ax.set_ylabel("Imaginary Part")
    fig.savefig(output_name, bbox_inches='tight')


def main():
    print("Plotting the mandelbrot set started")

    # parse path and load the data to numpy
    input_args = parser.parse_args()
    data_path = input_args.path
    result_img_name = str(input_args.result)

    # loaded and divide data
    re, im, conv_rad = load_data(data_path)

    # reshape the convergency radius list
    conv_radius_map = reshape_conv_list_to_image(re, im, conv_rad)

    # plot and save
    plt_and_save(conv_radius_map, result_img_name)

    print("Plotting finished. You can find the result in " + str(
        result_img_name))

if __name__ == "__main__":
    main()
