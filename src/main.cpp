#include <cstdlib>
#include <print>
#include <sys/stat.h>

auto main(const int argc, const char* argv[]) -> int 
{
  for(int index = 0; index < argc - 1; ++index)
  {
    struct stat stat_struct {};
    std::println("File: {}", argv[index]);
    if (stat(argv[index], &stat_struct) == -1)
    {
      std::println(stderr, "Failed to stat file!");
      return EXIT_FAILURE;
    }
    std::println("Size: {}", stat_struct.st_size);
  }

  return EXIT_SUCCESS;
}
