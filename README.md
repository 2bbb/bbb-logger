# bbb/logger

## build example

```sh
$ ./build_example.sh
```

## short introduction

```cpp
#include <bbb/logger.hpp>

bbb::log("tag", bbb::log_level::info) << "Hello";
bbb::log.info("tag") << "Hello";

bbb::log.enable();
bbb::log.disable();

bbb::set_log_level(bbb::log_level::info);
bbb::set_log_level(bbb::log_level::warning);
bbb::set_log_level(bbb::log_level::no_logging);
bbb::set_log_level(bbb::log_level::verbose);

bbb::flog.open("log.txt");
bbb::flog.info("tag") << "Hello";

bbb::slog.info("tag") << "Hello";
bbb::slog.info("tag") << "World";
std::string log_text = bbb::slog.text();
bbb::slog.clear();
```

## License

MIT

## Author

* ISHII 2bit [bufferRenaiss co., ltd.]
* ishii[at]buffer-renaiss.com
