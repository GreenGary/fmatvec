FROM centos:7.7.1908
# centos7 does not know cmake3

# install basic packages
RUN yum install -y \
         wget


# install packages to build
RUN yum install -y \
         automake \
         make \
         gcc-gfortran \
         gcc \
         gcc-c++

WORKDIR /tmp

# cmake package ships version 2.8, cmake3 requires another repo -> build cmake from source code
# https://gist.github.com/1duo/38af1abd68a2c7fe5087532ab968574e

RUN wget --no-check-certificate -O - https://cmake.org/files/v3.13/cmake-3.13.5.tar.gz | tar -xz

RUN cd /tmp/cmake-* && \
               ./bootstrap --prefix=/usr/local && \
               gmake -j$(nproc) && \
               gmake install

RUN groupadd --gid 1000 fmatvec
RUN useradd -m fmatvec --uid 1000 --gid 1000
RUN mkdir -p /home/fmatvec/lapack/build
WORKDIR /home/fmatvec/lapack

#
#From https://github.com/Reference-LAPACK/lapack
#
RUN wget --no-check-certificate  -O - https://github.com/Reference-LAPACK/lapack/archive/v3.9.0.tar.gz | tar -xz

RUN cd /home/fmatvec/lapack/build && cmake ../lapack-* && cmake --build . -j --target install && cd .. && rm -rf build

# install lapack, so cmake will find it - but that required root, changing permissions afterwards
RUN chown -R fmatvec:fmatvec /home/fmatvec


USER fmatvec:fmatvec
WORKDIR /home/fmatvec
