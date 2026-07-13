#pragma once

#include "core/actor.hpp"

namespace obcx::actors {

class ExampleActor final : public core::IActorV2 {
public:
  [[nodiscard]] auto get_name() const -> std::string override;
  [[nodiscard]] auto get_version() const -> std::string override;

  auto handle_message(const core::MessageEnvelope &message,
                      core::ActorContext &context)
      -> core::ActorTask<core::ActorResult> override;
};

} // namespace obcx::actors
