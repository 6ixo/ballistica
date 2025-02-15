// Released under the MIT License. See LICENSE for details.

#ifndef BALLISTICA_DYNAMICS_MATERIAL_MATERIAL_CONDITION_NODE_H_
#define BALLISTICA_DYNAMICS_MATERIAL_MATERIAL_CONDITION_NODE_H_

#include "ballistica/ballistica.h"
#include "ballistica/core/object.h"

namespace ballistica {

class MaterialConditionNode : public Object {
 public:
  enum class OpMode { LEAF_NODE = 0, AND_OPERATOR, OR_OPERATOR, XOR_OPERATOR };
  Object::Ref<MaterialConditionNode> left_child;
  Object::Ref<MaterialConditionNode> right_child;
  OpMode opmode{};
  MaterialCondition cond{};
  int val1{};
  Object::Ref<Material> val1_material;
  int val2{};

  // Return the number of values used by this node
  // assumes the node is a leaf node.
  auto GetValueCount() -> int {
    assert(opmode == OpMode::LEAF_NODE);
    switch (cond) {
      case MaterialCondition::kTrue:
      case MaterialCondition::kFalse:
      case MaterialCondition::kSrcDstSameMaterial:
      case MaterialCondition::kSrcDstDiffMaterial:
      case MaterialCondition::kSrcDstSameNode:
      case MaterialCondition::kSrcDstDiffNode:
      case MaterialCondition::kCollidingDstNode:
      case MaterialCondition::kNotCollidingDstNode:
      case MaterialCondition::kEvalColliding:
      case MaterialCondition::kEvalNotColliding:
        return 0;
      case MaterialCondition::kDstIsMaterial:
      case MaterialCondition::kDstNotMaterial:
      case MaterialCondition::kSrcYoungerThan:
      case MaterialCondition::kSrcOlderThan:
      case MaterialCondition::kDstYoungerThan:
      case MaterialCondition::kDstOlderThan:
        return 1;
      case MaterialCondition::kDstIsPart:
      case MaterialCondition::kDstNotPart:
        return 2;
      default:
        throw Exception();
    }
  }
  auto GetFlattenedSize() -> size_t;
  void Flatten(char** buffer, SceneStream* output_stream);
  void Restore(const char** buffer, ClientSession* cs);
};

}  // namespace ballistica

#endif  // BALLISTICA_DYNAMICS_MATERIAL_MATERIAL_CONDITION_NODE_H_
