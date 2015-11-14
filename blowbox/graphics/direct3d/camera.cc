#include "camera.h"

#include "../../window/window.h"

namespace blowbox
{
	namespace direct3d
	{
		//------------------------------------------------------------------------------------------------------
		Camera::Camera(const BB_CAMERA_PROJECTION_MODES& projection_mode) :
			position_({ 0.0f, 0.0f, 0.0f, 1.0f }),
			target_({0.0f, 0.0f, 1.0f, 1.0f }),
			up_({ 0.0f, 1.0f, 0.0f, 1.0f }),
			nearz_(0.0f),
			farz_(1000.0f),
			fov_(0.2f * 3.14f),
			projection_mode_(projection_mode)
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
		XMMATRIX Camera::GetViewMatrix() const
		{
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
		void Camera::TranslateBy(const XMVECTOR& translation)
		{
			position_ += translation;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::TranslateBy(const float& x, const float& y, const float& z)
		{
			position_ += { x, y, z, 1.0f };
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetTarget(const XMVECTOR& target)
		{
			target_ = target;
		}

		//------------------------------------------------------------------------------------------------------
		void Camera::SetTarget(const float& x, const float& y, const float& z)
		{
			target_ = { x, y, z, 1.0f };
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