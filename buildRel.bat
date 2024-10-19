cd "%~dp0"

mkdir build

cd .\build

cmake .. -DCMAKE_BUILD_TYPE=Release -DCONAN_PROFILE_HOST:STRING=release

cmake --build . --config Release

cmake --install . --config Release --prefix ../bin