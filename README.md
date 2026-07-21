# OBCX Actor Template

This repository is the canonical starting point for a native ABI 2 OBCX actor
package. It uses `ReflectedActor<Derived>`, typed `handle` overloads,
`ActorTask<ActorResult>`, canonical `actor.toml` metadata, the installed
`obcx-sdk`, and `OBCXActor.cmake`. It contains no runtime adapter or alternate
extension system.

## Create An Actor

1. Copy or instantiate this repository as an actor-named project.
2. Update every required field in `actor.toml`. Keep `actor.abi = 2`,
   `artifact.kind = "shared-library"`, and
   `artifact.entrypoint = "obcx_create_actor_v2"`. List only built and
   verified release targets in `artifact.platforms`.
3. Rename `ExampleActor`, its source files, and the `obcx_add_actor` target.
   `artifact.target` must equal `<name>_actor`; `artifact.name` must equal the
   helper's `OUTPUT_NAME`.
4. Define named message types with nlohmann ADL JSON conversions and implement
   public direct `handle` overloads returning `ActorResult` or
   `ActorTask<ActorResult>`. Use `ActorContext::await_asio` for network, timer,
   or other Asio suspension.

`OBCX_ACTOR_EXPORT_V2` supplies the numeric ABI generation, factory,
destructor, actor name, actor version, and generated schema-1 input contract.
The runtime validates this contract before actor construction.

## Build And Install

The supported baseline is Linux x86_64/arm64, CMake 3.30+, GCC 16.1+, C++26,
`-freflection`, and `__cpp_impl_reflection >= 202506L`.

Install OBCX or point CMake to an SDK prefix, then run:

```bash
cmake -S . -B build -DCMAKE_PREFIX_PATH=/path/to/obcx-sdk-prefix
cmake --build build
cmake --install build --prefix /path/to/actor-prefix
```

The shared actor is installed under `lib/obcx/actors/` and its canonical
metadata under `share/obcx/actors/<actor-id>/actor.toml`.

## Dependencies

`actor.toml` is the canonical identity, dependency, compatibility, and
publication document. Declare package-manager dependency names only in
`[dependencies].packages` and actor dependencies only in
`[dependencies].actors`. The consuming OBCX checkout merges package
dependencies from every package selected in its `actors.toml`; this standalone
template repository does not contain or invoke the OBCX manifest generator.

Use ordinary `find_package()` calls and pass linked CMake targets through the
`DEPS` argument of `obcx_add_actor`.

## Runtime Configuration

The actor name in runtime TOML must match the exported name. Message types are
fully qualified and must match the generated input contract exactly:

```toml
[actors.example]
library = "example"
enabled = true
partition = "conversation_id"

[actors.example.config]
id_prefix = "example"

[pipelines.example]
source = "obcx::actors::events::ExampleRequested"

[[pipelines.example.stages]]
name = "handle_example"
actor = "example"
input = "obcx::actors::events::ExampleRequested"
output = "obcx::actors::events::ExampleHandled"
mode = "await"
```

Actor-owned configuration must be read from the immutable generation view:

```cpp
auto id_prefix = context.config()
                     .get_value<std::string>("id_prefix")
                     .value_or("example");
```

Keep any derived settings on the actor instance. Do not call
`ConfigLoader::instance()`, use mutable namespace globals/function statics for
configuration, or read configuration in the factory constructor. Bot
connections and database instances are process-owned services and changing
them requires a restart.

## Layout

```text
.
├── actor.toml
├── CMakeLists.txt
└── src/
    ├── example_actor.cpp
    └── example_actor.hpp
```
