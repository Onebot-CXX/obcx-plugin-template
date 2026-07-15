#pragma once

#include "core/reflected_actor.hpp"

namespace obcx::actors {

namespace events {

struct ExampleRequested {
  std::string text;
};

struct ExampleHandled {
  std::string text;
};

inline void from_json(const common::json &document,
                      ExampleRequested &message) {
  document.at("text").get_to(message.text);
}

inline void to_json(common::json &document, const ExampleRequested &message) {
  document = {{"text", message.text}};
}

inline void to_json(common::json &document, const ExampleHandled &message) {
  document = {{"text", message.text}};
}

} // namespace events

class ExampleActor final : public core::ReflectedActor<ExampleActor> {
public:
  static constexpr std::string_view actor_name = "example";
  static constexpr std::string_view actor_version = "0.1.0";

  auto handle(const events::ExampleRequested &request,
              const core::MessageEnvelope &message,
              core::ActorContext &context) -> core::ActorResult;
};

} // namespace obcx::actors
