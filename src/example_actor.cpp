#include "example_actor.hpp"

namespace obcx::actors {

auto ExampleActor::get_name() const -> std::string { return "example"; }

auto ExampleActor::get_version() const -> std::string { return "0.1.0"; }

auto ExampleActor::handle_message(const core::MessageEnvelope &message,
                                  core::ActorContext &context)
    -> core::ActorTask<core::ActorResult> {
  context.throw_if_cancelled();
  auto result = core::ActorResult::success();
  auto emitted = message;
  emitted.id = "example:" + message.id;
  emitted.type = "ExampleHandled";
  emitted.causation_id = message.id;
  result.emit(std::move(emitted));
  co_return result;
}

} // namespace obcx::actors

OBCX_ACTOR_EXPORT_V2(obcx::actors::ExampleActor)
