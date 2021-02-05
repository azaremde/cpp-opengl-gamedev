#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#define NUM_BONES_PER_VEREX 4

namespace animation
{
    struct BoneSpace
    {
        glm::mat4x4 offsetMatrix;
        glm::mat4x4 finalWorldMatrix;
    };

    struct SkeletalBone
    {
        std::string name;

        glm::mat4x4 transformation;

        SkeletalBone* parent;
        std::vector<SkeletalBone> children;

        glm::mat4x4 lastGlobalTransform;
    };

    struct AnimationAvatar
    {
        std::vector<float> vertices;
        std::vector<int> indices;
        std::vector<float> normals;
        std::vector<float> uvs;
        std::vector<int> jointIDs;
        std::vector<float> weights;
    };

    template <class T>
    struct KeyFrame
    {
        float time;

        T value;
    };

    template <class T>
    struct KeyFrames
    {
        KeyFrame<T>* currentKeyFrame;
        KeyFrame<T>* nextKeyFrame;
    };

    template <class T>
    static unsigned int getFrameIndex(const float& time, const std::vector<KeyFrame<T>*>& keys)
    {
        for (unsigned int i = 0; i < keys.size() - 1; i++)
        {
            if (time < keys[i + 1]->time)
            {
                return i;
            }
        }

        return 0;
    }

    template <class T>
    static KeyFrames<T> getKeyFrames(const float& animationTime, const std::vector<KeyFrame<T>*>& current)
    {
        const unsigned int& currentIndex = getFrameIndex<T>(animationTime, current);
        const unsigned int& nextIndex = currentIndex < current.size() - 1 ? currentIndex + 1 : 0;

        return KeyFrames<T>{ current[currentIndex], current[nextIndex] };
    }

    template <class T>
    static float getBlendFactor(const KeyFrames<T>& keyFramesPair, const float& time)
    {
        const float& deltaTime = keyFramesPair.nextKeyFrame->time - keyFramesPair.currentKeyFrame->time;
        const float& blend = (time - keyFramesPair.currentKeyFrame->time) / deltaTime;

        return blend;
    }

    struct BoneAnimation
    {
        std::string name;

        std::vector<KeyFrame<glm::vec3>*> positionKeys;
        std::vector<KeyFrame<glm::quat>*> rotationKeys;
        std::vector<KeyFrame<glm::vec3>*> scaleKeys;
    };

    struct Animation
    {
        std::string name;

        float duration;
        float ticksPerSecond;

        std::vector<BoneAnimation*> channels;
    };

    struct Transition
    {
        std::vector<glm::mat4x4>* lastTransforms;
        std::vector<glm::mat4x4>* nextTransforms;

        bool interpolation = false;
        int animationToSwitch = 0;
        float interpolationFactor = 0.0f;
        float transitionSpeed = 0.0f;

        Transition()
        {
            lastTransforms = new std::vector<glm::mat4x4>();
            nextTransforms = new std::vector<glm::mat4x4>();
        }
    };
}
