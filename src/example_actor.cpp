#include "example_actor.hpp"

namespace obcx::actors {

auto ExampleActor::handle(const events::ExampleRequested &request,
                          const core::MessageEnvelope &message,
                          core::ActorContext &context) -> core::ActorResult {
  context.throw_if_cancelled();
  const auto id_prefix =
      context.config().get_value<std::string>("id_prefix").value_or("example");
  auto result = core::ActorResult::success();
  result.emit(events::ExampleHandled{.text = request.text}, message,
              core::ActorEmitOptions{.id = id_prefix + ":" + message.id});
  return result;
}

} // namespace obcx::actors

OBCX_ACTOR_EXPORT_V2(obcx::actors::ExampleActor)
