# OBCX Actor Template

This repository is the canonical starting point for a native V2 OBCX actor
package. It uses `ReflectedActor<Derived>`, typed `handle` overloads,
`ActorTask<ActorResult>`, `actor.toml`, the
installed `obcx-sdk`, and `OBCXActor.cmake`; it contains no runtime adapter or
alternate extension entry point.

## Create An Actor

1. Copy or instantiate this repository as an actor-named project.
2. Update every required field in `actor.toml`. Keep `actor.abi = 2`,
   `artifact.kind = "shared-library"`, and
   `artifact.entrypoint = "obcx_create_actor_v2"`.
   List only built and verified release targets in `artifact.platforms`.
3. Rename `ExampleActor`, its source files, and the `obcx_add_actor` target.
   `artifact.target` must equal `<name>_actor`; `artifact.name` must equal the
   helper's `OUTPUT_NAME`.
4. Define named message types with nlohmann ADL JSON conversions and implement
   public direct `handle` overloads returning `ActorResult` or
   `ActorTask<ActorResult>`. Use `ActorContext::await_asio` for network, timer,
   or other Asio suspension.

## Build And Install

Install OBCX or point CMake to an SDK prefix, then run:

The build requires Linux x86_64/arm64, CMake 3.25, GCC 16.1+, C++26, and
`-freflection`; `OBCXActor.cmake` enforces these target settings.

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/obcx-sdk-prefix
cmake --build build
cmake --install build --prefix /path/to/actor-prefix
```

The shared actor is installed under `lib/obcx/actors/` and its canonical
metadata under `share/obcx/actors/<actor-id>/actor.toml`.

## Dependencies

Declare package-manager dependency names only in
`[dependencies].packages` and actor dependencies only in
`[dependencies].actors`. The OBCX vcpkg generator reads these canonical fields:

```bash
python3 cmake/gen_vcpkg_manifest.py actors.toml
```

Use ordinary `find_package()` calls and pass linked CMake targets through the
`DEPS` argument of `obcx_add_actor`.

## Layout

```text
.
├── actor.toml
├── CMakeLists.txt
└── src/
    ├── example_actor.cpp
    └── example_actor.hpp
```
