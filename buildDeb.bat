cd "%~dp0"

mkdir build

cd .\build

cmake .. -DCMAKE_BUILD_TYPE=Debug -DCONAN_PROFILE_HOST:STRING=debug

cmake --build . --config Debug

cmake --install . --config Debug --prefix ../bin