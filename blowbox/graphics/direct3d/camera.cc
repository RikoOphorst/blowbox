#include "camera.h"

#include "../../window/window.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Camera::Camera(const BB_CAMERA_PROJECTION_MODES& projection_mode) :
			position_({ 0.0f, 0.0f, 0.0f, 1.0f }),
			rotation_({ 0.0f, 0.0f, 0.0f, 1.0f }),
			target_({0.0f, 0.0f, 1.0f, 1.0f }),
			up_({ 0.0f, 1.0f, 0.0f, 0.0f }),
			nearz_(0.0f),
			farz_(1000.0f),
			fov_(0.2f * 3.14f),
			projection_mode_(projection_mode),
			translate_right_(0.0f),
			translate_forward_(0.0f),
			translate_up_(0.0f)
		{

		}

		//------------------------------------------------------------------------------------------------------
		Camera::~Camera()
		{

		}

		//------------------------------------------------------------------------------------------------------
		Camera* Camera::Create(const BB_CAMERA_PROJECTION_MODES& projection_mode)
		{
			return new Camera(projection_mode);
		}
		
		//------------------------------------------------------------------------------------------------------
		const XMVECTOR& Camera::GetPosition() const
		{
			return position_;
		}

		//------------------------------------------------------------------------------------------------------
		const XMVECTOR& Camera::GetTarget() const
		{
			return target_;
		}

		//------------------------------------------------------------------------------------------------------
		const XMVECTOR& Camera::GetUp() const
		{
			return up_;
		}

		//------------------------------------------------------------------------------------------------------
		const float& Camera::GetNearZ() const
		{
			return nearz_;
		}

		//------------------------------------------------------------------------------------------------------
		const float& Camera::GetFarZ() const
		{
			return farz_;
		}

		//------------------------------------------------------------------------------------------------------
		const float& Camera::GetFOV() const
		{
			return fov_;
		}

		//------------------------------------------------------------------------------------------------------
		const BB_CAMERA_PROJECTION_MODES& Camera::GetProjectionMode() const
		{
			return projection_mode_;
		}

		//------------------------------------------------------------------------------------------------------
		XMMATRIX Camera::GetViewMatrix()
		{
			XMVECTOR cam_forward = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
			XMVECTOR cam_right = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
			
			XMMATRIX rotation = XMMatrixRotationRollPitchYawFromVector(rotation_);
			target_ = XMVector3TransformCoord(cam_forward, rotation);
			target_ = XMVector3Normalize(target_);

			right_ = XMVector3TransformCoord(cam_right, rotation);
			forward_ = XMVector3TransformCoord(cam_forward, rotation);
			up_ = XMVector3Cross(forward_, right_);

			position_ += translate_right_ * right_;
			position_ += translate_forward_ * forward_;
			position_ += translate_up_ * up_;

			translate_right_ = 0.0f;
			translate_forward_ = 0.0f;
			translate_up_ = 0.0f;

			target_ = position_ + target_;

			return XMMatrixLookAtLH(position_, target_, up_);
		}

		//------------------------------------------------------------------------------------------------------
		XMMATRIX Camera::GetProjectionMatrix(Window* window) const
		{
			switch (projection_mode_)
			{
			case BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_ORTHOGRAPHIC:
				return XMMatrixOrthographicLH(static_cast<float>(window->GetWidth()), static_cast<float>(window->GetHeight()), nearz_, farz_);
				break;

			case BB_CAMERA_PROJECTION_MODES::BB_CAMERA_PROJECTION_MODE_PERSPECTIVE:
				return XMMatrixPerspectiveFovLH(fov_, static_cast<float>(window->GetAspectRatio()), nearz_, farz_);
				break;
			default:
				return XMMatrixPerspectiveFovLH(fov_, static_cast<float>(window->GetAspectRatio()), nearz_, farz_);
				break;
			}
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetPosition(const XMVECTOR& position)
		{
			position_ = position_;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetPosition(const float& x, const float& y, const float& z)
		{
			position_ = XMVectorSet(x, y, z, 1.0f);
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::TranslateBy(const XMVECTOR& translation, const BB_CAMERA_TRANSFORMATION_SPACES& transform_space)
		{
			switch (transform_space)
			{
			default:
				position_ += translation;
				break;

			case BB_CAMERA_TRANSFORMATION_SPACE_LOCAL:
				translate_right_ += XMVectorGetX(translation);
				translate_up_ += XMVectorGetY(translation);
				translate_forward_ += XMVectorGetZ(translation);
				break;
			}
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::TranslateBy(const float& x, const float& y, const float& z, const BB_CAMERA_TRANSFORMATION_SPACES& transform_space)
		{
			switch (transform_space)
			{
			default:
				position_ += { x, y, z, 1.0f };
				break;

			case BB_CAMERA_TRANSFORMATION_SPACE_LOCAL:
				translate_right_ += x;
				translate_up_ += y;
				translate_forward_ += z;
				break;
			}
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetRotation(const XMVECTOR& rotation)
		{
			rotation_ = rotation;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetRotation(const float& x, const float& y, const float& z)
		{
			rotation_ = { x, y, z, 1.0f };
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::RotateBy(const XMVECTOR& rotation)
		{
			rotation_ += rotation;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::RotateBy(const float& x, const float& y, const float& z)
		{
			rotation_ += { x, y, z, 0.0f };
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetUp(const XMVECTOR& up)
		{
			up_ = up;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetUp(const float& x, const float& y, const float& z)
		{
			up_ = { x, y, z, 1.0f };
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetNearZ(const float& nearz)
		{
			nearz_ = nearz;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetFarZ(const float& farz)
		{
			farz_ = farz;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetFOV(const float& fov)
		{
			fov_ = fov;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetProjectionMode(const BB_CAMERA_PROJECTION_MODES& projection_mode)
		{
			projection_mode_ = projection_mode;
		}
	}
}