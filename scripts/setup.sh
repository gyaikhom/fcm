apt update
apt install git curl wget zip g++ cmake lcov -y
wget https://github.com/google/googletest/archive/release-1.8.1.zip
unzip release-1.8.1.zip
rm release-1.8.1.zip
cd googletest-release-1.8.1; cmake -G "Unix Makefiles"; make; make install; cd ..; rm -Rf googletest-release-1.8.1
wget http://bitbucket.org/eigen/eigen/get/3.3.5.zip
unzip 3.3.5.zip
rm 3.3.5.zip
cmake eigen-eigen-*; make install;rm -Rf *
