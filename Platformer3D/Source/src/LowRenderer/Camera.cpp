#include "Camera.h"
#include "App.h"
#include "Log.h"

#include "Utils/InputHandler.h"
#include "Utils/Time.h"

#include "GameObject.h"


Camera::Camera(GameObject* _gameObject)
{
    gameObject = _gameObject;

    projectionMatrix = GetProjectionMatrix();


    isOrtho = false;

    if (Application::Get().currentCam == nullptr)
        Application::Get().currentCam = this;
}

void Camera::Update()
{
    recalculateView = true;
    if (recalculateView)
        GetViewMatrix();

    if (recalculateProjection)
        GetProjectionMatrix();

    if (recalculateVP)
        GetVPMatrix();
}

void Camera::LateUpdate()
{
}

void Camera::Delete()
{
    delete this;
}

Matrix4x4 Camera::GetViewMatrix()
{
    if (recalculateView)
    {
        Vector3D localRota = gameObject->transform->GetLocalScale();
        gameObject->transform->SetLocalScale(Vector3D(localRota.x, localRota.y,-localRota.z));
        viewMatrix = Reverse(gameObject->transform->GetGlobalTransform());
        gameObject->transform->SetLocalScale(localRota);

        recalculateView = false;
        recalculateVP = true;
    }
    return viewMatrix;
}

Matrix4x4 Camera::GetProjectionMatrix()
{
    if (recalculateProjection)
    {
        if (isOrtho)
        {
            glClearColor(0.07f, 0.57f, 0.99f, 1.f); // Set background color to blue
            projectionMatrix = OrthoMatrix(-8.f, 8.f, 4.5f, -4.5f, 0.1f, 100.f);
        }
        else
        {
            projectionMatrix = PerspectiveMatrix(_fov, (float)Application::Get().m_width / (float)Application::Get().m_height
                , _near, _far);
        }
        recalculateProjection = false;
        recalculateVP = true;
    }
    return projectionMatrix;
}

Matrix4x4 Camera::GetVPMatrix()
{
    if (recalculateVP)
    {
        vpMatrix = projectionMatrix * viewMatrix;
        recalculateVP = false;
    }
    return vpMatrix;
}

void Camera::SetFov(float newFov)
{
    _fov = newFov;
    recalculateProjection = true;
}

void Camera::SetNearFar(float newNear, float newFar)
{
    _near = newNear;
    _far = newFar;
    recalculateProjection = true;
}

void Camera::SwitchView()
{
    recalculateProjection = true;
    isOrtho = !isOrtho;
}
