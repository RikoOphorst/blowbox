//#pragma once
//
//#include "../graphics/direct3d.h"
//
//using namespace DirectX;
//
//namespace blowbox
//{	
//	/**
//	* @class blowbox::GameObject
//	* @author Riko Ophorst
//	* @brief A Game Object
//	*/
//	class GameObject
//	{
//	public:
//		GameObject();
//		~GameObject();
//		
//		static GameObject* Create();
//
//		void SetPosition(const XMVECTOR& position);
//		void SetPosition(float& x, float& y, float& z);
//		void TranslateBy(const XMVECTOR& translation);
//		void TranslateBy(float& x, float& y, float& z);
//
//		void SetRotation(const XMVECTOR& rotation);
//		void SetRotation(float& x, float& y, float& z);
//		void RotateBy(const XMVECTOR& rotation);
//		void RotateBy(float& x, float& y, float& z);
//
//		void SetScale(const XMVECTOR& scale);
//		void SetScale(float& x, float& y, float& z);
//		void ScaleBy(const XMVECTOR& scale);
//		void ScaleBy(float& x, float& y, float& z);
//
//		void SetAnchor(const XMVECTOR& anchor);
//		void SetAnchor(float& x, float& y, float& z);
//
//		void SetAlpha(const float& a);
//
//		const XMVECTOR& GetPosition() const;
//		const XMVECTOR& GetRotation() const;
//		const XMVECTOR& GetScale() const;
//		const XMVECTOR& GetAnchor() const;
//		const float& GetAlpha() const;
//
//		XMMATRIX GetWorld() const;
//	private:
//		XMVECTOR position_;
//		XMVECTOR rotation_;
//		XMVECTOR scale_;
//		XMVECTOR anchor_;
//		
//		float alpha_;
//	};
//}