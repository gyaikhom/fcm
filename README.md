Fuzzy c-Means Algorithm
===

A clustering algorithm organises items into groups based on a similarity criteria. The Fuzzy c-Means algorithm is a clustering algorithm where each item may belong to more than one group (hence the word fuzzy), where the degree of membership for each item is given by a probability distribution over the clusters.

In this project, we Implement the Fuzzy c-Means Algorithm. For further details, please view the CWEB generated documentation`fcm.pdf`.


There are two separate programs in this project. They are:

## Program `fcm.c`

This is an implementation of the Fuzzy C-Means Algorithm. It expects an input data file in the following
format.

    <number of data-points>
    <number of clusters>
    <number of dimensions>
    <fuzzyness coefficient>
    <termination criterion>
    <data points> ...

For example, the following is a valid input file:

    10 3 2
    2.0 0.00005
    897 802 765 992 1 521 220 380 729 969
    184 887 104 641 909 378 724 582 387 583 

This has 10 data-points, each with 2 dimensions. The FCM
program will try to cluster these 10 points into 3 clusters.
The fuzzyness coefficient is 2.0 and the termination
criterion (accuracy of the clustering) is 0.00005. For each
of the 10 points, there are two values for each of the
two dimensions. Hence, there are 20 data points listed.

## Program `gen.c`

Since it is tedious to generate the data points by hand,
the gen program generates the data points automatically.
In order to use this program, provide a filename which will
be used for storing the input data for running fcm later.

## Usage

An example run of the above two programs will be (in sequence)

    $ cd fcm
    $ make
    $ ./gen input.dat
    $ ./fcm input.dat

If the number of dimensions is 2 (points on a plane), and if you
have access to gnuplot, then the graph plotting the clusters,
with different colours for each of the clusters, can be generated
by processing the file `gnuplot.script` with gnuplot. An example
run will be

    $ gnuplot gnuplot.script

This will generate an image file named `cluster_plot.png`.
