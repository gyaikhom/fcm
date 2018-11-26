Fuzzy c-Means Algorithm
===
[![Build Status](https://semaphoreci.com/api/v1/ahmad88me/fcm/branches/master/badge.svg)](https://semaphoreci.com/ahmad88me/fcm)
[![codecov](https://codecov.io/gh/ahmad88me/fcm/branch/master/graph/badge.svg)](https://codecov.io/gh/ahmad88me/fcm)

This project implements Fuzzy c-means from the original paper by James Bezdek. This project is derived from [gyaikhom's fcm](https://github.com/gyaikhom/fcm).
What is the addition of this compared to the base project.
* The use of Eign library for matrices instead of fix n-dimentional arrays.
* The use of dynamic sizes for matrices.
* Make the FCM as a class, with all the related variables inside, so no need for Global variables and it also allow having multiple instances of FCM.
* Add automated testings

What is taken out
* The drawing function
* The generation of automatic matrices

 


