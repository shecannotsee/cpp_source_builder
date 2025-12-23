#!/bin/bash
project="cpp_source_builder"
project_length=${#project}
# Get pwd string
path=$(pwd)
# Get last project_length chars
suffix="${path: -$project_length}"
if [ "$suffix" = "$project" ]; then
    echo "ok"
else
    echo "Path error.Please ensure that the last few strings after using pwd are "$project
    exit 1  # stop
fi
# check dir libraries
echo "Check libraries exist?"
if [ -d "./libraries" ];
then
    echo "libraries."
else
    echo "Create libraries."
fi

# get source code
git clone https://github.com/chriskohlhoff/asio.git ./libraries/asio/ --branch asio-1-28-0 || \
  { echo "Failed to clone asio repository."; exit 1; }

cd libraries
mv asio asio-src
# build
mkdir asio-1.28.0
cd asio-1.28.0
install_path=$(pwd)
cd ..

cd asio-src
cd asio
./autogen.sh || \
  { echo "autogen failed."; exit 1; }
./configure --without-boost --prefix="$install_path" || \
  { echo "configure failed."; exit 1; }
make -j8 || \
  { echo "Build failed."; exit 1; }
make install || \
  { echo "Install failed."; exit 1; }

