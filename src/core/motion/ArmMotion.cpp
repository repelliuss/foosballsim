#include <motion/ArmMotion.hpp>

using namespace godot;

ArmMotion::ArmMotion() noexcept {}

void ArmMotion::_init() { transform = get_transform(); }
