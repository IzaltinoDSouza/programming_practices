#include <benchmark/benchmark.h>

#include "extract_file_extension.h"

static void brenchmark_extract_file_extension(benchmark::State & state)
{
	const char * filename  = "pixel_art_001.png";
	char extension[8];
	for(auto _ : state)
	{
		extract_file_extension(filename,extension);
	}
}

BENCHMARK(brenchmark_extract_file_extension);

BENCHMARK_MAIN();
