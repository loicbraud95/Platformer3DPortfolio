#include "PlayerBehaviour.h"
#include "Camera.h"
#include "Utils/Time.h"
#include "GameObject.h"
#include "App.h"
#include "RigidBody.h"

PlayerBehaviour::PlayerBehaviour(GameObject* _gameObject)
{
	gameObject = _gameObject;
	rb = gameObject->GetComponent<RigidBody>();
}

void PlayerBehaviour::Update()
{

	if ( !oldGrounded && rb->isGrounded && nbJump < 2)
	{
		nbJump = 2;
	}
	oldGrounded = rb->isGrounded;

	if (!rb->useRigidBody)
	{
		rb->velocity.x = 0; rb->velocity.z = 0;
		rb->useRigidBody = true;
	}

	if (gameObject->transform->GetGlobalPosition().y < -10.f)
	{
		gameObject->transform->SetGlobalPosition(respawnPoint);
		rb->useRigidBody = false;
	}

	if (jump)
	{
		jump = false;
		rb->velocity.y = sqrtf((50.f * 0.3f) * 3.f * GRAVITY);
	}

	float movementSpeed = 300.f * Time::DeltaTime();
	Vector3D dir = Vector3D::zero;
	if (InputHandler::IsKeyDown(GLFW_KEY_A))
	{
		//left
		dir += gameObject->transform->GetRight() * -1.f;
	}
	if (InputHandler::IsKeyDown(GLFW_KEY_D))
	{
		//rigth
		dir += gameObject->transform->GetRight();
	}
	if (InputHandler::IsKeyDown(GLFW_KEY_W))
	{
		//front
		dir += gameObject->transform->GetForward() * -1.f;
	}
	if (InputHandler::IsKeyDown(GLFW_KEY_S))
	{
		//back
		dir += gameObject->transform->GetForward();
	}

	if (dir != Vector3D::zero)
		rb->velocity += Normalize(dir) * movementSpeed;

	if (!rb->isGrounded)
	{
		float maxVelo = 30.f / 2.f;
		if (fabsf( rb->velocity.x) > maxVelo)
		{
			float ratio = fabsf(maxVelo/rb->velocity.x);

			rb->velocity.x *= ratio;
			rb->velocity.z *= ratio;
		}

		if (fabsf(rb->velocity.z) > maxVelo)
		{
			float ratio = fabsf(maxVelo / rb->velocity.z);

			rb->velocity.x *= ratio;
			rb->velocity.z *= ratio;
		}
	}

	Vector2D dirMouse = Application::oldMousePos - InputHandler::GetMousePos();
	if (InputHandler::IsMousePressed(GLFW_MOUSE_BUTTON_2))
	{
		gameObject->transform->SetLocalRotation(gameObject->transform->GetLocalRotation() + Vector3D::axeY * (dirMouse.x * 20 * Time::DeltaTime()));
	}
}

void PlayerBehaviour::LateUpdate()
{
}

void PlayerBehaviour::Delete()
{
	delete this;
}

void PlayerBehaviour::Jump(int key)
{
	if (InputHandler::IsKeyPressed(key))
	{
		if (nbJump == 1)
		{
			--nbJump;
			jump = true;
		}

		if (rb->isGrounded && nbJump == 2)
		{
			--nbJump;
			jump = true;
		}

	}
}

void PlayerBehaviour::Bind()
{
	InputHandler::BindKeyToFunc(GLFW_KEY_SPACE, std::bind(&PlayerBehaviour::Jump, this, std::placeholders::_1));
}
