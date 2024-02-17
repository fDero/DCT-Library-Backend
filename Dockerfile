
# Use the official Ubuntu as a parent image
FROM ubuntu:latest

# Set the working directory in the container
WORKDIR /server

# Copy the current directory contents into the container at /app
COPY . /server

# Install any needed dependencies specified in requirements.txt
# For example, if you have a requirements.txt file for Python packages:
# RUN pip install --no-cache-dir -r requirements.txt

# Run commands within the container
# For example, if you're building a Python application:
# CMD ["python", "app.py"]

# Or if you want to run a bash shell:

ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=Europe/Rome

RUN apt-get update
RUN apt-get install -y gcc
RUN apt-get install -y git
RUN apt-get install -y locate
RUN apt-get install -y ranger
RUN apt-get install -y build-essential
RUN apt-get install -y cmake
RUN apt-get install -y make
RUN apt-get install -y postgresql-all
RUN apt-get install -y libpq-dev

EXPOSE 5432
EXPOSE 5433
EXPOSE 8080
EXPOSE 9000

CMD ["/bin/bash"]
