#pragma once

// sandbox api

#include "ugine/application.h"
#include "ugine/log.h"

#include "ugine/core/timestep.h"

// inputs
#include "ugine/input/input.h"
#include "ugine/input/key_codes.h"
#include "ugine/input/mouse_button_codes.h"
#include "ugine/camera/ortho_camera_controller.h"

#include "ugine/imgui/imgui_layer.h"

// renderer
#include "ugine/renderer/color.h"

#include "ugine/renderer/renderer.h"
#include "ugine/renderer/renderer_2d.h"
#include "ugine/renderer/render_command.h"

#include "ugine/renderer/buffer.h"
#include "ugine/renderer/shader.h"
#include "ugine/renderer/texture.h"
#include "ugine/renderer/vertex_array.h"

#include "ugine/renderer/orthographic_camera.h"

#include "ugine/layer.h"
#include "ugine/layer_stack.h"

// ecs
#include "ugine/ecs/ecs.h"
#include "ugine/ecs/entity_manager.h"
#include "ugine/ecs/entity.h"
#include "ugine/ecs/component.h"
#include "ugine/ecs/components/transform_component.h"
#include "ugine/ecs/components/renderer_component.h"
#include "ugine/ecs/components/script_component.h"

#include "tweeny/tweeny.h"

// coroutines
#include "ugine/coroutines/coroutines.h"
#include "ugine/coroutines/routine_manager.h"
#include "ugine/coroutines/routines/movement.h"

// object pooling
#include "ugine/pooling/object_pooling.h"