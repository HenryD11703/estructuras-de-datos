# Use gcc 11 which has better compatibility
FROM gcc:11

# Install make and other build essentials
RUN apt-get update && apt-get install -y \
    make \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory in the container
WORKDIR /app

# Copy all necessary files, including build.sh and other source files
COPY . /app

# Create necessary directories
RUN mkdir -p build bin

RUN make clean

RUN make

# Command to run the program
CMD ["./bin/program"]
