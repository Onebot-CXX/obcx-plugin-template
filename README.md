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

3. Build (standalone):

   ```bash
   cmake -B build
   cmake --build build
   ```

## Project Structure

```
.
├── CMakeLists.txt      # Build configuration (find_package + obcx_add_plugin)
├── plugin.toml         # Plugin metadata & dependency declarations
└── src/
    ├── example_plugin.cpp
    └── example_plugin.hpp
```

## Dependency Management

### Declaring Dependencies

Edit `plugin.toml` to declare your plugin's external dependencies:

```toml
[build]
# Package names your plugin needs (beyond OBCX core deps)
vcpkg_deps = ["nlohmann-json", "sqlite3"]
```

In `CMakeLists.txt`, use standard CMake `find_package()`:

```cmake
obcx_add_plugin(my_plugin
    SOURCES src/my_plugin.cpp
    DEPS nlohmann_json::nlohmann_json unofficial::sqlite3::sqlite3
)
```

### How Dependencies Are Resolved

This plugin can be built in two ways:

- **Standalone build**: You are responsible for making dependencies available — via vcpkg, system package manager, Nix, or any other method. `find_package()` does the discovery.

- **Built via OBCX** (FetchContent / in-tree): OBCX reads your `plugin.toml`'s `vcpkg_deps` and merges them into the project's dependency set. Run the following in the OBCX root to regenerate `vcpkg.json`:

  ```bash
  python3 cmake/gen_vcpkg_manifest.py plugins.toml
  ```

The `vcpkg_deps` field is **not tied to vcpkg** — it simply lists package names. Non-vcpkg users can read it to know what to install.

## Requirements

- CMake >= 3.20
- C++20 compatible compiler
- OBCX SDK (installed or available via FetchContent)

## License

[MIT](LICENSE)
