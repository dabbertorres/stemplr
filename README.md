## Minimal functionality string template header file for C++ 17

### Example
```c++
#include "stemplr.hpp"

auto t = stemplr::Template<> {"Hello, {{what}}! Yours, {{name}}."};
stemplr::Template<>::SubMap_t subs = { {"what", "world"}, {"name", "Codey McCodeface"} };

auto result = t.run(subs);

std::cout << result << '\n';
// "Hello, world! Yours, Codey McCodeface"
```

### Use
Include stemplr.hpp and stemplr.tpp in your project/include path.
