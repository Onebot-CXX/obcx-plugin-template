# OBCX Plugin Template

A template repository for creating [OBCX](https://github.com/Onebot-CXX/OBCX) plugins.

## Usage

Use this template to bootstrap a new OBCX plugin project:

1. Click **"Use this template"** on GitHub, or clone manually:
   ```bash
   git clone https://github.com/Onebot-CXX/obcx-plugin-template.git my-plugin
   cd my-plugin
   ```

2. Rename and edit files to match your plugin:
   - Update `plugin.toml` with your plugin metadata
   - Rename/replace `src/example_plugin.cpp` and `src/example_plugin.hpp`
   - Update `CMakeLists.txt` (plugin name, sources, dependencies)

3. Build:
   ```bash
   cmake -B build
   cmake --build build
   ```

## Project Structure

```
.
├── CMakeLists.txt      # Build configuration
├── plugin.toml         # Plugin metadata & dependencies
└── src/
    ├── example_plugin.cpp
    └── example_plugin.hpp
```

## Requirements

- CMake >= 3.20
- C++20 compatible compiler
- OBCX SDK (installed or available via FetchContent)

## License

[MIT](LICENSE)
