FROM debian:buster

# get the latest and graetest
RUN apt-get update -q && apt-get -y upgrade

# install basic packages
RUN apt-get update -q && apt-get -y --no-install-recommends install \
            gzip \
            git \
            wget \
            apt-utils

# apt-utils => debconf: delaying package configuration, since apt-utils is not installed



# install packages to build
RUN apt-get update -q && apt-get -y --no-install-recommends install \
            libboost1.67 \
            gfortran \
            gcc \
            g++ \
            autoconf \
            make \
            libtool \
            doxygen \
            graphviz \
            nodejs \
            cmake

# install packages (not sure if required)
RUN apt-get update -q && apt-get -y --no-install-recommends  install \
            bzip2

# cmake => Using cmake build for LAPACK
# bzip2 => unpack atlas3.x.y.tar.bz2
# make doc => Warning: Skipping MathJax check. 'node' program not found.
# TBD => Warning: Skipping MathJax check. nodejs module mathjax-node not found in NODE_PATH.

RUN groupadd --gid 1000 fmatvec
RUN useradd -m fmatvec --uid 1000 --gid 1000
RUN mkdir -p /home/fmatvec/lapack
RUN chown -R fmatvec:fmatvec /home/fmatvec
USER fmatvec:fmatvec
WORKDIR /home/fmatvec/lapack

#
#From https://github.com/Reference-LAPACK/lapack
#

RUN wget --no-check-certificate  -O - https://github.com/Reference-LAPACK/lapack/archive/v3.9.0.tar.gz | tar -xz

RUN cd /home/fmatvec/lapack/lapack-* && mkdir build && cd build && cmake -DCMAKE_INSTALL_LIBDIR=$HOME/.local/lapack .. && cmake --build . -j --target install
