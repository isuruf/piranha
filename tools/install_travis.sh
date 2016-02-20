#!/usr/bin/env bash

# Exit on error
set -e
# Echo each command
set -x

if [[ "${BUILD_TYPE}" == "Debug" ]]; then
    if [[ "${PIRANHA_COMPILER}" == "gcc" ]]; then
        cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="-fsanitize=address -Os" -DCMAKE_CXX_FLAGS_DEBUG=-g0 -DBUILD_TUTORIAL=yes -DPIRANHA_TEST_SPLIT=yes -DPIRANHA_TEST_SPLIT_NUM=${SPLIT_TEST_NUM} ../;
        make;
        ctest -E "thread|memory" -V;
    elif [[ "${PIRANHA_COMPILER}" == "clang" ]]; then
        cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TUTORIAL=yes -DPIRANHA_TEST_SPLIT=yes -DPIRANHA_TEST_SPLIT_NUM=${SPLIT_TEST_NUM} ../;
        make;
        ctest -E "thread" -V;
    fi
elif [[ "${BUILD_TYPE}" == "Release" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Release ../;
    make;
    ctest -E "gastineau|perminov" -V;
elif [[ "${BUILD_TYPE}" == "Python2" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_PYRANHA=yes -DBUILD_TESTS=no -DCMAKE_CXX_FLAGS_DEBUG=-g0 -DCMAKE_CXX_FLAGS=-Os -DCMAKE_INSTALL_PREFIX=/home/travis/.local ../;
    make install;
    pip install --user mpmath;
    python -c "import pyranha.test; pyranha.test.run_test_suite()";
elif [[ "${BUILD_TYPE}" == "Python3" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_PYRANHA=yes -DBUILD_TESTS=no -DCMAKE_CXX_FLAGS_DEBUG=-g0 -DCMAKE_CXX_FLAGS=-Os -DCMAKE_INSTALL_PREFIX=/home/travis/.local -DBoost_PYTHON_LIBRARY_RELEASE=/usr/lib/x86_64-linux-gnu/libboost_python-py32.so -DBoost_PYTHON_LIBRARY_DEBUG=/usr/lib/x86_64-linux-gnu/libboost_python-py32.so -DPYTHON_EXECUTABLE=/usr/bin/python3 -DPYTHON_INCLUDE_DIR=/usr/include/python3.2 -DPYTHON_LIBRARY=/usr/lib/libpython3.2mu.so ../;
    make install;
    wget "http://mpmath.org/files/mpmath-0.19.tar.gz";
    tar xzf mpmath-0.19.tar.gz;
    cd mpmath-0.19;
    python3 setup.py install --user;
    cd ..;
    python3 -c "import pyranha.test; pyranha.test.run_test_suite()";
elif [[ "${BUILD_TYPE}" == "Tutorial" ]]; then
    cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TUTORIAL=yes -DBUILD_TESTS=no ../;
    make;
    ctest -V;
elif [[ "${BUILD_TYPE}" == "Doxygen" ]]; then
    # Configure.
    cmake ../;
    # Install recent version of Doxygen locally.
    wget "http://ftp.stack.nl/pub/users/dimitri/doxygen-1.8.10.src.tar.gz";
    tar xzf doxygen-1.8.10.src.tar.gz;
    cd doxygen-1.8.10;
    mkdir build;
    cd build;
    cmake -DCMAKE_INSTALL_PREFIX=/home/travis/.local ../;
    make -j2;
    make install;
    # Now run it.
    cd ../../../doc/doxygen;
    /home/travis/.local/bin/doxygen;
    echo "Doxygen ran successfully";
    # Move out the resulting documentation.
    mv html /home/travis/doxygen;
    # Checkout a new copy of the repo, for pushing to gh-pages.
    cd ../../../;
    git config --global push.default simple
    git config --global user.name "Travis CI"
    git config --global user.email "bluescarni@gmail.com"
    set +x
    git clone "https://${GH_TOKEN}@github.com/bluescarni/piranha.git" piranha_gh_pages 2>&1 |cat - | > /dev/null
    set -x
    cd piranha_gh_pages
    git checkout -b gh-pages --track origin/gh-pages;
    git rm -fr doxygen;
    mv /home/travis/doxygen .;
    git add doxygen;
    git commit -m "Update Doxygen documentation [skip ci]."
    git push 2>&1 |cat - | > /dev/null
fi
