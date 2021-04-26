driver_test.exe: driver_test.cpp
  g++ -c driver_test.cpp -o driver_test.exe -std=c++2a
clear:
  rm driver_test.exe
run:
  chmod 700 driver_test.exe
  ./driver_test.exe
