#include "example_plugin.hpp"
#include "common/logger.hpp"

namespace obcx::plugins {

auto ExamplePlugin::get_name() const -> std::string {
    return "example";
}

auto ExamplePlugin::get_version() const -> std::string {
    return "0.1.0";
}

auto ExamplePlugin::get_description() const -> std::string {
    return "Example OBCX plugin template";
}

auto ExamplePlugin::initialize() -> bool {
    // Register event handlers here
    // auto [lock, bots] = get_bots();
    // for (auto& bot : bots) {
    //     bot->on_event<common::MessageEvent>(...);
    // }
    return true;
}

void ExamplePlugin::deinitialize() {
    // Called when plugin is being removed but before shutdown
}

void ExamplePlugin::shutdown() {
    // Clean up all resources:
    // - Clear cached bot pointers
    // - Stop async tasks
    // - Release handlers
    // - Clear database references
}

} // namespace obcx::plugins

OBCX_PLUGIN_EXPORT(obcx::plugins::ExamplePlugin)
