#include "Components/PointLightComponent.h"
#include "Components/CameraComponent.h"
#include "Renderer.h"
#include "Assets/StaticMesh.h"
#include "Engine.h"
#include "AssetManager.h"

#include <glm/gtc/matrix_transform.hpp>

#if EDITOR
#include "EditorState.h"
#endif

#undef min
#undef max

FORCE_LINK_DEF(PointLightComponent);
DEFINE_COMPONENT(PointLightComponent);

PointLightComponent::PointLightComponent() :
    mRadius(5)
{
    mName = "Point Light";
}

PointLightComponent::~PointLightComponent()
{
}

void PointLightComponent::Create()
{
    LightComponent::Create();
}

void PointLightComponent::Destroy()
{
    LightComponent::Destroy();
}

const char* PointLightComponent::GetTypeName() const
{
    return "PointLight";
}

void PointLightComponent::GatherProperties(std::vector<Property>& outProps)
{
    LightComponent::GatherProperties(outProps);

    outProps.push_back(Property(DatumType::Float, "Radius", this, &mRadius));
}

void PointLightComponent::GatherProxyDraws(std::vector<DebugDraw>& inoutDraws)
{
#if DEBUG_DRAW_ENABLED
    LightComponent::GatherProxyDraws(inoutDraws);

    if (GetType() == PointLightComponent::GetStaticType())
    {
        glm::vec4 color = glm::vec4(0.8f, 0.8f, 0.3f, 1.0f);

        if (mDomain == LightingDomain::Static)
        {
            color = glm::vec4(0.8f, 0.5f, 0.3f, 1.0f);
        }
        else if (mDomain == LightingDomain::Dynamic)
        {
            color = glm::vec4(0.8f, 0.8f, 0.6f, 1.0f);
        }

        {
            DebugDraw debugDraw;
            debugDraw.mMesh = LoadAsset<StaticMesh>("SM_Sphere");
            debugDraw.mActor = GetOwner();
            debugDraw.mComponent = this;
            debugDraw.mColor = color;
            debugDraw.mTransform = glm::scale(mTransform, { 0.2f, 0.2f, 0.2f });
            inoutDraws.push_back(debugDraw);
        }

#if EDITOR
        if (GetSelectedComponent() == this)
        {
            DebugDraw debugDraw;
            debugDraw.mMesh = LoadAsset<StaticMesh>("SM_Sphere");
            debugDraw.mActor = GetOwner();
            debugDraw.mComponent = this;
            debugDraw.mColor = color;
            debugDraw.mTransform = glm::scale(mTransform, { mRadius, mRadius, mRadius });
            inoutDraws.push_back(debugDraw);
        }
#endif // EDITOR
    }
#endif // DEBUG_DRAW_ENABLED
}

void PointLightComponent::SaveStream(Stream& stream)
{
    LightComponent::SaveStream(stream);
    stream.WriteFloat(mRadius);
}

void PointLightComponent::LoadStream(Stream& stream)
{
    LightComponent::LoadStream(stream);
    mRadius = stream.ReadFloat();
}

bool PointLightComponent::IsPointLightComponent() const
{
    return true;
}

bool PointLightComponent::IsDirectionalLightComponent() const
{
    return false;
}

void PointLightComponent::SetRadius(float radius)
{
    mRadius = radius;
}

float PointLightComponent::GetRadius() const
{
    return mRadius;
}
