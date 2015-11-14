#pragma once

#include "../../graphics/direct3d/direct3d.h"

using namespace DirectX;

namespace blowbox
{
	class Window;

	namespace direct3d
	{
		enum BB_CAMERA_PROJECTION_MODES
		{
			BB_CAMERA_PROJECTION_MODE_ORTHOGRAPHIC,
			BB_CAMERA_PROJECTION_MODE_PERSPECTIVE
		};
		
		/**
		* @class blowbox::direct3d::Camera
		* @author Riko Ophorst
		* @brief Defines a camera
		*/
		class Camera
		{
		public:
			Camera(const BB_CAMERA_PROJECTION_MODES& projection_mode);
			~Camera();

			static Camera* Create(const BB_CAMERA_PROJECTION_MODES& projection_mode);

			const XMVECTOR& GetPosition() const;
			const XMVECTOR& GetTarget() const;
			const XMVECTOR& GetUp() const;
			const float& GetNearZ() const;
			const float& GetFarZ() const;
			const float& GetFOV() const;
			const BB_CAMERA_PROJECTION_MODES& GetProjectionMode() const;

			XMMATRIX GetViewMatrix() const;
			XMMATRIX GetProjectionMatrix(Window* window) const;

			void SetPosition(const XMVECTOR& position);
			void SetPosition(const float& x, const float& y, const float& z);
			void TranslateBy(const XMVECTOR& translation);
			void TranslateBy(const float& x, const float& y, const float& z);

			void SetTarget(const XMVECTOR& target);
			void SetTarget(const float& x, const float& y, const float& z);

			void SetUp(const XMVECTOR& up);
			void SetUp(const float& x, const float& y, const float& z);

			void SetNearZ(const float& nearz);
			void SetFarZ(const float& farz);

			void SetFOV(const float& fov);

			void SetProjectionMode(const BB_CAMERA_PROJECTION_MODES& projection_mode);

		private:
			XMVECTOR position_; //<! The position of the camera
			XMVECTOR target_; //<! The target of the camera (direction)
			XMVECTOR up_; //<! The up/top of the camera
			float nearz_; //<! The near z plane of the camera
			float farz_; //<! The far z plane of the camera
			float fov_; //<! The fov of the camera
			BB_CAMERA_PROJECTION_MODES projection_mode_;
		};
	}
}