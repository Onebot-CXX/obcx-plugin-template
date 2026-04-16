#pragma once

#include "interfaces/plugin.hpp"

namespace obcx::plugins {

class ExamplePlugin : public interface::IPlugin {
public:
    [[nodiscard]] auto get_name() const -> std::string override;
    [[nodiscard]] auto get_version() const -> std::string override;
    [[nodiscard]] auto get_description() const -> std::string override;

    auto initialize() -> bool override;
    void deinitialize() override;
    void shutdown() override;
};

} // namespace obcx::plugins
