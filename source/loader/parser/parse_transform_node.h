#ifndef PARSE_TRANSFORM_NODE_H
#define PARSE_TRANSFORM_NODE_H

PUNK_ENGINE_LOCAL bool ParseTransformNode(Core::Buffer& buffer, Scene::Node* transform);
PUNK_ENGINE_LOCAL bool ParseSceneTransformNode(Core::Buffer &buffer, Scene::TransformNode *node);

#endif // PARSE_TRANSFORM_NODE_H
