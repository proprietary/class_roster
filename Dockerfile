FROM ubuntu:eoan

COPY . /roster
RUN apt-get update && apt-get install -y cmake g++ make
WORKDIR /roster
RUN mkdir build && cd build && \
	cmake .. && \
	cmake --build .
CMD /roster/build/class_roster