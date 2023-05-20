echo "build test : extract_file_extension"
g++ -O0 test_extract_file_extension.cpp -o test_extract_file_extension -lgtest -lfmt

echo "build benchmark : extract_file_extension"
g++ -O0 benchmark_extract_file_extension.cpp -o benchmark_extract_file_extension -lbenchmark
